/*
 * CApp.h
 *
 *  Created on: 29 juin 2020
 *      Author: armand
 */

#ifndef CAPP_H_
#define CAPP_H_

#include <iostream>
using namespace std;

#define SDL_MAIN_HANDLED
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include <CShip.h>
#include <CFigure.h>
#include "app.h"

class CApp {
private:
	Uint32				m_uStatus;
	Uint32				m_uWindowID;
	SDL_Window 	 	* 	m_pWindow;
	SDL_Renderer	*	m_pRenderer;
	SDL_Texture		*	m_pTextureBkgnd;
	SDL_TimerID			m_nTimerID;

	CShip				m_ship{10,10,SPACESHIP_SIZE,SPACESHIP_SIZE,0,0,0,0};


public:
	CApp();
	~CApp();

private:
	void Run();
	bool IsInitiated() const;
	Uint32	AnimationCallback(Uint32 interval, void*pParam);
};

#endif /* CAPP_H_ */
