#pragma once

#include "AudioManager.h"
#include <SDL_mixer.h>

#include <map>

/*
 *
 */
class SDLAudioManager: public AudioManager {
public:
	SDLAudioManager();
	SDLAudioManager(int channels);
	~SDLAudioManager();

	// supposed to be called before start using the object
	bool init() override;

	// sound effects
	bool loadSound(int tag, const string &fileName) override;
	int playChannel(int tag, int loops, int channel) override;
	void pauseChannel(int channel) override;
	void resumeChannel(int channel) override;
	void haltChannel(int channel) override;
	int setChannelVolume(int volume, int channel) override;
	int channels() override;

	// music
	bool loadMusic(int tag, const string &fileName) override;
	void playMusic(int tag, int loops) override;
	int setMusicVolume(int volume) override;
	void haltMusic() override;
	void pauseMusic() override;
	void resumeMusic() override;

private:
	bool initialized_;
	int channels_;
	map<int, Mix_Chunk*> chunks_;
	map<int, Mix_Music*> music_;
};

