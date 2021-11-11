#include "ResourceManager.h"
#include "Globals.h"
#include "SDL_Image.h"
#include "Video.h"
#include <iostream>
ResourceManager::~ResourceManager()
{
}

void ResourceManager::removeGraphic(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	SDL_DestroyTexture(mGraphicsVector[it->second]);
	mGraphicsVector[it->second] = NULL;
	mIDMap.erase(file);
	updateFirstFreeSlotGraphic();
}

Sint32 ResourceManager::loadAndGetGraphicID(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	if (it == mIDMap.end())
	{
		return addGraphic(file);
	}
	else
	{
		return it->second;
	}
}

std::string ResourceManager::getGraphicPathByID(Sint32 ID)
{
	std::map<std::string, Sint32>::iterator it;
	for (it = mIDMap.begin(); it != mIDMap.end(); ++it)
	{
		if (it->second == ID)
		{
			return it->first;
		}
	}
	return "";
}

void ResourceManager::getGraphicSize(Sint32 img, int& width, int& height)
{
	SDL_QueryTexture(mGraphicsVector[img],NULL,NULL, &width, &height);
}

Uint16 ResourceManager::getGraphicWidth(Sint32 img)
{
	int *width = nullptr;
	SDL_QueryTexture(mGraphicsVector[img], NULL, NULL, width, NULL);
	return (Uint16)&width;
}

Uint16 ResourceManager::getGraphicHeight(Sint32 img)
{
	int* height = nullptr;
	SDL_QueryTexture(mGraphicsVector[img], NULL, NULL, NULL, height);
	return (Uint16)&height;
}

SDL_Texture* ResourceManager::getGraphicByID(Sint32 ID)
{
	return mGraphicsVector[ID];
}

void ResourceManager::setAlphaGraphic(Sint32 ID, Uint8 alpha_value)
{
	SDL_SetTextureAlphaMod(mGraphicsVector[ID],alpha_value);
}

void ResourceManager::printLoadedGraphics()
{
	std::map<std::string, Sint32>::iterator it;
	std::cout << "\n---- Loaded Graphics ---------------------------------" << "\n";
	for (it = mIDMap.begin(); it != mIDMap.end(); ++it)
	{
		std::cout << "File Path: " << it->first << "\n";
	}
}

Sint32 ResourceManager::createGraphic(const char* name, Uint16 width, Uint16 height)
{
	SDL_Surface* tempSurface = SDL_CreateRGBSurface(0,width,height,32,0,0,0,0);
	if (SDL_FillRect(tempSurface, &tempSurface->clip_rect, SDL_MapRGB(tempSurface->format, 255, 255, 255)))
	{
		if (mFirstFreeSlot != NULL)
		{
			mGraphicsVector[mFirstFreeSlot] = SDL_CreateTextureFromSurface(Video::getInstance()->gRenderer,tempSurface);
			SDL_FreeSurface(tempSurface);
			mIDMap.insert(
				std::pair<std::string, Sint32>(name, mFirstFreeSlot));
			Uint32 temp = mFirstFreeSlot;
			mFirstFreeSlot = NULL;
			return temp;
		}
		else
		{
			mIDMap.insert(
				std::pair<std::string, Sint32>(name, mGraphicsVector.size()));
			mGraphicsVector.push_back(SDL_CreateTextureFromSurface(Video::getInstance()->gRenderer, tempSurface));
			SDL_FreeSurface(tempSurface);
			return mGraphicsVector.size() - 1;
		}
	}
	else
	{
		return -1;
	}
}

ResourceManager * ResourceManager::pInstance = NULL;
const char* ResourceManager::getDefaultTetxure()
{
	return defaultTex;
}
ResourceManager* ResourceManager::getInstance()
{
	if (pInstance==NULL)
	{
		pInstance = new ResourceManager();
	}
	return pInstance;
}

ResourceManager::ResourceManager()
{
	mFirstFreeSlot = NULL;
	defaultTex = "./assets/defaults/default.png";
	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
}

Sint32 ResourceManager::addGraphic(const char* file)
{
	if (mFirstFreeSlot != NULL)
	{
		mGraphicsVector[mFirstFreeSlot] = IMG_LoadTexture(Video::getInstance()->gRenderer,file);
		mIDMap.insert(
			std::pair<std::string, Sint32>(file, mFirstFreeSlot));
		Uint32 temp = mFirstFreeSlot;
		mFirstFreeSlot = NULL;
		return temp;
	}
	else
	{
		mGraphicsVector.push_back(IMG_LoadTexture(Video::getInstance()->gRenderer, file));
		if (!mGraphicsVector[mGraphicsVector.size() - 1])
		{
			mGraphicsVector.pop_back();
			printf("\n!!ERROR LOADING IMAGE: %s\n", IMG_GetError());
			return addGraphic(getDefaultTetxure());
		}
		mIDMap.insert(
			std::pair<std::string, Sint32>(file, mGraphicsVector.size()-1));

		return mGraphicsVector.size()-1;
	}
	
}

Uint32 ResourceManager::updateFirstFreeSlotGraphic()
{
	for (int i = 0; i < mGraphicsVector.size(); i++)
	{
		if (mGraphicsVector[i] == NULL)
		{
			mFirstFreeSlot = i;
			return i;
		}
	}
	return 0;
}
