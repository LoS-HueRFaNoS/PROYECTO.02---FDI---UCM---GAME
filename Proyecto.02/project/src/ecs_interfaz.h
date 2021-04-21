#pragma once

#include <ctime>

namespace interfaz {

	using idPanelType = std::size_t;

	enum idPanel : idPanelType {
		Fight, 
		Movement, 
		Minimap, 
		Heroes, 
		Info, 
		Inventory, 
		HeroesStats, 
		BigMap, 
		Turns, 
		Settings, 
		Chat,
		MenuPrincipal,
		Lobby,
		//
		// don't touch the rest of this enum, it is to identify the max
		// number of components
		_LastPanId_
	};

	constexpr std::size_t maxPanels = _LastPanId_;
}

