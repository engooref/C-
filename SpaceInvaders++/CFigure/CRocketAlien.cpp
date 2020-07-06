#include <CRocketAlien.h>

SDL_Texture * CRocketAlien::C_pTexture {nullptr};
Uint32 CRocketAlien::rocketAlienOvf {0};

CRocketAlien::CRocketAlien() {
	// TODO Auto-generated constructor stub

}

CRocketAlien::CRocketAlien(int iLocX,
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

CRocketAlien::~CRocketAlien() {
	// TODO Auto-generated destructor stub

}

void CRocketAlien::Draw() const{
	CFigure::Draw(C_pTexture);

}

void CRocketAlien::Move() {
	m_frame.y += m_speed.y;
	if(m_frame.y + m_frame.h > C_gameArea.h+C_gameArea.y) { SetOvfBot(rocketAlienOvf); }
}
