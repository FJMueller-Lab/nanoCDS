//
// Created by Remy Schwab on 03.11.21.
// https://www.biostars.org/p/337503/
//
#include "chron_downsampler.hpp"


date::sys_time<std::chrono::seconds> parse8601(std::string is)
{
    std::istringstream in{is};
    date::sys_time<std::chrono::seconds> tp;
    in >> date::parse("%FT%TZ", tp);
    return tp;
}


std::string remove_extension(std::string in_file_name)
{
    size_t lastindex = in_file_name.find_last_of(".");
    return in_file_name.substr(0, lastindex);
}


std::pair<std::string, std::string> compute_stop_time(fastQueue &fast_queue, uint32_t &minutes)
{
    using namespace date;
    // Determine what time the first read was sequenced
    rp queue_top = fast_queue.top();
    std::string run_start_time = queue_top.first;
    seqan3::debug_stream << "First read detected at: " << run_start_time;
    // Add user-specified time interval
    date::sys_time<std::chrono::seconds> down_stop_tp = parse8601(run_start_time);
    down_stop_tp += std::chrono::minutes(minutes);
    // Reformat stop time as string
    std::string stop_time = format("%FT%TZ", down_stop_tp);
    seqan3::debug_stream << " --> Sampling reads until: " << stop_time << std::endl;
    return std::make_pair(run_start_time, stop_time);
}


std::string extract_read_time(std::string &record_id)
{
    std::istringstream ss(record_id);
    std::string word;
    while (ss >> word)
    {
        if(word.rfind("start", 0) == 0) {
            break;
        }
    }
    return word.substr(11,20);
}


fastQueue build_fast_queue(std::filesystem::path fastq_file)
{
    seqan3::sequence_file_input fin{fastq_file};
    // Read FASTQ records onto priority queue
    std::priority_queue<rp, std::vector<rp>, std::greater<rp>> fast_queue;
    std::string record_start;
    seqan3::debug_stream << "Reading records and building priority queue... ";
    for(auto record : fin)
    {
        record_start = extract_read_time(record.id());
        fast_queue.push(std::make_pair(record_start, record));
    }
    seqan3::debug_stream << "DONE" << std::endl;
    return fast_queue;
}


void write_chrono_downsampled(fastQueue &fast_queue, uint32_t &minutes, std::string infile)
{
    // File stuff
    std::filesystem::path current_path = std::filesystem::current_path();
    std::string ofile = remove_extension(infile)+"_CDS.fastq";
    seqan3::sequence_file_output fout{current_path / ofile};
    // Get Start/Stop info
    std::pair<std::string, std::string> start_stop = compute_stop_time(fast_queue, minutes);
    std::string start_ts = start_stop.first, stop_ts = start_stop.second;
    // Start writing
    while(fast_queue.top().first < stop_ts) {
        fout.push_back(fast_queue.top().second);
        fast_queue.pop();
    }
}
