#include "GeocodingAPI.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t total = size * nmemb;
    s->append((char*)contents, total);
    return total;
}

bool GeocodingAPI::getCoordinates(const std::string& place,
                                  const std::string& apiKey,
                                  double& outLat,
                                  double& outLon)
{
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Errore: impossibile inizializzare cURL\n";
        return false;
    }

    char* escaped = curl_easy_escape(curl, place.c_str(), 0);
    if (!escaped) {
        std::cerr << "Errore: curl_easy_escape fallita\n";
        curl_easy_cleanup(curl);
        return false;
    }

    std::string url = "https://maps.googleapis.com/maps/api/geocode/json?address=";
    url += escaped;
    url += "&key=" + apiKey;

    curl_free(escaped);

    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        std::cerr << "Errore cURL (geocoding): " << curl_easy_strerror(res) << std::endl;
        return false;
    }

    json j = json::parse(response, nullptr, false);
    if (j.is_discarded()) {
        std::cerr << "Errore: risposta JSON non valida dal geocoding\n";
        return false;
    }

    if (!j.contains("status") || j["status"] != "OK") {
        std::cerr << "Errore Geocoding: " << j.value("status", "UNKNOWN") << std::endl;
        return false;
    }

    if (!j.contains("results") || !j["results"].is_array() || j["results"].empty()) {
        std::cerr << "Errore Geocoding: nessun risultato\n";
        return false;
    }

    const auto& loc = j["results"][0]["geometry"]["location"];
    outLat = loc["lat"].get<double>();
    outLon = loc["lng"].get<double>();

    return true;
}
