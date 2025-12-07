#include "pch.h"

pair<bool, string> CopyService::copyFileWithProgress(string& sourceDirectory, string& destinationDirectory, MediaFile& mediaFile, ProgressCallback showProgress) {
	fs::path source{ sourceDirectory };

	string mediaFileName = source.filename().string();
	string mediaFileDestination = destinationDirectory + "\\" + mediaFileName;
	int mediaFileSize = static_cast<int>(fs::file_size(source) / 1024);
	int mediaFileView = 0;

	mediaFile.setName(mediaFileName);
	mediaFile.setSize(mediaFileSize);
	mediaFile.setViewNumber(mediaFileView);
	mediaFile.setDirectory(mediaFileDestination);

	if (!fs::exists(source) || !fs::is_regular_file(source)) {
		return { false, "The media file directory is not existed/valid directory." };
	}

	if (!fs::exists(destinationDirectory)) {
		fs::create_directories(destinationDirectory);
	}

	if (fs::exists(mediaFileDestination)) {
		return { false, "The media file is existed." };
	}

	ifstream src(sourceDirectory, ios::binary);
	ofstream dst(mediaFileDestination, ios::binary);

	if (!src.is_open() || !dst.is_open())
		return { false, "Cannot open the media file. Please close all opening media file process." };

	uint64_t totalSize = filesystem::file_size(sourceDirectory);
	uint64_t copied = 0;

	const size_t bufferSize = 1024 * 1024;
	vector<char> buffer(bufferSize);

	while (src)
	{
		src.read(buffer.data(), bufferSize);
		streamsize bytesRead = src.gcount();

		if (bytesRead <= 0)
			break;

		dst.write(buffer.data(), bytesRead);
		copied += bytesRead;

		if (showProgress)
			showProgress(copied, totalSize);
	}

	return { true, "Upload media file successfully." };
}

