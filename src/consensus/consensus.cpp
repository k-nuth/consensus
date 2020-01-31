// Copyright (c) 2016-2020 Knuth Project developers.
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "consensus/consensus.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string.h>
#include <kth/consensus/define.hpp>
#include <kth/consensus/export.hpp>
#include <kth/consensus/version.hpp>
#include "primitives/transaction.h"
#include "pubkey.h"
#include "script/interpreter.h"
#include "script/script_error.h"
#include "version.h"

namespace kth {
namespace consensus {

// Initialize libsecp256k1 context.
static auto secp256k1_context = ECCVerifyHandle();

// Helper class, not published. This is tested internal to verify_script.
class transaction_istream
{
public:
    template<typename Type>
    transaction_istream& operator>>(Type& instance)
    {
        ::Unserialize(*this, instance);
        return *this;
    }

    transaction_istream(uint8_t const* transaction, size_t size)
      : source_(transaction), remaining_(size)
    {
    }

    void read(char* destination, size_t size)
    {
        if (size > remaining_)
            throw std::ios_base::failure("end of data");

        memcpy(destination, source_, size);
        remaining_ -= size;
        source_ += size;
    }

    int GetType() const
    {
        return SER_NETWORK;
    }

    int GetVersion() const
    {
        return PROTOCOL_VERSION;
    }

private:
    size_t remaining_;
    uint8_t const* source_;
};

// This mapping decouples the consensus API from the satoshi implementation
// files. We prefer to keep our copies of consensus files isomorphic.
// This function is not published (but non-static for testability).

#if defined(KTH_CURRENCY_BCH)
verify_result_type script_error_to_verify_result(ScriptError code) {
    switch (code)
    {
        // Logical result
        case ScriptError::OK:
            return verify_result_eval_true;
        case ScriptError::EVAL_FALSE:
            return verify_result_eval_false;

        // Max size errors
        case ScriptError::SCRIPT_SIZE:
            return verify_result_script_size;
        case ScriptError::PUSH_SIZE:
            return verify_result_push_size;
        case ScriptError::OP_COUNT:
            return verify_result_op_count;
        case ScriptError::STACK_SIZE:
            return verify_result_stack_size;
        case ScriptError::SIG_COUNT:
            return verify_result_sig_count;
        case ScriptError::PUBKEY_COUNT:
            return verify_result_pubkey_count;

        // Failed verify operations
        case ScriptError::VERIFY:
            return verify_result_verify;
        case ScriptError::EQUALVERIFY:
            return verify_result_equalverify;
        case ScriptError::CHECKMULTISIGVERIFY:
            return verify_result_checkmultisigverify;
        case ScriptError::CHECKSIGVERIFY:
            return verify_result_checksigverify;
        case ScriptError::NUMEQUALVERIFY:
            return verify_result_numequalverify;

        // Logical/Format/Canonical errors
        case ScriptError::BAD_OPCODE:
            return verify_result_bad_opcode;
        case ScriptError::DISABLED_OPCODE:
            return verify_result_disabled_opcode;
        case ScriptError::INVALID_STACK_OPERATION:
            return verify_result_invalid_stack_operation;
        case ScriptError::INVALID_ALTSTACK_OPERATION:
            return verify_result_invalid_altstack_operation;
        case ScriptError::UNBALANCED_CONDITIONAL:
            return verify_result_unbalanced_conditional;

        // BIP65/BIP112 (shared codes)
        case ScriptError::NEGATIVE_LOCKTIME:
            return verify_result_negative_locktime;
        case ScriptError::UNSATISFIED_LOCKTIME:
            return verify_result_unsatisfied_locktime;

        // BIP62
        case ScriptError::SIG_HASHTYPE:
            return verify_result_sig_hashtype;
        case ScriptError::SIG_DER:
            return verify_result_sig_der;
        case ScriptError::MINIMALDATA:
            return verify_result_minimaldata;
        case ScriptError::SIG_PUSHONLY:
            return verify_result_sig_pushonly;
        case ScriptError::SIG_HIGH_S:
            return verify_result_sig_high_s;
        case ScriptError::PUBKEYTYPE:
            return verify_result_pubkeytype;
        case ScriptError::CLEANSTACK:
            return verify_result_cleanstack;
        case ScriptError::MINIMALIF:
            return verify_result_minimalif;
        case ScriptError::SIG_NULLFAIL:
            return verify_result_sig_nullfail;

        // Softfork safeness
        case ScriptError::DISCOURAGE_UPGRADABLE_NOPS:
            return verify_result_discourage_upgradable_nops;

        // Other
        case ScriptError::OP_RETURN:
            return verify_result_op_return;
        case ScriptError::UNKNOWN:
        case ScriptError::ERROR_COUNT:
        default:
            return verify_result_unknown_error;
    }
}
#else
verify_result_type script_error_to_verify_result(ScriptError_t code) {
    switch (code)
    {
        // Logical result
        case SCRIPT_ERR_OK:
            return verify_result_eval_true;
        case SCRIPT_ERR_EVAL_FALSE:
            return verify_result_eval_false;

        // Max size errors
        case SCRIPT_ERR_SCRIPT_SIZE:
            return verify_result_script_size;
        case SCRIPT_ERR_PUSH_SIZE:
            return verify_result_push_size;
        case SCRIPT_ERR_OP_COUNT:
            return verify_result_op_count;
        case SCRIPT_ERR_STACK_SIZE:
            return verify_result_stack_size;
        case SCRIPT_ERR_SIG_COUNT:
            return verify_result_sig_count;
        case SCRIPT_ERR_PUBKEY_COUNT:
            return verify_result_pubkey_count;

        // Failed verify operations
        case SCRIPT_ERR_VERIFY:
            return verify_result_verify;
        case SCRIPT_ERR_EQUALVERIFY:
            return verify_result_equalverify;
        case SCRIPT_ERR_CHECKMULTISIGVERIFY:
            return verify_result_checkmultisigverify;
        case SCRIPT_ERR_CHECKSIGVERIFY:
            return verify_result_checksigverify;
        case SCRIPT_ERR_NUMEQUALVERIFY:
            return verify_result_numequalverify;

        // Logical/Format/Canonical errors
        case SCRIPT_ERR_BAD_OPCODE:
            return verify_result_bad_opcode;
        case SCRIPT_ERR_DISABLED_OPCODE:
            return verify_result_disabled_opcode;
        case SCRIPT_ERR_INVALID_STACK_OPERATION:
            return verify_result_invalid_stack_operation;
        case SCRIPT_ERR_INVALID_ALTSTACK_OPERATION:
            return verify_result_invalid_altstack_operation;
        case SCRIPT_ERR_UNBALANCED_CONDITIONAL:
            return verify_result_unbalanced_conditional;

        // BIP65/BIP112 (shared codes)
        case SCRIPT_ERR_NEGATIVE_LOCKTIME:
            return verify_result_negative_locktime;
        case SCRIPT_ERR_UNSATISFIED_LOCKTIME:
            return verify_result_unsatisfied_locktime;

        // BIP62
        case SCRIPT_ERR_SIG_HASHTYPE:
            return verify_result_sig_hashtype;
        case SCRIPT_ERR_SIG_DER:
            return verify_result_sig_der;
        case SCRIPT_ERR_MINIMALDATA:
            return verify_result_minimaldata;
        case SCRIPT_ERR_SIG_PUSHONLY:
            return verify_result_sig_pushonly;
        case SCRIPT_ERR_SIG_HIGH_S:
            return verify_result_sig_high_s;
        case SCRIPT_ERR_SIG_NULLDUMMY:
            return verify_result_sig_nulldummy;
        case SCRIPT_ERR_PUBKEYTYPE:
            return verify_result_pubkeytype;
        case SCRIPT_ERR_CLEANSTACK:
            return verify_result_cleanstack;
        case SCRIPT_ERR_MINIMALIF:
            return verify_result_minimalif;
        case SCRIPT_ERR_SIG_NULLFAIL:
            return verify_result_sig_nullfail;

        // Softfork safeness
        case SCRIPT_ERR_DISCOURAGE_UPGRADABLE_NOPS:
            return verify_result_discourage_upgradable_nops;

// #if ! defined(KTH_CURRENCY_BCH)
        // Softfork safeness
        case SCRIPT_ERR_DISCOURAGE_UPGRADABLE_WITNESS_PROGRAM:
            return verify_result_discourage_upgradable_witness_program;

        // Segregated witness
        case SCRIPT_ERR_WITNESS_PROGRAM_WRONG_LENGTH:
            return verify_result_witness_program_wrong_length;
        case SCRIPT_ERR_WITNESS_PROGRAM_WITNESS_EMPTY:
            return verify_result_witness_program_empty_witness;
        case SCRIPT_ERR_WITNESS_PROGRAM_MISMATCH:
            return verify_result_witness_program_mismatch;
        case SCRIPT_ERR_WITNESS_MALLEATED:
            return verify_result_witness_malleated;
        case SCRIPT_ERR_WITNESS_MALLEATED_P2SH:
            return verify_result_witness_malleated_p2sh;
        case SCRIPT_ERR_WITNESS_UNEXPECTED:
            return verify_result_witness_unexpected;
        case SCRIPT_ERR_WITNESS_PUBKEYTYPE:
            return verify_result_witness_pubkeytype;
// #endif //! defined(KTH_CURRENCY_BCH)

        // Other
        case SCRIPT_ERR_OP_RETURN:
            return verify_result_op_return;
        case SCRIPT_ERR_UNKNOWN_ERROR:
        case SCRIPT_ERR_ERROR_COUNT:
        default:
            return verify_result_unknown_error;
    }
}
#endif

// This mapping decouples the consensus API from the satoshi implementation
// files. We prefer to keep our copies of consensus files isomorphic.
// This function is not published (but non-static for testability).
unsigned int verify_flags_to_script_flags(unsigned int flags) {
    unsigned int script_flags = SCRIPT_VERIFY_NONE;

    if ((flags & verify_flags_p2sh) != 0)
        script_flags |= SCRIPT_VERIFY_P2SH;
    if ((flags & verify_flags_strictenc) != 0)
        script_flags |= SCRIPT_VERIFY_STRICTENC;
    if ((flags & verify_flags_dersig) != 0)
        script_flags |= SCRIPT_VERIFY_DERSIG;
    if ((flags & verify_flags_low_s) != 0)
        script_flags |= SCRIPT_VERIFY_LOW_S;

#if ! defined(KTH_CURRENCY_BCH)        
    if ((flags & verify_flags_nulldummy) != 0)
        script_flags |= SCRIPT_VERIFY_NULLDUMMY;
#endif

    if ((flags & verify_flags_sigpushonly) != 0)
        script_flags |= SCRIPT_VERIFY_SIGPUSHONLY;
    if ((flags & verify_flags_minimaldata) != 0)
        script_flags |= SCRIPT_VERIFY_MINIMALDATA;
    if ((flags & verify_flags_discourage_upgradable_nops) != 0)
        script_flags |= SCRIPT_VERIFY_DISCOURAGE_UPGRADABLE_NOPS;
    if ((flags & verify_flags_cleanstack) != 0)
        script_flags |= SCRIPT_VERIFY_CLEANSTACK;
    if ((flags & verify_flags_checklocktimeverify) != 0)
        script_flags |= SCRIPT_VERIFY_CHECKLOCKTIMEVERIFY;
    if ((flags & verify_flags_checksequenceverify) != 0)
        script_flags |= SCRIPT_VERIFY_CHECKSEQUENCEVERIFY;

#if ! defined(KTH_CURRENCY_BCH)
    if ((flags & verify_flags_witness) != 0)
        script_flags |= SCRIPT_VERIFY_WITNESS;
    if ((flags & verify_flags_discourage_upgradable_witness_program) != 0)
        script_flags |= SCRIPT_VERIFY_DISCOURAGE_UPGRADABLE_WITNESS_PROGRAM;
    if ((flags & verify_flags_minimal_if) != 0)
        script_flags |= SCRIPT_VERIFY_MINIMALIF;
    if ((flags & verify_flags_null_fail) != 0)
        script_flags |= SCRIPT_VERIFY_NULLFAIL;
    if ((flags & verify_flags_witness_public_key_compressed) != 0)
        script_flags |= SCRIPT_VERIFY_WITNESS_PUBKEYTYPE;

    if ((flags & verify_flags_const_scriptcode) != 0)
        script_flags |= SCRIPT_VERIFY_CONST_SCRIPTCODE;
#endif //! defined(KTH_CURRENCY_BCH)

#if defined(KTH_CURRENCY_BCH)

    if ((flags & verify_flags_script_verify_compressed_pubkeytype) != 0)
        script_flags |= SCRIPT_VERIFY_COMPRESSED_PUBKEYTYPE;

    if ((flags & verify_flags_script_enable_sighash_forkid) != 0)
        script_flags |= SCRIPT_ENABLE_SIGHASH_FORKID;

    if ((flags & verify_flags_script_enable_replay_protection) != 0)
        script_flags |= SCRIPT_ENABLE_REPLAY_PROTECTION;

    if ((flags & verify_flags_script_enable_checkdatasig_sigops) != 0)
        script_flags |= SCRIPT_VERIFY_CHECKDATASIG_SIGOPS;

    if ((flags & verify_flags_script_disallow_segwit_recovery) != 0)
        script_flags |= SCRIPT_DISALLOW_SEGWIT_RECOVERY;

    if ((flags & verify_flags_script_script_enable_schnorr_multisig) != 0)
        script_flags |= SCRIPT_ENABLE_SCHNORR_MULTISIG;

    if ((flags & verify_flags_script_verify_input_sigchecks) != 0)
        script_flags |= SCRIPT_VERIFY_INPUT_SIGCHECKS;

    if ((flags & verify_flags_script_report_sigchecks) != 0)
        script_flags |= SCRIPT_REPORT_SIGCHECKS;
#endif

    return script_flags;
}

// This function is published. The implementation exposes no satoshi internals.

#if defined(KTH_CURRENCY_BCH)
verify_result_type verify_script(const unsigned char* transaction,
    size_t transaction_size, const unsigned char* prevout_script,
    size_t prevout_script_size, unsigned int tx_input_index,
    unsigned int flags, int64_t amount /* = 0 */)
{
    if (amount > INT64_MAX)
        throw std::invalid_argument("value");

    if (transaction_size > 0 && transaction == NULL)
        throw std::invalid_argument("transaction");

    if (prevout_script_size > 0 && prevout_script == NULL)
        throw std::invalid_argument("prevout_script");

    std::shared_ptr<CTransaction> tx;

    try
    {
        transaction_istream stream(transaction, transaction_size);
        tx = std::make_shared<CTransaction>(deserialize, stream);
    }
    catch (const std::exception&)
    {
        return verify_result_tx_invalid;
    }

    if (tx_input_index >= tx->vin.size())
        return verify_result_tx_input_invalid;

    if (GetSerializeSize(*tx, PROTOCOL_VERSION) != transaction_size)
        return verify_result_tx_size_invalid;

    ScriptError error;
    auto const& tx_ref = *tx;
    Amount am(amount);
    TransactionSignatureChecker checker(&tx_ref, tx_input_index, am);
    const unsigned int script_flags = verify_flags_to_script_flags(flags);

    CScript output_script(prevout_script, prevout_script + prevout_script_size);
    auto const& input_script = tx->vin[tx_input_index].scriptSig;

    // See blockchain : validate.cpp :
    // if (!output_script.run(input.script, current_tx, input_index, flags))...
    // const CScriptWitness* witness = nullptr;
    
    // VerifyScript(input_script, output_script, witness, script_flags, checker, &error);
    VerifyScript(input_script, output_script, script_flags, checker, &error);

    return script_error_to_verify_result(error);
}
#else //KTH_CURRENCY_BCH

verify_result_type verify_script(const unsigned char* transaction,
    size_t transaction_size, const unsigned char* prevout_script,
    size_t prevout_script_size, unsigned long long prevout_value,
    unsigned int tx_input_index, unsigned int flags)
{
    if (prevout_value > INT64_MAX)
        throw std::invalid_argument("value");

    if (transaction_size > 0 && transaction == NULL)
        throw std::invalid_argument("transaction");

    if (prevout_script_size > 0 && prevout_script == NULL)
        throw std::invalid_argument("prevout_script");

    std::shared_ptr<CTransaction> tx;

    try
    {
        transaction_istream stream(transaction, transaction_size);
        tx = std::make_shared<CTransaction>(deserialize, stream);
    }
    catch (const std::exception&)
    {
        return verify_result_tx_invalid;
    }

    if (tx_input_index >= tx->vin.size())
        return verify_result_tx_input_invalid;

    if (GetSerializeSize(*tx, PROTOCOL_VERSION) != transaction_size)
        return verify_result_tx_size_invalid;

    ScriptError_t error;
    auto const& tx_ref = *tx;
    const CAmount amount(static_cast<int64_t>(prevout_value));
    TransactionSignatureChecker checker(&tx_ref, tx_input_index, amount);
    const unsigned int script_flags = verify_flags_to_script_flags(flags);
    CScript output_script(prevout_script, prevout_script + prevout_script_size);
    auto const& input_script = tx->vin[tx_input_index].scriptSig;
    auto const witness_stack = &tx->vin[tx_input_index].scriptWitness;

    // See blockchain : validate_input.cpp :
    // bc::blockchain::validate_input::verify_script(const transaction& tx,
    //     uint32_t input_index, uint32_t forks, bool use_libconsensus)...
    VerifyScript(input_script, output_script, witness_stack, script_flags,
        checker, &error);

    return script_error_to_verify_result(error);
}
#endif //KTH_CURRENCY_BCH

char const* version() {
    return KTH_CONSENSUS_VERSION;
}

} // namespace consensus
} // namespace kth
