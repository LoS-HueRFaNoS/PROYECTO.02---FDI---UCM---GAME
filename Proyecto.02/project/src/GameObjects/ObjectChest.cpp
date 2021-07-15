#include "ObjectChest.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Components/Rectangle.h"
#include "../Managers/game/AnimationManager.h"
#include "../Components/Interfaz.h"

void ObjectChest::Init()
{
	entities.clear();
	MousePanelMecanics::Init(1, set_FE::UP);
	ObjectPanel::Init(pan);

		//addTemplate();
		//example();

	itemChest(interiorCofre->getItems());

	// fondo de cofre
	fondo_ = new Entity(game_, this);
	SDL_Rect dest = RECT(
		pan.x,
		pan.y,
		pan.w,
		pan.h
	);
	fondo_->addComponent<Transform>(dest);
	fondo_->addComponent<Image>(game_->getTextureMngr()->getTexture(src::CofreMenu));
	//fondo_->addComponent<Rectangle_cmpt>(hex2sdlcolor("#000000FF"));
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


#include "../Structures/Item.h"
#include "../Managers/TheElementalMaze.h"
#include "../Managers/game/PartyManager.h"
#include "../Structures/Panel.h"
#include "../GameObjects/Button.h"
#include <stack>

//void ObjectChest::example()
//{
//	list<Item*> items = TheElementalMaze::instance()->getPartyManager()->getItems();
//	itemChest(items);
//}
struct param
{
	SDL_Rect rect;
	Item* item;
	int offset;
	Resources::TextureId tex;
};
void ObjectChest::itemChest(list<Item*> items)
{
	list<Item*>::iterator it = items.begin();
	int num = 0;
	int offset = 0;
	stack<param> pila;
	for (int i = 0; i < items.size(); i++)
	{
		if (it._Ptr->_Myval != nullptr) {
			Entity* e = new SDL_Object(game_, this);
			// IMAGEN
				//Transform
			SDL_Rect imgOfItem;
			imgOfItem.x = topElement().x + topElement().w * 0.05;
			imgOfItem.y = topElement().y + topElement().h * 0.005;
			imgOfItem.h = topElement().h * 0.99;
			imgOfItem.w = imgOfItem.h;
			e->addComponent<Transform>(imgOfItem);

			//Image
			uint pivot, auxId;
			Resources::TextureId id;

			ItemType itemType = it._Ptr->_Myval->getItemType();

			if (itemType == ItemType::ARMOR) {
				pivot = src::_firstArmorId_;
				auxId = (int) static_cast<Armor*>(it._Ptr->_Myval)->getArmorId();
			}
			else {
				pivot = src::_firstWeaponId_;
				auxId = (int) static_cast<Weapon*>(it._Ptr->_Myval)->getWeaponId();
			}
			id = (Resources::TextureId)(pivot + auxId + 1);


			it._Ptr->_Myval->getItemType();
			e->addComponent<Image>(game_->getTextureMngr()->getTexture(id));


			Entity* itemBackground = new SDL_Object(game_, this);
			itemBackground->addComponent<Transform>(imgOfItem);
			itemBackground->addComponent<Image>(game_->getTextureMngr()->getTexture(src::Slot));
			
			
			param parametros{ imgOfItem,it._Ptr->_Myval,offset,id };
			pila.push(parametros);
			add_element(itemBackground, topElement(), tuppleEspaces().getRight() + tuppleBorders().getRight(), this);

			addEntity(e);


			//TEXTO
			SDL_Color color = { 0,0,0,255 };
			string name = it._Ptr->_Myval->getName();
			Line* line = new Line(game_, this);

			SDL_Rect lineRect;
			lineRect.x = topElement().x + topElement().w * 0.35;
			lineRect.y = topElement().y + topElement().h * 0.005;
			lineRect.w = topElement().w * 0.6;
			lineRect.h = topElement().h * 0.99;

			line->init(lineRect, name, color);
			addEntity(line);
		}
		it++;
	}
	while (!pila.empty())
	{
		TheElementalMaze::instance()->getInterfaz()->botonChest(pila.top().rect, pila.top().item, offset, pila.top().tex);
		offset += (tuppleEspaces().getRight() + tuppleBorders().getRight()) * 2 + pila.top().rect.h;
		pila.pop();
	}
}

void ObjectChest::recogerOro()
{
	TheElementalMaze::instance()->getPartyManager()->gold += interiorCofre->getGold();
	if (interiorCofre->getGold() > 0) TheElementalMaze::instance()->getAnimManager()->showReward(0, interiorCofre->getGold(),0,0,0);
	interiorCofre->oroRecogido();
}

//--------------------------------------------------------------------------------------
void ObjectChest::restart()
{
	entities.clear();
	itemChest(interiorCofre->getItems());
}
#pragma endregion