/*
 * CRocketAlien.h
 *
 *  Created on: 1 juil. 2020
 *      Author: armand
 */

#ifndef CROCKETALIEN_H_
#define CROCKETALIEN_H_

#include <CFigure.h>

class CRocketAlien: public CFigure {
private:
	static SDL_Texture * C_pTexture;

public:
	CRocketAlien();
	CRocketAlien(
		int iLocX,
		int iLocY,
		int iWidth,
		int iHeigth,
		int iHotRatioX,
		int iHotRatioY,
		int iSpeedX,
		int iSpeedY );

	~CRocketAlien();

	void Draw() const;
	void Move();

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

	static CRocketAlien*DrawFunc(CRocketAlien*pRocket, void*pParam){
		pRocket->Draw();
		return pRocket;
	}

	static CRocketAlien*MoveFunc(CRocketAlien*pRocket, void*pParam){
			pRocket->Move();
			if(IsOvfBot(rocketAlienOvf)) { ClrOvfBot(rocketAlienOvf); return nullptr; }
			else { return pRocket; }
	}

	static void* DeleteFunc(CRocketAlien*pRocket){
			delete pRocket;
			return nullptr;
	}

	static Uint32 rocketAlienOvf;
};

#endif /* CROCKETALIEN_H_ */
