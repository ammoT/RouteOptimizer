#include "DistanceCalculator.h"
#include "GeocodingAPI.h"
#include <iostream>
#include <fstream>
#include <string>

std::string loadApiKey() {
    std::ifstream file("config.txt");
    std::string line;

    while (std::getline(file, line)) {
        if (line.rfind("API_KEY=", 0) == 0) {
            return line.substr(8);
        }
    }
    return "";
}

bool getCoordsFromUser(const std::string& label,
                       const std::string& apiKey,
                       double& lat,
                       double& lon)
{
    std::string place;
    std::cout << "Inserisci luogo " << label << ": ";
    std::getline(std::cin, place);

    if (place.empty()) {
        std::cerr << "Errore: luogo vuoto\n";
        return false;
    }

    if (!GeocodingAPI::getCoordinates(place, apiKey, lat, lon)) {
        std::cerr << "Impossibile ottenere coordinate per: " << place << "\n";
        return false;
    }

    std::cout << "→ " << label << " = " << lat << ", " << lon << "\n\n";
    return true;
}

int main() {
    std::string apiKey = loadApiKey();

    if (apiKey.empty()) {
        std::cerr << "Errore: impossibile leggere la API Key da config.txt\n";
        return 1;
    }

    std::cout << "=== RouteOptimizer con geocoding ===\n\n";

    double latA, lonA, latB, lonB, latDest, lonDest;

    // Per usare getline dopo eventuali cin precedenti
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!getCoordsFromUser("A", apiKey, latA, lonA)) return 1;
    if (!getCoordsFromUser("B", apiKey, latB, lonB)) return 1;
    if (!getCoordsFromUser("Destinazione", apiKey, latDest, lonDest)) return 1;

    DistanceCalculator::compareRoutes(
        latA, lonA,
        latB, lonB,
        latDest, lonDest,
        apiKey
    );

    return 0;
}
