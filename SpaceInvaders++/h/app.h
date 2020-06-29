/*
 * app.h
 *
 *  Created on: 14 mai 2020
 *      Author: Groupe 1
 */

/* D�finition des diff�rentes constantes li�es � notre fen�tre d'application */
#define MAIN_WINDOW_SCALE					(3.0/1.5)
#define MAIN_WINDOW_WIDTH					((int)(740*MAIN_WINDOW_SCALE))
#define MAIN_WINDOW_HEIGHT					((int)(480*MAIN_WINDOW_SCALE))
#define MAIN_WINDOW_TITLE					"Space Invaders"
#define MAIN_WINDOW_BACKGROUND_IMAGE		"./Resources/Images/galaxy.jpeg"
#define MAIN_WINDOW_PADDING_BOT				((int)(30*MAIN_WINDOW_SCALE))
#define MAIN_WINDOW_PADDING_TOP				((int)(50*MAIN_WINDOW_SCALE))
#define MAIN_WINDOW_PADDING_HRZ				((int)(20*MAIN_WINDOW_SCALE))
#define MAIN_WINDOW_WAITING_SHIP_PADDING	((int)(5*MAIN_WINDOW_SCALE))
#define MAIN_WINDOW_SCORE_PADDING			((int)(4*MAIN_WINDOW_SCALE))
#define MAIN_ANIMATION_TICK					(20)
#define MAIN_GAME_FONT						"./Resources/Fonts/ARCADE_N.TTF"
#define MAIN_GAME_PAUSE						"./Resources/Images/pause.jpeg"
#define MAIN_GAME_PLAY						"./Resources/Images/play.jpeg"
#define MAIN_SIZE_PAUSE_PLAY				(30)
#define MAIN_PAUSE_PLAY_X					((MAIN_WINDOW_WIDTH - MAIN_WINDOW_PADDING_HRZ) - MAIN_SIZE_PAUSE_PLAY)
#define MAIN_PAUSE_PLAY_Y					((MAIN_WINDOW_PADDING_TOP / 3) - MAIN_SIZE_PAUSE_PLAY)


/* D�finition des diff�rentes constantes li�es au vaisseau spatial */
#define SPACESHIP_IMAGE						"./Resources/Images/spaceship.jpeg"
#define SPACESHIP_SIZE						(int)(50*MAIN_WINDOW_SCALE)
#define SPACESHIP_HOT_RATIO_X				(0.5)
#define SPACESHIP_HOT_RATIO_Y				(0)
#define NB_LIFES_SHIP  						(5)


/* D�finition des diff�rentes constantes li�es aux aliens */
#define ALIEN_IMAGE							"./Resources/Images/alien.jpeg"
#define ALIEN_SIZE							(25*MAIN_WINDOW_SCALE)
#define ALIEN_SPACING						(5*MAIN_WINDOW_SCALE)
#define ALIEN_NB_ROW						(5)
#define ALIEN_NB_COL						(10)
#define ALIEN_HOT_RATIO_X			        (0.5)
#define ALIEN_HOT_RATIO_Y					(0)
#define ALIEN_SPEED_HRZ						(10)
#define ALIEN_SPEED_VRT 					(20)


/* D�finition des diff�rentes constantes li�es aux rockets */
#define ROCKET_IMAGE						"./Resources/Images/rocket.jpeg"
#define ROCKET_WIDTH						(MAIN_WINDOW_WIDTH/(120*MAIN_WINDOW_SCALE))		//ROCKET_WIDTH*2 pour les rockets envoy�s par les Aliens
#define ROCKET_HEIGHT						(MAIN_WINDOW_HEIGHT/(12*MAIN_WINDOW_SCALE))  	//ROCKET_HEIGHT/2 pour les rockets envoy�s par les Aliens
#define ROCKET_HOT_RATIO_X			        (0.5)
#define ROCKET_HOT_RATIO_Y					(0)
#define ROCKET_SHIP_SPEED_VRT				(-6)
#define ROCKET_ALIEN_SPEED_VRT				(2)
#define ROCKET_SHIP_SHOOTED					(5)

/* D�finition des diff�rentes constantes li�es aux scores */
#define SCORE_SIZE                          (75*MAIN_WINDOW_SCALE)
#define SCORE1_X                            (MAIN_WINDOW_PADDING_HRZ)
#define SCORE2_X                            (MAIN_WINDOW_WIDTH-MAIN_WINDOW_PADDING_HRZ)
#define HIGHSCORE_X   						(MAIN_WINDOW_WIDTH/2)
#define SCORE_Y								(MAIN_WINDOW_PADDING_TOP/2)

/* D�finition des diff�rents sons impl�ment�s dans notre jeu */
#define DESTRUCTION_SOUND 					"./Resources/Sounds/destruction.wav"
#define SHOOT_SHIP_SOUND 					"./Resources/Sounds/shootShip.wav"
#define SHOOT_ALIEN_SOUND 					"./Resources/Sounds/shootAlien.wav"
#define WIN_SOUND 							"./Resources/Sounds/win.wav"
#define GAME_OVER_SOUND 					"./Resources/Sounds/gameOver.wav"
#define THEME_SOUND							"./Resources/Sounds/theme.wav"

/* D�finition des diff�rentes masques */
#define mBitsSet(f,m)			((f)|=(m))
#define mBitsClr(f,m)			((f)&=(~(m)))
#define mBitsTgl(f,m)			((f)^=(m))
#define mBitsMsk(f,m)			((f)& (m))
#define mIsBitsSet(f,m)			(((f)&(m))==(m))
#define mIsBitsClr(f,m)			(((~(f))&(m))==(m))

int AppNew(void);
int AppRun(void);
int AppDel(void);
