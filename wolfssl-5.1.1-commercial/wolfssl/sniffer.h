/* sniffer.h
 *
 * Copyright (C) 2006-2021 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * https://www.wolfssl.com
 */



#ifndef WOLFSSL_SNIFFER_H
#define WOLFSSL_SNIFFER_H

#include <wolfssl/wolfcrypt/settings.h>
#include <wolfssl/wolfcrypt/asn_public.h>

#ifdef _WIN32
    #ifdef SSL_SNIFFER_EXPORTS
        #define SSL_SNIFFER_API __declspec(dllexport)
    #else
        #define SSL_SNIFFER_API __declspec(dllimport)
    #endif
#else
    #define SSL_SNIFFER_API
#endif /* _WIN32 */


#ifdef __cplusplus
    extern "C" {
#endif

/* @param typeK: (formerly keyType) was shadowing a global declaration in
 *                wolfssl/wolfcrypt/asn.h line 175
 */
WOLFSSL_API
SSL_SNIFFER_API int ssl_SetPrivateKey(const char* address, int port,
                                      const char* keyFile, int typeK,
                                      const char* password, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetPrivateKeyBuffer(const char* address, int port,
                                            const char* keyBuf, int keySz,
                                            int typeK, const char* password,
                                            char* error);


WOLFSSL_API
SSL_SNIFFER_API int ssl_SetNamedPrivateKey(const char* name,
                                           const char* address, int port,
                                           const char* keyFile, int typeK,
                                           const char* password, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetNamedPrivateKeyBuffer(const char* name,
                                                 const char* address, int port,
                                                 const char* keyBuf, int keySz,
                                                 int typeK, const char* password,
                                                 char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetEphemeralKey(const char* address, int port,
                                        const char* keyFile, int typeKey,
                                        const char* password, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetEphemeralKeyBuffer(const char* address, int port,
                                              const char* keyBuf, int keySz, int typeKey,
                                              const char* password, char* error);


WOLFSSL_API
SSL_SNIFFER_API int ssl_SetNamedEphemeralKey(const char* name,
                                             const char* address, int port,
                                             const char* keyFile, int typeKey,
                                             const char* password, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetNamedEphemeralKeyBuffer(const char* name,
                                                   const char* address, int port,
                                                   const char* keyBuf, int keySz, int typeKey,
                                                   const char* password, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_DecodePacket(const unsigned char* packet, int length,
                                     unsigned char** data, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_FreeDecodeBuffer(unsigned char** data, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_FreeZeroDecodeBuffer(unsigned char** data, int sz,
                                             char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_Trace(const char* traceFile, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_EnableRecovery(int onOff, int maxMemory, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_GetSessionStats(unsigned int* active,
                                        unsigned int* total,
                                        unsigned int* peak,
                                        unsigned int* maxSessions,
                                        unsigned int* missedData,
                                        unsigned int* reassemblyMemory,
                                        char* error);

WOLFSSL_API void ssl_InitSniffer(void);

WOLFSSL_API void ssl_FreeSniffer(void);


/* ssl_SetPrivateKey typeKs */
enum {
    FILETYPE_PEM = 1,
    FILETYPE_DER = 2,
};


/*
 * New Sniffer API that provides read-only access to the TLS and cipher
 * information associated with the SSL session.
 */

typedef struct SSLInfo
{
    unsigned char  isValid;
            /* indicates if the info in this struct is valid: 0 = no, 1 = yes */
    unsigned char  protocolVersionMajor;    /* SSL Version: major */
    unsigned char  protocolVersionMinor;    /* SSL Version: minor */
    unsigned char  serverCipherSuite0;      /* first byte, normally 0 */
    unsigned char  serverCipherSuite;       /* second byte, actual suite */
    unsigned char  serverCipherSuiteName[256];
            /* cipher name, e.g., "TLS_RSA_..." */
    unsigned char  serverNameIndication[128];
    unsigned int   keySize;
} SSLInfo;


WOLFSSL_API
SSL_SNIFFER_API int ssl_DecodePacketWithSessionInfo(
                        const unsigned char* packet, int length,
                        unsigned char** data, SSLInfo* sslInfo, char* error);

typedef void (*SSLConnCb)(const void* session, SSLInfo* info, void* ctx);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetConnectionCb(SSLConnCb cb);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetConnectionCtx(void* ctx);


typedef struct SSLStats
{
    unsigned long int sslStandardConns;      /* server_hello count not including resumed sessions */
    unsigned long int sslClientAuthConns;    /* client's who have presented certificates (mutual authentication) */
    unsigned long int sslResumedConns;       /* resumed connections */
    unsigned long int sslEphemeralMisses;    /* TLS v1.2 and older PFS / ephemeral connections missed (not able to decrypt) */
    unsigned long int sslResumeMisses;       /* Resumption sessions not found */
    unsigned long int sslCiphersUnsupported; /* No cipher suite match found when compared to supported */
    unsigned long int sslKeysUnmatched;      /* Key callback failures (not found). Applies to WOLFSSL_SNIFFER_WATCH only */
    unsigned long int sslKeyFails;           /* Failures loading or using keys */
    unsigned long int sslDecodeFails;        /* Dropped packets (not application_data or match protocol version) */
    unsigned long int sslAlerts;             /* Number of decoded alert messages */
    unsigned long int sslDecryptedBytes;     /* Number of decrypted bytes */
    unsigned long int sslEncryptedBytes;     /* Number of encrypted bytes */
    unsigned long int sslEncryptedPackets;   /* Number of encrypted packets */
    unsigned long int sslDecryptedPackets;   /* Number of decrypted packets */
    unsigned long int sslKeyMatches;         /* Key callback successes (failures tracked in sslKeysUnmatched). Applies to WOLFSSL_SNIFFER_WATCH only. */
    unsigned long int sslEncryptedConns;     /* Number of created sniffer sessions */
    unsigned long int sslResumptionInserts;  /* Number of sessions reused with resumption */
} SSLStats;

WOLFSSL_API
SSL_SNIFFER_API int ssl_ResetStatistics(void);

WOLFSSL_API
SSL_SNIFFER_API int ssl_ReadStatistics(SSLStats* stats);

WOLFSSL_API
SSL_SNIFFER_API int ssl_ReadResetStatistics(SSLStats* stats);


#if defined(WOLFSSL_STATIC_EPHEMERAL) && defined(WOLFSSL_TLS13)
/* macro indicating support for key callback */
#undef  WOLFSSL_SNIFFER_KEY_CALLBACK
#define WOLFSSL_SNIFFER_KEY_CALLBACK

typedef int (*SSLKeyCb)(void* vSniffer, int namedGroup,
    const unsigned char* srvPub, unsigned int srvPubSz,
    const unsigned char* cliPub, unsigned int cliPubSz,
    DerBuffer* privKey, void* cbCtx, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetKeyCallback(SSLKeyCb cb, void* cbCtx);
#endif


#ifdef WOLFSSL_SNIFFER_WATCH
typedef int (*SSLWatchCb)(void* vSniffer,
                        const unsigned char* certHash,
                        unsigned int certHashSz,
                        const unsigned char* certChain,
                        unsigned int certChainSz,
                        void* ctx, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetWatchKeyCallback(SSLWatchCb cb, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetWatchKeyCallback_ex(SSLWatchCb cb, int devId,
                        char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetWatchKeyCtx(void* ctx, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetWatchKey_buffer(void* vSniffer,
                        const unsigned char* key, unsigned int keySz,
                        int keyType, char* error);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetWatchKey_file(void* vSniffer,
                        const char* keyFile, int keyType,
                        const char* password, char* error);
#endif

#ifdef WOLFSSL_SNIFFER_STORE_DATA_CB
typedef int (*SSLStoreDataCb)(const unsigned char* decryptBuf,
        unsigned int decryptBufSz, unsigned int decryptBufOffset, void* ctx);

WOLFSSL_API
SSL_SNIFFER_API int ssl_SetStoreDataCallback(SSLStoreDataCb cb);
#endif

#ifdef WOLFSSL_SNIFFER_STORE_DATA_CB
WOLFSSL_API
SSL_SNIFFER_API int ssl_DecodePacketWithSessionInfoStoreData(
        const unsigned char* packet, int length, void* ctx,
        SSLInfo* sslInfo, char* error);
#endif

#ifdef WOLFSSL_SNIFFER_CHAIN_INPUT
WOLFSSL_API
SSL_SNIFFER_API int ssl_DecodePacketWithChain(void* vChain,
        unsigned int chainSz, unsigned char** data, char* error);
#endif

#if defined(WOLFSSL_SNIFFER_CHAIN_INPUT) && \
    defined(WOLFSSL_SNIFFER_STORE_DATA_CB)
WOLFSSL_API
SSL_SNIFFER_API int ssl_DecodePacketWithChainSessionInfoStoreData(
        void* vChain, unsigned int chainSz, void* ctx, SSLInfo* sslInfo,
        char* error);
#endif


#ifdef __cplusplus
    }  /* extern "C" */
#endif

#endif /* wolfSSL_SNIFFER_H */

