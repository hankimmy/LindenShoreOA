#include <iostream>
#include <fstream>
#include <string>

#include "pnl_calculator.h"
#include "trade.h"

std::string createOutputFileName(const std::string& inputFilePath) {
    if (inputFilePath.size() >= 4 && inputFilePath.substr(inputFilePath.size() - 4) == ".csv") {
        return inputFilePath.substr(0, inputFilePath.size() - 4) + "_pnl.csv";
    } else {
        return inputFilePath + "_pnl.csv";
    }
}

void processFile(const std::string& inputFilePath, const std::string& method, std::ostream& out) {
    std::ifstream file(inputFilePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << inputFilePath << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);

    PnlCalculator pnlCalculator(method, out);

    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        if (auto trade = Trade::makeTrade(line))
            pnlCalculator.processTrade(trade);
        else
            std::cerr << "Error processing line " << line << std::endl;
    }

}

int main(int argc, char* argv[]) {
    static std::string usage = "Usage: <input_file> <fifo|lifo>\n";
    if (argc != 3) {
        std::cerr << usage;
        return 1;
    }
    std::string input = argv[1];
    std::string method = argv[2];
    if (method != "fifo" && method != "lifo") {
        std::cerr << "Invalid method \n" << usage;
    }
    std::string outputFilePath = createOutputFileName(input);
    std::ofstream output(outputFilePath);
    if (!output.is_open()) {
        std::cerr << "Error opening output file " << outputFilePath << "\n";
        return 1;
    }
    processFile(input, method, output);
    output.close();

    std::cout << "Pnl Results: " << outputFilePath << std::endl;

    return 0;
}