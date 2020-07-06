/*
 * CApp.cpp
 *
 *  Created on: 29 juin 2020
 *      Author: armand
 */


#include "CApp.h"

#include "app.h"
#include "utils.h"

#include <iostream>
using namespace std;

extern CApp theApp;


enum STATUS	: Uint32 {
	ST_ALL_CLEARED = 0x00000000,
	ST_ALL_SETTED  = 0xFFFFFFFF,
	ST_INITIED     = 0x00000001,
	ST_APP_LOCKED  = 0x00000002,
};


#define SetLocked()		mBitsSet(theApp.m_uStatus,ST_APP_LOCKED)
#define ClrLocked()		mBitsClr(theApp.m_uStatus,ST_APP_LOCKED)
#define TglLocked()		mBitsTgl(theApp.m_uStatus,ST_APP_LOCKED)
#define IsLocked()		mIsBitsSet(theApp.m_uStatus,ST_APP_LOCKED)
#define IsNotLocked()	mIsBitsClr(theApp.m_uStatus,ST_APP_LOCKED)

CApp::CApp() :
		m_uStatus(0),
		m_uWindowID(-1),

		m_pWindow(nullptr),
		m_pRenderer(nullptr),

		m_pTextureBkgnd(nullptr),
		m_pTexture(nullptr),
		m_pTexturePause(nullptr),
		m_pTexturePlay(nullptr),

		m_pString(nullptr),

		m_colorText({240, 119, 17, 0}),

		m_pFont(nullptr),

		m_waveShootShip {nullptr},
		m_waveShootAlien {nullptr},
		m_waveDestruction {nullptr},
		m_waveWin {nullptr},
		m_waveGameOver {nullptr},

		m_pAliens(new CContainer((CContainer::t_ptfV)CAlien::DeleteFunc)),
		m_pShips(new CContainer((CContainer::t_ptfV)CShip::DeleteFunc)),
		m_pRocketsShip(new CContainer((CContainer::t_ptfV)CRocket::DeleteFunc)),
		m_pRocketsAlien(new CContainer((CContainer::t_ptfV)CRocketAlien::DeleteFunc))
{
	// TODO Auto-generated constructor stub
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)<0){
		cerr << "SDL_Init failed with error:" << SDL_GetError() << endl;
		return;
	}

	m_pWindow = SDL_CreateWindow(
			MAIN_WINDOW_TITLE,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			MAIN_WINDOW_WIDTH,
			MAIN_WINDOW_HEIGHT,
			SDL_WINDOW_SHOWN
	);

	if (!m_pWindow) {
			SDL_Quit();
			cerr << "SDL_CreateWindow() failed with error: " << SDL_GetError() << endl;
			return;
		}

	m_uWindowID = SDL_GetWindowID(m_pWindow);

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED);

	if (m_pRenderer == nullptr) {
		cerr << "Failed to create accelerated renderer." << endl;
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_SOFTWARE);
		if (m_pRenderer == nullptr) {
			cerr << "Failed to create software renderer.\n" << endl;
			return ;
		}
	}

	if (TTF_Init() == -1) {
		    cerr << "TTF_Init() failed :%s\n" << TTF_GetError() << endl;
			return ;
	}

	m_pFont = TTF_OpenFont(MAIN_GAME_FONT, SCORE_SIZE);

	if (m_pFont == NULL) {
			cerr << "TTF_OpenFont() failed : %s\n" << TTF_GetError() << endl;
			return ;
	}

	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 ){
		return ;
	}

	m_waveShootShip = Mix_LoadWAV(SHOOT_SHIP_SOUND);
	if (m_waveShootShip == NULL) {
		return ;
	}

	m_waveShootAlien = Mix_LoadWAV(SHOOT_ALIEN_SOUND);
	if (m_waveShootAlien == NULL) {
		return;
	}

	m_waveDestruction = Mix_LoadWAV(DESTRUCTION_SOUND);
	if (m_waveDestruction == NULL) {
		return;
	}

	m_waveWin = Mix_LoadWAV(WIN_SOUND);
	if (m_waveWin == NULL) {
		return ;
	}

	m_waveGameOver = Mix_LoadWAV(GAME_OVER_SOUND);
	if (m_waveGameOver == NULL) {
		return ;
	}

	SDL_Rect GameArea {
		MAIN_WINDOW_PADDING_HRZ,
		MAIN_WINDOW_PADDING_TOP,
		MAIN_WINDOW_WIDTH-2*(MAIN_WINDOW_PADDING_HRZ),
		MAIN_WINDOW_HEIGHT-(MAIN_WINDOW_PADDING_TOP + MAIN_WINDOW_PADDING_BOT)
	};

	CFigure::InitGraphic(m_pRenderer, &GameArea);
	CShip::InitGraphic(m_pRenderer,   SPACESHIP_IMAGE);
	CAlien::InitGraphic(m_pRenderer,  ALIEN_IMAGE);
	CRocket::InitGraphic(m_pRenderer, ROCKET_IMAGE);
	CRocketAlien::InitGraphic(m_pRenderer, ROCKET_ALIEN_IMAGE);

	SDL_Surface* pImageBkgnd = IMG_Load(MAIN_WINDOW_BACKGROUND_IMAGE);
	if (pImageBkgnd == nullptr) {
		cerr << "Failed to load image:" << SDL_GetError() << endl;
	}
	else {
		m_pTextureBkgnd=SDL_CreateTextureFromSurface(m_pRenderer, pImageBkgnd);
		SDL_FreeSurface(pImageBkgnd);
	}

	SDL_Surface* pImagePause = IMG_Load(MAIN_GAME_PAUSE);
		if (pImagePause == NULL) {
			fprintf(stderr,"Failed to load image: %s\n", SDL_GetError());
		}
		else {
			m_pTexturePause=SDL_CreateTextureFromSurface(m_pRenderer, pImagePause);
			SDL_FreeSurface(pImagePause);
		}
		if (m_pTexturePause) {
			SDL_RenderCopy(m_pRenderer, m_pTexturePause, NULL, NULL);
		}

	SDL_Surface* pImagePlay = IMG_Load(MAIN_GAME_PLAY);
		if (pImagePlay == NULL) {
			fprintf(stderr,"Failed to load image: %s\n", SDL_GetError());
		}
		else {
			m_pTexturePlay=SDL_CreateTextureFromSurface(m_pRenderer, pImagePlay);
			SDL_FreeSurface(pImagePlay);
		}
		if (m_pTexturePlay) {
			SDL_RenderCopy(m_pRenderer, m_pTexturePlay, NULL, NULL);
		}


	for(int k = 0; k < 4; k++){
			m_pShips->Pushback(
						new CShip(
								MAIN_WINDOW_WIDTH - 2*MAIN_WINDOW_PADDING_HRZ - (k*(SPACESHIP_SIZE * SPACESHIP_SIZE_RATIO)),
								MAIN_WINDOW_HEIGHT - MAIN_WINDOW_WAITING_SHIP_PADDING - (SPACESHIP_SIZE * SPACESHIP_SIZE_RATIO),
								SPACESHIP_SIZE_REDUCED,
								SPACESHIP_SIZE_REDUCED,
								SPACESHIP_HOT_RATIO_X,
								SPACESHIP_HOT_RATIO_Y,
								0,
								0
						)
			);
	}

	m_pShips->Pushback(
					new CShip(
							(MAIN_WINDOW_WIDTH-SPACESHIP_SIZE)/2,
							MAIN_WINDOW_HEIGHT-MAIN_WINDOW_PADDING_BOT-SPACESHIP_SIZE,
							SPACESHIP_SIZE,
							SPACESHIP_SIZE,
							SPACESHIP_HOT_RATIO_X,
							SPACESHIP_HOT_RATIO_Y,
							0,
							0
						)
				);


	for(int k=0;k<5;k++){
		for(int m=0;m<10;m++){
			m_pAliens->Pushback(
						new CAlien(
							MAIN_WINDOW_PADDING_HRZ+(ALIEN_SIZE+ALIEN_SPACING)*m,
							MAIN_WINDOW_PADDING_TOP+(ALIEN_SIZE+ALIEN_SPACING)*k,
							ALIEN_SIZE,
							ALIEN_SIZE,
							ALIEN_HOT_RATIO_X,
							ALIEN_HOT_RATIO_Y,
							ALIEN_SPEED_HRZ,
							ALIEN_SPEED_VRT
						)
			);
		}
	}









	m_nTimerID = SDL_AddTimer(MAIN_ANIMATION_TICK, AnimateCallBack, &theApp);
	m_nAlienFireID = SDL_AddTimer(1000, AlienFire, &theApp);

	SDL_RenderPresent(m_pRenderer);


	m_uStatus |= ST_INITIED;

	Run();
}

CApp::~CApp() {
	// TODO Auto-generated destructor stub

	SDL_RemoveTimer(m_nTimerID); m_nTimerID = -1;
	SDL_RemoveTimer(m_nAlienFireID); m_nAlienFireID = -1;

	delete m_pShips; m_pShips = nullptr;
	delete m_pAliens; m_pAliens = nullptr;
	delete m_pRocketsShip; m_pRocketsShip = nullptr;
	delete m_pRocketsAlien; m_pRocketsAlien = nullptr;

	CAlien::ReleaseGraphic();
	CShip::ReleaseGraphic();
	CRocket::ReleaseGraphic();
	CRocketAlien::ReleaseGraphic();

	SDL_DestroyTexture(m_pTextureBkgnd); m_pTextureBkgnd = nullptr;
	SDL_DestroyTexture(m_pTexturePause); m_pTexturePause = nullptr;
	SDL_DestroyTexture(m_pTexturePlay); m_pTexturePlay = nullptr;

	if (m_waveShootShip) {
		Mix_FreeChunk(m_waveShootShip);
	}

	if (m_waveShootAlien) {
		Mix_FreeChunk(m_waveShootAlien);
	}

	if (m_waveDestruction) {
		Mix_FreeChunk(m_waveDestruction);
	}

	if (m_waveWin) {
		Mix_FreeChunk(m_waveWin);
	}

	if (m_waveGameOver) {
		Mix_FreeChunk(m_waveGameOver);
	}

	Mix_CloseAudio();

	TTF_CloseFont(m_pFont);
	TTF_Quit();

	if(m_pRenderer){
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}

	if(m_pWindow){
		SDL_DestroyWindow(m_pWindow);
		m_pWindow = nullptr;
	}

	SDL_Quit();
}

void CApp::Run(){
	if(!(m_uStatus & ST_INITIED)) return;

	int quit {0};
	SDL_Event event;

	do{
		while(SDL_PollEvent(&event)){
			switch(event.type){
			case SDL_MOUSEMOTION:
				if (IsLocked())	{ break; }
				CShip::MoveFunc((CShip*)m_pShips->Getback(), event.motion.x, 0);
				break;
			case SDL_MOUSEBUTTONUP: // Evènement souris : Bouton gauche de la souris relâchée----------//
				if((event.button.button == SDL_BUTTON_LEFT) && (m_pRocketsShip->Card() < 3)) {
					if (IsLocked())	{ break; }
					m_pRocketsShip->Pushback(
									new CRocket(
										CShip::GetHotPointFunc((CShip*)m_pShips->Getback())->x + SPACESHIP_SIZE/2,
										MAIN_WINDOW_HEIGHT-MAIN_WINDOW_PADDING_BOT-SPACESHIP_SIZE,
										ROCKET_WIDTH,
										ROCKET_HEIGHT,
										ROCKET_HOT_RATIO_X,
										ROCKET_HOT_RATIO_Y,
										0,
										ROCKET_SHIP_SPEED_VRT
								)
						);
					Mix_PlayChannel(-1, m_waveShootShip, 0);
				}
						break;
			case SDL_QUIT:
				quit=1;
				break;

			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_SPACE:
					TglLocked();
					GamePaused(&theApp);
					break;
				case SDLK_ESCAPE:
					quit=1;
					break;

				default:
					break;
				}
				break;

			default:
				break;
			}
		}
	}while(quit!=1);
}

bool CApp::IsInitiated() const { return m_uStatus & ST_INITIED; }

Uint32 CApp::AnimateCallBack(Uint32 interval, void* pParam){

	CApp * pTheApp { reinterpret_cast<CApp*>(pParam) };

	if (IsLocked())	{SDL_RenderPresent(pTheApp->m_pRenderer); return interval; }

	SDL_Rect r;
	r.x = MAIN_PAUSE_PLAY_X;
	r.y = MAIN_PAUSE_PLAY_Y;
	r.h = MAIN_SIZE_PAUSE_PLAY;
	r.w = MAIN_SIZE_PAUSE_PLAY;

	SDL_RenderCopy(pTheApp->m_pRenderer, pTheApp->m_pTextureBkgnd, nullptr, nullptr);
	SDL_RenderCopy(pTheApp->m_pRenderer, pTheApp->m_pTexturePlay, NULL, &r);

	if (!pTheApp->m_pShips->Card() || IsOvfBot(CAlien::ovf)) {
		SetLocked();
		Mix_PlayChannel(-1, pTheApp->m_waveGameOver, 0);
		MessageBox(pParam, (char*)"GAME OVER", MAIN_WINDOW_PADDING_HRZ, ((MAIN_WINDOW_HEIGHT / 2) - (MAIN_WINDOW_HEIGHT / 6)), MAIN_WINDOW_WIDTH - (MAIN_WINDOW_PADDING_HRZ * 2), MAIN_WINDOW_HEIGHT / 6, -1);
		MessageBox(pParam, (char*)"YOUR SCORE:", MAIN_WINDOW_WIDTH / 4, ((MAIN_WINDOW_HEIGHT / 2) + (MAIN_WINDOW_HEIGHT / 8)), MAIN_WINDOW_WIDTH / 2, MAIN_WINDOW_HEIGHT / 8, 1);
		SDL_RenderPresent(pTheApp->m_pRenderer);
		return interval;
	}

	if (!pTheApp->m_pAliens->Card()) {
		SetLocked();
		Mix_PlayChannel(-1, pTheApp->m_waveWin, 0);
		MessageBox(pParam, (char*)"COMPLETED",0, ((MAIN_WINDOW_HEIGHT / 2) - (MAIN_WINDOW_HEIGHT / 6)), MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT / 6, -1);
		SDL_RenderPresent(pTheApp->m_pRenderer);
		return interval;
	}


	pTheApp->m_pAliens->Parse((CContainer::t_ptfVV)CAlien::MoveFunc, nullptr);
	if( (IsOvfLeft(CAlien::ovf)) || (IsOvfRight(CAlien::ovf)) ) {pTheApp->m_pAliens->Parse((CContainer::t_ptfVV)CAlien::MoveReverseFunc, nullptr); }
	pTheApp->m_pRocketsShip->ParseDelIf((CContainer::t_ptfVV)CRocket::MoveFunc, nullptr);
	pTheApp->m_pRocketsAlien->ParseDelIf((CContainer::t_ptfVV)CRocketAlien::MoveFunc, nullptr);



	pTheApp->m_pShips->Parse((CContainer::t_ptfVV)CShip::DrawFunc, nullptr);
	pTheApp->m_pAliens->Parse((CContainer::t_ptfVV)CAlien::DrawFunc, nullptr);
	pTheApp->m_pRocketsShip->Parse((CContainer::t_ptfVV)CRocket::DrawFunc, nullptr);
	pTheApp->m_pRocketsAlien->Parse((CContainer::t_ptfVV)CRocketAlien::DrawFunc, nullptr);

	pTheApp->m_pRocketsShip->IntersectDelElemsIf(pTheApp->m_pAliens, (CContainer::t_ptfVVVV)CFigure::Intersection, (CContainer::t_ptfV)pTheApp->GameUpdate, pParam);
	pTheApp->m_pRocketsAlien->IntersectShipDelElemsIf(pTheApp->m_pShips, (CContainer::t_ptfVVVV)CFigure::Intersection, (CContainer::t_ptfV)CShip::ShipRelife, nullptr);


	pTheApp->MessageBox(pParam, (char*)"SCORE<1>", SCORE1_X, SCORE_Y, SCORE_SIZE, SCORE_SIZE/8, pTheApp->m_score1);
	pTheApp->MessageBox(pParam, (char*)"HIGHSCORE", (HIGHSCORE_X-(SCORE_SIZE/2)), SCORE_Y, SCORE_SIZE, SCORE_SIZE/8, pTheApp->m_highScore);
	pTheApp->MessageBox(pParam, (char*)"SCORE<2>", (SCORE2_X-SCORE_SIZE), SCORE_Y, SCORE_SIZE, SCORE_SIZE/8, pTheApp->m_score2);

	SDL_RenderPresent(pTheApp->m_pRenderer);

	return interval;
}

Uint32 CApp::AlienFire(Uint32 interval, void* pParam){

	if (IsLocked())	{ return interval; }
	CApp * pTheApp { reinterpret_cast<CApp*>(pParam) };
		pTheApp->m_pRocketsAlien->Pushback(
									new CRocket(
											CAlien::GetHotPointFunc((CAlien*)pTheApp->m_pAliens->Getat(rand() % pTheApp->m_pAliens->Card()))->x - ROCKET_WIDTH/5,
											CAlien::GetHotPointFunc((CAlien*)pTheApp->m_pAliens->Getat(rand() % pTheApp->m_pAliens->Card()))->y + ALIEN_SIZE/2,
											ROCKET_WIDTH,
											ROCKET_HEIGHT,
											ROCKET_HOT_RATIO_X,
											ROCKET_HOT_RATIO_Y,
											0,
											ROCKET_ALIEN_SPEED_VRT
									)
								);
		Mix_PlayChannel(-1, pTheApp->m_waveShootAlien, 0);
	return interval;
}

int CApp::MessageBox(void*pParam, char*msg, int positionX,int positionY, int width, int height ,int valeur){

	CApp * pTheApp { reinterpret_cast<CApp*>(pParam) };
	SDL_Rect rectMessageBox;
	char buf[255];

	// Affichage des scores
	rectMessageBox.x = positionX;
	rectMessageBox.y = positionY;
	rectMessageBox.w = width;
	rectMessageBox.h = height;

	if(valeur == 1){
		sprintf(buf, "%s %d", msg, pTheApp->m_score1);
	}else if(valeur==-1){
		sprintf(buf, "%s", msg);
	}else{
		sprintf(buf, "%s %03d", msg, valeur);

	}

	pTheApp->m_pString = TTF_RenderText_Blended(pTheApp->m_pFont, buf, pTheApp->m_colorText);
	pTheApp->m_pTexture = SDL_CreateTextureFromSurface(pTheApp->m_pRenderer, pTheApp->m_pString);
	SDL_RenderCopy(pTheApp->m_pRenderer, pTheApp->m_pTexture, NULL, &rectMessageBox);
	SDL_DestroyTexture(pTheApp->m_pTexture);
	SDL_FreeSurface(pTheApp->m_pString);

	return 0;
}

int CApp::GamePaused(void*pParam) {

	CApp * pTheApp { reinterpret_cast<CApp*>(pParam) };
	SDL_Rect r;

	r.x = MAIN_PAUSE_PLAY_X;
	r.y = MAIN_PAUSE_PLAY_Y;
	r.w = MAIN_SIZE_PAUSE_PLAY;
	r.h = MAIN_SIZE_PAUSE_PLAY;

	SDL_RenderCopy(pTheApp->m_pRenderer, pTheApp->m_pTexturePause, NULL, &r);
	MessageBox(pParam, (char*)"PAUSE", ((MAIN_WINDOW_WIDTH / 2) - (MAIN_WINDOW_WIDTH / 4)) , ((MAIN_WINDOW_HEIGHT / 2) - (MAIN_WINDOW_HEIGHT / 6)), MAIN_WINDOW_WIDTH / 2, MAIN_WINDOW_HEIGHT / 6, -1);

	return 0;
}
