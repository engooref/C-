
#ifndef _UTILS_H
#define _UTILS_H

/* Définition des différentes masques */
#define mBitsSet(f,m)			((f)|=(m))
#define mBitsClr(f,m)			((f)&=(~(m)))
#define mBitsTgl(f,m)			((f)^=(m))
#define mBitsMsk(f,m)			((f)& (m))
#define mIsBitsSet(f,m)			(((f)&(m))==(m))
#define mIsBitsClr(f,m)			(((~(f))&(m))==(m))


/*		Overflow	*/
enum OVF : Uint32 {
	OVF_TOP   = 0x01,
	OVF_BOT   = 0x02,
	OVF_LEFT  = 0x03,
	OVF_RIGHT = 0x04,
};


#define SetOvfTop(ovf)			mBitsSet(ovf, OVF_TOP)
#define ClrOvfTop(ovf)			mBitsClr(ovf, OVF_TOP)
#define IsOvfTop(ovf)			mIsBitsSet(ovf, OVF_TOP)
#define IsNotOvfTop(ovf)		mIsBitsClr(ovf, OVF_TOP)

#define SetOvfBot(ovf)			mBitsSet(ovf, OVF_BOT)
#define ClrOvfBot(ovf)			mBitsClr(ovf, OVF_BOT)
#define IsOvfBot(ovf)			mIsBitsSet(ovf, OVF_BOT)
#define IsNotOvfBot(ovf)		mIsBitsClr(ovf, OVF_BOT)

#define SetOvfLeft(ovf)			mBitsSet(ovf, OVF_LEFT)
#define ClrOvfLeft(ovf)			mBitsClr(ovf, OVF_LEFT)
#define IsOvfLeft(ovf)			mIsBitsSet(ovf, OVF_LEFT)
#define IsNotOvfLeft(ovf)		mIsBitsClr(ovf, OVF_LEFT)

#define SetOvfRight(ovf)		mBitsSet(ovf, OVF_RIGHT)
#define ClrOvfRight(ovf)		mBitsClr(ovf, OVF_RIGHT)
#define IsOvfRight(ovf)			mIsBitsSet(ovf, OVF_RIGHT)
#define IsNotOvfRight(ovf)		mIsBitsClr(ovf, OVF_RIGHT)

#endif
