/* crl.h
 *
 * Copyright (C) 2006-2021 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */



#ifndef WOLFSSL_CRL_H
#define WOLFSSL_CRL_H


#ifdef HAVE_CRL

#include <wolfssl/ssl.h>
#include <wolfssl/wolfcrypt/asn.h>

#ifdef __cplusplus
    extern "C" {
#endif

WOLFSSL_LOCAL int  InitCRL(WOLFSSL_CRL* crl, WOLFSSL_CERT_MANAGER* cm);
WOLFSSL_LOCAL void FreeCRL(WOLFSSL_CRL* crl, int dynamic);

WOLFSSL_LOCAL int  LoadCRL(WOLFSSL_CRL* crl, const char* path, int type,
                           int monitor);
WOLFSSL_LOCAL int  BufferLoadCRL(WOLFSSL_CRL* crl, const byte* buff, long sz,
                                 int type, int verify);
WOLFSSL_LOCAL int  CheckCertCRL(WOLFSSL_CRL* crl, DecodedCert* cert);


#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* HAVE_CRL */
#endif /* WOLFSSL_CRL_H */
