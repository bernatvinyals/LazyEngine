#include "SoundManager.h"
SoundManager* SoundManager::pInstance = NULL;
SoundManager::~SoundManager()
{
}

void SoundManager::removeSound(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	Mix_FreeChunk(mSoundsVector[it->second]);
	mSoundsVector[it->second] = NULL;
	mIDMap.erase(file);
	updateFirstFreeSlotSound();
}

Sint32 SoundManager::loadAndGetSoundID(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	if (it == mIDMap.end()) {
		return addSound(file);
	}
	else {
		return it->second;
	}
}

std::string SoundManager::getSoundPathByID(Sint32 ID)
{
	std::map<std::string, Sint32>::iterator it;
	for (it = mIDMap.begin(); it != mIDMap.end(); it++)
	{
		if (it->second == ID) {
			return it->first;
		}
	}

	return "";
}

Mix_Chunk* SoundManager::getSoundByID(Sint32 ID)
{
	return mSoundsVector[ID];
}

Mix_Chunk* SoundManager::getSoundByName(const char* file)
{
	return mSoundsVector[mIDMap.find(file)->second];
}

void SoundManager::printLoadedSounds()
{
	std::map<std::string, Sint32>::iterator it;
	for (it = mIDMap.begin(); it != mIDMap.end(); it++)
	{
		std::cout << "File path: " << it->first << std::endl;
	}
}

SoundManager* SoundManager::getInstance()
{
	if (pInstance == NULL) {
		pInstance = new SoundManager();
	}
	return pInstance;
}

int SoundManager::playSound(Mix_Chunk* chunck, int loops)
{
	int aux = -1;
	if (Mix_PlayChannel(-1, chunck, loops) == -1) {
		printf("Mix_PlayChannel: %s\n", Mix_GetError());
	}
	else {
		aux = Mix_PlayChannel(-1, chunck, loops);
	}

	return aux;
}

int SoundManager::playSoundTimed(Mix_Chunk* chunck, int loops, int ticks)
{
	int aux = -1;
	if (Mix_PlayChannelTimed(-1, chunck, loops, ticks) == -1) {
		printf("Mix_PlayChannel: %s\n", Mix_GetError());
	}
	else {
		aux = Mix_PlayChannelTimed(-1, chunck, loops, ticks);
	}

	return aux;
}

int SoundManager::volumeSound(Mix_Chunk* chunk, int volume)
{
	Mix_VolumeChunk(chunk, volume);
	return volume;
}

int SoundManager::fadeInSound(Mix_Chunk* chunk, int loops, int ms)
{
	int aux = -1;
	if (Mix_FadeInChannel(-1, chunk, loops, ms) == -1) {
		printf("Mix_FadeInChannel: %s\n", Mix_GetError());
	}
	else {
		aux = Mix_FadeInChannel(-1, chunk, loops, ms);
	}
	return aux;
}

int SoundManager::fadeInSoundTimed(Mix_Chunk* chunk, int loops, int ms, int ticks)
{
	int aux = -1;
	if (Mix_FadeInChannelTimed(-1, chunk, loops, ms, ticks) == -1) {
		printf("Mix_PlayChannel: %s\n", Mix_GetError());
	}
	else {
		aux = Mix_FadeInChannelTimed(-1, chunk, loops, ms, ticks);
	}
	return aux;
}

Mix_Fading SoundManager::channelIsFading(int which)
{
	Mix_Fading aux = MIX_NO_FADING;
	switch (Mix_FadingChannel(which)) {
	case MIX_NO_FADING:
		printf("Not fading.\n");
		aux = MIX_NO_FADING;
		break;
	case MIX_FADING_OUT:
		printf("Fading out.\n");
		aux = MIX_FADING_OUT;
		break;
	case MIX_FADING_IN:
		printf("Fading in.\n");
		aux = MIX_FADING_IN;
		break;
	}
	return aux;
}



SoundManager::SoundManager()
{
	mFirstFreeSlot = NULL;
	SDL_InitSubSystem(SDL_INIT_AUDIO);
	SDL_Init(SDL_INIT_EVERYTHING);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_AllocateChannels(128);
}

Sint32 SoundManager::addSound(const char* file)
{
	if (mFirstFreeSlot != NULL) {
		mIDMap.insert(std::pair<std::string, Sint32>(file, mFirstFreeSlot));
		mSoundsVector[mFirstFreeSlot] = Mix_LoadWAV(file);
		int temp = mFirstFreeSlot;
		mFirstFreeSlot = NULL;
		return temp;
	}
	else {
		mSoundsVector.push_back(Mix_LoadWAV(file));
		printf("Mix_PlayChannel: %s\n", Mix_GetError());
		mIDMap.insert(std::pair<std::string, Sint32>(file, mSoundsVector.size() - 1));

		return mSoundsVector.size() - 1;
	}
}

Uint32 SoundManager::updateFirstFreeSlotSound()
{
	for (int i = 0; i < mSoundsVector.size(); i++)
	{
		if (mSoundsVector[i] == NULL) {
			return i;
		}
	}
}