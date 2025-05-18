#include "pnl_calculator.h"

#include <iomanip>
#include <iostream>

PnlCalculator::PnlCalculator(const std::string& method) : method_(method) {
    std::cout << "TIMESTAMP,SYMBOL,PNL\n";
}

void PnlCalculator::processTrade(const std::unique_ptr<Trade> &trade) {
    std::deque<Inventory>& inventory = inventory_[trade->symbol];
    if (trade->side == 'B')
        inventory.push_back({trade->price, trade->quantity});
    else {
        const double pnl = calcPnl(trade, inventory);
        printResult(trade->timestamp, trade->symbol, pnl);
    }
}

double PnlCalculator::calcPnl(const std::unique_ptr<Trade> &trade, std::deque<Inventory> &inventory) const {
    int quantityLeft = trade->quantity;
    double pnl = 0.0;

    while (quantityLeft > 0 && !inventory.empty()) {
        auto&[price, quantity] = (method_ == "fifo") ? inventory.front() : inventory.back();
        const int qtyUsed = std::min(quantityLeft, quantity);
        pnl += qtyUsed * (trade->price - price);
        quantity -= qtyUsed;
        quantityLeft -= qtyUsed;

        if (quantity == 0)
            (method_ == "fifo") ? inventory.pop_front() : inventory.pop_back();
    }

    return pnl;
}

void PnlCalculator::printResult(const int timestamp, const std::string& symbol, const double pnl) {
    std::cout << timestamp << "," << symbol << ","  << std::fixed << std::setprecision(2) << pnl << "\n";
}
