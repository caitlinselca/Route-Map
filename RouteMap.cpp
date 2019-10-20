/*Caitlin Selca
This project displays the route from origin to destination, using stacks.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stack>
#include <vector>
#include "RouteMap.hpp"


bool RouteMap::readMap(std::string input_file_name)
{
	std::ifstream fin(input_file_name); //this reads in the file
	if (fin.fail())
	{
    	std::cerr << "File cannot be opened for reading." << std::endl; //check if the file fails, if it does then exit
    	exit(1); // exit if failed to open the file
	}

	std::string city_names, newcitynames_;
	std::getline(fin, city_names); //this takes in the lines from the file
	std::stringstream names(city_names); //stringstream then only takes in the first line from the file, instead of continuing onto the second
	while(std::getline(names, newcitynames_, ',')) //while it is going through the first line, we will use the comma as a delimiter
	{
		City* new_city_ = new City(newcitynames_); //we will dynamically allocate each city
		Cities_.push_back(new_city_); //each city will be pushed (added) into the cities vector
	}

	std::string city_and_adj;
	while(getline(fin, city_and_adj, ',')) //this will take in the second line of the file, separating city-adjacent city by the comma delimiter
	{
		int dash_loc; //we are going to set the dash location to an integer

		for(int i = 0; i < city_and_adj.length(); i++)
		{
			if('-' == city_and_adj[i]) //as we loop through each individual city-adjacent city, we are looking for the dash location 
			{
				dash_loc = i; //once we find the dash location in each, we get the position that it is located at
				break;
			}
		}

		std::string city_origin, adj_city; //after finding the dash location, we find two substrings (one that will be the city string and one that will be the adjacent city)
		city_origin = city_and_adj.substr(0, dash_loc); //this substring will be the city origin, taking in from the first letter until the dash is found

		// std::cout << city_origin << std::endl;

		adj_city = city_and_adj.substr(dash_loc + 1); //this substring will be the adjacent city, taking in after the dash is found all the way until the end

		// std::cout << adj_city << std::endl;

		getCity_one(city_origin); //this will pass the substring city_origin into the function in order for it return a pointer to the city
		getCity_one(city_origin)->Add_Adjacent_Cities(getCity_one(adj_city)); //this will pass the substring city_origin into the function in order for it return a pointer to the city, which will then point to, and add, the adjacent cities to the vector of adjacent cities 

	}

	return true;
}

City* RouteMap::getCity_one(std::string city_name_)
{
	for(int i = 0; i < Cities_.size(); i++)
	{
		if(city_name_ == Cities_[i]->getCityName())
		{
			return Cities_[i]; //this will loop through the cities vector in order to match the string with a position that it is found in the vector, then it returns a pointer to the city
		}
	}
	return nullptr;
}

City* RouteMap::getCity(size_t position)
{
	bool getCity = (position < Cities_.size());
    if (getCity)
    {
		return Cities_[position]; //this will loop through the cities vector in order to get the position that the city is found in the vector, then it returns a pointer to the position of the city
	}

	else
	{
		return nullptr; //if there is no city/no position found in the vector, then it will just return a nullpointer
	}
 
}

// Sees whether a city was visited.
bool RouteMap::isVisited(City* city)
{
	for(int i = 0; i < Visited_Cities.size(); i++)
	{
		if(city == Visited_Cities[i])
		{
			return true; //this function will loop through the vector of visited cities in order to see if the city we are passing through is in there already, if it is then it is visited, if it is not then it is not visited
		}
	}
	return false;
}

// Returns the next unvisited city, if any, that is adjacent to a given city.

City* RouteMap::getNextCity(City* location)
{
	std::vector<City*> locationAdjacentCities = location->getAdjecentCities(); //this creates a vector which is set to getting the adjacent cities of the current location being passed through the function
	for(int i = 0; i < locationAdjacentCities.size(); i++)
	{
		if(isVisited(locationAdjacentCities[i]) == false)
		{
			return locationAdjacentCities[i]; //this loops through the vector of current location's adjacent cities, if an adjacent city is not visited then it will be returned
		}
	}
	return nullptr; //if all adjacent cities are visited or there are no adjacent cities then return nullpointer
}



bool RouteMap::isRoute(City* origin, City* destination)
{

	Backtracking_Cities.push(origin); //the origin will be pushed into the backtracking cities stack 
	Visited_Cities.push_back(origin); //the origin will also be pushed into the visited cities vector since it is the first location visited
	while(origin != destination)
	{
		// std::cout << Backtracking_Cities.top()->getCityName();

		if(Backtracking_Cities.empty())
		{
			return false; //if the backtracking cities stack is empty then we will return false
		}

		if(getNextCity(origin) == nullptr) //if there are no adjacent cities/no unvisited adjacent cities then it will be nullpointer
		{
			Backtracking_Cities.pop(); //this location will be popped from the backtracking cities stack
			if(Backtracking_Cities.empty()) //if the stack is empty then we will return false
			{
				return false;
			}
			else
			{
				origin = Backtracking_Cities.top(); //if the stack is not empty then we will set the new origin (location) to the city at the top of the stack
			}
		}

		else
		{
			origin = getNextCity(origin); //this sets the origin (location) to the next city of the current location
			Backtracking_Cities.push(origin); //this new location is then pushed onto the stack
			Visited_Cities.push_back(origin); //this new location is then also pushed into the visited cities vector
		}

	}

	printStack(); //this calls on the function print stack in order to display the contents of the stack (the route)
	return true;
	
}

void RouteMap::printStack()
{
	std::stack<City*> Display_Route_; //create a stack in order to put the contents of the backtracking cities stack into
	
	while(!(Backtracking_Cities.empty()))
	{
		Display_Route_.push(Backtracking_Cities.top()); //this will push the city that is found at the top of the stack in backtracking cities into the display route stack
		Backtracking_Cities.pop(); //this will then pop that city from the backtracking cities stack
	}

	while(!(Display_Route_.empty()))
	{
		if(Display_Route_.size() == 1) //if the display route stack size is equal to one
		{
			std::cout << Display_Route_.top()->getCityName() << "\n"; //it will display the city but then make a new line
			Display_Route_.pop(); //then pop this city from the stack
		}
		else
		{
			std::cout << Display_Route_.top()->getCityName() << " -> "; //otherwise, each city will be displayed then have an arrow which points to the direction of the next city in the route
			Display_Route_.pop(); //then each city will be popped from the stack after being displayed
		}

	}

}