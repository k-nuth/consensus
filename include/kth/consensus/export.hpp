// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KTH_CONSENSUS_EXPORT_HPP
#define KTH_CONSENSUS_EXPORT_HPP

#include <cstddef>
#include <cstdint>

#include <kth/consensus/define.hpp>
#include <kth/consensus/version.hpp>

namespace kth {
namespace consensus {

/**
 * Result values from calling verify_script.
 */
typedef enum verify_result_type
{
    // Logical result
    verify_result_eval_false = 0,
    verify_result_eval_true,

    // Max size errors
    verify_result_script_size,
    verify_result_push_size,
    verify_result_op_count,
    verify_result_stack_size,
    verify_result_sig_count,
    verify_result_pubkey_count,

    // Failed verify operations
    verify_result_verify,
    verify_result_equalverify,
    verify_result_checkmultisigverify,
    verify_result_checksigverify,
    verify_result_numequalverify,

    // Logical/Format/Canonical errors
    verify_result_bad_opcode,
    verify_result_disabled_opcode,
    verify_result_invalid_stack_operation,
    verify_result_invalid_altstack_operation,
    verify_result_unbalanced_conditional,

    // BIP62 errors
    verify_result_sig_hashtype,
    verify_result_sig_der,
    verify_result_minimaldata,
    verify_result_sig_pushonly,
    verify_result_sig_high_s,
    verify_result_sig_nulldummy,
    verify_result_pubkeytype,
    verify_result_cleanstack,
    verify_result_minimalif,
    verify_result_sig_nullfail,

    // Softfork safeness
    verify_result_discourage_upgradable_nops,
    verify_result_discourage_upgradable_witness_program,

    // Other
    verify_result_op_return,
    verify_result_unknown_error,

    // Segregated witness
    verify_result_witness_program_wrong_length,
    verify_result_witness_program_empty_witness,
    verify_result_witness_program_mismatch,
    verify_result_witness_malleated,
    verify_result_witness_malleated_p2sh,
    verify_result_witness_unexpected,
    verify_result_witness_pubkeytype,

    // augmention codes for tx deserialization
    verify_result_tx_invalid,
    verify_result_tx_size_invalid,
    verify_result_tx_input_invalid,

    // BIP65/BIP112 (shared codes)
    verify_result_negative_locktime,
    verify_result_unsatisfied_locktime
} verify_result;

/**
 * Flags to use when calling verify_script.
 */
typedef enum verify_flags_type
{
    /**
     * Set no flags.
     */
    verify_flags_none = 0,

    /**
     * Evaluate P2SH subscripts (softfork safe, BIP16).
     */
    verify_flags_p2sh = (1U << 0),

    /**
     * Passing a non-strict-DER signature or one with undefined hashtype to a
     * checksig operation causes script failure. Evaluating a pubkey that is
     * not (0x04 + 64 bytes) or (0x02 or 0x03 + 32 bytes) by checksig causes
     * script failure. (softfork safe, but not used or intended as a consensus
     * rule).
     */
    verify_flags_strictenc = (1U << 1),

    /**
     * Passing a non-strict-DER signature to a checksig operation causes script
     * failure (softfork safe, BIP62 rule 1, BIP66).
     */
    verify_flags_dersig = (1U << 2),

    /**
     * Passing a non-strict-DER signature or one with S > order/2 to a checksig
     * operation causes script failure
     * (softfork safe, BIP62 rule 5).
     */
    verify_flags_low_s = (1U << 3),

    /**
     * verify dummy stack item consumed by CHECKMULTISIG is of zero-length
     * (softfork safe, BIP62 rule 7, BIP147).
     */
    verify_flags_nulldummy = (1U << 4),

    /**
     * Using a non-push operator in the scriptSig causes script failure
     * (softfork safe, BIP62 rule 2).
     */
    verify_flags_sigpushonly = (1U << 5),

    /**
     * Require minimal encodings for all push operations (OP_0... OP_16,
     * OP_1NEGATE where possible, direct pushes up to 75 bytes, OP_PUSHDATA
     * up to 255 bytes, OP_PUSHDATA2 for anything larger). Evaluating any other
     * push causes the script to fail (BIP62 rule 3). In addition, whenever a
     * stack element is interpreted as a number, it must be of minimal length
     * (BIP62 rule 4).(softfork safe)
     */
    verify_flags_minimaldata = (1U << 6),

    /**
     * Discourage use of NOPs reserved for upgrades (NOP1,3-10)
     * Provided so that nodes can avoid accepting or mining transactions
     * containing executed NOP's whose meaning may change after a soft-fork,
     * thus rendering the script invalid; with this flag set executing
     * discouraged NOPs fails the script. This verification flag will never be
     * a mandatory flag applied to scripts in a block. NOPs that are not
     * executed, e.g.  within an unexecuted IF ENDIF block, are *not* rejected.
     */
    verify_flags_discourage_upgradable_nops = (1U << 7),

    /**
     * Require that only a single stack element remains after evaluation. This
     * changes the success criterion from "At least one stack element must
     * remain, and when interpreted as a boolean, it must be true" to "Exactly
     * one stack element must remain, and when interpreted as a boolean, it
     * must be true". (softfork safe, BIP62 rule 6)
     * Note: verify_flags_cleanstack must be used with verify_flags_p2sh.
     */
    verify_flags_cleanstack = (1U << 8),

    /**
     * Verify CHECKLOCKTIMEVERIFY, see BIP65 for details.
     */
    verify_flags_checklocktimeverify = (1U << 9),

    /**
     * Verify CHECKSEQUENCEVERIFY, see BIP112 for details.
     */
    verify_flags_checksequenceverify = (1U << 10)

#if ! defined(KTH_CURRENCY_BCH)
    /**
     * SCRIPT_VERIFY_WITNESS (bip141).
     */
    , verify_flags_witness = (1U << 11)

    /**
     * SCRIPT_VERIFY_DISCOURAGE_UPGRADABLE_WITNESS_PROGRAM (bip141 policy).
     */
    , verify_flags_discourage_upgradable_witness_program = (1U << 12)

    /**
     * SCRIPT_VERIFY_MINIMALIF (bip141 p2wsh policy).
     */
    , verify_flags_minimal_if = (1U << 13)

    /**
     * SCRIPT_VERIFY_NULLFAIL (bip141 global policy, bip146 soft fork).
     */
    , verify_flags_null_fail = (1U << 14)

    /**
     * SCRIPT_VERIFY_WITNESS_PUBKEYTYPE (bip141/bip143 p2wsh/p2wpkh policy).
     */
    , verify_flags_witness_public_key_compressed = (1U << 15)
#endif

#ifdef KTH_CURRENCY_BCH
    /**
     * SCRIPT_ENABLE_SIGHASH_FORKID (bitcoin-cash).
     */
    , verify_flags_script_enable_sighash_forkid = (1U << 16)

    /**
     * SCRIPT_ENABLE_REPLAY_PROTECTION (bitcoin-cash).
     */
    , verify_flags_script_enable_replay_protection = (1U << 17)

    /**
     * SCRIPT_ENABLE_CHECKDATASIG (bitcoin-cash).
     */
    , verify_flags_script_enable_checkdatasig = (1U << 18)

    /**
     * SCRIPT_ENABLE_SCHNORR (bitcoin-cash).
     */
    , verify_flags_script_enable_schnorr = (1U << 19)

    /**
     * SCRIPT_ALLOW_SEGWIT_RECOVERY (bitcoin-cash).
     */
    , verify_flags_script_enable_segwit_recovery = (1U << 20)

#endif

} verify_flags;

/**
 * Verify that the transaction input correctly spends the previous output,
 * considering any additional constraints specified by flags.
 * @param[in]  transaction         The transaction with the script to verify.
 * @param[in]  transaction_size    The byte length of the transaction.
 * @param[in]  prevout_script      The script public key to verify against.
 * @param[in]  prevout_script_size The byte length of the script public key.
 * @param[in]  prevout_value       The value of the output being spent. Just for BTC and LTC, not for BCH
 * @param[in]  tx_input_index      The zero-based index of the transaction
 *                                 input with signature to be verified.
 * @param[in]  flags               Verification constraint flags.
 * @param[in]  amount              . Just for BCH, not for BTC nor LTC.
 * @returns                        A script verification result code.
 */

#ifdef KTH_CURRENCY_BCH
 BCK_API verify_result_type verify_script(const unsigned char* transaction,
    size_t transaction_size, const unsigned char* prevout_script,
    size_t prevout_script_size, unsigned int tx_input_index,
    unsigned int flags, int64_t amount = 0);
#else
 BCK_API verify_result_type verify_script(const unsigned char* transaction,
    size_t transaction_size, const unsigned char* prevout_script,
    size_t prevout_script_size, unsigned long long prevout_value,
    unsigned int tx_input_index, unsigned int flags);
#endif //KTH_CURRENCY_BCH


} // namespace consensus
} // namespace kth

#endif
