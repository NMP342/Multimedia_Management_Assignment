#pragma once

using namespace std;

class FileHelper {
public:
	static void ReadMediaFilesFromRootPath(vector<MediaFile>& mediaList);
	static void SaveMediaListToFile(const vector<MediaFile>& mediaList);
};