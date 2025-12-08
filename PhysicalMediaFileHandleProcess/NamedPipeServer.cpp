#include "pch.h"

NamedPipeServer::NamedPipeServer() {
	_pOpenFileService = make_unique<OpenFileService>();
}

HANDLE NamedPipeServer::createNamedPipeServer() {
	HANDLE hPipe = CreateNamedPipeW(
		PIPE_NAME,
		PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,
		PIPE_TYPE_MESSAGE |
		PIPE_READMODE_MESSAGE |
		PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		1024,
		1024,
		0,
		nullptr
	);

	if (hPipe == INVALID_HANDLE_VALUE) {
		cout << "Failed to create named pipe server: " << GetLastError() << "\n";
		return NULL;
	}

	return hPipe;
}

bool NamedPipeServer::readMessageWithTimeOut(HANDLE hPipe, string& message) {
	OVERLAPPED ov{};
	ov.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

	if (!ov.hEvent) {
		return false;
	}

	char buffer[1024];
	DWORD bytesRead = 0;

	BOOL result = ReadFile(
		hPipe,
		buffer,
		sizeof(buffer) - 1,
		nullptr,
		&ov
	);

	if (!result && GetLastError() != ERROR_IO_PENDING) {
		CloseHandle(ov.hEvent);
		return false;
	}

	DWORD wait = WaitForSingleObject(ov.hEvent, 2000);

	if (wait == WAIT_TIMEOUT) {
		CancelIo(hPipe);
		CloseHandle(ov.hEvent);
		return false;
	}

	GetOverlappedResult(hPipe, &ov, &bytesRead, FALSE);

	buffer[bytesRead] = '\0';
	message.assign(buffer, buffer + bytesRead);

	CloseHandle(ov.hEvent);
	return true;
}

void NamedPipeServer::execute() {
	while (true) {
		HANDLE hPipe = createNamedPipeServer();

		if (hPipe == NULL) {
			cout << "Cannot create named pipe.\n";
			return;
		}

		cout << "Waiting for client...\n";

		if (!ConnectNamedPipe(hPipe, nullptr)) {
			CloseHandle(hPipe);
		}

		string message;
		char buffer[1024];
		DWORD bytesRead;

		readMessageWithTimeOut(hPipe, message);

		cout << "Client message: " << message << "\n";

		auto resultMessage = handleMessageFromClient(message);

		DWORD bytesWritten;
		WriteFile(
			hPipe,
			resultMessage.c_str(),
			static_cast<DWORD>(resultMessage.size()),
			&bytesWritten,
			nullptr
		);

		CloseHandle(hPipe);
	}
}

string NamedPipeServer::handleMessageFromClient(string& message) {
	vector<string> fields = StringHelper::splitStringByDelimiter(message, '|');
	string functionString = fields[0];

	pair<bool, string> result;

	if (functionString == "PLAY") {
		result = handlePlayFunction(fields[1]);
	}

	string resultMessage = functionString + "|" + (result.first ? "true" : "false") + "|" + result.second;
	return resultMessage;
}

pair<bool, string> NamedPipeServer::handlePlayFunction(const string& mediaFileDirectory) {
	auto playResult = _pOpenFileService->openFile(mediaFileDirectory);
	return playResult;
}