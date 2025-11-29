//http://166.111.236.164:6080/tyche/#!html/Problem.html&gid=36&tid=1383&pid=2593&isOOP=false
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <cmath>

struct WAVHeader {
    char riff[4];
    uint32_t size;
    char wave[4];

    char fmt[4];
    uint32_t fmt_size;
    uint16_t audio_fmt;
    uint16_t channels;
    uint32_t sample_rate;
    uint32_t byte_rate;
    uint16_t block_align;
    uint16_t bits_per_sample;

    char data[4];
    uint32_t data_size;
};

using SampleType = int16_t;

void op_cut(std::vector<SampleType>& samples);
void op_center_clip(std::vector<SampleType>& samples);
void op_force_mute(std::vector<SampleType>& samples);
void op_invert_segment(std::vector<SampleType>& samples);
void op_clipping(std::vector<SampleType>& samples);
void op_add_noise(std::vector<SampleType>& samples);

std::pair<std::vector<SampleType>::iterator, std::vector<SampleType>::iterator> get_safe_range(
    std::vector<SampleType>& samples, int start_index, int end_index) {
    
    size_t start = std::max(0, start_index);
    size_t end = std::min((int)samples.size() - 1, end_index); 

    if (start >= samples.size()) {
        return {samples.end(), samples.end()};
    }
    
    if (start > end) {
        return {samples.end(), samples.end()};
    }

    return {samples.begin() + start, samples.begin() + end + 1};
}

void op_cut(std::vector<SampleType>& samples) {
    auto range = get_safe_range(samples, 1000, 3000);
    auto start_it = range.first;
    auto end_it = range.second;

    if (start_it != samples.end()) {
        samples.erase(start_it, end_it);
    }
}

void op_center_clip(std::vector<SampleType>& samples) {
    auto new_end = std::remove_if(samples.begin(), samples.end(), 
        [](SampleType s) {
            return s >= -800 && s <= 800;
        });

    samples.erase(new_end, samples.end());
}

void op_force_mute(std::vector<SampleType>& samples) {
    auto range = get_safe_range(samples, 2000, 4000);
    auto start_it = range.first;
    auto end_it = range.second;
    
    if (start_it != samples.end()) {
        std::fill(start_it, end_it, 0);
    }
}

void op_invert_segment(std::vector<SampleType>& samples) {
    auto range = get_safe_range(samples, 500, 2500);
    auto start_it = range.first;
    auto end_it = range.second;

    if (start_it != samples.end()) {
        std::reverse(start_it, end_it);
    }
}

void op_clipping(std::vector<SampleType>& samples) {
    const SampleType upper_clip = 1000;
    const SampleType lower_clip = -1000;

    for (SampleType& s : samples) {
        if (s > upper_clip) {
            s = upper_clip;
        } else if (s < lower_clip) {
            s = lower_clip;
        }
    }
}

void op_add_noise(std::vector<SampleType>& samples) {
    const int amplitude = 1000;
    const int period = 2 * amplitude; 

    for (size_t i = 0; i < samples.size(); ++i) {
        int index_in_period = i % period;
        SampleType noise_val;
        
        if (index_in_period <= amplitude) {
            noise_val = amplitude - index_in_period;
        } else {
            noise_val = index_in_period - amplitude;
        }
        
        long sum = (long)samples[i] + noise_val;
        
        if (sum > 32767) {
            samples[i] = 32767;
        } else if (sum < -32768) {
            samples[i] = -32768;
        } else {
            samples[i] = (SampleType)sum;
        }
    }
}

bool process_wav(const std::string& input_filename, const std::string& output_filename) {
    std::ifstream input_file(input_filename, std::ios::binary);
    if (!input_file.is_open()) {
        std::cerr << "Error" << input_filename << std::endl;
        return false;
    }

    WAVHeader header;
    input_file.read(reinterpret_cast<char*>(&header), sizeof(WAVHeader));

    if (std::string(header.riff, 4) != "RIFF" || std::string(header.wave, 4) != "WAVE") {
        std::cerr << "Error: Not a valid RIFF/WAVE file." << std::endl;
        return false;
    }

    uint32_t num_samples = header.data_size / sizeof(SampleType);

    std::vector<SampleType> samples(num_samples);
    input_file.read(reinterpret_cast<char*>(samples.data()), header.data_size);
    input_file.close();

    int operation_code = num_samples % 6;

    switch (operation_code) {
        case 0: op_cut(samples); break;
        case 1: op_center_clip(samples); break;
        case 2: op_force_mute(samples); break;
        case 3: op_invert_segment(samples); break;
        case 4: op_clipping(samples); break;
        case 5: op_add_noise(samples); break;
        default: return false;
    }

    uint32_t new_num_samples = samples.size();
    header.data_size = new_num_samples * sizeof(SampleType);
    header.size = 4 + (8 + 16) + (8 + header.data_size);

    std::ofstream output_file(output_filename, std::ios::binary);
    if (!output_file.is_open()) {
        std::cerr << "Error: Cannot open output file " << output_filename << std::endl;
        return false;
    }

    output_file.write(reinterpret_cast<const char*>(&header), sizeof(WAVHeader));
    output_file.write(reinterpret_cast<const char*>(samples.data()), header.data_size);
    output_file.close();

    return true;
}

int main() {
    const std::string input_file = "input.wav";
    const std::string output_file = "output.wav";
    
    if (process_wav(input_file, output_file)) {
        return 0;
    } else {
        return 1;
    }
}