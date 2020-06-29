/*
 * Window.h
 *
 *  Created on: 17 juin 2020
 *      Author: armand
 */

/* Définition des différentes constantes liées à notre fenêtre d'application */
#define MAIN_WINDOW_SCALE					(2.0/1.0)
#define MAIN_WINDOW_WIDTH					(740*MAIN_WINDOW_SCALE)
#define MAIN_WINDOW_HEIGHT					(480*MAIN_WINDOW_SCALE)
#define MAIN_WINDOW_TITLE					"Space Invaders"
#define MAIN_WINDOW_BACKGROUND_IMAGE		"./Resources/Images/galaxy.jpeg"
#define MAIN_WINDOW_PADDING_BOT				(30*MAIN_WINDOW_SCALE)
#define MAIN_WINDOW_PADDING_TOP				(50*MAIN_WINDOW_SCALE)
#define MAIN_WINDOW_PADDING_HRZ				(20*MAIN_WINDOW_SCALE)
#define MAIN_WINDOW_WAITING_SHIP_PADDING	(5*MAIN_WINDOW_SCALE)
#define MAIN_WINDOW_SCORE_PADDING			(4*MAIN_WINDOW_SCALE)
#define MAIN_ANIMATION_TICK					(20)
#define MAIN_GAME_FONT						"./Resources/Fonts/ARCADE_N.TTF"

/* Définition des différentes constantes liées aux scores */
#define SCORE_SIZE                          (75*MAIN_WINDOW_SCALE)
#define SCORE1_X                            (MAIN_WINDOW_PADDING_HRZ)
#define SCORE2_X                            (MAIN_WINDOW_WIDTH-MAIN_WINDOW_PADDING_HRZ)
#define HIGHSCORE_X   						(MAIN_WINDOW_WIDTH/2)
#define SCORE_Y								(MAIN_WINDOW_PADDING_TOP/2)

