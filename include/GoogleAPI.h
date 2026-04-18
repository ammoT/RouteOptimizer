#pragma once
#include <string>

class GoogleAPI {
public:
    static int getDistance(double latA, double lonA,
                           double latB, double lonB,
                           const std::string& apiKey);
};
