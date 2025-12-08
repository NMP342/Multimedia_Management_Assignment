#pragma once

#include <windows.h>
#include <string>
#include "OpenFileService.h"

using namespace std;

class NamedPipeServer {
public:
	NamedPipeServer();
	void execute();

private:
	unique_ptr<OpenFileService> _pOpenFileService;

	const wchar_t* PIPE_NAME = L"\\\\.\\pipe\\PhysicalMediaFileHandlerProcess";
	HANDLE createNamedPipeServer();
	bool readMessageWithTimeOut(HANDLE hPipe, string& message);
	string handleMessageFromClient(string& message);
	pair<bool, string> handlePlayFunction(const string& mediaFileDirectory);
};
