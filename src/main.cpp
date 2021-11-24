#include <seqan3/argument_parser/all.hpp>
#include "chron_downsampler.hpp"
#include "arg_parse.hpp"


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
    write_chrono_downsampled(fast_queue, cmd_args.minutes, std::string(cmd_args.fastq_file));
    return 0;
}
