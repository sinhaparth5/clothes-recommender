#include "Weather.h"
#include <iostream>
#include <curl/curl.h>

// Helper function to handle data from the API
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* buffer) {
    buffer->append((char*)contents, size * nmemb);
    return size * nmemb;
}

Weather::Weather(const std::string& apiKey) : apiKey(apiKey), temperature(0.0), description("") {}

// Fetch weather data from the API
std::string Weather::fetchWeatherData(const std::string& location) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        std::string url = "https://weather.visualcrossing.com/VisualCrossingWebServices/rest/services/timeline/"
                          + location + "?unitGroup=metric&key=" + apiKey;

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        curl_easy_cleanup(curl);
    }

    return readBuffer;
}

// Parse the JSON response to extract temperature and description
void Weather::parseWeatherData(const std::string& data) {
    Json::Reader reader;
    Json::Value jsonData;
    if (reader.parse(data, jsonData)) {
        temperature = jsonData["days"][0]["temp"].asFloat();
        description = jsonData["days"][0]["description"].asString();
    } else {
        std::cerr << "Failed to parse weather data.\n";
    }
}

// Suggest clothing based on temperature
void Weather::suggestClothing() const {
    std::cout << "Current temperature: " << temperature << "°C\n";
    std::cout << "Weather description: " << description << "\n";

    if (temperature > 30.0) {
        std::cout << "It's very hot! Wear light clothes and stay hydrated.\n";
    } else if (temperature > 20.0) {
        std::cout << "It's warm. T-shirt and shorts are a good choice.\n";
    } else if (temperature > 10.0) {
        std::cout << "It's cool. A light jacket or sweater would be good.\n";
    } else if (temperature > 0.0) {
        std::cout << "It's cold. Wear a jacket and warm clothing.\n";
    } else {
        std::cout << "It's freezing! Make sure to wear heavy winter clothing.\n";
    }
}
