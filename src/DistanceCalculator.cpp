#include "DistanceCalculator.h"
#include "GoogleAPI.h"
#include "TablePrinter.h"
#include <sstream>
#include <iostream>
#include <iomanip>

void DistanceCalculator::compareRoutes(double latA, double lonA,
                                       double latB, double lonB,
                                       double latDest, double lonDest,
                                       const std::string &apiKey)
{
    int dA  = GoogleAPI::getDistance(latA, lonA, latDest, lonDest, apiKey);
    int dB  = GoogleAPI::getDistance(latB, lonB, latDest, lonDest, apiKey);
    int dAB = GoogleAPI::getDistance(latA, lonA, latB, lonB, apiKey);
    int dBA = GoogleAPI::getDistance(latB, lonB, latA, lonA, apiKey);

    auto fmt = [](double km) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(1) << km << " km";
        return oss.str();
    };

    TablePrinter table;
    table.addRow("A -> Dest",       fmt(dA / 1000.0));
    table.addRow("B -> Dest",       fmt(dB / 1000.0));
    table.addRow("A -> B -> Dest",  fmt((dAB + dB) / 1000.0));
    table.addRow("B -> A -> Dest",  fmt((dBA + dA) / 1000.0));
    table.print();

    int twoTrips = dA + dB;
    int oneTripA = dAB + dB;
    int oneTripB = dBA + dA;

    int best = std::min({twoTrips, oneTripA, oneTripB});

    if (best == twoTrips)
        std::cout << "Soluzione migliore: due viaggi separati\n";
    else if (best == oneTripA)
        std::cout << "Soluzione migliore: partire da A e poi passare da B\n";
    else
        std::cout << "Soluzione migliore: partire da B e poi passare da A\n";

    std::cout << "Risparmio: "
              << (std::max({twoTrips, oneTripA, oneTripB}) - best) / 1000.0
              << " km\n";
}
