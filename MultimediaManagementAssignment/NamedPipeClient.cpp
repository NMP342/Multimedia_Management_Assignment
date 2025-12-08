#include "pch.h"

HANDLE NamedPipeClient::createNamedPipeClient() {
	HANDLE hPipe = CreateFileW(
		PIPE_NAME,
		GENERIC_READ | GENERIC_WRITE,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,
		nullptr
	);

	if (hPipe == INVALID_HANDLE_VALUE) {
		cout << "Failed to create named pipe client: " << GetLastError() << "\n";
		return NULL;
	}

	return hPipe;
}

bool NamedPipeClient::writeMessage(HANDLE hPipe, const string& message) {
	DWORD bytesWritten = 0;

	bool writeResult = WriteFile(
		hPipe,
		message.c_str(),
		static_cast<DWORD>(message.size()),
		&bytesWritten,
		nullptr
	);

	return writeResult && bytesWritten == message.size();
}

bool NamedPipeClient::readMessageWithTimeout(HANDLE hPipe) {
	OVERLAPPED overlapped{};
	overlapped.hEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

	if (!overlapped.hEvent) {
		return false;
	}

	char buffer[1024];
	DWORD bytesRead = 0;

	BOOL readResult = ReadFile(
		hPipe,
		buffer,
		sizeof(buffer),
		&bytesRead,
		&overlapped
	);

	if (!readResult) {
		DWORD err = GetLastError();

		if (err != ERROR_IO_PENDING) {
			CloseHandle(overlapped.hEvent);
			return false;
		}
	}

	DWORD wait = WaitForSingleObject(overlapped.hEvent, 2000);

	if (wait == WAIT_TIMEOUT) {
		CancelIo(hPipe);
		CloseHandle(overlapped.hEvent);
		return false;
	}

	if (!GetOverlappedResult(hPipe, &overlapped, &bytesRead, FALSE)) {
		CloseHandle(overlapped.hEvent);
		return false;
	}

	buffer[bytesRead] = '\0';

	CloseHandle(overlapped.hEvent);
	return true;
}

pair<bool, string> NamedPipeClient::sendMessageToNamedPipeServer(string& message) {
	HANDLE hPipe = createNamedPipeClient();

	if (hPipe == NULL) {
		return { false, "Cannot connect to the server." };
	}

	bool writeResult = writeMessage(hPipe, message);
	if (!writeResult) {
		CloseHandle(hPipe);
		return {false, "Failed to send request to server."};
	}
	bool readResult = readMessageWithTimeout(hPipe);
	CloseHandle(hPipe);

	if (!readResult) return { false, "Failed to receive response from server." };
	return { true, "Connect to server successfully." };
}