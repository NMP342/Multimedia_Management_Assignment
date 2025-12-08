#pragma once

using namespace std;

class FileHelper {
public:
	static void readMediaFilesFromRootPath(vector<MediaFile>& mediaList);
	static void readMediaListFromFile(vector<MediaFile>& mediaList);
	static void saveMediaListToFile(const vector<MediaFile>& mediaList);
	static bool appendMediaFileToFile(MediaFile& mediaFile);
};