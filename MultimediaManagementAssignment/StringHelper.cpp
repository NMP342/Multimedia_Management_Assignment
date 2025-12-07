#include "pch.h"

string StringHelper::toLower(string& toLowerString) {
	string loweredString = toLowerString;

	transform(loweredString.begin(), loweredString.end(), loweredString.begin(),
		[](unsigned char c) {
			return std::tolower(c);
		});

	return loweredString;
}

string StringHelper::toUpperCamelCase(string& toUpperCamelCaseString) {
    string upperCamelCaseString;
    bool makeUpper = true;

    for (char c : toUpperCamelCaseString)
    {
        if (isspace(static_cast<unsigned char>(c)))
        {
            makeUpper = true;
        }
        else
        {
            if (makeUpper)
            {
                upperCamelCaseString += toupper(c);
                makeUpper = false;
            }
            else
                upperCamelCaseString += tolower(c);
        }
    }

    return upperCamelCaseString;
}