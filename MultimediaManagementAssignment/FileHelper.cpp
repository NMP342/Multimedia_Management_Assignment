#include "pch.h"

string FileHelper::_filePath;
string FileHelper::_rootPath;
mutex FileHelper::_mutex;

void FileHelper::initializeMediaFiles(vector<MediaFile>& mediaList) {
	string filePath = getFilePath();

	if (!fs::exists(filePath)) {
		string rootPath = getRootPath();

		readMediaFilesFromRootPath(mediaList);
		saveMediaListToFile(mediaList);
	}
	else {
		readMediaListFromFile(mediaList);
	}
}

void FileHelper::readMediaFilesFromRootPath(vector<MediaFile>& mediaList) {
	mediaList.clear();

	string rootPath = getRootPath();
	for (const auto& typeEntry : fs::directory_iterator(rootPath))
	{
		if (!typeEntry.is_directory())
			continue;

		std::string fileType = typeEntry.path().filename().string();

		for (const auto& genreEntry : fs::directory_iterator(typeEntry.path()))
		{
			if (!genreEntry.is_directory())
				continue;

			std::string genre = genreEntry.path().filename().string();

			for (const auto& fileEntry :
				fs::directory_iterator(genreEntry.path()))
			{
				if (!fileEntry.is_regular_file())
					continue;

				string fileName = fileEntry.path().filename().string();
				int size = static_cast<int>(fs::file_size(fileEntry.path()) / 1024);
				int viewNumber = 0;
				string description = "No description";
				string directory = fileEntry.path().string();

				MediaFile file;
				file.setName(fileName);
				file.setSize(size);
				file.setViewNumber(viewNumber);
				file.setType(fileType); 
				file.setGenre(genre);
				file.setDescription(description);
				file.setDirectory(directory);

				mediaList.push_back(file);
			}
		}
	}
}

void FileHelper::readMediaListFromFile(vector<MediaFile>& mediaList) {
	lock_guard<mutex> lock(_mutex);

	string filePath = getFilePath();

	std::ifstream inFile(filePath);
	if (!inFile.is_open())
	{
		std::cerr << filePath << '\n';
		std::cerr << "Cannot open file for reading!\n";
		return;
	}

	std::string line;

	while (std::getline(inFile, line))
	{
		if (line.empty()) {
			continue;
		}

		auto fields = StringHelper::splitStringByDelimiter(line, '|');

		if (fields.size() != 7)
			continue;

		string name = fields[0];
		int size = stoi(fields[1]);
		int viewNumber = stoi(fields[2]);
		string type = fields[3];
		string genre = fields[4];
		string description = fields[5];
		string directory = fields[6];

		MediaFile file;
		file.setName(name);
		file.setSize(size);
		file.setViewNumber(viewNumber);
		file.setType(type);
		file.setGenre(genre);
		file.setDescription(description);
		file.setDirectory(directory);

		mediaList.push_back(file);
	}

	inFile.close();
}

void FileHelper::saveMediaListToFile(const vector<MediaFile>& mediaList)
{
	lock_guard<mutex> lock(_mutex);

	//this_thread::sleep_for(chrono::milliseconds(20000));
	//cout << "Start save files.\n";

	string filePath = getFilePath();
	std::ofstream outFile(filePath);

	if (!outFile.is_open())
	{
		std::cerr << filePath << '\n';
		std::cerr << "Cannot open file for writing!\n";
		return;
	}

	for (auto file : mediaList)
	{
		outFile
			<< file.getName() << "|"
			<< file.getSize() << "|"
			<< file.getViewNumber() << "|"
			<< file.getType() << "|"
			<< file.getGenre() << "|"
			<< file.getDescription() << "|"
			<< file.getDirectory() << "\n";
	}

	outFile.close();
}

bool FileHelper::appendMediaFileToFile(MediaFile& mediaFile) {
	lock_guard<mutex> lock(_mutex);

	string filePath = getFilePath();
	ofstream outFile(filePath, std::ios::out | std::ios::app);

	if (!outFile)
	{
		std::cerr << "Cannot open file for appending: " << filePath << '\n';
		return false;
	}

	outFile
		<< mediaFile.getName() << "|"
		<< mediaFile.getSize() << "|"
		<< mediaFile.getViewNumber() << "|"
		<< mediaFile.getType() << "|"
		<< mediaFile.getGenre() << "|"
		<< mediaFile.getDescription() << "|"
		<< mediaFile.getDirectory() << "\n";

	outFile.close();
	return true;
}

string FileHelper::getFilePath() {
	if (!_filePath.empty()) {
		return _filePath;
	}

	string currentPath = fs::current_path().parent_path().string() + "\\";
	currentPath += FILEPATH;
	_filePath = currentPath;

	return _filePath;
}

string FileHelper::getRootPath() {
	if (!_rootPath.empty()) {
		return _rootPath;
	}

	string currentPath = fs::current_path().parent_path().string() + "\\";
	currentPath += ROOTPATH;
	_rootPath = currentPath;

	return _rootPath;
}

