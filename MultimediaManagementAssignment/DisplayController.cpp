#include "pch.h"

DisplayController::DisplayController() {
	_pMediaFileManager = make_unique<MediaFilesManager>();
	_pMediaFileManager->initialize();
}

void DisplayController::displayFunctions() {
	cout << "\n";
	cout << "=================MULTIMEDIA MANAGEMENT SYSTEM================" << '\n';
	cout << "1. Display the media files list." << '\n';
	cout << "2. Upload media file." << '\n';
	cout << "3. Remove media file." << '\n';
	cout << "4. Search media file by name." << '\n';
	cout << "5. Filter media files list." << '\n';
	cout << "6. Play media file." << '\n';
	cout << "0. Exit." << '\n';

	int funcNumber = 0;
	cout << "Please choose the number of function: ";
	cin >> funcNumber;
	executeFunction(funcNumber);
}

void DisplayController::executeFunction(const int& funcNumber) {
	switch (funcNumber) {
	case DISPLAY: {
		vector<MediaFile>& mediaList = _pMediaFileManager->getAllMediaFiles();
		displayMediaList(mediaList);
		break;
	}
	case SEARCH: {
		string searchedString = inputSearchedString();
		vector<MediaFile> searchedMediaList = _pMediaFileManager->searchMediaFiles(searchedString);
		displayMediaList(searchedMediaList);
		break;
	}
	case FILTER: {
		FilterCriteria filterCriteria = chooseFilterCriteria();
		string filterValue = chooseFilterValue(filterCriteria);

		vector<MediaFile> filteredMediaList = _pMediaFileManager->filterMediaFiles(filterCriteria, filterValue);
		displayMediaList(filteredMediaList);

		break;
	}
	case EXIT:
		cout << "\nGoodbye!";
		return;
	}

	displayFunctions();
}

void DisplayController::displayMediaList(vector<MediaFile>& mediaList) {
	cout << "There is totally " << mediaList.size() << " result(s):\n";

	if (mediaList.size() == 0) {
		return;
	}

	int mediaNumber = 1;
	for (auto file : mediaList)
	{
		cout << mediaNumber++ << ".\n";
		cout << "----------------------\n";
		cout << "Name       : " << file.getName() << "\n";
		cout << "Size (KB)  : " << file.getSize() << "\n";
		cout << "View       : " << file.getViewNumber() << "\n";
		cout << "Type       : " << file.getType() << "\n";
		cout << "Genre      : " << file.getGenre() << "\n";
		cout << "Description: " << file.getDescription() << "\n\n";
	}
}

string DisplayController::inputSearchedString() {
	string searchedString;

	cout << "Please enter the media file name: ";
	cin >> searchedString;

	return searchedString;
}

FilterCriteria DisplayController::chooseFilterCriteria() {
	cout << "1. Type" << "\n";
	cout << "2. Genre" << "\n";
	cout << "Please choose the vriteria you want to filter by: ";

	int filterCriteria;
	cin >> filterCriteria;

	switch (filterCriteria)
	{
	case FilterCriteria::TYPE: return FilterCriteria::TYPE;
	case FilterCriteria::GENRE: return FilterCriteria::GENRE;
	}
}

string DisplayController::chooseFilterValue(FilterCriteria filterCriteria) {
	switch (filterCriteria)
	{
	case FilterCriteria::TYPE: return chooseFilterTypeCriteria();
	case FilterCriteria::GENRE: return chooseFilterGenreCriteria();
	}
}

string DisplayController::chooseFilterTypeCriteria() {
	vector<string> mediaTypes = _pMediaFileManager->getAllMediaTypes();

	int typeNumber = 1;
	for (const string& mediaType : mediaTypes) {
		cout << typeNumber++ << ". " << mediaType << "\n";
	}

	cout << "Please choose the media type you want to filter by: ";

	int filterTypeCriteria;
	cin >> filterTypeCriteria;

	switch (filterTypeCriteria)
	{
	case FilterTypeCriteria::VIDEO: return filterTypeCriteriaEnumToString(FilterTypeCriteria::VIDEO);
	case FilterTypeCriteria::AUDIO: return filterTypeCriteriaEnumToString(FilterTypeCriteria::AUDIO);
	}
}

string DisplayController::chooseFilterGenreCriteria() {
	vector<string> mediaGenres = _pMediaFileManager->getAllMediaGenres();

	int genreNumber = 1;
	for (const string& genre : mediaGenres) {
		cout << genreNumber++ << ". " << genre << "\n";
	}

	cout << "Please choose the genre you want to filter by.\n";

	int filterGenreCriteria;
	cin >> filterGenreCriteria;

	return mediaGenres[filterGenreCriteria - 1];
}