/*
 * CFigure.h
 *
 *  Created on: 29 juin 2020
 *      Author: armand
 */

#ifndef CFIGURE_H_
#define CFIGURE_H_

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class CFigure {
private:
	static SDL_Renderer	* C_pRenderer;
	static SDL_Rect		* C_gameArea;


protected:
	SDL_Rect	m_frame;
	SDL_Point	m_hotPointRatio;
	SDL_Point	m_speed;

public:
	CFigure();
	CFigure(
		int iLocX,
		int iLocY,
		int iWidth,
		int iHeigth,
		int iHotRatioX,
		int iHotRatioY,
		int iSpeedX,
		int iSpeedY
	);
	~CFigure();

	int  Move();
	int  Move(int iX, int iY);
	void Draw(SDL_Texture*pTexture) const;

public:
	static void InitGraphic(SDL_Renderer*pRenderer,const SDL_Rect* pGameArea){
		C_pRenderer = pRenderer;
		SDL_memcpy(&C_gameArea, pGameArea, sizeof(SDL_Rect));
	}
};

#endif /* CFIGURE_H_ */
