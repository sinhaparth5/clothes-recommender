#ifndef WEATHER_H
#define WEATHER_H

#include <string>
#include <json/json.h>

class Weather {
public:
    Weather(const std::string& apiKey);
    std::string fetchWeatherData(const std::string& location);
    void parseWeatherData(const std::string& data);
    void suggestClothing() const;

private:
    std::string apiKey;
    float temperature;
    std::string description;
};

#endif