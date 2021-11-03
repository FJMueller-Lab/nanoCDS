//
// Created by Remy Schwab on 03.11.21.
//

#ifndef NANOCDS_CHRON_DOWNSAMPLER_HPP
#define NANOCDS_CHRON_DOWNSAMPLER_HPP
#endif //NANOCDS_CHRON_DOWNSAMPLER_HPP

#pragma once

#include <seqan3/std/filesystem>

void cycle_fastq(std::filesystem::path fastq_file, std::filesystem::path out);
