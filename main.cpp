#include <iostream>
#include <fstream>
#include <string>

#include "pnl_calculator.h"
#include "trade.h"

void processFile(const std::string& inputFilePath, const std::string& method) {
    std::ifstream file(inputFilePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file " << inputFilePath << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line);

    PnlCalculator pnlCalculator(method);

    while (std::getline(file, line)) {
        if (line.empty())
            continue;
        if (auto trade = Trade::makeTrade(line))
            pnlCalculator.processTrade(trade);
        else
            std::cerr << "Error processing line " << line << std::endl;
    }

}

int main(const int argc, char* argv[]) {
    static std::string usage = "Usage: <input_file> <fifo|lifo>\n";
    if (argc != 3) {
        std::cerr << usage;
        return 1;
    }
    const std::string input = argv[1];
    const std::string method = argv[2];
    if (method != "fifo" && method != "lifo") {
        std::cerr << "Invalid method \n" << usage;
    }
    processFile(input, method);

    return 0;
}