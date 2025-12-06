#pragma once

class DisplayController {
public:
	DisplayController();
	void displayFunctions();
	void executeFunction(const int& funcNumber);
	void displayMediaList(vector<MediaFile>& mediaList);

	int& getCurrentFunction();
	void setCurrentFunction(int& currentFunction);

private:
	unique_ptr<MediaFilesManager> _pMediaFileManager;
};
