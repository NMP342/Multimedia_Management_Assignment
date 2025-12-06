#include "pch.h"

vector<MediaFile> MediaFilesManager::_mediaFiles;

void MediaFilesManager::initialize() {
	_pFileHelper->readMediaFilesFromRootPath(_mediaFiles);
    _pFileHelper->saveMediaListToFile(_mediaFiles);
}

void MediaFilesManager::downloadMediaFile() {}

void MediaFilesManager::filterMediaFiles() {}

void MediaFilesManager::searchMediaFiles() {}

void MediaFilesManager::removeMediaFile() {}

void MediaFilesManager::playMediaFile() {}

vector<MediaFile>& MediaFilesManager::getAllMediaFiles() 
{
    return _mediaFiles;
}

