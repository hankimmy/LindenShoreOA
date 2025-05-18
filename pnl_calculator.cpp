#include "pnl_calculator.h"

PnlCalculator::PnlCalculator(const std::string& method, std::ostream& out) : method_(method), out_(out) {
    out_ << "TIMESTAMP,SYMBOL,PNL\n";
}

void
PnlCalculator::processTrade(const std::unique_ptr<Trade> &trade) {
    std::deque<Inventory>& inventory = inventory_[trade->symbol];
    if (trade->side == 'B')
        inventory.push_back({trade->price, trade->quantity});
}