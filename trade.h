#pragma once
#include <string>
#include <sstream>
#include <memory>
#include <array>

struct Trade {
    int timestamp{};
    std::string symbol;
    char side{};
    double price{};
    int quantity{};

    static std::unique_ptr<Trade> makeTrade(const std::string& line) {
        std::istringstream ss(line);
        std::array<std::string, 5> tokens;
        std::string token;
        for (int i = 0; i < 5; ++i) {
            if (!std::getline(ss, token, ','))
                return nullptr;

            tokens[i] = token;
        }

        if (std::getline(ss, token, ','))
            return nullptr;

        try {
            auto trade = std::make_unique<Trade>();
            trade->timestamp = std::stoi(tokens[0]);
            trade->symbol = tokens[1];
            if (tokens[2].size() != 1 || (tokens[2][0] != 'B' && tokens[2][0] != 'S'))
                return nullptr;
            trade->side = tokens[2][0];
            trade->price = std::stod(tokens[3]);
            trade->quantity = std::stoi(tokens[4]);
            return trade;
        } catch (const std::exception&) {
            return nullptr;
        }
    }
};
