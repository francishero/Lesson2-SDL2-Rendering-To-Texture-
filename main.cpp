#include "Texture.h"
int main(int argc, char* args[])
{
	RenderTexture obj;
	if (!obj.initSystems())
	{
		std::cout << "Failed to initialise";
	}
	else
	{
		if (!obj.loadMedia())
		{
			std::cout << "Failed to load Media";
		}
		else
		{
			while (!obj.gameLoop()) {
				SDL_RenderClear(obj.getRenderer());
				SDL_RenderCopy(obj.getRenderer(), obj.getCurrentTexture(), NULL, NULL);
				
				SDL_RenderPresent(obj.getRenderer());
				
			}
		}
	}
	obj.close();
	return 0;
}