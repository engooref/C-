/*
 * CRocket.h
 *
 *  Created on: 1 juil. 2020
 *      Author: armand
 */

#ifndef CROCKET_H_
#define CROCKET_H_

#include <CFigure.h>

class CRocket: public CFigure {
private:
	static SDL_Texture * C_pTexture;

public:
	CRocket();
	CRocket(
		int iLocX,
		int iLocY,
		int iWidth,
		int iHeigth,
		int iHotRatioX,
		int iHotRatioY,
		int iSpeedX,
		int iSpeedY );

	~CRocket();

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

	static CRocket*DrawFunc(CRocket*pRocket, void*pParam){
		pRocket->Draw();
		return pRocket;
	}

	static CRocket*MoveFunc(CRocket*pRocket, void*pParam){
			pRocket->Move();
			if(IsOvfTop(rocketOvf)) { ClrOvfTop(rocketOvf); return nullptr; }
			else { return pRocket; }
	}

	static void* DeleteFunc(CRocket*pRocket){
			delete pRocket;
			return nullptr;
	}


	static Uint32 rocketOvf;
};

#endif /* CROCKET_H_ */
