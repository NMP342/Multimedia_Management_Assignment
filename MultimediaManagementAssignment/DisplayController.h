#pragma once

class DisplayController {
public:
	DisplayController();
	void displayFunctions();
	void executeFunction(const int& funcNumber);
	void displayMediaList(vector<MediaFile>& mediaList);

private:
	unique_ptr<MediaFilesManager> _pMediaFileManager;

	string inputSearchedString();
	FilterCriteria chooseFilterCriteria();
	string chooseFilterValue(FilterCriteria filterCriteria);
	string chooseFilterTypeCriteria();
	string chooseFilterGenreCriteria();
};
