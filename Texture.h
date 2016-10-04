#ifndef TEXTURE
#define TEXTURE
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<iostream>
class RenderTexture
{
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_CurrentTexture;
	SDL_Surface* m_ScreenSurface;
	
public:
	SDL_Texture* loadTexture(std::string path);
	bool initSystems();
	bool loadMedia();
	void pngLoading();
	
	


	RenderTexture();
	~RenderTexture();
	bool gameLoop();
	void close();
	SDL_Renderer* getRenderer() {
		return m_Renderer;
	}
	SDL_Texture* getCurrentTexture() {
		return m_CurrentTexture;
	}
	

};
#endif
