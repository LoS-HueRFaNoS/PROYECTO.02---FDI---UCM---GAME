#pragma once

#include <ctime>

namespace interfaz {

	using idPanelType = std::size_t;

	enum idPanel : idPanelType {
		Fight, 
		Movement, 
		Heroes, 
		Inventory, 
		Info, 
		Minimap, 
		HeroesStats, 
		BigMap, 
		Turns, 
		Settings, 
		Chat,
		//
		// don't touch the rest of this enum, it is to identify the max
		// number of components
		_LastPanId_
	};

	constexpr std::size_t maxPanels = _LastPanId_;
}

