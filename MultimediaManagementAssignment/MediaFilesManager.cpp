#include "pch.h"

vector<MediaFile> MediaFilesManager::_mediaFiles;

void MediaFilesManager::initialize() {
	_pFileHelper->readMediaListFromFile(_mediaFiles);
}

void MediaFilesManager::downloadMediaFile() {}

void MediaFilesManager::filterMediaFiles() {}

vector<MediaFile> MediaFilesManager::searchMediaFiles(string& searchedString) {
	vector<MediaFile> searchedMediaList;

	searchedString = toLower(searchedString);

	for (auto& media : _mediaFiles)
	{
		if (toLower(media.getName()).find(searchedString) != string::npos)
		{
			searchedMediaList.push_back(media);
		}
	}

	return searchedMediaList;
}

void MediaFilesManager::removeMediaFile() {}

void MediaFilesManager::playMediaFile() {}

vector<MediaFile>& MediaFilesManager::getAllMediaFiles()
{
	return _mediaFiles;
}

string MediaFilesManager::toLower(string& word) {
	string loweredWord = word;

	transform(loweredWord.begin(), loweredWord.end(), loweredWord.begin(),
		[](unsigned char c) {
			return std::tolower(c);
		});

	return loweredWord;
}

