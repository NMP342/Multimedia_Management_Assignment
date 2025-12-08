#pragma once

#define ROOTPATH "D:\\Training\\C++ From Basics to Advanced\\Multimedia_Management_Assignment\\Media"
#define FILEPATH "D:\\Training\\C++ From Basics to Advanced\\Multimedia_Management_Assignment\\Media\\media_files_list.txt"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <windows.h>
#include <shellapi.h>

#include "FunctionNumber.h"
#include "FilterCriteria.h"
#include "MediaType.h"

#include "MediaFile.h"
#include "MediaFilesManager.h"
#include "DisplayController.h"
#include "CopyService.h"
#include "OpenFileService.h"
#include "NamedPipeClient.h"

#include "FileHelper.h"
#include "StringHelper.h"
#include "EnumHelper.h"

using namespace std;
using namespace EnumString;
namespace fs = std::filesystem;