#include <sstream>
#include <seqan3/argument_parser/all.hpp>
#include "chron_downsampler.hpp"


struct cmd_arguments
{
    std::filesystem::path fastq_file{};
    int megabases;
    int minutes;
};

void initialise_argument_parser(seqan3::argument_parser & parser, cmd_arguments & args)
{
    // Parser
    parser.info.author = "Remy Schwab"; // give parser some infos
    parser.info.version = "1.0.0";

    parser.add_positional_option(fastq_file, "Please provide a fastq file.",
                                 seqan3::input_file_validator{{"fq","fastq"}});

    parser.add_option(args.megabases, 'mb', "megabases",
                      "Downsample to a specified number of Megabases");

    parser.add_option(args.minutes, 'w', "time-window",
                      "Specify a window of time to take reads from");
}

int main(int argc, char ** argv)
{
    seqan3::argument_parser parser{"Chronological-Downsampler", argc, argv};
    cmd_arguments cmd_args{};
    initialise_argument_parser(parser, cmd_args);

    try
    {
         parser.parse();                                                  // trigger command line parsing
    }
    catch (seqan3::argument_parser_error const & ext)                     // catch user errors
    {
        std::cerr << "Parsing error. " << ext.what() << "\n"; // give error message
        return -1;
    }

    return 0;
}
