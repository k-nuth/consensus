
#ifndef LIBBITCOIN_CONSENSUS_REPLIER_SETTINGS_HPP
#define LIBBITCOIN_CONSENSUS_REPLIER_SETTINGS_HPP

#include <cstdint>
#include <bitcoin/bitcoin/config/endpoint.hpp>
#include <bitcoin/bitcoin/config/settings.hpp>
#include <bitcoin/bitcoin/constants.hpp>
#include <bitcoin/consensus/define.hpp>

namespace libbitcoin {
namespace consensus {

/// Common consensus configuration settings, properties not thread safe.
class BCK_API settings
{
public:
    settings();
    settings(config::settings context);

    /// Properties.
    config::endpoint replier;
};

} // namespace consensus
} // namespace libbitcoin

#endif
