// MultimediaManagementAssignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

static void PrintMediaList(const std::vector<MediaFile>& mediaList)
{
    for (MediaFile file : mediaList)
    {
        std::cout << "------------------------\n";
        std::cout << "Name       : " << file.GetName() << "\n";
        std::cout << "Size (KB)  : " << file.GetSize() << "\n";
        std::cout << "Type       : " << file.GetType() << "\n";
        std::cout << "Genre      : " << file.GetGenre() << "\n";
        std::cout << "Description: " << file.GetDescription() << "\n";
    }
}

int main()
{
	vector<MediaFile> mediaFilesList;
	FileHelper::ReadMediaFilesFromRootPath(mediaFilesList);
	FileHelper::SaveMediaListToFile(mediaFilesList);
	PrintMediaList(mediaFilesList);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
