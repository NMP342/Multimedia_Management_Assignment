#pragma once

#include <string>
#include <filesystem>

using namespace std;

class StringHelper {
public:
	static string toLower(string& toLowerString);
	static string toUpperCamelCase(string& toCamelCaseString);
};
