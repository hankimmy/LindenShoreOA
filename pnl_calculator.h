#pragma once
#include <deque>
#include "trade.h"

struct Inventory {
    double price;
    int quantity;
};

class PnlCalculator {
public:
    PnlCalculator(const std::string& method);
    void processTrade(const std::unique_ptr<Trade> &trade);
private:
    std::unordered_map<std::string, std::deque<Inventory>> inventory_;
    std::string method_;

    double calcPnl(const std::unique_ptr<Trade> &trade, std::deque<Inventory> &inventory) const;
    static void printResult(const int timestamp, const std::string& symbol, const double pnl);
};
