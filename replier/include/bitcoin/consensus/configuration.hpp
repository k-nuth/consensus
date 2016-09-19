
#ifndef LIBBITCOIN_CONSENSUS_CONFIGURATION_HPP
#define LIBBITCOIN_CONSENSUS_CONFIGURATION_HPP

#include <boost/filesystem.hpp>
#include <bitcoin/consensus/define.hpp>
#include <bitcoin/consensus/settings.hpp>

namespace libbitcoin {
namespace consensus {

// Not localizable.
#define BK_HELP_VARIABLE "help"
#define BK_SETTINGS_VARIABLE "settings"
#define BK_VERSION_VARIABLE "version"

// This must be lower case but the env var part can be any case.
#define BK_CONFIG_VARIABLE "config"

// This must match the case of the env var.
#define BK_ENVIRONMENT_VARIABLE_PREFIX "BK_"

/// Full node configuration, thread safe.
class BCK_API configuration
{
public:
    configuration(bc::settings context);
    configuration(const configuration& other);

    /// Options.
    bool help;
    bool settings;
    bool version;

    /// Options and environment vars.
    boost::filesystem::path file;

    /// Settings.
    consensus::settings consensus;
};

} // namespace consensus
} // namespace libbitcoin

#endif
