#include <iostream>
#include <fstream>
#include<string>
#include<filesystem>
#include "MediaFile.cpp"
#define PATH "D:\\Training\\C++ From Basics To Advanced\\Multimedia_Management_Assignment\\Media"

using namespace std;
namespace fs = std::filesystem;



class FileHelper {
public:
	static void ReadMediaRoot(vector<MediaFile>& mediaList) {

        for (const auto& typeEntry : fs::directory_iterator(PATH))
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

    static void SaveMediaListToFile(
        const std::vector<MediaFile>& mediaList)
    {
        string filePath = PATH;
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