#pragma once
#include <string>

class GeocodingAPI {
public:
    static bool getCoordinates(const std::string& place,
                               const std::string& apiKey,
                               double& outLat,
                               double& outLon);
};
