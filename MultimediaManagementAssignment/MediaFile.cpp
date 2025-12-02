#include "pch.h"

string& MediaFile::GetName() {
	return m_name;
}

string& MediaFile::GetType() {
	return m_type;
}

string& MediaFile::GetGenre() {
	return m_genre;
}

int& MediaFile::GetSize() {
	return m_size;
}

string& MediaFile::GetDescription() {
	return m_description;
}

string& MediaFile::GetDirectory() {
	return m_directory;
}

void MediaFile::SetName(string name) {
	m_name = name;
}

void MediaFile::SetType(string type) {
	m_type = type;
}

void MediaFile::SetGenre(string genre) {
	m_genre = genre;
}

void MediaFile::SetSize(int size) {
	m_size = size;
}

void MediaFile::SetDescription(string description) {
	m_description = description;
}

void MediaFile::SetDirectory(string directory) {
	m_directory = directory;
}