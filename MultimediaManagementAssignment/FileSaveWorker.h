#pragma once

#include <thread>
#include <queue>
#include <mutex>
#include "MediaFile.h"

using namespace std;

class FileSaveWorker {
public:
	static int _saveFileCommandId;

	FileSaveWorker();
	~FileSaveWorker();
	void requestSave(const int saveCommandId, const vector<MediaFile>& mediaList);

private:
	static int _currentSaveCommandId;
	bool _running;
	bool _hasNewData;
	thread _thread;
	vector<MediaFile> _mediaFiles;
	mutex _mutex;
	condition_variable _cv;

	void run();
};
