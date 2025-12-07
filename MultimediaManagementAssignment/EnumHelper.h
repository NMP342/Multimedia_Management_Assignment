#pragma once

#include <string>
#include "FilterCriteria.h"

using namespace std;

namespace EnumString {

	static string filterCriteriaEnumToString(FilterCriteria filterCriteria) {
		switch (filterCriteria) {
		case FilterCriteria::TYPE:  return "type";
		case FilterCriteria::GENRE: return "genre";
		}
		return "unknown";
	}

	static string filterTypeCriteriaEnumToString(FilterTypeCriteria filterTypeCriteria) {
		switch (filterTypeCriteria) {
		case FilterTypeCriteria::VIDEO:  return "video";
		case FilterTypeCriteria::AUDIO: return "audio";
		}
		return "unknown";
	}
}
