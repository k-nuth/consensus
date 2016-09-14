
#include <bitcoin/consensus.hpp>
#include <bitcoin/protocol.hpp>
#include <bitcoin/protocol/consensus.pb.h>

#define LOG_CONSENSUS "consensus"

using namespace libbitcoin::protocol;

namespace libbitcoin {
namespace consensus {

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

        protocol::consensus::request request;
        if (!message.dequeue(request))
            break;

        zmq::message reply = dispatch(request);
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
