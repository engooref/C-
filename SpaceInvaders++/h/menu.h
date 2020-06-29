/*
 * menu.h
 *
 *  Created on: 16 juin 2020
 *      Author: armand
 */

/* Définition des différentes masques */
#define mBitsSet(f,m)			((f)|=(m))
#define mBitsClr(f,m)			((f)&=(~(m)))
#define mBitsTgl(f,m)			((f)^=(m))
#define mBitsMsk(f,m)			((f)& (m))
#define mIsBitsSet(f,m)			(((f)&(m))==(m))
#define mIsBitsClr(f,m)			(((~(f))&(m))==(m))

int MenuNew(void);
int MenuDel(void);
int MenuRun(void);
