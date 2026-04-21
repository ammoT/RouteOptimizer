#include "TablePrinter.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

static const std::string CYAN  = "\033[36m";
static const std::string RESET = "\033[0m";

void TablePrinter::addRow(const std::string& name, const std::string& dist) {
    rows.emplace_back(name, dist);
}

void TablePrinter::print() const {
    size_t nameW = 8;     // "Percorso"
    size_t distW = 8;     // "Distanza"

    for (auto& r : rows) {
        nameW = std::max(nameW, r.first.size());
        distW = std::max(distW, r.second.size());
    }

    std::string border =
        "+-" + std::string(nameW, '-') +
        "-+-" + std::string(distW, '-') + "-+";

    std::cout << CYAN << border << RESET << "\n";

    std::cout << CYAN << "| "
              << std::left  << std::setw(nameW) << "Percorso"
              << " | "
              << std::right << std::setw(distW) << "Distanza"
              << " |" << RESET << "\n";

    std::cout << CYAN << border << RESET << "\n";

    for (auto& r : rows) {
        std::cout << "| "
                  << std::left  << std::setw(nameW) << r.first
                  << " | "
                  << std::right << std::setw(distW) << r.second
                  << " |\n";
    }

    std::cout << CYAN << border << RESET << "\n\n";
}
