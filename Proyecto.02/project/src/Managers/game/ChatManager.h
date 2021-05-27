#pragma once
#include <string>
#include "../../ecs/Manager.h"
#include "../TheElementalMaze.h"
#include "../../GameObjects/SDL_Objects.h"

enum class LineType {
	Info,
	Experience,
	DamageDone,
	DamageReceive
}; using linTy = LineType;
const int NUM_LINES = 20;
const int NUM_LETTERS_IN_LINE = 30; // 70

class ChatManager : public EntityManager {
private:
	ChatManager(SDLGame* game) : EntityManager(game), firstLine(), marco(), margin(), chatSize() {};
	
	template<typename T, typename ... TArgs>
	T* addLine(TArgs&& ... mArgs)
	{
		T* b(new T(game_, this));
		std::unique_ptr<Entity> uPtr(b);
		entities.emplace_back(std::move(uPtr));
		b->init(std::forward<TArgs>(mArgs)...);
		return b;
	}
	void removeLine(Line* e);

	void init();
	void moveUp(Entity* e);
	void moveDown(Entity* e);
	void drawLine(Entity* e);
	bool checkLineSize(std::string line, LineType type);
	void checkChatSize();
	bool checkTopDownMax(int y);
	int getFirstLinePOS();
	void clean();
	void cleanALL();


public:
	static void Init();

	static ChatManager* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	void add(std::string line, LineType type);
	void addLine(std::string line, LineType type);
	void clean_n_addLine(std::string line, LineType type);
	void update() override;
	void draw() override;

	virtual ~ChatManager() {};

private:
	static std::unique_ptr<ChatManager> instance_;
	SDL_Rect firstLine;
	SDL_Rect marco;
	double margin;
	int chatSize;
	std::map<LineType, SDL_Color> lineTypesMap_;
	
};
