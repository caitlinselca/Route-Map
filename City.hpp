/*Caitlin Selca
This project displays the route from origin to destination, using stacks.
*/

#ifndef CITY_HPP_
#define CITY_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

class City
{

	public:

		City(std::string city); //function that takes in the city name string

		std::string getCityName() const; //function that returns the city name

		std::vector<City*> getAdjecentCities() const; //function that will return what adjacent cities (from what origin city) are being pointed to in the vector

		void Add_Adjacent_Cities(City* city); //functino that will add adjacent cities to the vector

	// private:

		std::string city_name_; //string city name
		std::vector<City*> Adjacent_Cities_; //vector of of adjacent cities

};

#endif