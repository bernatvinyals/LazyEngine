#pragma once
#include "sdl.h"
#include "sdl_mixer.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>
class SoundManager
{
public:
	~SoundManager();


	void removeSound(const char* file);



	Sint32 loadAndGetSoundID(const char* file);



	std::string getSoundPathByID(Sint32 ID);



	Mix_Chunk* getSoundByID(Sint32 ID);
	Mix_Chunk* getSoundByName(const char* file);


	void printLoadedSounds();


	static SoundManager* getInstance();

	int playSound(Mix_Chunk* chunck, int loops = 0);

	int playSoundTimed(Mix_Chunk* chunck, int loops = 0, int ticks = -1);

	int volumeSound(Mix_Chunk* chunk, int volume = MIX_MAX_VOLUME);

	void CloseSoundManager() { Mix_CloseAudio(); };

	void getError() { printf("Error: %s", Mix_GetError()); }

	int fadeInSound(Mix_Chunk* chunk, int loops = 0, int ms = 1);

	int fadeInSoundTimed(Mix_Chunk* chunk, int loops = 0, int ms = 1, int ticks = -1);

	void pauseSound(int channel = -1) { Mix_Pause(channel); };
	void resumeSound(int channel = -1) { Mix_Resume(channel); };
	int haltSound(int channel = -1) { Mix_HaltChannel(channel); };
	int haltSoundTimed(int channel = -1, int ticks = 1) { Mix_ExpireChannel(channel, ticks); };
	int fadeOutSound(int channel = -1, int ms = 1) { return Mix_FadeOutChannel(channel, ms); };
	//if channel =-1 returns all the channels
	int channelIsPlaying(int channel = -1) { return Mix_Playing(channel); };
	//if channel =-1 returns all the channels
	int channelIsPaused(int channel = -1) { return Mix_Paused(channel); };

	Mix_Fading channelIsFading(int which);

	/*Get the most recent sample chunk pointer played on channel.This pointer may be currently playing, or just the last used.
		Note: The actual chunk may have been freed, so this pointer may not be valid anymore.

		Returns : Pointer to the Mix_Chunk.NULL is returned if the channel is not allocated, or if the channel has not played any samples yet.*/
	Mix_Chunk* getChunk(int channel) { return Mix_GetChunk(channel); };


	//void channelDone(int channel){printf("channel %d finished playing.\n", channel);};
	//void channelFinished() { Mix_ChannelFinished(channelDone); };



protected:
	//! Constructor of an empty ResourceManager.
	SoundManager();

private:

	//! Loads from disc and adds a graphic to the ResourceManager 
	/*!
		\param file Filepath to the graphic
		\return -1 if there's an error when loading
	*/
	Sint32 addSound(const char* file);

	//! Searches the first NULL in mGraphicsVector and updates mFirstFreeSlot to store its position
	/*!
		\return Index of the first NULL in mGraphicsVectorTexture
	*/
	Uint32 updateFirstFreeSlotSound();

	std::vector<Mix_Chunk*>	mSoundsVector;	/*!<  Vector that stores Surfaces. Useful in render methods and sequential access*/
	std::map<std::string, Sint32>	mIDMap;			/*!<  Map that stores ID. Links strings to ID, Useful for check if graphic has been loaded previously*/
	Uint32				mFirstFreeSlot;		/*!<  First free slot in the mGraphicsVector*/
	static SoundManager* pInstance;		/*!<  Singleton instance*/
};
