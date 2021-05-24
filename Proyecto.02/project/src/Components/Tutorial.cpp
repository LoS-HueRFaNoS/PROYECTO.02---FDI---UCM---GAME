#include "Tutorial.h"
#include "../Managers/game/InterfazManager.h"
#include "../Utilities/InputHandler.h"
#include "../Utilities/SDL_macros.h"
#include "../Templates/Resources.h"
#include "../GameObjects/SDL_Objects.h"

//-------------------------------------------------------------

void TutorialManager::show(MsgId mID)
{
	src::TextureId id_fondo = src::TextureId();
	src::TextureId id_cartel = src::TextureId();

	switch (mID)
	{
	case MsgId::_BIENVENIDA_:
		id_fondo = src::cinematica;
		id_cartel = src::cartel_bienvenida_pt1;
		break;
	case MsgId::_BIENVENIDA_pt2_:
		id_fondo = src::cinematica;
		id_cartel = src::cartel_bienvenida_pt2;
		break;
	case MsgId::_INTRO_:
		id_fondo = src::foco_support;
		//id_cartel = src::;
		break;
	case MsgId::_MOVIMIENTO_:
		id_fondo = src::foco_combate;
		id_cartel = src::cartel_movimiento;
		break;
	case MsgId::_COFRE_:
		/*id_fondo = src::fondo_cofre;
		id_cartel = src::cartel_cofre;*/
		break;
	case MsgId::_COMBATE_:
		id_fondo = src::foco_combate;
		id_cartel = src::cartel_combate;
		break;
	case MsgId::_INVENTARIO_:
		id_fondo = src::foco_inventario;
		id_cartel = src::cartel_inventario;
		break;
	case MsgId::_CONFIG_:
		id_fondo = src::foco_inventario;
		id_cartel = src::cartel_configuracion;
		break;
	case MsgId::_HEROES_:
		id_fondo = src::foco_heroes;
		id_cartel = src::cartel_heroes;
		break;
	case MsgId::_MINIMAP_:
		id_fondo = src::foco_minimapa;
		id_cartel = src::cartel_minimapa;
		break;
	case MsgId::_SUPPORT_:
		id_fondo = src::foco_support;
		id_cartel = src::cartel_support;
		break;
	case MsgId::_LOBBY_:
		/*id_fondo = src::foco_lobby;
		id_cartel = src::cartel_lobby;*/
		break;
	default:
		break;
	}

	fondo = iManager->addButton<SDL_Object>(fondo_dest, id_fondo);

	cartel = iManager->addButton<SDL_Object>(cartel_dest, id_cartel);

	uint size = 64;
	SDL_Rect dest = RECT(
		cartel_dest.x + cartel_dest.w - size,
		cartel_dest.y + 10,
		size,
		size
	);
	
	bt_exit = iManager->addButton<ButtonMenu>(dest, src::close, accionMenu::closeMessage);
}

//-------------------------------------------------------------

TutorialManager::TutorialManager(InterfazManager* i) :
	Component(ecs::Tutorial),
	iManager(i),
	on_receive_message(false),
	fondo(nullptr),
	cartel(nullptr),
	fondo_dest(),
	cartel_dest(),
	index(0),
	achievementsMap_(),
	activeMsg(MsgId::_BIENVENIDA_)
{
	msgsQueue_.reserve(10);
	initAchievements();
}

void TutorialManager::init()
{
	fondo_dest = RECT(0, 0, game_->getWindowWidth(), game_->getWindowHeight());

	SDL_Panel aux = game_->relativePanel(260, 160, 800, 440);
	cartel_dest = RECT(aux.x, aux.y, aux.w, aux.h);
}

//-------------------------------------------------------------

void TutorialManager::update()
{
	flushMsgsQueue();
	if (on_receive_message) {
		InputHandler* ih_ = InputHandler::instance();
		if (ih_->isKeyDown(SDLK_KP_ENTER)) {
			exitMessage();
		}
	}
	if (!on_receive_message) {
		if (tutorialCompleted())
			this->disable(); //
	}
}

void TutorialManager::draw()
{
}

//-------------------------------------------------------------

// add message:: llamar a este método para invocar mensajes
void TutorialManager::send(const Message& msg) {
	msgsQueue_.emplace_back(msg);
	/*on_receive_message = true;*/
}

// recibe mensajes de uno en uno:
void TutorialManager::flushMsgsQueue() {
	// si tiene mensajes pendientes
	if (msgsQueue_.size() > 0) { 
		// y si no está en mitad de uno
		if (!on_receive_message && index < msgsQueue_.size()) { 
			// recibe el siguiente mensaje
			actionMsg();
		}
		// si ya ha leido todos, resetea
		if (index == msgsQueue_.size()) {
			msgsQueue_.clear();
			index = 0;
		}
	}	
}

// read message
void TutorialManager::actionMsg()
{
	auto& m = msgsQueue_[index];
	activeMsg = m.id_;
	show(m.id_);
	on_receive_message = true;
	//iManager->togglePause();
	index++;
}

// exit message
void TutorialManager::exitMessage() {
	fondo->disable(); fondo = nullptr;
	cartel->disable(); cartel = nullptr;
	bt_exit->disable(); bt_exit = nullptr;
	on_receive_message = false;
	//iManager->togglePause();
	achievementsMap_[activeMsg] = true;
}

//-------------------------------------------------------------

void TutorialManager::initAchievements()
{
	achievementsMap_[MsgId::_BIENVENIDA_] = false;
	achievementsMap_[MsgId::_BIENVENIDA_pt2_] = false;
	achievementsMap_[MsgId::_INTRO_] = false;
	achievementsMap_[MsgId::_MOVIMIENTO_] = false;
	achievementsMap_[MsgId::_COFRE_] = true; //
	achievementsMap_[MsgId::_COMBATE_] = false;
	achievementsMap_[MsgId::_INVENTARIO_] = false;
	achievementsMap_[MsgId::_CONFIG_] = false;
	achievementsMap_[MsgId::_HEROES_] = false;
	achievementsMap_[MsgId::_MINIMAP_] = false;
	achievementsMap_[MsgId::_SUPPORT_] = false;
	achievementsMap_[MsgId::_LOBBY_] = true; //
}

bool TutorialManager::tutorialCompleted()
{
	for (uint j = 0; j < achievementsMap_.size(); j++)
		if (!achievementsMap_[MsgId(j)]) return false;
	return true;
}

void TutorialManager::autoCompleted()
{
	for (uint j = 0; j < achievementsMap_.size(); j++)
		achievementsMap_[MsgId(j)] = true;
}

void TutorialManager::resetTutorial()
{
	for (uint j = 0; j < achievementsMap_.size(); j++)
		achievementsMap_[MsgId(j)] = false;
	achievementsMap_[MsgId::_COFRE_] = true; //
	achievementsMap_[MsgId::_LOBBY_] = true; //
}
