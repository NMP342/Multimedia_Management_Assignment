#include "pch.h"

int FileSaveWorker::_saveFileCommandId;
int FileSaveWorker::_currentSaveCommandId;

FileSaveWorker::FileSaveWorker() {
    _saveFileCommandId = 1;
    _currentSaveCommandId = 0;
	_running = true;
    _hasNewData = false;
	_thread = thread(&FileSaveWorker::run, this);	
}

FileSaveWorker::~FileSaveWorker() {
    {
        lock_guard<mutex> lock(_mutex);
        _running = false;
    }
    _cv.notify_one();
    _thread.join();
}

void FileSaveWorker::requestSave(const int saveCommandId, const vector<MediaFile>& mediaList) {
    {
        lock_guard<mutex> lock(_mutex);

        if (saveCommandId > _currentSaveCommandId) {
            _mediaFiles = mediaList;
            _hasNewData = true;
        }
    }
    _cv.notify_one();
}

void FileSaveWorker::run() {
    while (true) {
        unique_lock<mutex> lock(_mutex);

        _cv.wait(lock, [this] {
            return _hasNewData || !_running;
            });

        if (!_running && !_hasNewData)
            break;

        auto data = move(_mediaFiles);
        _hasNewData = false;

        lock.unlock();

        FileHelper::saveMediaListToFile(data);
    }
}