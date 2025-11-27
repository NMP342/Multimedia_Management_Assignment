#pragma once
#include<string>

using namespace std;

class MediaFile {
private:
	string m_name{};
	string m_type{};
	string m_genre{};
	string m_size{};
	string m_description{};
	string m_directory{};

public:
	string& getName() {
		return m_name;
	}

	string setName(string name) {
		m_name = name;
	}

	string& getType() {
		return m_type;
	}

	string setType(string type) {
		m_type = type;
	}

	string& getGenre() {
		return m_genre;
	}

	string setGenre(string genre) {
		m_genre = genre;
	}

	string& getSize() {
		return m_size;
	}

	string setSize(string size) {
		m_size = size;
	}

	string& getDescription() {
		return m_description;
	}

	string setDescription(string description) {
		m_description = description;
	}

	string& getDirectory() {
		return m_directory;
	}

	string setFirectory(string directory) {
		m_directory = directory;
	}
};
