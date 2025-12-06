#include "pch.h"

vector<MediaFile> MediaFilesManager::_mediaFiles;

void MediaFilesManager::initialize() {
	_pFileHelper->readMediaFilesFromRootPath(_mediaFiles);
    _pFileHelper->saveMediaListToFile(_mediaFiles);
    displayMediaFiles(_mediaFiles);
}

void MediaFilesManager::downloadMediaFile() {}

void MediaFilesManager::filterMediaFiles() {}

void MediaFilesManager::searchMediaFiles() {}

void MediaFilesManager::removeMediaFile() {}

void MediaFilesManager::playMediaFile() {}

void MediaFilesManager::displayMediaFiles(const vector<MediaFile>& mediaFiles) {
    for (MediaFile file : mediaFiles)
    {
        std::cout << "------------------------\n";
        std::cout << "Name       : " << file.getName() << "\n";
        std::cout << "Size (KB)  : " << file.getSize() << "\n";
        std::cout << "Type       : " << file.getType() << "\n";
        std::cout << "Genre      : " << file.getGenre() << "\n";
        std::cout << "Description: " << file.getDescription() << "\n";
    }
}

