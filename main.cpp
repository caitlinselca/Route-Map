/*
Caitlin Selca
*/

#include "City.hpp"
#include "RouteMap.hpp"
#include <iostream>
using namespace std;

int main()
{

    RouteMap obj;
    obj.readMap("sample_map.txt");

    std::cout << obj.isRoute(obj.getCity_one("Athens"), obj.getCity_one("Firenze")) << std::endl;

    obj.printStack();

}