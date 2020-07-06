/*
 * CShip.cpp
 *
 *  Created on: 29 juin 2020
 *      Author: armand
 */

#include <CShip.h>
SDL_Texture * CShip::C_pTexture {nullptr};
CShip::CShip() {
	// TODO Auto-generated constructor stub

}

CShip::CShip(	int iLocX,
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

CShip::~CShip() {
	// TODO Auto-generated destructor stub

}

void CShip::Draw() const{
	CFigure::Draw(C_pTexture);

}

void CShip::Move(int iLocX, int iLocY) {
	iLocY = m_frame.x;
	m_frame.x = iLocX-m_frame.w/2;

	if( (m_frame.x < C_gameArea.x) || (m_frame.x + m_frame.w > C_gameArea.x+C_gameArea.w) ) { m_frame.x = iLocY; }
}

SDL_Point* CShip::GetHotPoint(){
	return CFigure::GetHotPoint();
}


