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
	cout << "CShip::CShip()" << endl;

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
	cout << "~CShip::~CShip()" << endl;

}

void CShip::Draw() const{
	CFigure::Draw(C_pTexture);

}
