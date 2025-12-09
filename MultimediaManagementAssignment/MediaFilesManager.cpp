#include "pch.h"

vector<MediaFile> MediaFilesManager::_mediaFiles;

MediaFilesManager::MediaFilesManager() {
	_pCopyService = make_unique<CopyService>();
	_pNamedPipeClient = make_unique<NamedPipeClient>();
}

void MediaFilesManager::initialize() {
	FileHelper::initializeMediaFiles(_mediaFiles);
}

pair<bool, string> MediaFilesManager::downloadMediaFile(string& sourceDirectory, string& destinationDirectory, MediaFile& mediaFile, function<void(uint64_t copied, uint64_t total)> showProgress) {
	auto downloadResult = _pCopyService->copyFileWithProgress(sourceDirectory, destinationDirectory, mediaFile, showProgress);

	if (downloadResult.first) {
		_mediaFiles.push_back(mediaFile);
		bool appendFileResult = FileHelper::appendMediaFileToFile(mediaFile);

		if (!appendFileResult) {
			//Need lock
			FileHelper::saveMediaListToFile(_mediaFiles);
		}
	}

	return downloadResult;
}

const vector<MediaFile> MediaFilesManager::filterMediaFiles(const FilterCriteria& filterCriteria, string& filterValue) {
	filterValue = StringHelper::toLower(filterValue);

	switch (filterCriteria)
	{
	case TYPE: return filterMediaFilesByType(filterValue);
	case GENRE: return filterMediaFilesByGenre(filterValue);
	}
}

const vector<MediaFile> MediaFilesManager::filterMediaFilesByType(const string& typeValue) {
	vector<MediaFile> filteredMediaList;

	for (auto& mediaFile : _mediaFiles) {
		if (StringHelper::toLower(mediaFile.getType()) == typeValue) {
			filteredMediaList.push_back(mediaFile);
		}
	}

	return filteredMediaList;
}

const vector<MediaFile> MediaFilesManager::filterMediaFilesByGenre(const string& genreValue) {
	vector<MediaFile> filteredMediaList;

	for (auto& mediaFile : _mediaFiles) {
		if (StringHelper::toLower(mediaFile.getGenre()) == genreValue) {
			filteredMediaList.push_back(mediaFile);
		}
	}

	return filteredMediaList;
}

const vector<MediaFile> MediaFilesManager::searchMediaFiles(string& searchedString) {
	vector<MediaFile> searchedMediaList;

	searchedString = StringHelper::toLower(searchedString);

	for (auto& media : _mediaFiles)
	{
		if (StringHelper::toLower(media.getName()).find(searchedString) != string::npos)
		{
			searchedMediaList.push_back(media);
		}
	}

	return searchedMediaList;
}

pair<bool, string> MediaFilesManager::playMediaFile(MediaFile& mediaFile) {
	string message = "PLAY|" + mediaFile.getDirectory();
	auto playResult = _pNamedPipeClient->sendMessageToNamedPipeServer(message);

	if (playResult.first) {
		int viewNumber = mediaFile.getViewNumber() + 1;
		mediaFile.setViewNumber(viewNumber);

		FileHelper::saveMediaListToFile(_mediaFiles);
	}

	return playResult;
}

vector<MediaFile>& MediaFilesManager::getAllMediaFiles()
{
	return _mediaFiles;
}

const vector<string>& MediaFilesManager::getAllMediaTypes() {
	return _mediaTypes;
}

const vector<string>& MediaFilesManager::getAllMediaGenres() {
	if (_mediaGenres.size() == 0)
	{
		set<string> mediaGenresSet;
		for (auto& media : _mediaFiles)
		{
			if (!media.getGenre().empty())
			{
				mediaGenresSet.insert(media.getGenre());
			}
		}

		for (auto& genre : mediaGenresSet) {
			_mediaGenres.push_back(genre);
		}
	}

	return _mediaGenres;
}

const vector<string> MediaFilesManager::getMediaGenresByType(const string& mediaType)
{
	set<string> mediaGenresSet;
	for (auto& media : _mediaFiles)
	{
		if (media.getType() == mediaType) {
			if (!media.getGenre().empty())
			{
				mediaGenresSet.insert(media.getGenre());
			}
		}
	}

	vector<string> mediaGenresByType;
	for (auto& genre : mediaGenresSet) {
		mediaGenresByType.push_back(genre);
	}

	return mediaGenresByType;
}

void MediaFilesManager::addNewGenre(const string& newGenre) {
	_mediaGenres.push_back(newGenre);
}

