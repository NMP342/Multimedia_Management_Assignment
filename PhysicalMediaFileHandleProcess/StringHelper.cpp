#include "pch.h"

vector<string> StringHelper::splitStringByDelimiter(string& line, char delimiter) {
	vector<string> tokens;
	stringstream ss(line);
	string item;

	while (getline(ss, item, delimiter)) {
		tokens.push_back(item);
	}

	return tokens;
}