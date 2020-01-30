// Copyright (c) 2012-2016 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_VERSION_H
#define BITCOIN_VERSION_H

/**
 * network protocol versioning
 */

static int const PROTOCOL_VERSION = 70015;

//! initial proto version, to be increased after version/verack negotiation
static int const INIT_PROTO_VERSION = 209;

//! In this version, 'getheaders' was introduced.
static int const GETHEADERS_VERSION = 31800;

//! disconnect from peers older than this proto version
static int const MIN_PEER_PROTO_VERSION = GETHEADERS_VERSION;

//! nTime field added to CAddress, starting with this version;
//! if possible, avoid requesting addresses nodes older than this
static int const CADDR_TIME_VERSION = 31402;

//! BIP 0031, pong message, is enabled for all versions AFTER this one
static int const BIP0031_VERSION = 60000;

//! "filter*" commands are disabled without NODE_BLOOM after and including this version
static int const NO_BLOOM_VERSION = 70011;

//! "sendheaders" command and announcing blocks with headers starts with this version
static int const SENDHEADERS_VERSION = 70012;

//! "feefilter" tells peers to filter invs to you by fee starts with this version
static int const FEEFILTER_VERSION = 70013;

//! short-id-based block download starts with this version
static int const SHORT_IDS_BLOCKS_VERSION = 70014;

//! not banning for invalid compact blocks starts with this version
static int const INVALID_CB_NO_BAN_VERSION = 70015;

#endif // BITCOIN_VERSION_H
