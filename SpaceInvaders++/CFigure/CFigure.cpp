/*
 * CFigure.cpp
 *
 *  Created on: 29 juin 2020
 *      Author: armand
 */

#include <CFigure.h>


#include <iostream>
using namespace std;

SDL_Renderer * CFigure::C_pRenderer {nullptr};
SDL_Rect	  CFigure::C_gameArea  {0};


CFigure::CFigure() :
	m_frame({0}),
	m_hotPointRatio({0}),
	m_speed({0})
{

}
CFigure::CFigure(	int iLocX,
		int iLocY,
		int iWidth,
		int iHeigth,
		int iHotRatioX,
		int iHotRatioY,
		int iSpeedX,
		int iSpeedY ) :

		m_frame({iLocX, iLocY, iWidth, iHeigth}),
		m_hotPointRatio({iHotRatioX, iHotRatioY}),
		m_speed({iSpeedX, iSpeedY})

{
	// TODO Auto-generated constructor stub

}

CFigure::~CFigure() {
	// TODO Auto-generated destructor stub

}

int CFigure::Move(){
	m_frame.x += m_speed.x;
	m_frame.y += m_frame.y;
	return 0;
}

int CFigure::Move(int iX, int iY){
	m_frame.x = iX;
	m_frame.y = iY;
	return 0;
}

void CFigure::Draw(SDL_Texture*pTexture) const {
	SDL_SetTextureBlendMode(pTexture, SDL_BLENDMODE_ADD);
	SDL_RenderCopy(C_pRenderer, pTexture, NULL, &m_frame);
}

SDL_Point* CFigure::GetHotPoint(){
	static SDL_Point hotPoint;
	hotPoint.x = m_frame.x + m_frame.w * (m_hotPointRatio.x/100);
	hotPoint.y = m_frame.y + m_frame.h * (m_hotPointRatio.y/100);
	return &hotPoint;

}

