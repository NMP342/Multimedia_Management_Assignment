#include "pch.h"


void FileHelper::ReadMediaFilesFromRootPath(vector<MediaFile>& mediaList) {

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
				file.SetName(fileEntry.path().filename().string());
				file.SetSize(static_cast<int>(fs::file_size(fileEntry.path()) / 1024));
				file.SetType(fileType); // Video / Audio
				file.SetGenre(genre);       // Horror / Action / Rock
				file.SetDescription("No description");

				mediaList.push_back(file);
			}
		}
	}
}

void FileHelper::SaveMediaListToFile(const vector<MediaFile>& mediaList)
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
			<< file.GetName() << "|"
			<< file.GetSize() << "|"
			<< file.GetType() << "|"
			<< file.GetGenre() << "|"
			<< file.GetDescription() << "\n";
	}

	outFile.close();
}