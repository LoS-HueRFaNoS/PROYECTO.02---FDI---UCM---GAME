#include "ObjectChest.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Components/Rectangle.h"

void ObjectChest::Init()
{
	SDL_Panel pan = game_->relativePanel(1470, 320, 420, 410, 1, 4, 30, 30, 10, 10, 0, 5); // 1510, 360
	MousePanelMecanics::Init(1, set_FE::UP);
	ObjectPanel::Init(pan);
	addTemplate();

	// fondo de cofre
	fondo_ = new Entity(game_, this);
	/*SDL_Rect dest = RECT(
		pan.x - pan.eh, 
		pan.y - pan.eh, 
		pan.w + pan.eh * 2, 
		pan.h + pan.eh * 2
	);*/
	SDL_Rect dest = RECT(
		pan.x,
		pan.y,
		pan.w,
		pan.h
	);
	fondo_->addComponent<Transform>(dest);
	fondo_->addComponent<Image>(game_->getTextureMngr()->getTexture(src::Cofre));
	//fondo_->addComponent<Rectangle_cmpt>(hex2sdlcolor("#000000FF"));

	/*ElementsResources::setFE_way(set_FE::UP);
	MousePanelMecanics::set_exceed(1);*/
}

void ObjectChest::update()
{
	ElementsResources::checkBlockSize(entities, numItems_);
	scroll(marco(), tuppleLimits(), entities, topElement().h, tuppleEspaces().getRight() + tuppleBorders().getRight());
	//EntityManager::update();
	//move();
}

void ObjectChest::draw()
{
	fondo_->draw();
	ElementsResources::draw(entities, tuppleLimits());
}

#pragma region ChestTemplate

//--- TEMPLATE -------------------------------------------------------------------------

#include "../GameObjects/SDL_Objects.h"

void ObjectChest::addTemplate()
{
	//for (size_t i = 0; i < 7; i++)
	for (int i = 6; i >= 0; i--)
	{

		Entity* e = new SDL_Object(game_, this);
		e->addComponent<Transform>(topElement());
		e->addComponent<Image>(game_->getTextureMngr()->getTexture(src::Joker));
		add_element(e, topElement(), tuppleEspaces().getRight() + tuppleBorders().getRight(), this);

		SDL_Color color = { 0,0,0,255 };
		string line = "ELEMENT " + to_string(i);
		Line* li = new Line(game_, this);
		li->init(topElement(), line, color);
		addEntity(li);

	}
}

//--------------------------------------------------------------------------------------

#pragma endregion