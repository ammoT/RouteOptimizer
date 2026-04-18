#pragma once
#include <string>

class DistanceCalculator {
public:
    static void compareRoutes(double latA, double lonA,
                              double latB, double lonB,
                              double latDest, double lonDest,
                              const std::string& apiKey);
};
