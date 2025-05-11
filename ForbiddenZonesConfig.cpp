#include "ForbiddenZonesConfig.h"

std::vector<sf::FloatRect> ForbiddenZones::FORBIDDEN_ZONES = {
	//sf::FloatRect(0, 0, 1920, 10),//up
	//sf::FloatRect(1910, 0, 20, 1080)//right


};

vector<FloatRect>& ForbiddenZones::GetForbiddenZones()
{
	return FORBIDDEN_ZONES;
}