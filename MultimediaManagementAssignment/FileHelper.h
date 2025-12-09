#pragma once

using namespace std;

class FileHelper {
public:
	static void initializeMediaFiles(vector<MediaFile>& mediaList);
	static void readMediaFilesFromRootPath(vector<MediaFile>& mediaList);
	static void readMediaListFromFile(vector<MediaFile>& mediaList);
	static void saveMediaListToFile(const vector<MediaFile>& mediaList);
	static bool appendMediaFileToFile(MediaFile& mediaFile);
	static string getFilePath();
	static string getRootPath();

private:
	static string _filePath;
	static string _rootPath;
};