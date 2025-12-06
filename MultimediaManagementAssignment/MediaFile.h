#pragma once

#include <string>

using namespace std;

class MediaFile {
public:
	string& getName();
	string& getType();
	string& getGenre();
	int& getSize();
	int& getViewNumber();
	string& getDescription();
	string& getDirectory();

	void setName(string& name);
	void setType(string& type);
	void setGenre(string& genre);
	void setSize(int& size);
	void setViewNumber(int& viewNumber);
	void setDescription(string& description);
	void setDirectory(string& directory);

private:
	string _name;
	string _type;
	string _genre;
	int _size;
	int _viewNumber;
	string _description;
	string _directory;
};
