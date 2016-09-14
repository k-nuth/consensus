/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-consensus.
 *
 * libbitcoin-consensus is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
//#include "consensus/consensus.hpp"

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <bitcoin/consensus/define.hpp>
#include <bitcoin/consensus/export.hpp>
#include <bitcoin/consensus/version.hpp>
#include <bitcoin/protocol.hpp>
#include <bitcoin/protocol/consensus.pb.h>

using namespace libbitcoin::protocol;

namespace libbitcoin {
namespace consensus {

zmq::context context;
zmq::socket socket(context, zmq::socket::role::requester);

template <typename Reply>
static Reply send_request(
    const protocol::consensus::request& request, Reply& reply)
{
    static auto sc = socket.connect({ "tcp://localhost:5555" });

    // send message
    zmq::message message;
    message.enqueue(request.SerializeAsString());
    auto ec = socket.send(message);
    assert(!ec);

    // receive response
    zmq::message response;
    ec = socket.receive(response);
    assert(!ec);

    data_chunk payload;
    response.dequeue(payload);
    reply.ParseFromArray(payload.data(), payload.size());
    return reply;
}

// This function is published. The implementation exposes no satoshi internals.
verify_result_type verify_script(const unsigned char* transaction,
    size_t transaction_size, const unsigned char* prevout_script,
    size_t prevout_script_size, unsigned int tx_input_index,
    unsigned int flags)
{
    if (transaction_size > 0 && transaction == NULL)
        throw std::invalid_argument("transaction");

    if (prevout_script_size > 0 && prevout_script == NULL)
        throw std::invalid_argument("prevout_script");

    // send message
    protocol::consensus::request request;
    auto* verify_script = request.mutable_verify_script();
    verify_script->set_transaction(transaction, transaction_size);
    verify_script->set_prevout_script(prevout_script, prevout_script_size);
    verify_script->set_tx_input_index(tx_input_index);
    verify_script->set_flags(flags);

    protocol::consensus::verify_script_reply reply;
    send_request(request, reply);

    return static_cast<verify_result_type>(reply.result());
}

} // namespace consensus
} // namespace libbitcoin
