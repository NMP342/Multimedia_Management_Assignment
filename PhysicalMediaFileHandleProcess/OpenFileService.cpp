#include "pch.h"

pair<bool, string> OpenFileService::openFile(const string& fileDirectory) {
    if (fileDirectory.empty())
        return { false, "The file directory is empty." };

    HINSTANCE result = ShellExecuteA(
        nullptr,            // hwnd
        "open",              // operation
        fileDirectory.c_str(),    // file
        nullptr,             // parameters
        nullptr,             // directory
        SW_SHOWNORMAL
    );

    int res = reinterpret_cast<intptr_t>(result);

    if (res > 32) {
        return { true, "Open file successfully." };
    }
    else if (res == SE_ERR_FNF) {
        return { false, "File is not found." };
    }
    else if (res == SE_ERR_NOASSOC) {
        return { false, "There is no app on the computer to open this file." };
    }

    return { false, "Unknown error." };
}