#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <map>
#include <vector>
#include "SDL.h"
#include <string>

//! ResourceManager class
/*!
	Handles the load and management of the graphics in the game.
*/
class ResourceManager
{
public:

	//! Destructor.
	~ResourceManager();

	//! Deletes a graphic from the ResourceManager map
	/*!
		\param file Filepath to the graphic
	*/
	void removeGraphic(const char* file);


	//! Gets the graphic ID from file name. Use addGraphic if it needs to load image from disc
	/*!
		\param file Filepath to the graphic
		\return ID of the graphic
	*/
	Sint32 loadAndGetGraphicID(const char* file);


	//! Gets the graphic path given an ID graphic
	/*!
		\param ID of the graphic
		\return Filepath to the graphic
	*/
	std::string getGraphicPathByID(Sint32 ID);


	//! Returns width and Height of a Surface
	/*!
	 *	\param img ID texture
	 *	\param width Return variable for width value
	 *	\param height Return variable for height value
	 */
	void getGraphicSize(Sint32 img, int& width, int& height);

	//! Returns width of a Surface
	/*!
	 *	\param img ID texture
	 * 	\return Width of Texture
	 */
	Uint16 getGraphicWidth(Sint32 img);

	//! Returns Height of a Texture
	/*!
	 *	\param img ID texture
	 *  \return Height of Texture
	 */
	Uint16 getGraphicHeight(Sint32 img);

	//! Returns the SDL_Texture of the graphic. Only for render methods.
	/*!
		\param ID ID of the graphic
		\return SDL_Texture
	*/
	SDL_Texture* getGraphicByID(Sint32 ID);

	//! Change general Alpha value to paint a concrete surface
	/*!
		\param ID ID of the graphic
		\param alpha_value From SDL_ALPHA_TRANSPARENT(0) to SDL_ALPHA_OPAQUE(255)
	*/
	void setAlphaGraphic(Sint32 ID, Uint8 alpha_value);

	//! Prints the path to loaded graphics
	void printLoadedGraphics();

	//! Create a new surface graphic to the ResourceManager
	/*!
		\param name for the graphic
		\param width Width for the graphic
		\param height Height for the graphic
		\return -1 if there's an error when loading
	*/
	Sint32 createGraphic(const char* name, Uint16 width, Uint16 height);

	//! Gets Default Texture
	/*!
		\return pointer for default texture
	*/
	const char* getDefaultTetxure();
	//! Gets Singleton instance
	/*!
		\return Instance of ResourceManager (Singleton).
	*/
	static ResourceManager* getInstance();

protected:
	//! Constructor of an empty ResourceManager.
	ResourceManager();

private:

	//! Loads from disc and adds a graphic to the ResourceManager 
	/*!
		\param file Filepath to the graphic
		\return -1 if there's an error when loading
	*/
	Sint32 addGraphic(const char* file);

	//! Searches the first NULL in mGraphicsVector and updates mFirstFreeSlot to store its position
	/*!
		\return Index of the first NULL in mGraphicsVectorTexture
	*/
	Uint32 updateFirstFreeSlotGraphic();

	std::vector<SDL_Texture*>	mGraphicsVector;	/*!<  Vector that stores Surfaces. Useful in render methods and sequential access*/
	std::map<std::string, Sint32>	mIDMap;			/*!<  Map that stores ID. Links strings to ID, Useful for check if graphic is has been loaded previously*/
	Uint32				mFirstFreeSlot;		/*!<  First free slot in the mGraphicsVector*/
	static ResourceManager* pInstance;		/*!<  Singleton instance*/
	const char* defaultTex;
};

#endif

