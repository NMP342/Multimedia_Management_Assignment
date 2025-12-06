#include "pch.h"

DisplayController::DisplayController() {
	_pMediaFileManager = make_unique<MediaFilesManager>();
	_pMediaFileManager->initialize();
}

void DisplayController::displayFunctions() {
	cout << "\n\n";
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
	case EXIT:
		cout << "\nGoodbye!";
		return;
	}

	displayFunctions();
}

void DisplayController::displayMediaList(vector<MediaFile>& mediaList) {
	for (auto file : mediaList)
	{
		cout << "------------------------\n";
		cout << "Name       : " << file.getName() << "\n";
		cout << "Size (KB)  : " << file.getSize() << "\n";
		cout << "View       : " << file.getViewNumber() << "\n";
		cout << "Type       : " << file.getType() << "\n";
		cout << "Genre      : " << file.getGenre() << "\n";
		cout << "Description: " << file.getDescription() << "\n";
	}
}