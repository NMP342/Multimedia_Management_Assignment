#include "pch.h"

string StringHelper::toLower(string& toLowerString) {
	string loweredString = toLowerString;

	transform(loweredString.begin(), loweredString.end(), loweredString.begin(),
		[](unsigned char c) {
			return std::tolower(c);
		});

	return loweredString;
}