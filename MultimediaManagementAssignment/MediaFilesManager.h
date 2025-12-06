#include<iostream>
#include <vector>

#include "MediaFile.h"
#include "FileHelper.h"

using namespace std;

class MediaFilesManager {
private:
	static vector<MediaFile> _mediaFiles;
	unique_ptr<FileHelper> _pFileHelper;

public:
	void initialize();
	void downloadMediaFile();
	void removeMediaFile();
	void playMediaFile();
	void filterMediaFiles();
	void searchMediaFiles();
	void displayMediaFiles(const vector<MediaFile>& mediaFiles);
};