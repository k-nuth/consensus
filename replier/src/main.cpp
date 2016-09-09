
#include <bitcoin/consensus.hpp>
#include <bitcoin/protocol.hpp>
#include <bitcoin/protocol/consensus.pb.h>

#define LOG_CONSENSUS "consensus"

using namespace libbitcoin::protocol;

namespace libbitcoin {
namespace consensus {

static Consensus_VerifyScriptReply dispatch_verify_script(
    const Consensus_VerifyScript& msg)
{
    const unsigned char* transaction = reinterpret_cast<const unsigned char*>(msg.transaction().data());
    const size_t transaction_size = msg.transaction().size();
    const unsigned char* prevout_script = reinterpret_cast<const unsigned char*>(msg.prevout_script().data());
    const size_t prevout_script_size = msg.prevout_script().size();
    const unsigned int tx_input_index = msg.tx_input_index();
    const unsigned int flags = msg.flags();

    const verify_result_type result =
        verify_script(transaction, transaction_size, prevout_script, prevout_script_size, tx_input_index, flags);

    Consensus_VerifyScriptReply reply;
    reply.set_result(result);
    return reply;
}

static zmq::message dispatch(const Consensus& msg)
{
    zmq::message reply;
    switch (msg.message_case())
    {
    case Consensus::kVerifyScript:
    {
        reply.enqueue_protobuf_message(
            dispatch_verify_script(msg.verify_script()));
        break;
    }
    }
    return reply;
}

static int main(int argc, char *argv[])
{
    zmq::context context;
    zmq::socket socket(context, zmq::socket::role::replier);
    auto ec = socket.bind({ "tcp://*:5555" });
    assert(!ec);

    while (true)
    {
        zmq::message message;
        ec = socket.receive(message);
        assert(!ec);

        Consensus consensus_message;
        if (!message.dequeue(consensus_message))
            break;

        zmq::message reply = dispatch(consensus_message);
        ec = socket.send(reply);
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
    return consensus::main(argc, argv);
}
