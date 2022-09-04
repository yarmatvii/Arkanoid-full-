#include <filesystem>
#include "Tools.h"

std::string getResourcePath(std::string resourceName)
{
	auto path = std::filesystem::current_path() / "data" / resourceName;
	return path.string();
}

bool linesIntersects(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y)
{
	double s1x = p1x - p0x;
	double s1y = p1y - p0y;
	double s2x = p3x - p2x;
	double s2y = p3y - p2y;

	double s = (-s1y * (p0x - p2x) + s1x * (p0y - p2y)) / (-s2x * s1y + s1x * s2y);
	double t = (s2x * (p0y - p2y) - s2y * (p0x - p2x)) / (-s2x * s1y + s1x * s2y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
		return true;
	return false;
}

std::pair<double, double> reflectionVector(std::pair<double, double> d, std::pair<double, double> n)
{
	double dotProduct = d.first * n.first + d.second * n.second;
	return
	{
		d.first - 2 * dotProduct * n.first,
		d.second - 2 * dotProduct * n.second
	};
}

std::pair<double, double> normalizeVector(double x, double y)
{
	long double len = sqrt(pow(x, 2) + pow(y, 2));
	return { x / len, y / len };
}
