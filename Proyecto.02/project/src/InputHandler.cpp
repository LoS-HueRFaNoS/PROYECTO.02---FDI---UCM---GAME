#include "InputHandler.h"

unique_ptr<InputHandler> InputHandler::instance_;

InputHandler::InputHandler() {
	clearState();
	kbState_ = SDL_GetKeyboardState(0);
}

InputHandler::~InputHandler() {
}

void InputHandler::update() {

	SDL_Event event;

	clearState();

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
			onKeyDown(event);
			break;
		case SDL_KEYUP:
			onKeyUp(event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMotion(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonChange(event, true);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonChange(event, false);
			break;
		}
	}
}

void InputHandler::clearState() {
	isKeyDownEvent_ = false;
	isKeyUpEvent_ = false;
	isMouseButtonEvent_ = false;
	isMouseMotionEvent_ = false;
	for (int i = 0; i < 3; i++) {
		mbState_[i] = false;
	}
}
