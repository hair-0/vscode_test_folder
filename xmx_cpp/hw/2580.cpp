#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

int main() {
    std::ifstream inputFile("input.csv");
    std::vector<std::vector<int>> columns;
    std::string line;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            if (line.empty()) continue;
            if (line.back() == '\r') line.pop_back();

            std::stringstream ss(line);
            std::string valueStr;
            size_t colIndex = 0;

            while (std::getline(ss, valueStr, ',')) {
                if (colIndex >= columns.size()) {
                    columns.resize(colIndex + 1);
                }
                if (!valueStr.empty()) {
                    columns[colIndex].push_back(std::stoi(valueStr));
                }
                colIndex++;
            }
        }
        inputFile.close();
    }

    std::ofstream outputFile("output.csv");
    outputFile << std::fixed << std::setprecision(2);

    for (size_t i = 0; i < columns.size(); ++i) {
        std::vector<int>& scores = columns[i];
        if (scores.empty()) continue;

        std::sort(scores.begin(), scores.end());

        double n = static_cast<double>(scores.size());
        double sum = 0.0;
        for (int score : scores) {
            sum += score;
        }
        double mean = sum / n;

        double median = 0.0;
        if (scores.size() % 2 != 0) {
            median = static_cast<double>(scores[scores.size() / 2]);
        } else {
            median = (scores[scores.size() / 2 - 1] + scores[scores.size() / 2]) / 2.0;
        }

        double maxVal = static_cast<double>(scores.back());
        double minVal = static_cast<double>(scores.front());

        double varianceSum = 0.0;
        for (int score : scores) {
            varianceSum += (score - mean) * (score - mean);
        }
        double variance = varianceSum / n;

        if (i > 0) {
            outputFile << "\n";
        }
        outputFile << mean << "," 
                   << median << "," 
                   << maxVal << "," 
                   << minVal << "," 
                   << variance;
    }

    outputFile.close();
    return 0;
}