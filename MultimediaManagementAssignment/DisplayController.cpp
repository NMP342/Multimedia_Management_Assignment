#include "pch.h"

DisplayController::DisplayController() {
	_pMediaFileManager = make_unique<MediaFilesManager>();
	_pMediaFileManager->initialize();
}

void DisplayController::displayFunctions() {
	cout << "\n";
	cout << "=================MULTIMEDIA MANAGEMENT SYSTEM================" << "\n\n";
	cout << "1. Display the media files list." << '\n';
	cout << "2. Upload media file." << '\n';
	cout << "3. Search media file by name." << '\n';
	cout << "4. Filter media files list." << '\n';
	cout << "5. Play media file." << '\n';
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
	case UPLOAD: {
		MediaFile mediaFile{};
		string sourceDirectory = inputMediaFileSourceDirectory();
		string mediaFileType = chooseDestinationMediaFileType(mediaFile);
		string mediaFileGenre = chooseDestinationMediaFileGenre(mediaFile, mediaFileType);
		string destinationDirectory = createMediaFileDestinationDirectory(mediaFileType, mediaFileGenre);
		inputMediaFileDescription(mediaFile);

		pair<bool, string> downloadResult = _pMediaFileManager->downloadMediaFile(
			sourceDirectory,
			destinationDirectory,
			mediaFile,
			[this](uint64_t copied, uint64_t total) {
				showProgress(copied, total);
			});

		handleDownloadResult(downloadResult);

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
	case PLAY: {
		vector<MediaFile>& mediaList = _pMediaFileManager->getAllMediaFiles();
		displayMediaList(mediaList);
		
		MediaFile& mediaFile = chooseMediaFileToPlay(mediaList);
		pair<bool, string> playResult = _pMediaFileManager->playMediaFile(mediaFile);

		handlePlayResult(playResult);

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

	// ====== Header ======
	cout << left
		<< setw(7) << "Number" << " | "
		<< setw(35) << "Name" << " | "
		<< setw(10) << "Size(KB)" << " | "
		<< setw(8) << "Views" << " | "
		<< setw(10) << "Type" << " | "
		<< setw(10) << "Genre" << " | "
		<< setw(20) << "Description"
		<< "\n";

	// ====== Separator ======
	cout << string(7, '-') << "-+-"
		<< string(35, '-') << "-+-"
		<< string(10, '-') << "-+-"
		<< string(8, '-') << "-+-"
		<< string(10, '-') << "-+-"
		<< string(10, '-') << "-+-"
		<< string(20, '-')
		<< "\n";

	// ====== Rows ======
	for (auto& file : mediaList) {
		cout << left
			<< setw(7) << mediaNumber++ << " | "
			<< setw(35) << fitText(file.getName(), 35) << " | "
			<< setw(10) << file.getSize() << " | "
			<< setw(8) << file.getViewNumber() << " | "
			<< setw(10) << fitText(file.getType(), 10) << " | "
			<< setw(10) << fitText(file.getGenre(), 10) << " | "
			<< setw(20) << fitText(file.getDescription(), 20)
			<< "\n";
	}
}

string DisplayController::fitText(const string& text, size_t width)
{
	if (text.length() <= width)
		return text;
	return text.substr(0, width - 3) + "...";
}

string DisplayController::inputMediaFileSourceDirectory() {
	cout << "Please enter your media file directory:\n";

	cin.ignore();
	string sourceDirectory;
	getline(cin, sourceDirectory);

	return sourceDirectory;
}

string DisplayController::chooseDestinationMediaFileType(MediaFile& mediaFile) {
	const vector<string> mediaTypes = _pMediaFileManager->getAllMediaTypes();

	int typeNumber = 1;
	for (const auto& mediaType : mediaTypes) {
		cout << typeNumber++ << ". " << mediaType << "\n";
	}

	cout << "Please choose the media type: ";

	int chosenType;
	cin >> chosenType;

	switch (chosenType)
	{
	case MediaType::VIDEO: {
		string mediaType = mediaTypeEnumToString(VIDEO);
		mediaFile.setType(mediaType);

		return mediaType;
	}
	case MediaType::AUDIO: {
		string mediaType = mediaTypeEnumToString(AUDIO);
		mediaFile.setType(mediaType);

		return mediaTypeEnumToString(AUDIO);
	}
	}
}

string DisplayController::chooseDestinationMediaFileGenre(MediaFile& mediaFile, const string& type) {
	const vector<string> mediaGenres = _pMediaFileManager->getMediaGenresByType(type);

	int genreNumber = 1;
	for (const auto& genre : mediaGenres) {
		cout << genreNumber++ << ". " << genre << "\n";
	}
	cout << "0. New genre\n";
	cout << "Please choose the media file genre: ";

	int chosenGenre;
	cin >> chosenGenre;

	if (chosenGenre == 0) {
		cout << "Please enter new genre name (only alphabet, number and space character): ";

		cin.ignore();
		string newGenre;
		getline(cin, newGenre);

		string mediaGenre = StringHelper::toUpperCamelCase(newGenre);
		mediaFile.setGenre(mediaGenre);

		_pMediaFileManager->addNewGenre(mediaGenre);

		return mediaGenre;
	}

	string mediaGenre = mediaGenres[chosenGenre - 1];
	mediaFile.setGenre(mediaGenre);

	return mediaGenre;
}

string DisplayController::createMediaFileDestinationDirectory(const string& mediaType, const string& mediaGenre) {
	string destinationDirectory = FileHelper::getRootPath();
	destinationDirectory += "\\" + mediaType + "\\" + mediaGenre;

	return destinationDirectory;
}

void DisplayController::inputMediaFileDescription(MediaFile& mediaFile) {
	cout << "Please enter the media file description.\n";

	string mediaFileDescription;
	getline(cin, mediaFileDescription);
	mediaFile.setDescription(mediaFileDescription);
}

void DisplayController::showProgress(uint64_t copied, uint64_t total) {
	int percent = static_cast<int>(copied * 100 / total);

	cout << "Uploading: " << percent << "% ("
		<< copied / 1024 << " / "
		<< total / 1024 << " KB)"
		<< "\n";
	cout.flush();

	if (copied == total)
		cout << "Uploading completed!\n";
}

void DisplayController::handleDownloadResult(pair<bool, string>& downloadResult) {
	if (downloadResult.first) {
		cout << downloadResult.second << "\n";
	}
	else {
		cout << "Upload media file failed: " << downloadResult.second << "\n";
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
	cout << "Please choose the criteria you want to filter by: ";

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
	const vector<string> mediaTypes = _pMediaFileManager->getAllMediaTypes();

	int typeNumber = 1;
	for (const string& mediaType : mediaTypes) {
		cout << typeNumber++ << ". " << mediaType << "\n";
	}

	cout << "Please choose the media type you want to filter by: ";

	int filterTypeCriteria;
	cin >> filterTypeCriteria;

	switch (filterTypeCriteria)
	{
	case MediaType::VIDEO: return mediaTypeEnumToString(MediaType::VIDEO);
	case MediaType::AUDIO: return mediaTypeEnumToString(MediaType::AUDIO);
	}
}

string DisplayController::chooseFilterGenreCriteria() {
	const vector<string> mediaGenres = _pMediaFileManager->getAllMediaGenres();

	int genreNumber = 1;
	for (const string& genre : mediaGenres) {
		cout << genreNumber++ << ". " << genre << "\n";
	}

	cout << "Please choose the genre you want to filter by.\n";

	int filterGenreCriteria;
	cin >> filterGenreCriteria;

	return mediaGenres[filterGenreCriteria - 1];
}

MediaFile& DisplayController::chooseMediaFileToPlay(vector<MediaFile>& mediaList) {
	cout << "Please choose the media file number you want to play: ";

	int chosenMediaFileNumber;
	cin >> chosenMediaFileNumber;

	return mediaList[chosenMediaFileNumber - 1];
}

void DisplayController::handlePlayResult(const pair<bool, string>& playResult) {
	if (playResult.first) {
		cout << "Open file successfully.\n";
	}
	else {
		cout << "Open file failed: " << playResult.second << "\n";
	}
}