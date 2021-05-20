#pragma once
#include "../../Templates/HabilityResources.h"
#include "../../Utilities/checkML.h"


class HabilityManager {
private:

	static std::unique_ptr<HabilityManager> instance_;

	std::map<Hability_Id, Hability* (*)()> habilityMap_;

	void init();

	template<typename T>
	static Hability* createHability() {
		return new T();
	}

public:

	static void Init();

	HabilityManager() {}
	~HabilityManager();

	static HabilityManager* instance() {
		assert(instance_.get() != nullptr);
		return instance_.get();
	}

	Hability* getHability(Hability_Id id) {
		return habilityMap_[id]();
	}

};
