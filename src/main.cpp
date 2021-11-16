#include <seqan3/argument_parser/all.hpp>
#include "chron_downsampler.hpp"


struct cmd_arguments
{
    std::filesystem::path fastq_file{};
    uint32_t minutes{};
};


void initialise_argument_parser(seqan3::argument_parser & parser, cmd_arguments & args)
{
    // Parser
    parser.info.author = "Remy Schwab"; // give parser some infos
    parser.info.version = "1.0.0";

    parser.add_positional_option(args.fastq_file, "Please provide a fastq file.",
                                 seqan3::input_file_validator{{"fq","fastq"}});

    parser.add_option(args.minutes, 'm', "minutes",
                      "Specify an amount of time you'd like to sample from [in minutes]");
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
    fastQueue fast_queue = build_fast_queue(cmd_args.fastq_file);
    write_chrono_downsampled(fast_queue, cmd_args.minutes);
    return 0;
}
