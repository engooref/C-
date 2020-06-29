/*
 * CShip.h
 *
 *  Created on: 29 juin 2020
 *      Author: armand
 */

#ifndef CSHIP_H_
#define CSHIP_H_

#include <CFigure.h>
#include <iostream>
using namespace std;
class CShip : public CFigure {
private:
	static SDL_Texture * C_pTexture;

public:
	CShip();
	CShip(
		int iLocX,
		int iLocY,
		int iWidth,
		int iHeigth,
		int iHotRatioX,
		int iHotRatioY,
		int iSpeedX,
		int iSpeedY );

	~CShip();

	void Draw() const;
public:
	static void InitGraphic(SDL_Renderer*pRenderer, const char*pImageFileName){
		SDL_Surface * image = IMG_Load(pImageFileName);
		if (image == nullptr) return;
		C_pTexture = SDL_CreateTextureFromSurface(pRenderer, image);
		SDL_FreeSurface(image);

	};
	static void ReleaseGraphic(){
		if (C_pTexture) {
				SDL_DestroyTexture(C_pTexture);
				C_pTexture = nullptr;
			}
	}
};

#endif /* CSHIP_H_ */
