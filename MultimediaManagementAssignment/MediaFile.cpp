#include<string>

using namespace std;

class MediaFile {
private:
	string m_name{};
	string m_type{};
	string m_genre{};
	int m_size{};
	string m_description{};
	string m_directory{};

public:
	string& getName() {
		return m_name;
	}

	void setName(string name) {
		m_name = name;
	}

	string& getType() {
		return m_type;
	}

	void setType(string type) {
		m_type = type;
	}

	string& getGenre() {
		return m_genre;
	}

	void setGenre(string genre) {
		m_genre = genre;
	}

	int& getSize() {
		return m_size;
	}

	void setSize(int size) {
		m_size = size;
	}

	string& getDescription() {
		return m_description;
	}

	void setDescription(string description) {
		m_description = description;
	}

	string& getDirectory() {
		return m_directory;
	}

	void setFirectory(string directory) {
		m_directory = directory;
	}
};