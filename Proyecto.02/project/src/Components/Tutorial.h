#pragma once
#include "../Structures/messages.h"
#include "../ecs/Component.h"
#include "../GameObjects/SDL_Objects.h"
#include "../GameObjects/Button.h"

class InterfazManager;

class TutorialManager : public Component {
private:
	InterfazManager* iManager;
	bool on_receive_message;

	SDL_Object* fondo;
	SDL_Object* cartel;
	Button* bt_exit;

	void show(MsgId mID);
	void actionMsg();

	void initAchievements();
	bool tutorialCompleted();

	void autoCompleted();
	void resetTutorial();

public:
	TutorialManager(InterfazManager* i);
	virtual ~TutorialManager() {
		fondo->disable(); fondo = nullptr;
		cartel->disable(); cartel = nullptr;
		bt_exit->disable(); bt_exit = nullptr;
		achievementsMap_.clear();
	};

	void init() override;
	void update() override;
	void draw() override;

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
