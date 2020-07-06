/*
 * CRocket.cpp
 *
 *  Created on: 1 juil. 2020
 *      Author: armand
 */

#include <CRocket.h>

SDL_Texture * CRocket::C_pTexture {nullptr};
Uint32 CRocket::rocketOvf {0};

CRocket::CRocket() {
	// TODO Auto-generated constructor stub

}

CRocket::CRocket(int iLocX,
		int iLocY,
		int iWidth,
		int iHeigth,
		int iHotRatioX,
		int iHotRatioY,
		int iSpeedX,
		int iSpeedY ) :

		CFigure(iLocX, iLocY, iWidth, iHeigth, iHotRatioX, iHotRatioY, iSpeedX, iSpeedY )
{
	// TODO Auto-generated constructor stub

}

CRocket::~CRocket() {
	// TODO Auto-generated destructor stub

}

void CRocket::Draw() const{
	CFigure::Draw(C_pTexture);

}

void CRocket::Move() {
	m_frame.y += m_speed.y;
	if(m_frame.y < C_gameArea.y) { SetOvfTop(rocketOvf); }
}
