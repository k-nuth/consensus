
#include <bitcoin/consensus/parser.hpp>

#include <cstdint>
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/consensus/settings.hpp>

BC_DECLARE_CONFIG_DEFAULT_PATH("libbitcoin" / "bk.cfg")

// TODO: localize descriptions.

namespace libbitcoin {
namespace consensus {

using namespace boost::filesystem;
using namespace boost::program_options;
using namespace bc::config;

// Initialize configuration by copying the given instance.
parser::parser(const configuration& defaults)
  : configured(defaults)
{
}

// Initialize configuration using defaults of the given context.
parser::parser(const bc::settings& context)
  : configured(context)
{
    // Default endpoint for replier.
    configured.consensus.replier = { "tcp://*:5501" };
}

options_metadata parser::load_options()
{
    options_metadata description("options");
    description.add_options()
    (
        BK_CONFIG_VARIABLE ",c",
        value<path>(&configured.file),
        "Specify path to a configuration settings file."
    )
    (
        BK_HELP_VARIABLE ",h",
        value<bool>(&configured.help)->
            default_value(false)->zero_tokens(),
        "Display command line options."
    )
    (
        BK_SETTINGS_VARIABLE ",s",
        value<bool>(&configured.settings)->
            default_value(false)->zero_tokens(),
        "Display all configuration settings."
    )
    (
        BK_VERSION_VARIABLE ",v",
        value<bool>(&configured.version)->
            default_value(false)->zero_tokens(),
        "Display version information."
    );

    return description;
}

arguments_metadata parser::load_arguments()
{
    arguments_metadata description;
    return description
        .add(BK_CONFIG_VARIABLE, 1);
}

options_metadata parser::load_environment()
{
    options_metadata description("environment");
    description.add_options()
    (
        // For some reason po requires this to be a lower case name.
        // The case must match the other declarations for it to compose.
        // This composes with the cmdline options and inits to system path.
        BK_CONFIG_VARIABLE,
        value<path>(&configured.file)->composing()
            ->default_value(config_default_path()),
        "The path to the configuration settings file."
    );

    return description;
}

options_metadata parser::load_settings()
{
    options_metadata description("settings");
    description.add_options()
    /* [consensus] */
    (
        "consensus.replier",
        value<config::endpoint>(&configured.consensus.replier),
        "The endpoint for the replier."
    );

    return description;
}

bool parser::parse(int argc, const char* argv[], std::ostream& error)
{
    try
    {
        auto file = false;
        variables_map variables;
        load_command_variables(variables, argc, argv);
        load_environment_variables(variables, BK_ENVIRONMENT_VARIABLE_PREFIX);

        // Don't load the rest if any of these options are specified.
        if (!get_option(variables, BK_VERSION_VARIABLE) &&
            !get_option(variables, BK_SETTINGS_VARIABLE) &&
            !get_option(variables, BK_HELP_VARIABLE))
        {
            // Returns true if the settings were loaded from a file.
            file = load_configuration_variables(variables, BK_CONFIG_VARIABLE);
        }

        // Update bound variables in metadata.settings.
        notify(variables);

        // Clear the config file path if it wasn't used.
        if (!file)
            configured.file.clear();
    }
    catch (const boost::program_options::error& e)
    {
        // This is obtained from boost, which circumvents our localization.
        error << format_invalid_parameter(e.what()) << std::endl;
        return false;
    }

    return true;
}

} // namespace consensus
} // namespace libbitcoin
