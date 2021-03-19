#pragma once

#include <SDL.h>
#include <string>
#include <vector>

using namespace std;

class Resources {
public:

	enum TextureId : std::size_t {
		// images
		Airplanes,
		Asteroid,
		Heart,
		WhiteRect,
		camino_izq,
		camino_der,
		camino_del,
		muro_izq,
		muro_der,
		muro_del,

		// text
		HelloWorld,
		PressAnyKey,
		GameOverWon,
		GameOverLost
	};

	enum AudioId : std::size_t {
		// music
		ImperialMarch,

		// sound effects
		Explosion,
		GunShot
	};

	enum FontId : std::size_t {
		ARIAL16, ARIAL24,
	};

	enum JsonId : std::size_t {
		Characters,
		Weapons,
		Armors
	};

	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};

	struct ImageInfo {
		TextureId id;
		string fileName;
	};

	struct TextMsgInfo {
		TextureId id;
		string msg;
		SDL_Color color;
		FontId fontId;
	};

	struct MusicInfo {
		AudioId id;
		string fileName;
	};

	struct SoundInfo {
		AudioId id;
		string fileName;

	};

	struct JsonInfo {
		JsonId id;
		string filename;
	};

	static vector<FontInfo> fonts_; // initialized in .cpp
	static vector<ImageInfo> images_; // initialized in .cpp
	static vector<TextMsgInfo> messages_; // initialized in .cpp
	static vector<MusicInfo> musics_; // initialized in .cpp
	static vector<SoundInfo> sounds_; // initialized in .cpp
	static vector<JsonInfo> jsons_; // initialized in .cpp
	//static vector<ClassTemplates> classTemplates_;

};
