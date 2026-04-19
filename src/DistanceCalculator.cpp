#include "DistanceCalculator.h"
#include "GoogleAPI.h"
#include <iostream>
#include <iomanip>

const std::string CYAN = "\033[36m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RESET = "\033[0m";

void printColoredTable(double dA, double dB, double dAB, double dBA)
{
    std::cout << CYAN << "+----------------------+--------------+" << RESET << "\n";
std::cout << CYAN << "|        Percorso      |   Distanza   |" << RESET << "\n";
std::cout << CYAN << "+----------------------+--------------+" << RESET << "\n";

auto row = [&](const std::string &name, double km)
{
    std::cout << "| "
              << std::left << std::setw(20) << name
              << " | "
              << std::right << std::setw(10)
              << std::fixed << std::setprecision(1)
              << km << " km |\n";
};

row("A -> Dest", dA);
row("B -> Dest", dB);
row("A -> B -> Dest", dAB);
row("B -> A -> Dest", dBA);

std::cout << CYAN << "+----------------------+--------------+" << RESET << "\n\n";

}

void DistanceCalculator::compareRoutes(double latA, double lonA,
                                       double latB, double lonB,
                                       double latDest, double lonDest,
                                       const std::string &apiKey)
{
    int dA = GoogleAPI::getDistance(latA, lonA, latDest, lonDest, apiKey);
    int dB = GoogleAPI::getDistance(latB, lonB, latDest, lonDest, apiKey);
    int dAB = GoogleAPI::getDistance(latA, lonA, latB, lonB, apiKey);
    int dBA = GoogleAPI::getDistance(latB, lonB, latA, lonA, apiKey);

    printColoredTable(dA / 1000.0, dB / 1000.0, (dAB + dB) / 1000.0, (dBA + dA) / 1000.0);

    int twoTrips = dA + dB;
    int oneTripA = dAB + dB;
    int oneTripB = dBA + dA;

    int best = std::min({twoTrips, oneTripA, oneTripB});

    if (best == twoTrips)
        std::cout << GREEN << "Soluzione migliore: due viaggi separati" << RESET << "\n";
    else if (best == oneTripA)
        std::cout << GREEN << "Soluzione migliore: partire da A e poi passare da B" << RESET << "\n";
    else
        std::cout << GREEN << "Soluzione migliore: partire da B e poi passare da A" << RESET << "\n";

    std::cout << YELLOW << "Risparmio: "
              << (std::max({twoTrips, oneTripA, oneTripB}) - best) / 1000.0
              << " km" << RESET << "\n";
}
