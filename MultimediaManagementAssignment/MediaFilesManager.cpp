#include "pch.h"

vector<MediaFile> MediaFilesManager::_mediaFiles;

void MediaFilesManager::initialize() {
	_pFileHelper->ReadMediaFilesFromRootPath(_mediaFiles);
    _pFileHelper->SaveMediaListToFile(_mediaFiles);
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
        std::cout << "Name       : " << file.GetName() << "\n";
        std::cout << "Size (KB)  : " << file.GetSize() << "\n";
        std::cout << "Type       : " << file.GetType() << "\n";
        std::cout << "Genre      : " << file.GetGenre() << "\n";
        std::cout << "Description: " << file.GetDescription() << "\n";
    }
}

