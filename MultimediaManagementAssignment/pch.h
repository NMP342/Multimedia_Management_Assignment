#pragma once

#define ROOTPATH "D:\\Training\\C++ From Basics to Advanced\\Multimedia_Management_Assignment\\Media"
#define FILEPATH "D:\\Training\\C++ From Basics to Advanced\\Multimedia_Management_Assignment\\Media\\media_files_list.txt"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include "FunctionNumber.h"
#include "FilterCriteria.h"

#include "MediaFile.h"
#include "MediaFilesManager.h"
#include "DisplayController.h"

#include "FileHelper.h"
#include "StringHelper.h"
#include "EnumHelper.h"

using namespace std;
using namespace EnumString;
namespace fs = std::filesystem;