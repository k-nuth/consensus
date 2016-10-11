
#include <bitcoin/consensus.hpp>
#include <bitcoin/consensus/configuration.hpp>
#include <bitcoin/consensus/parser.hpp>
#include <bitcoin/consensus/settings.hpp>
#include <bitcoin/protocol/consensus.pb.h>
#include <bitcoin/protocol/replier.hpp>
#include <bitcoin/protocol/zmq/context.hpp>
#include <bitcoin/protocol/zmq/message.hpp>
#include <bitcoin/protocol/zmq/socket.hpp>

#define LOG_CONSENSUS "consensus"

using namespace libbitcoin::protocol;

namespace libbitcoin {
namespace consensus {

static zmq::context context;
static replier replier_(context);

//! verify_result_type verify_script(const unsigned char* transaction,
//!   size_t transaction_size, const unsigned char* prevout_script,
//!   size_t prevout_script_size, unsigned int tx_input_index,
//!   unsigned int flags);
static protocol::consensus::verify_script_reply dispatch_verify_script(
    const protocol::consensus::verify_script_request& request)
{
    const unsigned char* transaction = reinterpret_cast<const unsigned char*>(request.transaction().data());
    const size_t transaction_size = request.transaction().size();
    const unsigned char* prevout_script = reinterpret_cast<const unsigned char*>(request.prevout_script().data());
    const size_t prevout_script_size = request.prevout_script().size();
    const unsigned int tx_input_index = request.tx_input_index();
    const unsigned int flags = request.flags();

    const verify_result_type result =
        verify_script(transaction, transaction_size, prevout_script, prevout_script_size, tx_input_index, flags);

    protocol::consensus::verify_script_reply reply;
    reply.set_result(result);
    return reply;
}

static zmq::message dispatch(
    const protocol::consensus::request& request)
{
    zmq::message reply;
    switch (request.request_type_case())
    {
    case protocol::consensus::request::kVerifyScript:
    {
        reply.enqueue_protobuf_message(
            dispatch_verify_script(request.verify_script()));
        break;
    }
    }
    return reply;
}

static int main(parser& metadata)
{
    auto ec = replier_.bind(metadata.configured.consensus.replier);
    assert(!ec);

    while (true)
    {
        protocol::consensus::request request;
        ec = replier_.receive(request);
        assert(!ec);

        zmq::message reply = dispatch(request);
        ec = replier_.send(reply);
        assert(!ec);
    }

    return 0;
}

} // namespace consensus
} // namespace libbitcoin

BC_USE_LIBBITCOIN_MAIN

int bc::main(int argc, char* argv[])
{
    set_utf8_stdio();
    consensus::parser metadata(bc::settings::mainnet);
    const auto& args = const_cast<const char**>(argv);

    if (!metadata.parse(argc, args, cerr))
        return console_result::failure;

    return consensus::main(metadata);
}
