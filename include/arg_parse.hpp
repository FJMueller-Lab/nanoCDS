//
// Created by Remy Schwab on 24.11.21.
//
#pragma once

struct cmd_arguments
{
    std::filesystem::path fastq_file{};
    uint32_t minutes{};
    uint32_t megabases{};
};

inline void initialise_argument_parser(seqan3::argument_parser & parser, cmd_arguments & args)
{
    // Parser
    parser.info.author = "Remy Schwab"; // give parser some infos
    parser.info.version = "1.0.0";

    parser.add_positional_option(args.fastq_file, "Please provide a fastq file.",
                                 seqan3::input_file_validator{{"fq","fastq"}});

    parser.add_option(args.minutes, 'm', "minutes",
                      "Specify an amount of time you'd like to sample from [in minutes]");
    parser.add_option(args.megabases, 'b', "megabases",
                      "Specify the amount of DNA [in megabases] you would like to sample");
}
