#pragma once

#define ROOTPATH "Media"
#define FILEPATH "Media\\media_files_list.txt"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <thread>
#include <windows.h>
#include <shellapi.h>

#include "FunctionNumber.h"
#include "FilterCriteria.h"
#include "MediaType.h"

#include "MediaFile.h"
#include "MediaFilesManager.h"
#include "DisplayController.h"
#include "CopyService.h"
#include "NamedPipeClient.h"
#include "FileSaveWorker.h"

#include "FileHelper.h"
#include "StringHelper.h"
#include "EnumHelper.h"

using namespace std;
using namespace EnumString;
namespace fs = std::filesystem;