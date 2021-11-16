//
// Created by Remy Schwab on 03.11.21.
//
#pragma once

#include <queue>
#include <sstream>
#include <seqan3/std/filesystem>
#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/core/debug_stream.hpp>
#include "date.h"


using record_type = typename decltype(seqan3::sequence_file_input {""})::record_type;
using rp = typename std::pair<std::string, record_type>;
using fastQueue = typename std::priority_queue<rp, std::vector<rp>, std::greater<rp>>;


fastQueue build_fast_queue(std::filesystem::path fastq_file);
void write_chrono_downsampled(fastQueue &fast_queue, uint32_t &minutes);
