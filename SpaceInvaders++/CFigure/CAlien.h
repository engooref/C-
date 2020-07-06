/*
 * CAliens.h
 *
 *  Created on: 1 juil. 2020
 *      Author: armand
 */

#ifndef CALIEN_H_
#define CALIEN_H_

#include <CFigure.h>


class CAlien: public CFigure {
private:
	static SDL_Texture * C_pTexture;


public:
	CAlien();
	CAlien(
		int iLocX,
		int iLocY,
		int iWidth,
		int iHeigth,
		int iHotRatioX,
		int iHotRatioY,
		int iSpeedX,
		int iSpeedY );

	~CAlien();

	void Draw() const;
	void Move();
	void MoveReverse();
	SDL_Point* GetHotPoint();

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

	static CAlien*DrawFunc(CAlien*pAlien, void*pParam){
		pAlien->Draw();
		return pAlien;
	}

	static CAlien*MoveFunc(CAlien*pAlien, void*pParam){
			pAlien->Move();
			return pAlien;
	}

	static CAlien*MoveReverseFunc(CAlien*pAlien, void*pParam){
				pAlien->MoveReverse();
				return pAlien;
	}

	static void* DeleteFunc(CAlien*pAlien){
		delete pAlien;
		return nullptr;
	}

	static SDL_Point*GetHotPointFunc(CAlien*pAlien){
				return pAlien->GetHotPoint();
	}

	static Uint32 ovf;
};

#endif /* CALIENS_H_ */
