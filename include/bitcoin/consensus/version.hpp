///////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014-2015 libbitcoin-consensus developers (see COPYING).
//
//        GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY
//
///////////////////////////////////////////////////////////////////////////////
#ifndef LIBBITCOIN_CONSENSUS_VERSION_HPP
#define LIBBITCOIN_CONSENSUS_VERSION_HPP

/**
 * The semantic version of this repository as: [major].[minor].[patch]
 * For interpretation of the versioning scheme see: http://semver.org
 */

#define LIBBITCOIN_CONSENSUS_VERSION "0.8.0"
#define LIBBITCOIN_CONSENSUS_MAJOR_VERSION 0
#define LIBBITCOIN_CONSENSUS_MINOR_VERSION 8
#define LIBBITCOIN_CONSENSUS_PATCH_VERSION 0

// #define STR_HELPER(x) #x
// #define STR(x) STR_HELPER(x)
// #define LIBBITCOIN_CONSENSUS_VERSION STR(LIBBITCOIN_CONSENSUS_MAJOR_VERSION) "." STR(LIBBITCOIN_CONSENSUS_MINOR_VERSION) "." STR(LIBBITCOIN_CONSENSUS_PATCH_VERSION)
// #undef STR
// #undef STR_HELPER

#ifdef BITPRIM_BUILD_NUMBER
#define BITPRIM_CONSENSUS_VERSION BITPRIM_BUILD_NUMBER
#else
#define BITPRIM_CONSENSUS_VERSION "v0.0.0"
#endif

// namespace libbitcoin { namespace ?????? {
// char const* version();
// }} /*namespace libbitcoin::????????*/
 

#endif
