#pragma once
#include <SDL_stdinc.h>

struct Entity;

enum class MsgId : Uint8 {
	_BIENVENIDA_,
	_BIENVENIDA_pt2_,
	_INTRO_,
	_MOVIMIENTO_,
	_COFRE_,
	_COMBATE_,
	_INVENTARIO_,
	_CONFIG_,
	_HEROES_,
	_MINIMAP_,
	_SUPPORT_,
	_LOBBY_
};

struct Boolean {
	bool data;
};

struct SomeOtherMsg { // just for the example
	int otherData_;
};

struct Message {
	MsgId id_;
	union {
		Boolean data;
		SomeOtherMsg otherMsg_;
	};
};
