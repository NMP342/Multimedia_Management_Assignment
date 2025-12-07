#include<iostream>
#include <vector>
#include<set>

#include "MediaFile.h"
#include "FileHelper.h"
#include "CopyService.h"

using namespace std;

class MediaFilesManager {
private:
	static vector<MediaFile> _mediaFiles;
	vector<string> _mediaTypes{ "Video", "Audio" };
	vector<string> _mediaGenres;
	unique_ptr<FileHelper> _pFileHelper;
	unique_ptr<CopyService> _pCopyService;

	const vector<MediaFile> filterMediaFilesByType(const string& typeValue);
	const vector<MediaFile> filterMediaFilesByGenre(const string& genreValue);

public:
	MediaFilesManager();

	void initialize();
	pair<bool, string> downloadMediaFile(string& sourceDirectory, string& destinationDirectory, MediaFile& mediaFile, function<void(uint64_t copied, uint64_t total)> showProgress);
	void removeMediaFile();
	void playMediaFile();
	const vector<MediaFile> filterMediaFiles(const FilterCriteria& filterCriteria, string& filterValue);
	const vector<MediaFile> searchMediaFiles(string& searchedString);
	vector<MediaFile>& getAllMediaFiles();
	const vector<string>& getAllMediaTypes();
	const vector<string>& getAllMediaGenres();
};