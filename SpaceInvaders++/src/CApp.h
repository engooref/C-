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

#include "CFigure.h"
#include "CShip.h"
#include "CAlien.h"
#include "CRocket.h"
#include "CRocketAlien.h"

#include "CContainer.h"


class CApp {
private:
	Uint32				m_uStatus;
	Uint32				m_uWindowID;

	SDL_Window 	 	* 	m_pWindow;
	SDL_Renderer	*	m_pRenderer;

	SDL_Texture		*	m_pTextureBkgnd;
	SDL_Texture		*   m_pTexture;
	SDL_Texture		*	m_pTexturePause;
	SDL_Texture		*	m_pTexturePlay;

	SDL_Surface	 	*	m_pString;

	SDL_Color       	m_colorText;

	SDL_TimerID			m_nTimerID;
	SDL_TimerID			m_nAlienFireID;

	TTF_Font     	*   m_pFont;

	Mix_Chunk	 	*	m_waveShootShip;
	Mix_Chunk	 	*	m_waveShootAlien;
	Mix_Chunk	 	*	m_waveDestruction;
	Mix_Chunk	 	*	m_waveWin;
	Mix_Chunk	 	*	m_waveGameOver;

	CContainer		*	m_pAliens;
	CContainer		*	m_pShips;
	CContainer		*   m_pRocketsShip;
	CContainer		*	m_pRocketsAlien;

	int					m_score1;
	int					m_score2;
	int 				m_highScore;

public:
	CApp();
	~CApp();

private:
	void Run();
	bool IsInitiated() const;
	static Uint32 AnimateCallBack(Uint32 interval, void *pParam);
	static Uint32 AlienFire(Uint32 interval, void* pParam);
	static int MessageBox(void*pParam, char*msg, int positionX,int positionY, int width, int height ,int valeur);
	static int GamePaused(void*pParam);
	static void* GameUpdate(void* pParam){
		CApp * pTheApp { reinterpret_cast<CApp*>(pParam) };
		pTheApp->m_score1 += 100;
		return nullptr;
	}
};

#endif /* CAPP_H_ */
