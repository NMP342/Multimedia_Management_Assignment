#include "pch.h"

string& MediaFile::getName() {
	return _name;
}

string& MediaFile::getType() {
	return _type;
}

string& MediaFile::getGenre() {
	return _genre;
}

int& MediaFile::getSize() {
	return _size;
}

string& MediaFile::getDescription() {
	return _description;
}

string& MediaFile::getDirectory() {
	return _directory;
}

void MediaFile::setName(string name) {
	_name = name;
}

void MediaFile::setType(string type) {
	_type = type;
}

void MediaFile::setGenre(string genre) {
	_genre = genre;
}

void MediaFile::setSize(int size) {
	_size = size;
}

void MediaFile::setDescription(string description) {
	_description = description;
}

void MediaFile::setDirectory(string directory) {
	_directory = directory;
}