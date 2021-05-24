#include "LobbyManager.h"
#include "../../GameObjects/Character.h"
#include "../../Structures/messages.h"
#include "CharacterManager.h"
#include "ItemManager.h"
#include "PartyManager.h"
#include "../TheElementalMaze.h"


LobbyManager::LobbyManager(PartyManager* party)
	: party_(party), lobbyStore_(nullptr)
{
	playerStash_ = new Stash();
}

LobbyManager::~LobbyManager()
{
	delete playerStash_;
	playerStash_ = nullptr;
	clearLobby();
}

void LobbyManager::startExploring()
{
	clearLobby();
	TheElementalMaze::instance()->changeState(gameST::START_EXPLORING);
}

void LobbyManager::clearLobby()
{
	if (lobbyStore_)
		delete lobbyStore_;
	lobbyStore_ = nullptr;
}


void LobbyManager::backFromDungeon()
{
	playerStash_->gold += party_->gold;
	party_->gold = 0;

	for (Item* i : party_->getItems())
	{
		addItemToStash(i);
	}
	party_->getItems().clear();

	lobbyStore_ = new Store();
	generateHeroStore();
	generateItemStore();
	//startExploring();
}

void LobbyManager::firstLobby()
{
	Message m;
	m.id_ = MsgId::_BIENVENIDA_;
	TheElementalMaze::instance()->sendMsg(m);
	m.id_ = MsgId::_BIENVENIDA_pt2_;
	TheElementalMaze::instance()->sendMsg(m);
	m.id_ = MsgId::_HEROES_;
	TheElementalMaze::instance()->sendMsg(m);
	lobbyStore_ = new Store();
	generateHeroStore();
	generateItemStore();
}

void LobbyManager::generateHeroStore()
{
	CharacterManager* cm = TheElementalMaze::instance()->getCharacterManager();
	for (int i = 0; i < 10; i++) {
		Hero* hero = cm->addRandomHero();
		int price = SDLGame::instance()->getRandGen()->nextInt(50, 301);
		HeroContract* contract = new HeroContract(hero, price);
		lobbyStore_->heroes.push_back(contract);
	}
}

void LobbyManager::generateItemStore()
{
	ItemManager* im = TheElementalMaze::instance()->getItemManager();
	for (int i = 0; i < 10; i++) {
		Item* item;
		if (rpgLogic::throwDice(1, 100) < 51)
			item = im->getRandomArmor();
		else
			item = im->getRandomWeapon();
		ItemToBuy* it = new ItemToBuy(item);
		lobbyStore_->items.push_back(it);
	}
}

void LobbyManager::removeItemFromStash(Item* i)
{
	for (auto it = playerStash_->items.begin(); it != playerStash_->items.end(); it++) {
		if ((*it) == i) {
			playerStash_->items.erase(it);
			return;
		}
	}
}

void LobbyManager::removeItemFromShop(ItemToBuy* item)
{
	for(int i = 0; i < lobbyStore_->items.size(); i++){
		if (lobbyStore_->items[i] == item) {
			removeItemFromShop(i);
			return;
		}
	}
}

void LobbyManager::removeItemFromShop(int i)
{
	delete lobbyStore_->items[i];
	lobbyStore_->items.erase(lobbyStore_->items.begin() + i);
}

Stash* LobbyManager::getPlayerStash()
{
	return playerStash_;
}

void LobbyManager::addHeroToParty(int index, int partyIndex)
{
	assert(partyIndex >= 0 && partyIndex <= 3);

	PartyManager* p = TheElementalMaze::instance()->getPartyManager();
	Hero* h = playerStash_->heroes[index];
	Hero* change = nullptr;

	if (partyIndex == -1) {
		if (!p->addHero(h)) {
			change = p->addHero(h, 0);
		}
	}
	else {
		change = p->addHero(h, partyIndex);
	}

	if (change)
		playerStash_->heroes[index] = change;
	else {
		playerStash_->heroes.erase(playerStash_->heroes.begin() + index);
	}
}

void LobbyManager::heroFromPartyToStash(int partyIndex)
{
	assert(partyIndex >= 0 && partyIndex <= 3);

	PartyManager* p = TheElementalMaze::instance()->getPartyManager();
	Hero* h = nullptr;
	Hero* change = nullptr;

	if (partyIndex == -1) {
		if (!p->addHero(h)) {
			change = p->addHero(h, 0);
		}
	}
	else {
		change = p->addHero(h, partyIndex);
	}

	if (change)
	{
		int i = 0;
		while (i < playerStash_->heroes.size() && playerStash_->heroes[i] == nullptr)
			i++;
		if (playerStash_->heroes.size() > 0 && playerStash_->heroes[i] == nullptr) playerStash_->heroes[i] = change;
		else playerStash_->heroes.push_back(change);
	}
}

void LobbyManager::addHeroToStash(Hero* hero)
{
	playerStash_->heroes.push_back(hero);
}

void LobbyManager::addItemToStash(Item* item)
{
	playerStash_->items.push_back(item);
}

Store* LobbyManager::getLobbyStore()
{
	return lobbyStore_;
}

void LobbyManager::buyPotion(PotionType type)
{
	if (playerStash_->gold < PRICE_OF_POTION)
		return;

	playerStash_->gold -= PRICE_OF_POTION;

	(type) ? playerStash_->manaPotions++ : playerStash_->healthPotions++;

	std::cout << "Potion purchased" << std::endl;
}

void LobbyManager::swapPotions(bool fromParty, PotionType type)
{
	if (fromParty) {
		if (type) {
			party_->manaPotions--;
			playerStash_->manaPotions++;
		}
		else {
			party_->healthPotions--;
			playerStash_->healthPotions++;
		}
	}
	else {
		if (type) {
			party_->manaPotions++;
			playerStash_->manaPotions--;
		}
		else {
			party_->healthPotions++;
			playerStash_->healthPotions--;
		}
	}
}


void LobbyManager::buyItem(int item)
{
	ItemToBuy* itemToBuy = lobbyStore_->items[item];
	if (itemToBuy->sold || playerStash_->gold < itemToBuy->item->getBuyValue())
		return;

	playerStash_->gold -= itemToBuy->item->getBuyValue();
	playerStash_->items.push_back(itemToBuy->item);
	itemToBuy->sold = true;
	removeItemFromShop(item);
	std::cout << "Item purchased" << std::endl;
}

void LobbyManager::buyHero(int hero)
{
	HeroContract* contract = lobbyStore_->heroes[hero];
	if (contract->sold || playerStash_->gold < contract->price)
		return;

	playerStash_->gold -= contract->price;
	int i = 0;
	while (i < playerStash_->heroes.size() && playerStash_->heroes[i] == nullptr)
		i++;
	if (playerStash_->heroes.size() > 0 && playerStash_->heroes[i] == nullptr) playerStash_->heroes[i] = contract->hero;
	else playerStash_->heroes.push_back(contract->hero);
	contract->sold = true;

	std::cout << "Hero purchased" << std::endl;
}

void LobbyManager::sellItem(Item* item)
{
	playerStash_->gold += item->getSellValue();

	removeItemFromStash(item);

	ItemToBuy* it = new ItemToBuy(item);

	lobbyStore_->items.push_back(it);
}

void LobbyManager::sellItemFromStash(int indexStash)
{
	assert(playerStash_->items[indexStash] != nullptr);

	//playerStash_->items.erase(playerStash_->items.begin() + indexStash);
	sellItem(playerStash_->items[indexStash]);
}

Stash::~Stash()
{
	for (Item* i : items)
	{
		delete i; i = nullptr;
	}
	items.clear();
	for (Hero* i : heroes)
	{
		i->disable();
	}
	heroes.clear();
}

HeroContract::~HeroContract()
{
	if (!sold)
	{
		if (hero)
			hero->disable();
		hero = nullptr;
	}
}

ItemToBuy::~ItemToBuy()
{
	if (!sold)
	{
		delete item;
		item = nullptr;
	}
}
