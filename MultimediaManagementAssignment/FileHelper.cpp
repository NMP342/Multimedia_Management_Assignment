#include <iostream>
#include<string>
#include<filesystem>
#include "MediaFile.cpp"

using namespace std;
namespace fs = std::filesystem;



class FileHelper {
public:

	static void ReadMediaRoot(vector<MediaFile>& mediaList) {
        string rootPath = "D:\\C_Plus_Projects\\MultimediaManagementAssignment\\Media";

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

    static void PrintMediaList(const std::vector<MediaFile>& mediaList)
    {
        for (MediaFile file : mediaList)
        {
            std::cout << "------------------------\n";
            std::cout << "Name       : " << file.getName() << "\n";
            std::cout << "Size (KB)  : " << file.getSize() << "\n";
            std::cout << "Type       : " << file.getType() << "\n";
            std::cout << "Genre      : " << file.getGenre() << "\n";
            std::cout << "Description: " << file.getDescription() << "\n";
        }
    }
};