#include "TextBlockResources.h"
#include "../../GameObjects/SDL_Objects.h"
#include "../../Components/Transform.h"

//--- PUBLIC -------------------------------------------------------------------------

void TextBlockResources::Init(SDL_Rect bottom_elem, tb_Mngr* mngr)
{
	bottomElement_ = bottom_elem; 
	mngr_ = mngr;
	LineTypes::Init();
	ElementsResources::Init(set_FE::DOWN);
}

// checks if they are in their standar position and then insert a new line
void TextBlockResources::add(std::string line, LineColor type)
{
	reset(mngr_->entities, bottomElement_, limits_);
	addLine(line, type);
}

// cleans all the chat and insert a new line, it can be a title
void TextBlockResources::clean_n_addLine(std::string line, LineColor type, bool makeTitle)
{
	cleanALL(mngr_->entities);
	isTitle_ = makeTitle;
	addLine(line, type);
}

//--- PRIVATE ------------------------------------------------------------------------

// inserts another line, checking the line size and the format
void TextBlockResources::addLine(std::string line, LineColor type)
{
	if (!checkLineSize(line, type)) {
		for (auto it = mngr_->entities.begin(); it != mngr_->entities.end(); it++) {
			moveUp(it->get(), bottomElement_.h);
		}
		if (line.size() > 0) {
			line = formatLine(line);
			mngr_->addLine(bottomElement_, line, lineTypesMap_[type], isTitle_);
			if (isTitle_) isTitle_ = false;
		} 
		else {
			int a = 0;
		}
	}
}

// checks the size of the line, if it exceeds the limit the line will be cut
bool TextBlockResources::checkLineSize(std::string line, LineColor type)
{
	bool cut = false;
	if (line.size() > lineLetters_) {
		string lin = cutLine(line);
		addLine(lin, type);
		string lin2 = line.substr(lin.size());
		addLine(lin2, type);
		cut = true;
	}
	return cut;
}

//--- FORMATS -------------------------------------------------------------------------

// cuts the line to the limit, avoiding to cut the last word
string TextBlockResources::cutLine(string line)
{
	string cut;
	if (line.at(lineLetters_) != ' ' && line.at(size_t(lineLetters_) + 1) != ' ') {
		string aux = line.substr(0, lineLetters_);
		size_t n = aux.rfind(' ', lineLetters_);
		cut = aux.substr(0, n + 1);
	}
	else {
		cut = line.substr(0, lineLetters_);
	}
	return cut;
}

// formats line to the size given
string TextBlockResources::formatLine(string line)
{
	if (line.front() == ' ') line.erase(line.begin());
	if (line.size() < lineLetters_) line.resize(lineLetters_, ' ');
	return line;
}
