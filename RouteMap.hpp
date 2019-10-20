/*Caitlin Selca
This project displays the route from origin to destination, using stacks.
*/

#ifndef ROUTEMAP_HPP_
#define ROUTEMAP_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stack>
#include "City.hpp"

class RouteMap
{

	public:
		
		bool readMap(std::string input_file_name); //function that reads in the file

		City* getCity(size_t position); //function that gets us a pointer to the position of the city

		bool isRoute(City* origin, City* destination); //function that shows the route from origin to destination

		City* getCity_one(std::string city_name_); //function that takes in a city name by string and then returns a pointer to a city

		bool isVisited(City* city); //function that checks if a city was visited or not

		City* getNextCity(City* location); //function that gets the next city in the route

		void printStack(); //prints the stack to display the route in order

	// private:

		std::vector<City*> Cities_; //a vector that takes in the city names from the file/contains pointers to the cities
		std::stack<City*> Backtracking_Cities; //a stack that will contain the cities that are being backtracked
		std::vector<City*> Visited_Cities; //a vector that will keep track of which cities have been visited or not

};

#endif