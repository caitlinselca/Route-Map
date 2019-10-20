/*Caitlin Selca
This project displays the route from origin to destination, using stacks.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "City.hpp"

City::City(std::string city)
{
    city_name_ = city; //this function sets the private variable city_name_ to the city string that is being passed through the function
}

std::string City::getCityName() const
{
    return city_name_; //this functions returns the city name
}

std::vector<City*> City::getAdjecentCities() const
{
    return Adjacent_Cities_; //this function returns the adjacent cities (from what origin city) are being pointed to
}

void City::Add_Adjacent_Cities(City* city)
{
    Adjacent_Cities_.push_back(city); //this function will push (add) cities to the adjacent cities vector in order to store what cities are adjacent from an origin city
}