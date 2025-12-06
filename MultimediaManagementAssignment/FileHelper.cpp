#include "pch.h"


void FileHelper::readMediaFilesFromRootPath(vector<MediaFile>& mediaList) {

	for (const auto& typeEntry : fs::directory_iterator(ROOTPATH))
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

				MediaFile file;
				file.setName(fileEntry.path().filename().string());
				file.setSize(static_cast<int>(fs::file_size(fileEntry.path()) / 1024));
				file.setType(fileType); // Video / Audio
				file.setGenre(genre);       // Horror / Action / Rock
				file.setDescription("No description");

				mediaList.push_back(file);
			}
		}
	}
}

void FileHelper::saveMediaListToFile(const vector<MediaFile>& mediaList)
{
	string filePath = ROOTPATH;
	filePath += "\\media_files_list.txt";
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
			<< file.getType() << "|"
			<< file.getGenre() << "|"
			<< file.getDescription() << "\n";
	}

	outFile.close();
}