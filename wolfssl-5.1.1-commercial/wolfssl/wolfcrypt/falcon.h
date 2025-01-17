/* falcon.h
 *
 * Copyright (C) 2006-2021 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */

/*!
    \file wolfssl/wolfcrypt/falcon.h
*/

/* Interfaces for Falcon NIST Level 1 (Falcon512) and Falcon NIST Level 5
 * (Falcon1024). */

#ifndef WOLF_CRYPT_FALCON_H
#define WOLF_CRYPT_FALCON_H

#include <wolfssl/wolfcrypt/types.h>

#ifdef HAVE_PQC

#ifdef HAVE_LIBOQS
#include <oqs/oqs.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

/* Macros Definitions */

#ifdef HAVE_LIBOQS
#define FALCON_LEVEL1_KEY_SIZE     OQS_SIG_falcon_512_length_secret_key
#define FALCON_LEVEL1_SIG_SIZE     OQS_SIG_falcon_512_length_signature
#define FALCON_LEVEL1_PUB_KEY_SIZE OQS_SIG_falcon_512_length_public_key
#define FALCON_LEVEL1_PRV_KEY_SIZE (FALCON_LEVEL1_PUB_KEY_SIZE+FALCON_LEVEL1_KEY_SIZE)

#define FALCON_LEVEL5_KEY_SIZE     OQS_SIG_falcon_1024_length_secret_key
#define FALCON_LEVEL5_SIG_SIZE     OQS_SIG_falcon_1024_length_signature
#define FALCON_LEVEL5_PUB_KEY_SIZE OQS_SIG_falcon_1024_length_public_key
#define FALCON_LEVEL5_PRV_KEY_SIZE (FALCON_LEVEL5_PUB_KEY_SIZE+FALCON_LEVEL5_KEY_SIZE)
#endif

#define FALCON_MAX_KEY_SIZE     FALCON_LEVEL5_PRV_KEY_SIZE
#define FALCON_MAX_SIG_SIZE     FALCON_LEVEL5_SIG_SIZE
#define FALCON_MAX_PUB_KEY_SIZE FALCON_LEVEL5_PUB_KEY_SIZE
#define FALCON_MAX_PRV_KEY_SIZE FALCON_LEVEL5_PRV_KEY_SIZE

/* Structs */

struct falcon_key {
    bool pubKeySet;
    bool prvKeySet;
    byte level;
    byte p[FALCON_MAX_PUB_KEY_SIZE];
    byte k[FALCON_MAX_PRV_KEY_SIZE];
};

#ifndef WC_FALCONKEY_TYPE_DEFINED
    typedef struct falcon_key falcon_key;
    #define WC_FALCONKEY_TYPE_DEFINED
#endif

/* Functions */

WOLFSSL_API
int wc_falcon_sign_msg(const byte* in, word32 inLen, byte* out, word32 *outLen,
                       falcon_key* key);
WOLFSSL_API
int wc_falcon_verify_msg(const byte* sig, word32 sigLen, const byte* msg,
                         word32 msgLen, int* res, falcon_key* key);

WOLFSSL_API
int wc_falcon_init(falcon_key* key);
WOLFSSL_API
int wc_falcon_set_level(falcon_key* key, byte level);
WOLFSSL_API
int wc_falcon_get_level(falcon_key* key, byte* level);
WOLFSSL_API
void wc_falcon_free(falcon_key* key);

WOLFSSL_API
int wc_falcon_import_public(const byte* in, word32 inLen, falcon_key* key);
WOLFSSL_API
int wc_falcon_import_private_only(const byte* priv, word32 privSz,
                                  falcon_key* key);
WOLFSSL_API
int wc_falcon_import_private_key(const byte* priv, word32 privSz,
                                 const byte* pub, word32 pubSz,
                                 falcon_key* key);

WOLFSSL_API
int wc_falcon_export_public(falcon_key*, byte* out, word32* outLen);
WOLFSSL_API
int wc_falcon_export_private_only(falcon_key* key, byte* out, word32* outLen);
WOLFSSL_API
int wc_falcon_export_private(falcon_key* key, byte* out, word32* outLen);
WOLFSSL_API
int wc_falcon_export_key(falcon_key* key, byte* priv, word32 *privSz,
                         byte* pub, word32 *pubSz);

WOLFSSL_API
int wc_falcon_check_key(falcon_key* key);

WOLFSSL_API
int wc_falcon_size(falcon_key* key);
WOLFSSL_API
int wc_falcon_priv_size(falcon_key* key);
WOLFSSL_API
int wc_falcon_pub_size(falcon_key* key);
WOLFSSL_API
int wc_falcon_sig_size(falcon_key* key);

#ifdef __cplusplus
    }    /* extern "C" */
#endif

#endif /* HAVE_PQC */
#endif /* WOLF_CRYPT_FALCON_H */
