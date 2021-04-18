#pragma once
#include <string>
#include <list>
#include "Component.h"
#include "Panel.h"
#include "Cursor.h"

using namespace std;

class InterfazManager : public Component {
private:
	vector<Panel*> allPanels;
	vector<Entity*> entitiesV;
	Cursor* c_;

	Cursor* createCursor(Vector2D pos, uint width, uint height, Resources::TextureId image);
	/*template<typename T, typename ... TArgs>
	T* createButton(Panel* p, void cb(TArgs&& ...), Vector2D pos, uint width, uint height, Resources::TextureId image, TArgs&& ... mArgs);*/
	
	template<typename T, typename ... TArgs>
	T* createButton(Panel* p, Vector2D pos, uint width, uint height, Resources::TextureId image, TArgs&& ... mArgs);
	// generador de botones generico ¿?
	/*template<typename T,>
	void addButton(Button* b);*/


	/*template<typename T> 
	ButtonType<T>* createButtonType(T* add, Panel* p, InterfazManager* im, CallBackOnClick* cb, Vector2D pos, uint width, uint height, Resources::TextureId image);
	template<typename K> 
	ButtonType_2T<K>* createButtonType_2T(K* add, Panel* p, InterfazManager* im, CallBackOnClick* cb, Vector2D pos, uint width, uint height, Resources::TextureId image);*/

	/*void createButtonFight(Panel* p, AtkType type, PlayerMotion* plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonMovement(Panel * p, MovType type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonHeroes(Panel * p, HeroNum type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);
	void createButtonInfo(Panel * p, Inf type, PlayerMotion * plmot, Vector2D pos, uint width, uint height, Resources::TextureId image);*/

	bool createFight();
	bool createMovement();
	bool createHeroes();
	bool createInfo();
	bool createMinimap(){ return true; }; //
	Panel* createInventory(); 
	bool createHeroesStats(){ return true; }; //
	bool createBigMap(){ return true; }; //
	bool createTurns(){ return true; }; //
	bool createSettings(){ return true; }; //
	bool createChat(){ return true; }; //

public:
	InterfazManager() : 
		Component(ecs::InterfazManager), 
		allPanels(vector<Panel*>()), 
		c_(nullptr) 
	{};
	virtual ~InterfazManager();

	bool createPanel(idPanel panelID);
	bool destroyPanel(idPanel panelID);

	void togglePanel(idPanel panID) {
		allPanels[panID]->toggleButtons();
	}

	virtual void init() override;
	virtual void update() override {};
	virtual void draw() override {};

	Entity* getEntity();
};