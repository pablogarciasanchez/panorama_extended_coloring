#ifndef AUX_H_INCLUDED
#define AUX_H_INCLUDED
#include <string>

enum Axis {X = 0, Y = 1, Z = 2};
enum Map {SDM = 0, NDM = 1};

std::string axis_to_string(Axis axis);
std::string map_to_string(Map map);
#endif