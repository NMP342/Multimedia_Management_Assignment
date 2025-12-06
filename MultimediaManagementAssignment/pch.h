#pragma once

#define ROOTPATH "D:\\Training\\C++ From Basics to Advanced\\Multimedia_Management_Assignment\\Media"
#define FILEPATH "D:\\Training\\C++ From Basics to Advanced\\Multimedia_Management_Assignment\\Media\\media_files_list.txt"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>

#include "FunctionNumber.h"

#include "MediaFile.h"
#include "FileHelper.h"
#include "MediaFilesManager.h"
#include "DisplayController.h"

using namespace std;
namespace fs = std::filesystem;