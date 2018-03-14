/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//#include "script.hpp"

#include <stdint.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <bitcoin/consensus.hpp>
#include <boost/test/unit_test.hpp>

#ifdef BITPRIM_CURRENCY_BCH
#include <clone-abc/script/interpreter.h>
#else // BITPRIM_CURRENCY_BCH
#include <clone-legacy/script/interpreter.h>
#endif // BITPRIM_CURRENCY_BCH

BOOST_AUTO_TEST_SUITE(consensus__script_verify)

using namespace libbitcoin::consensus;

typedef std::vector<uint8_t> data_chunk;

static unsigned from_hex(const char ch)
{
    if ('A' <= ch && ch <= 'F')
        return 10 + ch - 'A';

    if ('a' <= ch && ch <= 'f')
        return 10 + ch - 'a';

    return ch - '0';
}

static bool decode_base16_private(uint8_t* out, size_t size, const char* in)
{
    for (size_t i = 0; i < size; ++i)
    {
        if (!isxdigit(in[0]) || !isxdigit(in[1]))
            return false;

        out[i] = (from_hex(in[0]) << 4) + from_hex(in[1]);
        in += 2;
    }

    return true;
}

static bool decode_base16(data_chunk& out, const std::string& in)
{
    // This prevents a last odd character from being ignored:
    if (in.size() % 2 != 0)
        return false;

    data_chunk result(in.size() / 2);
    if (!decode_base16_private(result.data(), result.size(), in.data()))
        return false;

    out = result;
    return true;
}

static verify_result test_verify(const std::string& transaction,
    const std::string& prevout_script, uint32_t tx_input_index=0,
    const uint32_t flags=verify_flags_p2sh, int32_t tx_size_hack = 0, uint64_t amount = 0 )
{
    data_chunk tx_data, prevout_script_data;
    BOOST_REQUIRE(decode_base16(tx_data, transaction));
    BOOST_REQUIRE(decode_base16(prevout_script_data, prevout_script));
    return verify_script(&tx_data[0], tx_data.size() + tx_size_hack,
        &prevout_script_data[0], prevout_script_data.size(), tx_input_index,
        flags, amount);
}

// Test cases derived from:
// github.com/libbitcoin/libbitcoin-explorer/wiki/How-to-Spend-Bitcoin

#define CONSENSUS_SCRIPT_VERIFY_TX \
    "01000000017d01943c40b7f3d8a00a2d62fa1d560bf739a2368c180615b0a7937c0e883e7c000000006b4830450221008f66d188c664a8088893ea4ddd9689024ea5593877753ecc1e9051ed58c15168022037109f0d06e6068b7447966f751de8474641ad2b15ec37f4a9d159b02af68174012103e208f5403383c77d5832a268c9f71480f6e7bfbdfa44904becacfad66163ea31ffffffff01c8af0000000000001976a91458b7a60f11a904feef35a639b6048de8dd4d9f1c88ac00000000"
#define CONSENSUS_SCRIPT_VERIFY_PREVOUT_SCRIPT \
    "76a914c564c740c6900b93afc9f1bdaef0a9d466adf6ee88ac"

BOOST_AUTO_TEST_CASE(consensus__script_verify__null_tx__throws_invalid_argument)
{
    data_chunk prevout_script_data;
    BOOST_REQUIRE(decode_base16(prevout_script_data, CONSENSUS_SCRIPT_VERIFY_PREVOUT_SCRIPT));
    BOOST_REQUIRE_THROW(verify_script(NULL, 1, &prevout_script_data[0], prevout_script_data.size(), 0, 0, 0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(consensus__script_verify__null_prevout_script__throws_invalid_argument)
{
    data_chunk tx_data;
    BOOST_REQUIRE(decode_base16(tx_data, CONSENSUS_SCRIPT_VERIFY_TX));
    BOOST_REQUIRE_THROW(verify_script(&tx_data[0], tx_data.size(), NULL, 1, 0, 0, 0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(consensus__script_verify__invalid_tx__tx_invalid)
{
    const verify_result result = test_verify("42", "42");
    BOOST_REQUIRE_EQUAL(result, verify_result_tx_invalid);
}

BOOST_AUTO_TEST_CASE(consensus__script_verify__invalid_input__tx_input_invalid)
{
    const verify_result result = test_verify(CONSENSUS_SCRIPT_VERIFY_TX, CONSENSUS_SCRIPT_VERIFY_PREVOUT_SCRIPT, 1);
    BOOST_REQUIRE_EQUAL(result, verify_result_tx_input_invalid);
}

BOOST_AUTO_TEST_CASE(consensus__script_verify__undersized_tx__tx_invalid)
{
    const verify_result result = test_verify(CONSENSUS_SCRIPT_VERIFY_TX, CONSENSUS_SCRIPT_VERIFY_PREVOUT_SCRIPT, 0, verify_flags_p2sh, -1);
    BOOST_REQUIRE_EQUAL(result, verify_result_tx_invalid);
}

BOOST_AUTO_TEST_CASE(consensus__script_verify__oversized_tx__tx_size_invalid)
{
    const verify_result result = test_verify(CONSENSUS_SCRIPT_VERIFY_TX, CONSENSUS_SCRIPT_VERIFY_PREVOUT_SCRIPT, 0, verify_flags_p2sh, +1);
    BOOST_REQUIRE_EQUAL(result, verify_result_tx_size_invalid);
}

BOOST_AUTO_TEST_CASE(consensus__script_verify__incorrect_pubkey_hash__equalverify)
{
    const verify_result result = test_verify(CONSENSUS_SCRIPT_VERIFY_TX, "76a914c564c740c6900b93afc9f1bdaef0a9d466adf6ef88ac");
    BOOST_REQUIRE_EQUAL(result, verify_result_equalverify);
}

BOOST_AUTO_TEST_CASE(consensus__script_verify__valid__true)
{
    const verify_result result = test_verify(CONSENSUS_SCRIPT_VERIFY_TX, CONSENSUS_SCRIPT_VERIFY_PREVOUT_SCRIPT);
    BOOST_REQUIRE_EQUAL(result, verify_result_eval_true);
}

//TODO: just for Bitcoin Cash
BOOST_AUTO_TEST_CASE(consensus__script_verify__valid__true__non_forkid)
{
    std::string CONSENSUS_FORKID_TX="0100000001f2ca1aebc2e51b345f87365bdfa4956aaa5443cfb38f58e75318e3a3d3f1462e000000006b483045022100845a35869063291e4610de4939ac76f123a0b11b74e0615694a09206c30afbfc022063347ec313a582ab2025863ebdca71015ffc698eb37dbbf679b2865be944cf79012102fee381c90149e22ae182156c16316c24fe680a0e617646c3d58531112ac82e29ffffffff01b2e60200000000001976a914b96b816f378babb1fe585b7be7a2cd16eb99b3e488ac00000000";
    std::string CONSENSUS_FORKID_TX_PREV_SCRIPT = "76a914b96b816f378babb1fe585b7be7a2cd16eb99b3e488ac";
    const verify_result result = test_verify(CONSENSUS_FORKID_TX, CONSENSUS_FORKID_TX_PREV_SCRIPT);
    BOOST_REQUIRE_EQUAL(result, verify_result_eval_true);
}

//TODO: just for Bitcoin Cash
BOOST_AUTO_TEST_CASE(consensus__script_verify__valid__true__forkid)
{
    std::string CONSENSUS_FORKID_TX="0200000001131df2e09cd21da7897b9be4dba49fabb49ca979c569c2e1c80ea942748df144000000006a473044022005faf4f6726817a2a81288694bd73473ccaa610ffd4f356323e861285e5b6119022010eee370ce7be0f4c7cdca9bbc6129b648b2c555499bb2c926637df947c86aae412103e18167f4be43032ce2e62f559fef271902e8ce1aaaf0d518a6a2f40d4e01ad47ffffffff02fa6e1c05000000001976a9140bd183d2e2333b99fc4d5c70377f8bc0645d30b188aca0860100000000001976a91405ef21a2ee76c2015eaf9f1d57b6e85137f05cfc88ac00000000";
    std::string CONSENSUS_FORKID_TX_PREV_SCRIPT = "76a9140bd183d2e2333b99fc4d5c70377f8bc0645d30b188ac";
    int CONSENSUS_FORKID_TX_AMMOUT = 85899498;

    auto flags = SCRIPT_ENABLE_SIGHASH_FORKID;

    const verify_result result = test_verify(CONSENSUS_FORKID_TX, CONSENSUS_FORKID_TX_PREV_SCRIPT,0,flags,0,CONSENSUS_FORKID_TX_AMMOUT);
    BOOST_REQUIRE_EQUAL(result, verify_result_eval_true);
}

//TODO: just for Bitcoin Cash
BOOST_AUTO_TEST_CASE(consensus__script_verify__valid__true__forkid_long_int)
{
    std::string CONSENSUS_FORKID_TX="02000000016d4a52bbec92aca5014955a2d1d317f54a684dcc8b2ade9f9f1b5f873eb0933100000000694630430220058750aaa604cde20738ba2ae9949685b06f62c441e22e5e1374b422adde3865021f0c27d7f71603a86ebf05e7de0d29923d0616de03424bcbb858408fb8247d50412102a105d2380adc8f6b1148eab7db12098bb3860c5d856a24452fd6c6d63ba53e17feffffff0210270000000000001976a914bf9350c2ff5b147c33cab3307974f9a298b92a0688ac43b7052a010000001976a9149705d4b593f98f34e19a5961199db0ed7f04ebaf88ac23a31100";
    std::string CONSENSUS_FORKID_TX_PREV_SCRIPT = "76a914b939fdc5c4dd28318fd80b4203dc43003c4353ec88ac";
    unsigned long int CONSENSUS_FORKID_TX_AMMOUT = 5000000000;

    auto flags = SCRIPT_ENABLE_SIGHASH_FORKID;

    const verify_result result = test_verify(CONSENSUS_FORKID_TX, CONSENSUS_FORKID_TX_PREV_SCRIPT,0,flags,0,CONSENSUS_FORKID_TX_AMMOUT);
    BOOST_REQUIRE_EQUAL(result, verify_result_eval_true);
}

// TODO: create negative test vector.
//BOOST_AUTO_TEST_CASE(consensus__script_verify__invalid__false)
//{
//    const verify_result result = test_verify(...);
//    BOOST_REQUIRE_EQUAL(result, verify_result_eval_false);
//}

BOOST_AUTO_TEST_SUITE_END()
