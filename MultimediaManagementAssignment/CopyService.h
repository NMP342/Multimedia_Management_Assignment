#pragma once

#include <functional>
#include <string>

using namespace std;

class CopyService {
public:
	using ProgressCallback = function<void(uint64_t copied, uint64_t total)>;

	static pair<bool, string> copyFileWithProgress(string& sourceDirectory, string& destinationDirectory, MediaFile& mediaFile, ProgressCallback showProgress);
};