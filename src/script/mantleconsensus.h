// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2018 The Mantle Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MANTLE_SCRIPT_MANTLECONSENSUS_H
#define MANTLE_SCRIPT_MANTLECONSENSUS_H

#include <stdint.h>

#if defined(BUILD_MANTLE_INTERNAL) && defined(HAVE_CONFIG_H)
#include <config/mantle-config.h>
  #if defined(_WIN32)
    #if defined(DLL_EXPORT)
      #if defined(HAVE_FUNC_ATTRIBUTE_DLLEXPORT)
        #define EXPORT_SYMBOL __declspec(dllexport)
      #else
        #define EXPORT_SYMBOL
      #endif
    #endif
  #elif defined(HAVE_FUNC_ATTRIBUTE_VISIBILITY)
    #define EXPORT_SYMBOL __attribute__ ((visibility ("default")))
  #endif
#elif defined(MSC_VER) && !defined(STATIC_LIBMANTLECONSENSUS)
  #define EXPORT_SYMBOL __declspec(dllimport)
#endif

#ifndef EXPORT_SYMBOL
  #define EXPORT_SYMBOL
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define MANTLECONSENSUS_API_VER 1

typedef enum mantleconsensus_error_t
{
    mantleconsensus_ERR_OK = 0,
    mantleconsensus_ERR_TX_INDEX,
    mantleconsensus_ERR_TX_SIZE_MISMATCH,
    mantleconsensus_ERR_TX_DESERIALIZE,
    mantleconsensus_ERR_AMOUNT_REQUIRED,
    mantleconsensus_ERR_INVALID_FLAGS,
} mantleconsensus_error;

/** Script verification flags */
enum
{
    mantleconsensus_SCRIPT_FLAGS_VERIFY_NONE                = 0,
    mantleconsensus_SCRIPT_FLAGS_VERIFY_P2SH                = (1U << 0), // evaluate P2SH (BIP16) subscripts
    mantleconsensus_SCRIPT_FLAGS_VERIFY_DERSIG              = (1U << 2), // enforce strict DER (BIP66) compliance
    mantleconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY           = (1U << 4), // enforce NULLDUMMY (BIP147)
    mantleconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY = (1U << 9), // enable CHECKLOCKTIMEVERIFY (BIP65)
    mantleconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY = (1U << 10), // enable CHECKSEQUENCEVERIFY (BIP112)
    mantleconsensus_SCRIPT_FLAGS_VERIFY_WITNESS             = (1U << 11), // enable WITNESS (BIP141)
    mantleconsensus_SCRIPT_FLAGS_VERIFY_ALL                 = mantleconsensus_SCRIPT_FLAGS_VERIFY_P2SH | mantleconsensus_SCRIPT_FLAGS_VERIFY_DERSIG |
                                                               mantleconsensus_SCRIPT_FLAGS_VERIFY_NULLDUMMY | mantleconsensus_SCRIPT_FLAGS_VERIFY_CHECKLOCKTIMEVERIFY |
                                                               mantleconsensus_SCRIPT_FLAGS_VERIFY_CHECKSEQUENCEVERIFY | mantleconsensus_SCRIPT_FLAGS_VERIFY_WITNESS
};

/// Returns 1 if the input nIn of the serialized transaction pointed to by
/// txTo correctly spends the scriptPubKey pointed to by scriptPubKey under
/// the additional constraints specified by flags.
/// If not nullptr, err will contain an error/success code for the operation
EXPORT_SYMBOL int mantleconsensus_verify_script(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen,
                                                 const unsigned char *txTo        , unsigned int txToLen,
                                                 unsigned int nIn, unsigned int flags, mantleconsensus_error* err);

EXPORT_SYMBOL int mantleconsensus_verify_script_with_amount(const unsigned char *scriptPubKey, unsigned int scriptPubKeyLen, int64_t amount,
                                    const unsigned char *txTo        , unsigned int txToLen,
                                    unsigned int nIn, unsigned int flags, mantleconsensus_error* err);

EXPORT_SYMBOL unsigned int mantleconsensus_version();

#ifdef __cplusplus
} // extern "C"
#endif

#undef EXPORT_SYMBOL

#endif // MANTLE_SCRIPT_MANTLECONSENSUS_H
