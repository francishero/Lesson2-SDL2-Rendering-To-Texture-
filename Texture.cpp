#include "Texture.h"
RenderTexture::RenderTexture()
{
	m_Window = nullptr;
	m_Renderer = nullptr;
	m_CurrentTexture = nullptr;
	m_ScreenSurface = nullptr;

}
//the game loop
bool RenderTexture::gameLoop()
{
	bool quit = false;
	SDL_Event e;
	
	while (!quit && SDL_PollEvent(&e)!=0)
	{
		switch (e.key.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
	}
	return quit;
}
RenderTexture::~RenderTexture() {};
 SDL_Texture* RenderTexture::loadTexture(std::string path)
{
	// m_ScreenSurface = SDL_GetWindowSurface(m_Window);// we need to pass the window to the surface
	 SDL_Texture* newTexture = nullptr;
	 SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	 if (loadedSurface == nullptr)
	 {
		 std::cout << "Could not load the Surface " << SDL_GetError() << std::endl;
	 }
	 else
	 {
		 /*the loadedSurface is raw pixels and uses the CPU for rendering which is slow and inefficient
		 /* we convert the Surface to a Texture which uses the GPU for rendering*/
		 newTexture = SDL_CreateTextureFromSurface(m_Renderer, loadedSurface);
		 if (newTexture == nullptr)
		 {
			 std::cout << "Surface could not be converted to Texture " << SDL_GetError() << std::endl;
		 }
		 //free the Surface because we dont want two copies
		 SDL_FreeSurface(loadedSurface);
	 }
	 return newTexture;
}
 void RenderTexture::pngLoading()
 {
	 int imgFlags = IMG_INIT_PNG;
	 if (!(IMG_Init(imgFlags) & imgFlags))
	 {
		 std::cout << "Png could not be loaded" << IMG_GetError() << std::endl;
	 }
 }
 //function to initialise SDL and SDL_image
 bool RenderTexture::initSystems()
 {
	 bool success = true;
	 if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	 {
		 std::cout << "SDL could not be initialised " << SDL_GetError() << std::endl;
		 success = false;
	 }
	 else
	 {
		 //create our main Window
		 m_Window = SDL_CreateWindow("Rendering to Texture", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			 SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		 if (m_Window == nullptr)
		 {
			 std::cout << "Window could not be created " << SDL_GetError() << std::endl;
			 success = false;
		 }
		 else
		 {
			 //create the render to render to the window
			 m_Renderer=SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
			 if (m_Renderer == nullptr)
			 {
				 std::cout << "Renderer could not be created " << SDL_GetError() << std::endl;
			 }
			 else
			 {
				 //we need to set the color
				 SDL_SetRenderDrawColor(m_Renderer, 255, 255, 255, 255);
				 //call function to initialise PNG loading
				 pngLoading();
			 }
		 }
		 
	 }
	 return success;
	 
 }
 bool RenderTexture::loadMedia()
 {
	 bool success = true;
	 //loading PNG image
 m_CurrentTexture = loadTexture("\C:\\Users/Francis/Documents/Visual Studio 2015/Projects/SDL_RenderingToTexture/texture.png");
 if (m_CurrentTexture == nullptr)
 {
	 std::cout << "PNG image could not be loaded " << IMG_GetError() << std::endl;
	 success = false;
 }
 return success;

 }
 void RenderTexture::close()
 {
	 SDL_DestroyTexture(m_CurrentTexture);
	 m_CurrentTexture = nullptr;
	 SDL_DestroyWindow(m_Window);//when we destroy the window the m_ScreenSurface is destroyed too
	 m_Window = nullptr;
	 SDL_DestroyRenderer(m_Renderer);
	 m_Renderer = nullptr;
	 //shutdown SDL 
	 IMG_Quit();
	 SDL_Quit();
	

 }