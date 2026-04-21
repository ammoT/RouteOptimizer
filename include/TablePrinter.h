#pragma once
#include <string>
#include <vector>

class TablePrinter {
public:
    void addRow(const std::string& name, const std::string& dist);
    void print() const;

private:
    std::vector<std::pair<std::string, std::string>> rows;
};
