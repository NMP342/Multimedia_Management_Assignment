#pragma once

class DisplayController {
public:
	DisplayController();
	void displayFunctions();
	void executeFunction(const int& funcNumber);
	void displayMediaList(vector<MediaFile>& mediaList);

private:
	unique_ptr<MediaFilesManager> _pMediaFileManager;

	string inputMediaFileSourceDirectory();
	string chooseDestinationMediaFileType(MediaFile& mediaFile);
	string chooseDestinationMediaFileGenre(MediaFile& mediaFile);
	string createMediaFileDestinationDirectory(const string& mediaType, const string& mediaGenre);
	void inputMediaFileDescription(MediaFile& mediaFile);
	void showProgress(uint64_t copied, uint64_t total);
	void handleDownloadResult(pair<bool, string>& downloadResult);
	string inputSearchedString();
	FilterCriteria chooseFilterCriteria();
	string chooseFilterValue(FilterCriteria filterCriteria);
	string chooseFilterTypeCriteria();
	string chooseFilterGenreCriteria();
	MediaFile& chooseMediaFileToPlay(vector<MediaFile>& mediaList);
	void handlePlayResult(const pair<bool, string>& playResult);
};
