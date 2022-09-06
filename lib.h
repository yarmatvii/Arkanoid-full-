#include <string>

std::string getResourcePath(std::string resourceName);
bool linesIntersection(double p0x, double p0y, double p1x, double p1y, double p2x, double p2y, double p3x, double p3y);
std::pair<double, double> reflectionVector(std::pair<double, double> d, std::pair<double, double> n);
std::pair<double, double> normalize(double x, double y);