/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */

#ifndef __AWSS_PASSWD_H__
#define __AWSS_PASSWD_H__

#define KEY_MAX_LEN     (40)
#define AES128_KEY_LEN  (16)
#define RANDOM_MAX_LEN  (16)

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

enum {
    SSID_DECODE_TABLE = 0x0,
    NOTIFY_ENCODE_TABLE,
    DICT_CRYPT_TABLE_IDX_MAX,
};

int awss_dict_crypt(char tab_idx, uint8_t *data, uint8_t len);
#ifdef WIFI_PROVISION_ENABLED
int produce_signature(uint8_t *sign, uint8_t *txt, uint32_t txt_len, const char *key);
#endif

typedef enum {
    TOKEN_TYPE_NOT_CLOUD = 0x00,
    TOKEN_TYPE_CLOUD,
    TOKEN_TYPE_MAX,
    TOKEN_TYPE_INVALID = 0xFF
} bind_token_type_t;

typedef unsigned char uint8_t;
extern uint8_t aes_random[RANDOM_MAX_LEN];

int awss_set_token(uint8_t token[RANDOM_MAX_LEN], bind_token_type_t token_type);
int awss_get_token(uint8_t token_buf[], int token_buf_len, bind_token_type_t *p_token_type);
#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif

#endif
