#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class ForbiddenZones
{
private:
	static vector<FloatRect>FORBIDDEN_ZONES;
public:
	
	static vector<FloatRect>& GetForbiddenZones();

};


