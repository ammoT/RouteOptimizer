#include "GoogleAPI.h"
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *s)
{
    size_t total = size * nmemb;
    s->append((char *)contents, total);
    return total;
}

int GoogleAPI::getDistance(double latA, double lonA,
                           double latB, double lonB,
                           const std::string &apiKey)
{
    json payload = {
        {"origins", {{{"waypoint", {{"location", {{"latLng", {{"latitude", latA}, {"longitude", lonA}}}}}}}}}},
        {"destinations", {{{"waypoint", {{"location", {{"latLng", {{"latitude", latB}, {"longitude", lonB}}}}}}}}}},
        {"travelMode", "DRIVE"}};

    std::string payloadStr = payload.dump();
    std::string response;

    CURL *curl = curl_easy_init();
    if (!curl)
        return -1;

    curl_easy_setopt(curl, CURLOPT_URL,
                     "https://routes.googleapis.com/distanceMatrix/v2:computeRouteMatrix");

    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());

    struct curl_slist *headers = nullptr;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("X-Goog-Api-Key: " + apiKey).c_str());
    headers = curl_slist_append(headers, "X-Goog-FieldMask: distanceMeters");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);

    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
    {
        std::cerr << "Errore cURL: " << curl_easy_strerror(res) << std::endl;
        return -1;
    }

    json j = json::parse(response);

    // La risposta è un array, quindi prendi il primo elemento
    if (!j.is_array() || j.empty())
    {
        std::cerr << "Errore: risposta API inattesa\n";
        return -1;
    }

    return j[0]["distanceMeters"].get<int>();
}
