#pragma once
#include <deque>
#include "trade.h"

struct Inventory {
    double price;
    int quantity;
};

class PnlCalculator {
public:
    PnlCalculator(const std::string& method, std::ostream& out);
    void processTrade(const std::unique_ptr<Trade> &trade);
private:
    std::unordered_map<std::string, std::deque<Inventory>> inventory_;
    std::string method_;
    std::ostream& out_;
};
