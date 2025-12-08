#pragma once

#include <string>

using namespace std;

class OpenFileService {
public:
	pair<bool, string> openFile(const string& fileDirectory);
};
