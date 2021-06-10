#pragma once
#include <string>
#include "../../ecs/Manager.h"
#include "../TheElementalMaze.h"
#include "../../GameObjects/SDL_Objects.h"

enum class LineColor {
	White,
	Yellow,
	Green,
	Red,
	Blue
}; using linCol = LineColor;
using Tupple = Vector2D;
// valores por defecto
const int NUM_LINES = 20;
const int NUM_LETTERS_IN_LINE = 30;

class ChatManager : public EntityManager {
private:
	ChatManager(SDLGame* game) : EntityManager(game), bottomLine(), marco(), tuppleLimits(), isTitle(false), fondo_(nullptr) {};
	
	template<typename T, typename ... TArgs>
	T* addLine(TArgs&& ... mArgs)
	{
		T* b(new T(game_, this));
		std::unique_ptr<Entity> uPtr(b);
		entities.emplace_back(std::move(uPtr));
		b->init(std::forward<TArgs>(mArgs)...);
		return b;
	}

	void init();
	void initialValues();

	void moveUp(Entity* e);
	void moveDown(Entity* e);

	bool checkLineSize(std::string line, LineColor type);
	void checkChatSize();
	bool checkTopDownMax(int y);

	bool isMouseIN();
	string cutLine(string line);
	string formatLine(string line);

	void reset();
	void cleanALL();

	void addLine(std::string line, LineColor type);
	void drawLine(Entity* e);


public:
	static void Init();

	static ChatManager* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	void add(std::string line, LineColor type);
	void clean_n_addLine(std::string line, LineColor type, bool makeTitle = false);

	void update() override;
	void draw() override;

	virtual ~ChatManager() {};

private:
	static std::unique_ptr<ChatManager> instance_;
	SDL_Rect bottomLine;
	SDL_Rect marco;
	Tupple tuppleLimits;

	bool isTitle;
	std::map<LineColor, SDL_Color> lineTypesMap_;

	Entity* fondo_;
	// valores por defecto
	int numLines = NUM_LINES;
	int lineNL = NUM_LETTERS_IN_LINE;
	
};
