#include "ObjectChest.h"
#include "../Components/Transform.h"
#include "../Components/Image.h"
#include "../Components/Rectangle.h"

void ObjectChest::Init()
{
	if (generated) return;
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
	generated = true;
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

void ObjectChest::example()
{
	vector<Item*> items = TheElementalMaze::instance()->getPartyManager()->getItems();
	itemChest(items);
}

void ObjectChest::itemChest(vector<Item*> items)
{
	for (int i = items.size() - 1; i >= 0; i--)
	{
		if (items[i] != nullptr) {
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

			ItemType itemType = items[i]->getItemType();

			if (itemType == ItemType::ARMOR) {
				pivot = src::_firstArmorId_;
				auxId = (int) static_cast<Armor*>(items[i])->getArmorId();
			}
			else {
				pivot = src::_firstWeaponId_;
				auxId = (int) static_cast<Weapon*>(items[i])->getWeaponId();
			}
			id = (Resources::TextureId)(pivot + auxId + 1);


			items[i]->getItemType();
			e->addComponent<Image>(game_->getTextureMngr()->getTexture(id));


			Entity* itemBackground = new SDL_Object(game_, this);
			itemBackground->addComponent<Transform>(imgOfItem);
			itemBackground->addComponent<Image>(game_->getTextureMngr()->getTexture(src::Slot));


			add_element(itemBackground, topElement(), tuppleEspaces().getRight() + tuppleBorders().getRight(), this);

			addEntity(e);


			//TEXTO
			SDL_Color color = { 0,0,0,255 };
			string name = items[i]->getName();
			Line* line = new Line(game_, this);

			SDL_Rect lineRect;
			lineRect.x = topElement().x + topElement().w * 0.35;
			lineRect.y = topElement().y + topElement().h * 0.005;
			lineRect.w = topElement().w * 0.6;
			lineRect.h = topElement().h * 0.99;

			line->init(lineRect, name, color);
			addEntity(line);
		}
	}
}


//--------------------------------------------------------------------------------------

#pragma endregion