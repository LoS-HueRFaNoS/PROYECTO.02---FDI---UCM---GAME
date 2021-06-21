#pragma region TextBlock
#include "../ecs/Manager.h"
#include "../Utilities/interfaz/TextBlockResources.h"
#include "../Managers/game/TextBlockManager.h"
#include "../Templates/interfaz/ObjectPanel.h"


const int NUM_LINES = 20;

class TextBlock : public TextBlockManager, public ObjectPanel, public TextBlockResources
{
private:
	Entity* fondo_ = nullptr;
	int numLines_ = NUM_LINES;

public:
	TextBlock(SDLGame* game) : TextBlockManager(game) {};
	virtual ~TextBlock() { 
		delete fondo_; 
		fondo_ = nullptr;
		entities.clear();
	};

	void Init(SDL_Panel pan);
	void update() override;
	void draw() override;

};

#pragma endregion
