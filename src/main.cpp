#include <iostream>
#include "Weather.h"

int main() {
    // Replace with your API key
    std::string apiKey = "YS8CMRCZTSDCQT3CMSZPYVQUE";
    
    // Get user input for location
    std::string location;
    std::cout << "Enter the location (e.g., London,UK): ";
    std::getline(std::cin, location);
    
    // Create a Weather object
    Weather weather(apiKey);

    // Fetch weather data for the input location
    std::string weatherData = weather.fetchWeatherData(location);

    // Parse and display the weather data
    weather.parseWeatherData(weatherData);
    weather.suggestClothing();

    return 0;
}
