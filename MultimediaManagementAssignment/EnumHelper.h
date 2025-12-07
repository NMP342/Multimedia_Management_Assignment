#pragma once

#include <string>
#include "FilterCriteria.h"
#include "MediaType.h"

using namespace std;

namespace EnumString {

	static string filterCriteriaEnumToString(FilterCriteria filterCriteria) {
		switch (filterCriteria) {
		case FilterCriteria::TYPE:  return "Type";
		case FilterCriteria::GENRE: return "Genre";
		}
		return "Unknown";
	}

	static string mediaTypeEnumToString(MediaType mediaType) {
		switch (mediaType) {
		case MediaType::VIDEO:  return "Video";
		case MediaType::AUDIO: return "Audio";
		}
		return "Unknown";
	}
}
