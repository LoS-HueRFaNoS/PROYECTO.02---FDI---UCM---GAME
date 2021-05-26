#include <cassert>
#include "ChatManager.h"
#include "../../ecs/ecs.h"
#include "../../Components/Transform.h"
#include "../../Components/Image.h"
#include "../../Utilities/SDL_macros.h"
#include "../../Utilities/InputHandler.h"
#include "../TheElementalMaze.h"

std::unique_ptr<ChatManager> ChatManager::instance_;

void ChatManager::init()
{
	SDL_Panel pan = game_->relativePanel(710,790,540,190,1,6,20,20,5,5);
	firstLine = RECT(pan.lcx, pan.lcy, pan.cw, pan.ch);
	marco = RECT(pan.x, pan.y, pan.w, pan.h);
	margin = pan.mh;
	chatSize = NUM_LINES;
	// color messages
	lineTypesMap_[linTy::Info] = hex2sdlcolor("#FFFFFFFF");
	lineTypesMap_[linTy::Experience] = hex2sdlcolor("#BBBB00FF");
	lineTypesMap_[linTy::DamageDone] = hex2sdlcolor("#FF0000FF");
	lineTypesMap_[linTy::DamageReceive] = hex2sdlcolor("#0055FFFF");
}

void ChatManager::moveUp(Entity* e)
{
	Transform* tr_ = GETCMP2(e, Transform);
	tr_->setPosY(tr_->getPos().getY() - firstLine.h);
}

void ChatManager::moveDown(Entity* e)
{
	Transform* tr_ = GETCMP2(e, Transform);
	tr_->setPosY(tr_->getPos().getY() + firstLine.h);
}

void ChatManager::drawLine(Entity* e)
{
	Transform* tr_ = GETCMP2(e, Transform);
	Image* img_ = GETCMP2(e, Image);
	double y = tr_->getPos().getY();
	if (checkTopDownMax(y)) {
		img_->draw(); 
	};
}

bool ChatManager::checkLineSize(std::string text, LineType type)
{
	bool cut = false;
	if (text.size() > NUM_LETTERS_IN_LINE) {
		string line = text.substr(0, NUM_LETTERS_IN_LINE);
		addLine(line, type);
		string line2 = text.substr(NUM_LETTERS_IN_LINE);
		addLine(line2, type);
		cut = true;
	}
	return cut;
}

void ChatManager::checkChatSize()
{
	if (entities.size() > chatSize) entities.begin()->get()->disable();
}

bool ChatManager::checkTopDownMax(int y)
{
	if (y >= marco.y + margin && y < double(marco.y) + marco.h - margin)
	{
		return true;
	}
	else return false;
}

void ChatManager::Init()
{
	assert(instance_.get() == nullptr);
	instance_.reset(new ChatManager(TheElementalMaze::instance()->getSDLGame()));
	instance_->init();
}

void ChatManager::addLine(std::string line, LineType type)
{
	if (!checkLineSize(line, type)) {
		for (auto it = entities.begin(); it != entities.end(); it++) {
			moveUp(it->get());
		}
		if (line.size() < NUM_LETTERS_IN_LINE) line.resize(NUM_LETTERS_IN_LINE, ' ');
		addLine<Line>(firstLine, line, lineTypesMap_[type]);
	}
}

void ChatManager::update()
{
	checkChatSize();
	Transform* tr_ = GETCMP2(entities.rbegin()->get(), Transform);
	double y = tr_->getPos().getY();

	InputHandler* ih_ = InputHandler::instance();
	if (ih_->mouseWheelEvent()) {
		if (checkTopDownMax(y))
		{
			if (ih_->getMouseWheelState(InputHandler::UP)) // away from the user
			{
				if (checkTopDownMax(y + firstLine.h)) {
					for (auto it = entities.begin(); it != entities.end(); it++) {
						moveDown(it->get());
					}
				}
			}
			else if (ih_->getMouseWheelState(InputHandler::DOWN)) // toward the user
			{
				if (checkTopDownMax(y - firstLine.h)) {
					for (auto it = entities.begin(); it != entities.end(); it++) {
						moveUp(it->get());
					}
				}
			}
		}
	}
	
}

void ChatManager::draw()
{
	for (auto it = entities.begin(); it != entities.end(); it++) {
		drawLine(it->get());
	}
}
