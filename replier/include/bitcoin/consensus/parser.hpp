
#ifndef LIBBITCOIN_CONSENSUS_PARSER_HPP
#define LIBBITCOIN_CONSENSUS_PARSER_HPP

#include <ostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/consensus/define.hpp>
#include <bitcoin/consensus/configuration.hpp>

namespace libbitcoin {
namespace consensus {

/// Parse configurable values from environment variables, settings file, and
/// command line positional and non-positional options.
class BCK_API parser
  : public config::parser
{
public:
    parser(const config::settings& context);
    parser(const configuration& defaults);

    /// Parse all configuration into member settings.
    virtual bool parse(int argc, const char* argv[], std::ostream& error);

    /// Load command line options (named).
    virtual options_metadata load_options();

    /// Load command line arguments (positional).
    virtual arguments_metadata load_arguments();

    /// Load configuration file settings.
    virtual options_metadata load_settings();

    /// Load environment variable settings.
    virtual options_metadata load_environment();

    /// The populated configuration settings values.
    configuration configured;
};

} // namespace consensus
} // namespace libbitcoin

#endif
