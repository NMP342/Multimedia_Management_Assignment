#pragma once

#include <windows.h>
#include <string>

using namespace std;

class NamedPipeClient {
public:
	pair<bool, string> sendMessageToNamedPipeServer(string& message);

private:
	const wchar_t* PIPE_NAME = L"\\\\.\\pipe\\PhysicalMediaFileHandlerProcess";
	HANDLE createNamedPipeClient();
	bool writeMessage(HANDLE hPipe, const string& message);
	bool readMessageWithTimeout(HANDLE hPipe);
};