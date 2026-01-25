/**
  ******************************************************************************
  * @file    network_data_params.c
  * @author  AST Embedded Analytics Research Platform
  * @date    2026-01-25T10:18:32-0300
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ******************************************************************************
  */

#include "network_data_params.h"


/**  Activations Section  ****************************************************/
ai_handle g_network_activations_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(NULL),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};




/**  Weights Section  ********************************************************/
AI_ALIGNED(32)
const ai_u64 s_network_weights_array_u64[393] = {
  0x3d0ecff33e5c9cc2U, 0x3e40bce2bd3fdebdU, 0xbc784a003db2f164U, 0xbe340e14be0f7f18U,
  0x3dde3597be29f8a3U, 0xbda017d0be4ea1ddU, 0x3e201a45bd9e27b6U, 0x3e5fb0f6bdf11ae2U,
  0xbc88c2003e2df25dU, 0x3e1abbc03e0405d3U, 0xbc5cb700be2aeee7U, 0xbdf4a84c3d92088aU,
  0xbe488238be52f6aeU, 0x3e00f8b4be7b4d08U, 0xbdb540a8be3488bfU, 0xbdcc1374bd8c7e3cU,
  0x3dd3185bbd07e2adU, 0x3dbe6064be44e964U, 0x3dda5b6bbe87cd72U, 0xbd0ba0e3be6b5919U,
  0xbd0e367bbe944881U, 0x3e157edebe579ba6U, 0xbe50f018be3323dfU, 0xbe28662bbe0488ffU,
  0xbe9b4bce3d0d5308U, 0xbda43a2cbe10666fU, 0x3e3d8bcebe8649f8U, 0xbe25fdcabe99ed32U,
  0xbe1e7036bd3cae49U, 0x3e1e5be7bca336faU, 0xbe8785babde9aeeeU, 0x3d77a9823d8a7a99U,
  0xbf0120003dedfeeaU, 0xbf7a7b99bdedac8cU, 0xbe6f4118U, 0x0U,
  0xbe63d45c00000000U, 0x0U, 0xbf5f874500000000U, 0xbf30a5973ec3ae29U,
  0xbf52178bU, 0x3d03791ebe8768edU, 0x0U, 0xbe562072U,
  0x0U, 0xbe94c94900000000U, 0x0U, 0x0U,
  0x3d09d67c3e53f867U, 0xbd90e9a300000000U, 0xbe6d0d7000000000U, 0x3cbcaa0a00000000U,
  0x3ddac63b00000000U, 0xbeae803e00000000U, 0x0U, 0x0U,
  0xbed3ed6dU, 0x3f12797200000000U, 0xbeb220b100000000U, 0x0U,
  0xbd36b351U, 0xbed2ad9a3e08f0b3U, 0x0U, 0x3e275ce4befd92fcU,
  0xbfeee71fc00457f7U, 0xbfb65fc2bfceceebU, 0xbf73b758bf97e84fU, 0xbef1fe32bf440a50U,
  0xbe1e4e39be8c42b3U, 0x3d8d6b0ebd16ef04U, 0x3ee9cfcc3e2e65b4U, 0x3f7428583f4e6ae2U,
  0xc89799bc99cc96aaU, 0xbab9b99a99cc9b9cU, 0xcac9bb9accbbbab9U, 0x9c9bb999cc999c9aU,
  0xaa9a9ab999c9babaU, 0xacc99cbbcbb9a9a9U, 0xababbabb9bcaaabcU, 0xbbbc9bbb9bca9bc9U,
  0x9c99c9bb9b9b9a8bU, 0xba9abb9aabaccbaaU, 0xcaab9997a89ab898U, 0xa9aa9cbbaacab9c9U,
  0x8bc79abbac9ab7abU, 0xb9acbcbcaaab9b9bU, 0xaa989a99c99babbbU, 0x98cbab9c9cca9ab9U,
  0xbcadbb9abcaa9dccU, 0x999ac9bacbbbbba9U, 0xa9bb9abacbba99bcU, 0xc9c9b9a99a9caaccU,
  0x9bb8ba98cbaaba9aU, 0xaab9ac9cab9cb9baU, 0xcabbcaba9998ca9aU, 0x9ba9cbaccacb99baU,
  0x89c9ccccb9a9ab99U, 0xa9cc9abcab9caa99U, 0xb9bcac99acabb9acU, 0x99bccca9cbcbacbaU,
  0xa9abcb9acbacccb9U, 0xbaaaca99999cbbbbU, 0xbc9bbaaacb9aa9a9U, 0x9bcbac9abbbab9caU,
  0x8893ac999c9aa0c6U, 0xcac9c9bc9cabac7bU, 0xc99ac89cac9999caU, 0x9dbacacbb9cabd8cU,
  0xbb9cbbc9c99acccaU, 0xabaccc9cbb9c9bb9U, 0x9aaab8aa9aaa9ba9U, 0xabbc998999aa98bbU,
  0x99a99abcacba99bbU, 0x9cba99bbaa9b99baU, 0xa9cacab9ca9998baU, 0x9aaccbbba9cac99bU,
  0xbbb99a9aba9bac99U, 0xa9b9c9ab9cbaca9bU, 0xbbcbc9cb99bbcacbU, 0xbccbca9cc9c99ac9U,
  0x8899bbba9b9bb98cU, 0xa99ba9bbbcbcabcbU, 0xa9baba9a99aac9b8U, 0x8ac9aa99caa9ab9bU,
  0xc898b9bbacaa98caU, 0xab9a99cca9b98b89U, 0xccc9a8bc9c98a9c9U, 0x9ccca8a99aa79c9bU,
  0x9accacaccbaa9cb9U, 0xbb9cb99cbc9ba9ccU, 0x9baa9cb9aa9ac9caU, 0x98ba9bacccaa9a9aU,
  0x9c989ac9aaaaac9bU, 0xabcbcbba9999b9c9U, 0x999cc99999aac9acU, 0x9acb99a9abc9abbaU,
  0x89b79a99babca7c9U, 0x9abbccccb9caaa8bU, 0x99bc9baca9a9acbcU, 0xb9bb989b9baabcbbU,
  0x9ba898b9bcba97cbU, 0x9cb99b9abca99c8bU, 0xca9c98cbbbb9c99aU, 0xbbac9ab9cc9acaabU,
  0xcaadb99a9cac9dcaU, 0xcbcb9aab99c9ccaaU, 0x9a99aabcb9cc9aaaU, 0xc9aca9bb9aabbbcbU,
  0xac9cabcbbabb899cU, 0xbcacbb9bcbc9b99aU, 0xbccc9ac8aa9bc99aU, 0xcabb8ab9ac999999U,
  0x99acbabb9c8cc9abU, 0x9ba9c89b9cbcbb9cU, 0xb9bcc9b9b99bb9a9U, 0xacaa9aa9ac9ccbbcU,
  0xaaabaaaa99aabc9aU, 0xbabbc9b9a9b99cbbU, 0xc99bab9aabba99b9U, 0x99c9bc89cc99babbU,
  0x9cb99abccaaa9aa9U, 0x9b9ca9a9bacba9b9U, 0xaa9a99acaa9c9a9aU, 0xa9cccb9999caaaabU,
  0x9bc9caa9aca9c98aU, 0x9ccca999baabab99U, 0xabcba898abaabaaaU, 0xb8b9bccbcabbbb99U,
  0xabadb9caaa9c9c9bU, 0xba9cbc99ca9ccbaaU, 0xb9c9cc9cccb99cabU, 0xaaaccba9aacb9aaaU,
  0xb9b9acbb9cbc9acbU, 0x9c9cab9caaabba9bU, 0xcb9bbb9aca9a9a8aU, 0x9bb9ab988acac88aU,
  0xd9aabba89ca9bb5cU, 0x9c99c99acccaa6c9U, 0xcbbc9a98ccb9c7b6U, 0x97a9ba9b9aab9cbbU,
  0xac98cbcbbc89a9bbU, 0x9c9bc9a9ca9b9b9bU, 0xa99abba8ab9aca89U, 0x989b999999bbb9acU,
  0xf8b8bbc7a98ba959U, 0xccbacbb9aabba68cU, 0xbc9baab9bb9ba7c7U, 0x779acabb9babbcbcU,
  0x9997bccaab9b97caU, 0xbcbc9a9cbbcbb9aaU, 0xaaaac9cbabbabb9aU, 0xacbabb8cbb9b9c99U,
  0x78b9ca9aabb9a8a9U, 0xb9bccacbb99a9b8cU, 0xbcbaaab9cbba9bccU, 0xbccca9babba9b99cU,
  0x89b4babc99a993a7U, 0x9a9cb9cbbb9b8c7cU, 0x9bccbbbb9a9b9cbcU, 0x9aaac9abbcc99d79U,
  0xbbaacabaaabab99bU, 0xcbbc9bbb9cacc8bbU, 0xac9cb9999a9acca8U, 0xca99a89c99a89999U,
  0xa99c9a99aaac8ba9U, 0x9aa9b99cccaa99a9U, 0xc9cc9bc8aaaac9aaU, 0xabbaab9a9abaaa99U,
  0xb9b9aa9ab988caa9U, 0xc9cacaccaa9aa99aU, 0xaba9acb9ab9b9baaU, 0xb99a9bcacaba9abaU,
  0x99cb99abb9aab9aaU, 0xc9aacbc98cb99c9cU, 0x9c99b8b99aba99b8U, 0xc8b9bacaacc9b8aaU,
  0xa899bcaab9ab8baaU, 0xa99abac999ac899aU, 0xb99cc99aaaabcbbcU, 0xaa9ac8b999b89abaU,
  0xe8a99cc8cb7aaa68U, 0xcc9ba9c989cc96abU, 0xa99a99ccab9bb2c7U, 0x999b98ca99bbab99U,
  0xc9aaacc98bcbabaaU, 0x9cba9bbccacba8bbU, 0xbba9cababbbcb989U, 0xcbac9ca9aa9a9a9aU,
  0xaa98b9a9aa8b99caU, 0xbcc9a8caac9b9999U, 0x9ccacab9babab8bbU, 0x8bbaa8bca8979cabU,
  0xa999bcb8ba7c977bU, 0xbbcaa9ba8cbc788cU, 0xc99999b8ba99a9b7U, 0x989b79cc9998b89aU,
  0x99a7ca9cca99b7c8U, 0xcc99c9cbbaba8aabU, 0x9aa9aabbaabccabaU, 0xcbbb9aacbcabcc9aU,
  0xd7c7bcb8cb8ba7b8U, 0xccbbb7a98acc7a79U, 0x9c9b98bcbca799bcU, 0x9bccc89baab7bd79U,
  0x7898999cacacb7c9U, 0x9b9a9a9a89ac8b9bU, 0xa9bcababbca999acU, 0xbab9c8aa9abac99cU,
  0xacbbcbabc9aab9abU, 0x99bcaabb9a9c999bU, 0x9aaba9bbaab9b9a9U, 0xc9b9b9bccabcabccU,
  0xc799a9b8bc8aa8b7U, 0xbc9ba7997b9a7c7aU, 0xc999b79a9ac9aacbU, 0x9c9cc78acbc7bd8cU,
  0xa9999c9ab98a999bU, 0xac9cbbaccbc99999U, 0xb9babab999aa999cU, 0x99bacbacbbcbaabaU,
  0x99c99babbccb9c99U, 0xbbc9cbacbcbbbbacU, 0xa9a9bcccbacc999cU, 0xa89aaa9ac9cc9ac9U,
  0xa8c7acaa99ca98abU, 0xcb9999cbabbbaa99U, 0xb9b9ababba999bccU, 0xba99b99a9baaa9a9U,
  0x9ca9ba999c99ba9cU, 0xabbccb9cacbbb99aU, 0x9c99a9a9a99cca9bU, 0x9cabbaabccccc9cbU,
  0x99a9acaabacca9baU, 0xac99babbbc9a8bc9U, 0xacbb9999a8a99aa8U, 0x9aaa98aaac9ab9acU,
  0xca9c99ab99aba99bU, 0x9b9c9aa99bbc99bcU, 0x9cb9c9c8c8acbaa7U, 0x98c99aacbacbb899U,
  0x99989baba9bbcba9U, 0xaac9aca9bcbbb9aaU, 0xacbac9ca99c999c8U, 0x9a9aba999ccb899bU,
  0xaac89aaba99ab9b8U, 0x9a9bbacb9bc9aa8aU, 0x99a9c9cc9ca99cbbU, 0xacbab8ac9bbbcab9U,
  0xc9999c999cbabbaaU, 0xb9ab9bacbb9a99acU, 0xbc9b99c9b89aab99U, 0xcaacb999bbaab89cU,
  0xabb9a9a9aa8cba98U, 0xcaaa98baaccbb99cU, 0x9bbba999a89ac88aU, 0xab9baac9abca9aaaU,
  0xab99c9b9bcacc98aU, 0xcb9bbb99bbbab8c9U, 0xabc999999ac9b8a9U, 0x9bbb99bbbb99ba9bU,
  0xabb89aba9b9c98b8U, 0xaaaaabacac9cbc8aU, 0xa9cc99babbabac9aU, 0xc99b989ab9999bbcU,
  0x8ac7a99aabbc98caU, 0x9b9ca9aba99bba99U, 0xbbaac99999caa9cbU, 0x8bb9c9ccaa98bb8cU,
  0xa9c99aa9bbbab9b9U, 0xa9ba98caac9ca8bbU, 0xaccccc9898b9c9bbU, 0xb9acaaaa9c98b9aaU,
  0x9baabb9abb9aabbcU, 0x9aca9999caccac9bU, 0x9bcbbba999a9999aU, 0xabcca9aa9bc9aa99U,
  0x7997cca79979978aU, 0xbabbb799899c797aU, 0xcbbc99b9c898c988U, 0x89ab79accba9a7b9U,
  0xa9c8c99c9cbcb8c8U, 0xc9a9bacb99999989U, 0xaacaaa9bbb9a99cbU, 0xaaccba9cba98acbcU,
  0x89bbaab99caaac99U, 0xa9bab8a9ab99ab9aU, 0xc9c9a9aabb98abcaU, 0x98b999c999caccacU,
  0xbd71f18e3e944d12U, 0x3e2ff5d7beb2e691U, 0xbd75f856be1f7709U, 0xbd4ea6b0U,
  0xbe7b79803f3dfeabU, 0xbd5b4f8a3e22ec12U, 0x3ed30895bd70981eU, 0x0U,
  0x3d2165c43e214e21U, 0x3d3cfcbebd73acdbU, 0xbd75f526bd75f84fU, 0x3dc16e9d00000000U,
  0xbd80b22ebe280441U, 0xbd75f4033eb8cd0aU, 0x3dc88e643f0105a6U, 0x3f0195953c61e253U,
  0xbd991fd7bd9a13feU, 0xbb53801abd9a65d8U, 0x3e8e05f03e7dd153U, 0x3df5ef06bd95228fU,
  0x3dc5e9f1bebae89cU, 0x3d5dd7f23f14c8aeU, 0x3f0d63d000000000U, 0xbd64e0e2U,
  0xbdbc76ea3db93d75U, 0xbcf605f8bd75f511U, 0xbcd52ef4bd75f7f8U, 0xbdf3799bbd636445U,
  0x3cdab6e3be51b242U, 0xbd75a6a83d6663a1U, 0xbe5b9483bd592987U, 0xbc0bf3bb3cd2640fU,
  0x3c8fb108bd11e533U, 0xbc6bbed3bc1db4b7U, 0x3e6335253e20feeeU, 0xbd3f1740be4b3f89U,
  0x3d828b20bf1e28eaU, 0x3cdc93723db12a83U, 0x3f3bd5fdbde96942U, 0xbe03846ebe983381U,
  0xbdbbb89fbe5ba243U, 0x3cf5fa1a3d27e438U, 0x3db374e63e6197a0U, 0xbd176661be97451cU,
  0x3d4c49503e200b2cU, 0x3d87b3a9bf441a93U, 0xbdc1c785bf4be0a2U, 0xbe95a41fbd34d160U,
  0x3d4d8839be38625eU, 0x3e60d3b8be741163U, 0xbf087bf23e59fd36U, 0x3e480fffbc836c69U,
  0xbd65199c3d9608d4U, 0xbd649e3b3f4f695fU, 0x3f5c47a23ceee340U, 0xbe1fe3a23e3e9b00U,
  0xbc511b50be475f74U, 0xbe61aa4c3dafc312U, 0xbd4f819b3e47d7a0U, 0xbc848e7bbd8f698eU,
  0xbd07e44b3da5a98cU, 0xbd468163bdc4b88aU, 0x3e80b54dbe3049b1U, 0x3e22e588be178c02U,
  0xbe2251b9U,
};


ai_handle g_network_weights_table[1 + 2] = {
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
  AI_HANDLE_PTR(s_network_weights_array_u64),
  AI_HANDLE_PTR(AI_MAGIC_MARKER),
};

