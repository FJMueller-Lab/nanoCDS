#include <sstream>
#include <seqan3/argument_parser/all.hpp>
#include "chron_downsampler.hpp"


struct cmd_arguments
{
    std::filesystem::path fastq_file{};
    uint32_t megabases{};
    uint32_t minutes{};
};

void initialise_argument_parser(seqan3::argument_parser & parser, cmd_arguments & args)
{
    // Parser
    parser.info.author = "Remy Schwab"; // give parser some infos
    parser.info.version = "1.0.0";

    parser.add_positional_option(args.fastq_file, "Please provide a fastq file.",
                                 seqan3::input_file_validator{{"fq","fastq"}});

    parser.add_option(args.megabases, 'm', "megabases",
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
         parser.parse();
    }
    catch (seqan3::argument_parser_error const & ext)
    {
        std::cerr << "Parsing error. " << ext.what() << "\n";
        return -1;
    }
    build_fast_queue(cmd_args.fastq_file);
    return 0;
}
