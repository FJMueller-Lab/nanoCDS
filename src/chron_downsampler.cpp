//
// Created by Remy Schwab on 03.11.21.
//
#include "chron_downsampler.hpp"
#include <queue>
#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/core/debug_stream.hpp>


std::string extract_start_time(std::string & record_id)
{
    std::istringstream ss(record_id);
    std::string word;
    std::vector<std::string> words{};
    while (ss >> word)
    {
        words.push_back(word);
    }
    std::string timestamp = words[5];
    return timestamp.substr(11,20);
}


void build_fast_queue(std::filesystem::path fastq_file)
{
    seqan3::sequence_file_input fin{fastq_file};

    using record_type = typename decltype(fin)::record_type;
    typedef std::pair<std::string, record_type> rp;

    std::priority_queue<rp, std::vector<rp>, std::greater<rp>> fast_queue;
    std::string record_start;
    seqan3::debug_stream << "Reading records and building priority queue: ";
    for(auto record : fin)
    {
        record_start = extract_start_time(record.id());
        fast_queue.push(std::make_pair(record_start, record));
    }
    seqan3::debug_stream << "DONE" << std::endl;
    rp queue_top = fast_queue.top();
    std::string run_start_time = queue_top.first;
}
