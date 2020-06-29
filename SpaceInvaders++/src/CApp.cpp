/*
 * CApp.cpp
 *
 *  Created on: 29 juin 2020
 *      Author: armand
 */


#include "CApp.h"

#include "app.h"

#include <iostream>
using namespace std;

enum STATUS	: Uint32 {
	ST_ALL_CLEARED = 0x00000000,
	ST_ALL_SETTED  = 0xFFFFFFFF,
	ST_INITIED     = 0x00000001,
};

CApp::CApp() :
		m_uStatus(0),
		m_uWindowID(-1),
		m_pWindow(nullptr),
		m_pRenderer(nullptr)
{
	// TODO Auto-generated constructor stub
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)<0){
		cerr << "SDL_Init failed with error:" << SDL_GetError() << endl;
		return;
	}

	m_pWindow = SDL_CreateWindow(
			MAIN_WINDOW_TITLE,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			MAIN_WINDOW_WIDTH,
			MAIN_WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN
	);

	if (!m_pWindow) {
			SDL_Quit();
			cerr << "SDL_CreateWindow() failed with error: " << SDL_GetError() << endl;
			return;
		}

	m_uWindowID = SDL_GetWindowID(m_pWindow);

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	if (m_pRenderer == nullptr) {
		cerr << "Failed to create accelerated renderer." << endl;
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
		if (m_pRenderer == nullptr) {
			cerr << "Failed to create software renderer.\n" << endl;
			return ;
		}
		cout << "Software renderer created instead!" << endl;
	}


	SDL_Rect GameArea {
		MAIN_WINDOW_PADDING_HRZ,
		MAIN_WINDOW_PADDING_TOP,
		MAIN_WINDOW_WIDTH-2*(MAIN_WINDOW_PADDING_HRZ),
		MAIN_WINDOW_HEIGHT-(MAIN_WINDOW_PADDING_TOP + MAIN_WINDOW_PADDING_BOT)
	};

	CFigure::InitGraphic(m_pRenderer, &GameArea);
	CShip::InitGraphic(m_pRenderer, SPACESHIP_IMAGE);

	SDL_Surface* pImageBkgnd = IMG_Load(MAIN_WINDOW_BACKGROUND_IMAGE);
	if (pImageBkgnd == NULL) {
		cerr << "Failed to load image:" << SDL_GetError() << endl;
	}
	else {
		m_pTextureBkgnd=SDL_CreateTextureFromSurface(m_pRenderer, pImageBkgnd);
		SDL_FreeSurface(pImageBkgnd);
	}
	if (m_pTextureBkgnd) {
		SDL_RenderCopy(m_pRenderer, m_pTextureBkgnd, NULL, NULL);
	}


	m_ship.Draw();

	//m_nTimerID = SDL_AddTimer(MAIN_ANIMATION_TICK, AnimationCallback, NULL);
	SDL_RenderPresent(m_pRenderer);


	m_uStatus |= ST_INITIED;
	cout << "CApp::CApp()" << endl;

	Run();
}

CApp::~CApp() {
	// TODO Auto-generated destructor stub

	SDL_RemoveTimer(m_nTimerID); m_nTimerID = -1;

	CShip::ReleaseGraphic();

	if(m_pRenderer){
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}

	if(m_pWindow){
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}

	SDL_Quit();
	cout << "CApp::~CApp()" << endl;
}

void CApp::Run(){
	cout << "CApp::Run()" << endl;

	if(!(m_uStatus & ST_INITIED)) return;

	int quit {0};
	SDL_Event event;

	do{
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_QUIT:
				quit=1;
				break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_ESCAPE:
					quit=1;
					break;

				default:
					break;
				}
				break;

			default:
				break;
			}
		}
	}while(quit!=1);
}

bool CApp::IsInitiated() const { return m_uStatus & ST_INITIED; }

Uint32 AnimationCallback(Uint32 interval, void*pParam) {

	return interval;
}
