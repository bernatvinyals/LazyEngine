#include "ResourceManager.h"
#include "Globals.h"
#include "SDL_Image.h"
#include <iostream>
ResourceManager::~ResourceManager()
{
}

void ResourceManager::removeGraphic(const char* file)
{
	std::map<std::string, Sint32>::iterator it;
	it = mIDMap.find(file);
	SDL_FreeSurface(mGraphicsVector[it->second]);
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
	width = mGraphicsVector[img]->w;
	height = mGraphicsVector[img]->h;
}

Uint16 ResourceManager::getGraphicWidth(Sint32 img)
{
	return mGraphicsVector[img]->w;
}

Uint16 ResourceManager::getGraphicHeight(Sint32 img)
{
	return mGraphicsVector[img]->h;
}

SDL_Surface* ResourceManager::getGraphicByID(Sint32 ID)
{
	return mGraphicsVector[ID];
}

void ResourceManager::setAlphaGraphic(Sint32 ID, Uint8 alpha_value)
{
	SDL_SetSurfaceAlphaMod(mGraphicsVector[ID],alpha_value);
}

void ResourceManager::printLoadedGraphics()
{
	std::map<std::string, Sint32>::iterator it;
	std::cout << "---- Loaded Graphics ---------------------------------" << "\n";
	for (it = mIDMap.begin(); it != mIDMap.end(); ++it)
	{
		std::cout << "File Path: " << it->first << "\n";
	}
}

Sint32 ResourceManager::createGraphic(const char* name, Uint16 width, Uint16 height)
{
	SDL_Surface* tempSurface = new SDL_Surface;
	tempSurface->clip_rect.w = width;
	tempSurface->clip_rect.h = height;
	if (SDL_FillRect(tempSurface, &tempSurface->clip_rect, SDL_MapRGB(tempSurface->format, 255, 255, 255)))
	{
		if (mFirstFreeSlot != NULL)
		{
			mGraphicsVector[mFirstFreeSlot] = tempSurface;
			mIDMap.insert(
				std::pair<std::string, Sint32>("Generated", mFirstFreeSlot));
			Uint32 temp = mFirstFreeSlot;
			mFirstFreeSlot = NULL;
			return temp;
		}
		else
		{
			mIDMap.insert(
				std::pair<std::string, Sint32>("Generated", mGraphicsVector.size()));
			mGraphicsVector.push_back(tempSurface);

			return mGraphicsVector.size() - 1;
		}
	}
	else
	{
		return -1;
	}
}

ResourceManager * ResourceManager::pInstance = NULL;
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
	int flags = IMG_INIT_JPG || IMG_INIT_PNG;
	int initted = IMG_Init(flags);
}

Sint32 ResourceManager::addGraphic(const char* file)
{
	if (mFirstFreeSlot != NULL)
	{
		mGraphicsVector[mFirstFreeSlot] = IMG_Load(file);
		mIDMap.insert(
			std::pair<std::string, Sint32>(file, mFirstFreeSlot));
		Uint32 temp = mFirstFreeSlot;
		mFirstFreeSlot = NULL;
		return temp;
	}
	else
	{
		mIDMap.insert(
			std::pair<std::string, Sint32>(file, mGraphicsVector.size()));
		mGraphicsVector.push_back(IMG_Load(file));

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
