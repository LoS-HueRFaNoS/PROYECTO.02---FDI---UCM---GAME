#pragma once
#include "../Structures/messages.h"
#include "../ecs/Component.h"
#include "../GameObjects/SDL_Objects.h"
#include "../GameObjects/Button.h"

class InterfazManager;

class TutorialManager : public Component {
private:
	InterfazManager* manager_;
	bool on_receive_message;

	SDL_Object* fondo;
	SDL_Object* cartel;
	ButtonCloseMessage* bt_exit;

	void show(MsgId mID);
	void actionMsg();

	void initAchievements();
	bool tutorialCompleted();

	void autoCompleted();
	void resetTutorial();

	void setUIPause();
	void setUIContinue();

public:
	TutorialManager(InterfazManager* i);
	virtual ~TutorialManager() {
		if (cartel != nullptr) {
			delete fondo; fondo = nullptr;
			delete cartel; cartel = nullptr;
			bt_exit->disable(); bt_exit = nullptr;
		}
		achievementsMap_.clear();
	};

	void init() override;
	void update() override;
	void draw() override {};
	void drawTutorial();

	void send(const Message& msg);
	void flushMsgsQueue();

	void exitMessage();

private:
	std::vector<Message> msgsQueue_;
	SDL_Rect cartel_dest, fondo_dest;
	uint index;

	std::map<MsgId, bool> achievementsMap_;
	MsgId activeMsg;
};
