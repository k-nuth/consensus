
#include <bitcoin/consensus/configuration.hpp>

#include <cstddef>

namespace libbitcoin {
namespace consensus {

// Construct with defaults derived from given context.
configuration::configuration(config::settings context)
  : help(false),
    settings(false),
    version(false),
    consensus(context)
{
}

// Copy constructor.
configuration::configuration(const configuration& other)
  : help(other.help),
    settings(other.settings),
    version(other.version),
    file(other.file),
    consensus(other.consensus)
{
}

} // namespace consensus
} // namespace libbitcoin
