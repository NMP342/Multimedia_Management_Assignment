#pragma once

#include <string>

using namespace std;

class MediaFile {
public:
	string& GetName();
	string& GetType();
	string& GetGenre();
	int& GetSize();
	string& GetDescription();
	string& GetDirectory();

	void SetName(string name);
	void SetType(string type);
	void SetGenre(string genre);
	void SetSize(int size);
	void SetDescription(string description);
	void SetDirectory(string directory);

private:
	string m_name;
	string m_type;
	string m_genre;
	int m_size;
	string m_description;
	string m_directory;
};
