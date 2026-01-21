/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "wm8904.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/** @defgroup AUDIO_Driver_structure  Audio Driver structure
 * @{
 */
typedef struct
{
	int32_t (*Init)(void *, void *);
	int32_t (*DeInit)(void *);
	int32_t (*ReadID)(void *, uint32_t *);
	int32_t (*Play)(void *);
	int32_t (*Pause)(void *);
	int32_t (*Resume)(void *);
	int32_t (*Stop)(void *, uint32_t);
	int32_t (*SetFrequency)(void *, uint32_t);
	int32_t (*GetFrequency)(void *);
	int32_t (*SetVolume)(void *, uint32_t, uint8_t);
	int32_t (*GetVolume)(void *, uint32_t, uint8_t *);
	int32_t (*SetMute)(void *, uint32_t);
	int32_t (*SetOutputMode)(void *, uint32_t);
	int32_t (*SetResolution)(void *, uint32_t);
	int32_t (*GetResolution)(void *, uint32_t *);
	int32_t (*SetProtocol)(void *, uint32_t);
	int32_t (*GetProtocol)(void *, uint32_t *);
	int32_t (*Reset)(void *);
} AUDIO_Drv_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

I2C_HandleTypeDef hi2c2;

SAI_HandleTypeDef hsai_BlockA1;
DMA_HandleTypeDef handle_GPDMA1_Channel0;

/* USER CODE BEGIN PV */
static AUDIO_Drv_t *Audio_Drv = NULL;
static void *Audio_CompObj;
extern uint32_t audio_samples_count;
extern const int16_t audio_samples_16k[];
static __IO uint32_t PcmBufferCplt;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void SystemIsolation_Config(void);
static void MX_GPIO_Init(void);
static void MX_GPDMA1_Init(void);
static void MX_I2C2_Init(void);
static void MX_SAI1_Init(void);
/* USER CODE BEGIN PFP */

/**
 * @brief  Write a value in a register of the device through BUS.
 * @param  DevAddr    Device address on Bus.
 * @param  MemAddSize Size of internal memory address
 * @param  Reg        The target register address to write
 * @param  pData      The target register value to be written
 * @param  Length     data length in bytes
 * @retval BSP status
 */
static int32_t I2C2_WriteReg(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length)
{
	if (HAL_I2C_Mem_Write(&hi2c2, DevAddr, Reg, MemAddSize, pData, Length, 1000) == HAL_OK)
	{
		return HAL_OK;
	}

	return HAL_ERROR;
}

/**
 * @brief  Read a register of the device through BUS
 * @param  DevAddr    Device address on BUS
 * @param  MemAddSize Size of internal memory address
 * @param  Reg        The target register address to read
 * @param  pData      The target register value to be read
 * @param  Length     data length in bytes
 * @retval BSP status
 */
static int32_t I2C2_ReadReg(uint16_t DevAddr, uint16_t Reg, uint16_t MemAddSize, uint8_t *pData, uint16_t Length)
{
	if (HAL_I2C_Mem_Read(&hi2c2, DevAddr, Reg, MemAddSize, pData, Length, 1000) == HAL_OK)
	{
		return HAL_OK;
	}

	return HAL_ERROR;
}


/**
 * @brief  Initializes I2C HAL.
 * @retval HAL status
 */
int32_t WM8904_I2C2_Init(void)
{
	int32_t ret = HAL_OK;
	if (HAL_I2C_GetState(&hi2c2) == HAL_I2C_STATE_RESET)
	{
		MX_I2C2_Init();
	}
	return ret;
}

/**
 * @brief  DeInitializes I2C HAL.
 * @retval HAL status
 */
int32_t WM8904_I2C2_DeInit(void)
{
	int32_t ret = HAL_OK;
	/* Init the I2C */
	if (HAL_I2C_DeInit(&hi2c2) != HAL_OK)
	{
		ret = HAL_ERROR;
	}
	return ret;
}

/**
 * @brief  Write a 8bit value in a register of the device through BUS.
 * @param  DevAddr Device address on Bus.
 * @param  Reg    The target register address to write
 * @param  pData  The target register value to be written
 * @param  Length buffer size to be written
 * @retval HAL status
 */
int32_t WM8904_I2C2_WriteReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
	int32_t ret;
#if defined(BSP_USE_CMSIS_OS)
	/* Get semaphore to prevent multiple I2C access */
	osSemaphoreWait(BspI2cSemaphore, osWaitForever);
#endif /* BSP_USE_CMSIS_OS */
	if (I2C2_WriteReg(DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length) == 0)
	{
		ret = HAL_OK;
	}
	else
	{
		ret = HAL_I2C_GetError(&hi2c2);
	}
#if defined(BSP_USE_CMSIS_OS)
	/* Release semaphore to prevent multiple I2C access */
	osSemaphoreRelease(BspI2cSemaphore);
#endif /* BSP_USE_CMSIS_OS */
	return ret;
}

/**
 * @brief  Read a 8bit register of the device through BUS
 * @param  DevAddr Device address on BUS
 * @param  Reg     The target register address to read
 * @param  pData   Pointer to data buffer
 * @param  Length  Length of the data
 * @retval HAL status
 */
int32_t WM8904_I2C2_ReadReg(uint16_t DevAddr, uint16_t Reg, uint8_t *pData, uint16_t Length)
{
	int32_t ret;
#if defined(BSP_USE_CMSIS_OS)
	/* Get semaphore to prevent multiple I2C access */
	osSemaphoreWait(BspI2cSemaphore, osWaitForever);
#endif /* BSP_USE_CMSIS_OS */
	if (I2C2_ReadReg(DevAddr, Reg, I2C_MEMADD_SIZE_8BIT, pData, Length) == 0)
	{
		ret = HAL_OK;
	}
	else
	{
		ret = HAL_I2C_GetError(&hi2c2);
	}
#if defined(BSP_USE_CMSIS_OS)
	/* Release semaphore to prevent multiple I2C access */
	osSemaphoreRelease(BspI2cSemaphore);
#endif /* BSP_USE_CMSIS_OS */
	return ret;
}

/**
  * @brief  Delay function
  * @retval Tick value
  */
int32_t WM8904_GetTick(void)
{
  return (int32_t)HAL_GetTick();
}
/**
 * @brief  Probe the WM8904 audio codec.
 * @param  None
 * @retval None
 */
static void WM8904_Probe(void)
{
	WM8904_IO_t              IOCtx;
	uint32_t                 wm8904_id;
	static WM8904_Object_t   WM8904Obj;

	/* Configure the audio driver */
	  IOCtx.Address     = 0x34U;
	  IOCtx.Init        = WM8904_I2C2_Init;
	  IOCtx.DeInit      = WM8904_I2C2_DeInit;
	  IOCtx.ReadReg     = WM8904_I2C2_ReadReg;
	  IOCtx.WriteReg    = WM8904_I2C2_WriteReg;
	  IOCtx.GetTick     = WM8904_GetTick;


	if (WM8904_RegisterBusIO(&WM8904Obj, &IOCtx) != WM8904_OK)
	{
		Error_Handler();
	}
	else if (WM8904_ReadID(&WM8904Obj, &wm8904_id) != WM8904_OK)
	{
		Error_Handler();
	}
	else if ((wm8904_id & WM8904_ID_MASK) != WM8904_ID)
	{
		Error_Handler();
	}
	else
	{
		Audio_Drv = (AUDIO_Drv_t *) &WM8904_Driver;
		Audio_CompObj = &WM8904Obj;
	}
}

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */
	WM8904_Init_t codec_init;
	uint32_t PlaybackStarted = 0;
	uint8_t i = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_GPDMA1_Init();
  MX_I2C2_Init();
  MX_SAI1_Init();
  SystemIsolation_Config();
  /* USER CODE BEGIN 2 */
	WM8904_Probe();
	/* Initialize audio codec */

	codec_init.InputDevice  = WM8904_IN_NONE;
	codec_init.OutputDevice = WM8904_OUT_HEADPHONE;
	codec_init.Resolution   = WM8904_RESOLUTION_16B;
	codec_init.Frequency    = WM8904_FREQUENCY_16K;
	codec_init.Volume       = 80U;
	if (Audio_Drv->Init(Audio_CompObj, &codec_init) < 0)
	{
		Error_Handler();
	}
	if (Audio_Drv->Play(Audio_CompObj) != 0)
	{
		Error_Handler();
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if(PlaybackStarted == 0)
		{
			if (HAL_OK != HAL_SAI_Transmit_DMA(&hsai_BlockA1, (uint8_t *) &audio_samples_16k[0+(i*audio_samples_count/16)], audio_samples_count/16))
			{
				Error_Handler();
			}
			PlaybackStarted = 1;
		}
		if(PcmBufferCplt == 1)
		{
			PcmBufferCplt = 0;
			PlaybackStarted = 0;
			i++;
			if(i >= 15)
				i = 0;
		}
	}
  /* USER CODE END 3 */
}
/* USER CODE BEGIN CLK 1 */
/* USER CODE END CLK 1 */

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the System Power Supply
  */
  if (HAL_PWREx_ConfigSupply(PWR_EXTERNAL_SOURCE_SUPPLY) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }

  /* Enable HSI */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL1.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Get current CPU/System buses clocks configuration and if necessary switch
 to intermediate HSI clock to ensure target clock can be set
  */
  HAL_RCC_GetClockConfig(&RCC_ClkInitStruct);
  if ((RCC_ClkInitStruct.CPUCLKSource == RCC_CPUCLKSOURCE_IC1) ||
     (RCC_ClkInitStruct.SYSCLKSource == RCC_SYSCLKSOURCE_IC2_IC6_IC11))
  {
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_CPUCLK | RCC_CLOCKTYPE_SYSCLK);
    RCC_ClkInitStruct.CPUCLKSource = RCC_CPUCLKSOURCE_HSI;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler();
    }
  }

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
  RCC_OscInitStruct.PLL1.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL1.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL1.PLLM = 4;
  RCC_OscInitStruct.PLL1.PLLN = 75;
  RCC_OscInitStruct.PLL1.PLLFractional = 0;
  RCC_OscInitStruct.PLL1.PLLP1 = 1;
  RCC_OscInitStruct.PLL1.PLLP2 = 1;
  RCC_OscInitStruct.PLL2.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL2.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL2.PLLM = 8;
  RCC_OscInitStruct.PLL2.PLLN = 172;
  RCC_OscInitStruct.PLL2.PLLFractional = 0;
  RCC_OscInitStruct.PLL2.PLLP1 = 7;
  RCC_OscInitStruct.PLL2.PLLP2 = 4;
  RCC_OscInitStruct.PLL3.PLLState = RCC_PLL_NONE;
  RCC_OscInitStruct.PLL4.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_CPUCLK|RCC_CLOCKTYPE_HCLK
                              |RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2|RCC_CLOCKTYPE_PCLK5
                              |RCC_CLOCKTYPE_PCLK4;
  RCC_ClkInitStruct.CPUCLKSource = RCC_CPUCLKSOURCE_IC1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_IC2_IC6_IC11;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;
  RCC_ClkInitStruct.APB5CLKDivider = RCC_APB5_DIV1;
  RCC_ClkInitStruct.IC1Selection.ClockSelection = RCC_ICCLKSOURCE_PLL1;
  RCC_ClkInitStruct.IC1Selection.ClockDivider = 2;
  RCC_ClkInitStruct.IC2Selection.ClockSelection = RCC_ICCLKSOURCE_PLL1;
  RCC_ClkInitStruct.IC2Selection.ClockDivider = 3;
  RCC_ClkInitStruct.IC6Selection.ClockSelection = RCC_ICCLKSOURCE_PLL1;
  RCC_ClkInitStruct.IC6Selection.ClockDivider = 4;
  RCC_ClkInitStruct.IC11Selection.ClockSelection = RCC_ICCLKSOURCE_PLL1;
  RCC_ClkInitStruct.IC11Selection.ClockDivider = 3;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPDMA1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPDMA1_Init(void)
{

  /* USER CODE BEGIN GPDMA1_Init 0 */

  /* USER CODE END GPDMA1_Init 0 */

  /* Peripheral clock enable */
  __HAL_RCC_GPDMA1_CLK_ENABLE();

  /* GPDMA1 interrupt Init */
    HAL_NVIC_SetPriority(GPDMA1_Channel0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(GPDMA1_Channel0_IRQn);

  /* USER CODE BEGIN GPDMA1_Init 1 */

  /* USER CODE END GPDMA1_Init 1 */
  /* USER CODE BEGIN GPDMA1_Init 2 */

  /* USER CODE END GPDMA1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.Timing = 0x30C0EDFF;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief SAI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SAI1_Init(void)
{

  /* USER CODE BEGIN SAI1_Init 0 */

  /* USER CODE END SAI1_Init 0 */

  /* USER CODE BEGIN SAI1_Init 1 */

  /* USER CODE END SAI1_Init 1 */
  hsai_BlockA1.Instance = SAI1_Block_A;
  hsai_BlockA1.Init.Protocol = SAI_FREE_PROTOCOL;
  hsai_BlockA1.Init.AudioMode = SAI_MODEMASTER_TX;
  hsai_BlockA1.Init.DataSize = SAI_DATASIZE_16;
  hsai_BlockA1.Init.FirstBit = SAI_FIRSTBIT_MSB;
  hsai_BlockA1.Init.ClockStrobing = SAI_CLOCKSTROBING_FALLINGEDGE;
  hsai_BlockA1.Init.Synchro = SAI_ASYNCHRONOUS;
  hsai_BlockA1.Init.OutputDrive = SAI_OUTPUTDRIVE_ENABLE;
  hsai_BlockA1.Init.NoDivider = SAI_MASTERDIVIDER_ENABLE;
  hsai_BlockA1.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_1QF;
  hsai_BlockA1.Init.AudioFrequency = SAI_AUDIO_FREQUENCY_16K;
  hsai_BlockA1.Init.SynchroExt = SAI_SYNCEXT_DISABLE;
  hsai_BlockA1.Init.MckOutput = SAI_MCK_OUTPUT_ENABLE;
  hsai_BlockA1.Init.MonoStereoMode = SAI_MONOMODE;
  hsai_BlockA1.Init.CompandingMode = SAI_NOCOMPANDING;
  hsai_BlockA1.Init.TriState = SAI_OUTPUT_NOTRELEASED;
  hsai_BlockA1.Init.PdmInit.Activation = DISABLE;
  hsai_BlockA1.Init.PdmInit.MicPairsNbr = 1;
  hsai_BlockA1.Init.PdmInit.ClockEnable = SAI_PDM_CLOCK1_ENABLE;
  hsai_BlockA1.FrameInit.FrameLength = 32;
  hsai_BlockA1.FrameInit.ActiveFrameLength = 16;
  hsai_BlockA1.FrameInit.FSDefinition = SAI_FS_CHANNEL_IDENTIFICATION;
  hsai_BlockA1.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
  hsai_BlockA1.FrameInit.FSOffset = SAI_FS_BEFOREFIRSTBIT;
  hsai_BlockA1.SlotInit.FirstBitOffset = 0;
  hsai_BlockA1.SlotInit.SlotSize = SAI_SLOTSIZE_16B;
  hsai_BlockA1.SlotInit.SlotNumber = 2;
  hsai_BlockA1.SlotInit.SlotActive = 0x00000003;
  if (HAL_SAI_Init(&hsai_BlockA1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SAI1_Init 2 */

  /* USER CODE END SAI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/**
  * @brief RIF Initialization Function
  * @param None
  * @retval None
  */
  static void SystemIsolation_Config(void)
{

/* USER CODE BEGIN RIF_Init 0 */

/* USER CODE END RIF_Init 0 */

  /* set all required IPs as secure privileged */
  __HAL_RCC_RIFSC_CLK_ENABLE();

  /* RIF-Aware IPs Config */

  /* set up GPDMA configuration */
  /* set GPDMA1 channel 0 used by SAI1 */
  if (HAL_DMA_ConfigChannelAttributes(&handle_GPDMA1_Channel0,DMA_CHANNEL_SEC|DMA_CHANNEL_PRIV|DMA_CHANNEL_SRC_SEC|DMA_CHANNEL_DEST_SEC)!= HAL_OK )
  {
    Error_Handler();
  }

/* USER CODE BEGIN RIF_Init 1 */

/* USER CODE END RIF_Init 1 */
/* USER CODE BEGIN RIF_Init 2 */

/* USER CODE END RIF_Init 2 */

}

/* USER CODE BEGIN 4 */
void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
{
	PcmBufferCplt = 1;
	HAL_SAI_DMAStop(&hsai_BlockA1);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
