/*
 * CAliens.cpp
 *
 *  Created on: 1 juil. 2020
 *      Author: armand
 */

#include <CAlien.h>
#include <iostream>
using namespace std;

SDL_Texture * CAlien::C_pTexture {nullptr};
Uint32 CAlien::ovf {0};


CAlien::CAlien() {
	// TODO Auto-generated constructor stub

}

CAlien::CAlien(	int iLocX,
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

CAlien::~CAlien() {
	// TODO Auto-generated destructor stub

}

void CAlien::Draw() const{
	CFigure::Draw(C_pTexture);

}

void CAlien::Move() {
	m_frame.x += m_speed.x;
	if( (m_frame.x < C_gameArea.x) ) { SetOvfLeft(ovf); }
	if( (m_frame.x + m_frame.w > C_gameArea.x+C_gameArea.w) ) { SetOvfRight(ovf); }
	if( m_frame.y + m_frame.h > C_gameArea.h) { SetOvfBot(ovf); }
}

void CAlien::MoveReverse() {
	m_speed.x *= -1;
	m_frame.y += m_speed.y;
	if(IsOvfLeft(ovf)) { ClrOvfLeft(ovf); }
	if(IsOvfRight(ovf)) { ClrOvfRight(ovf); }

}

SDL_Point* CAlien::GetHotPoint(){
	return CFigure::GetHotPoint();
}
