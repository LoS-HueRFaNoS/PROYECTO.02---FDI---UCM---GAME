#pragma once

#include "Font.h"
#include <string>

using namespace std;

/*
 *
 */
class FontsManager {
public:
	FontsManager();
	virtual ~FontsManager();

	// supposed to be called before start using the object
	virtual bool init() = 0;

	virtual Font* getFont(std::size_t tag) = 0;
	virtual bool loadFont(std::size_t tag, const string& fileName, int size) = 0;
};

