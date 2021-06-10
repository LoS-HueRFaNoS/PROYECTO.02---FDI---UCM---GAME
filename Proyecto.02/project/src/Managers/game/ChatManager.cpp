#include <cassert>
#include "ChatManager.h"
#include "../../ecs/ecs.h"
#include "../../Components/Transform.h"
#include "../../Components/Image.h"
#include "../../Components/Rectangle.h"
#include "../../Utilities/SDL_macros.h"
#include "../../Utilities/InputHandler.h"
#include "../TheElementalMaze.h"

std::unique_ptr<ChatManager> ChatManager::instance_;

//--- INIT ----------------------------------------------------------------------

// Inicializa el Manager/Singleton
void ChatManager::Init()
{
	assert(instance_.get() == nullptr);
	instance_.reset(new ChatManager(TheElementalMaze::instance()->getSDLGame()));
	instance_->init();
}

// Inicializa los valores para el panel del chat y los colores que se van a usar
void ChatManager::init()
{
	// relative sizes
	SDL_Panel pan = game_->relativePanel(710,790,540,190,1,9,20,10);
	bottomLine = RECT(pan.lcx, pan.lcy, pan.cw, pan.ch);
	marco = RECT(pan.x, pan.y, pan.w, pan.h);
	tuppleLimits = Tupple(pan.fcy, pan.lcy);
	// fondo oscuro
	fondo_ = new Entity(game_, this);
	SDL_Rect dest = RECT(pan.x, pan.y, pan.w, pan.h);
	fondo_->addComponent<Transform>(dest);
	fondo_->addComponent<Rectangle_cmpt>(hex2sdlcolor("#000000FF"));
	// color messages
	lineTypesMap_[linCol::White] = hex2sdlcolor("#FFFFFFFF");
	lineTypesMap_[linCol::Yellow] = hex2sdlcolor("#FFD700FF");
	lineTypesMap_[linCol::Green] = hex2sdlcolor("#00FF00FF");
	lineTypesMap_[linCol::Red] = hex2sdlcolor("#FF0000FF");
	lineTypesMap_[linCol::Blue] = hex2sdlcolor("#0055FFFF");
	// valores del chat
	initialValues();
}

void ChatManager::initialValues()
{
	numLines = NUM_LINES;
	lineNL = NUM_LETTERS_IN_LINE;
}

//--- MECANICS ----------------------------------------------------------------

// Mueve una fila hacia arriba una linea
void ChatManager::moveUp(Entity* e)
{
	Transform* tr_ = GETCMP2(e, Transform);
	tr_->setPosY(tr_->getPos().getY() - bottomLine.h);
}

// Mueve una fila hacia abajo una linea
void ChatManager::moveDown(Entity* e)
{
	Transform* tr_ = GETCMP2(e, Transform);
	tr_->setPosY(tr_->getPos().getY() + bottomLine.h);
}

// Pinta una linea
void ChatManager::drawLine(Entity* e)
{
	Transform* tr_ = GETCMP2(e, Transform);
	Image* img_ = GETCMP2(e, Image);
	double y = tr_->getPos().getY();
	if (checkTopDownMax(y)) {
		img_->draw(); 
	};
}

//--- CHECKERS ---------------------------------------------------------------

// Comprueba el tamanio de la linea, si supera el limite, la divide
bool ChatManager::checkLineSize(std::string text, LineColor type)
{
	bool cut = false;
	if (text.size() > lineNL) {
		string line = cutLine(text);
		addLine(line, type);
		string line2 = text.substr(line.size());
		addLine(line2, type);
		cut = true;
	}
	return cut;
}

// Comprueba el tamaño del chat, si lo supera elimina la ultima linea (la primera en entrar)
void ChatManager::checkChatSize()
{
	if (entities.size() > numLines) {
		entities.begin()->get()->disable();
	}
}

// Comprueba que la primera linea no se sale de los limites del panel
bool ChatManager::checkTopDownMax(int y)
{
	// Getters: x = first line; y = last line
	if (y >= tuppleLimits.getX() && y <= tuppleLimits.getY()) 
	{
		return true;
	}
	else return false;
}

bool ChatManager::isMouseIN()
{
	InputHandler* ih_ = InputHandler::instance();
	Vector2D pos_ = ih_->getMousePos();
	SDL_Point p_ = { (int)pos_.getX(), (int)pos_.getY() };
	return SDL_PointInRect(&p_, &marco);
}

string ChatManager::cutLine(string line)
{
	string cut;
	if (line.at(lineNL) != ' ' && line.at(double(lineNL) + 1) != ' ') {
		string aux = line.substr(0, lineNL);		
		size_t n = aux.rfind(' ', lineNL);
		cut = aux.substr(0, n + 1);
	}
	else {
		cut = line.substr(0, lineNL);
	}
	return cut;
}

string ChatManager::formatLine(string line)
{
	if (line.front() == ' ') line.erase(line.begin());
	if (line.size() < lineNL) line.resize(lineNL, ' ');
	return line;
}

//--- CLEANERS ---------------------------------------------------------------

// Restores initial position (scroll hacia abajo completo)
void ChatManager::reset()
{
	Transform* tr_ = GETCMP2(entities.rbegin()->get(), Transform);
	double y = tr_->getPos().getY();		// check last line

	while (y != bottomLine.y && (y + bottomLine.h) <= tuppleLimits.getY()) {
		for (auto it = entities.begin(); it != entities.end(); it++) {
			moveDown(it->get());	// move down
		}
		y = tr_->getPos().getY();
	}
}

// Limpia TODO el chat
void ChatManager::cleanALL()
{
	for (auto it = entities.rbegin(); it != entities.rend(); it++) {
		Line* line = dynamic_cast<Line*>(it->get());
		if (line != nullptr) {
			line->disable();
		}
	}
	entities.clear();
}

//--- ADD TEXT ---------------------------------------------------------------

// Comprueba que estan en su sitio y añade una linea nueva
void ChatManager::add(std::string line, LineColor type)
{
	reset();
	addLine(line, type);
}

// Añade una linea nueva, segmentadola en caso de que exceda el limite por linea
void ChatManager::addLine(std::string line, LineColor type)
{
	if (!checkLineSize(line, type)) {
		for (auto it = entities.begin(); it != entities.end(); it++) {
			moveUp(it->get());
		}
		if (line.size() > 0) {
			line = formatLine(line);
			addLine<Line>(bottomLine, line, lineTypesMap_[type], isTitle);
			if (isTitle) isTitle = false;
		}
		else {
			int a = 0;
		}
	}
}

// Limpia todo el chat y añade una linea nueva
void ChatManager::clean_n_addLine(std::string line, LineColor type, bool makeTitle)
{
	cleanALL();
	isTitle = makeTitle;
	addLine(line, type);
}

//--- UPDATE ---------------------------------------------------------------

// Hace el efecto de scroll si detecta MouseScrollEvent dentro del chat
void ChatManager::update()
{
	checkChatSize();
	double y;

	InputHandler* ih_ = InputHandler::instance();
	if (ih_->mouseWheelEvent() && isMouseIN()) 
	{
		// away from the user
		if (ih_->getMouseWheelState(InputHandler::UP))	
		{			
			Transform* tr_ = GETCMP2(entities.begin()->get(), Transform);
			y = tr_->getPos().getY();		// check first line

			if ((y + bottomLine.h) <= tuppleLimits.getY()) {	
				for (auto it = entities.begin(); it != entities.end(); it++) {
					moveDown(it->get());	// move down
				}
			}
		}
		// toward the user
		else if (ih_->getMouseWheelState(InputHandler::DOWN))	
		{
			Transform* tr_ = GETCMP2(entities.rbegin()->get(), Transform);
			y = tr_->getPos().getY();		// check last line

			if ((y - bottomLine.h) >= tuppleLimits.getX()) {	
				for (auto it = entities.begin(); it != entities.end(); it++) {
					moveUp(it->get());		// move up
				}
			}
		}
	}	
}

//--- DRAW ---------------------------------------------------------------

void ChatManager::draw()
{
	fondo_->draw();
	for (auto it = entities.begin(); it != entities.end(); it++) {
		drawLine(it->get());
	}
}
