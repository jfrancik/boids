#include "stdafx.h"
#include "MyGame.h"
#include "Boid.h"

CMyGame::CMyGame(void) : m_greybox(-10, -10, 10, 10, CColor::Black(224), 0)
{
	// TODO: add initialisation here
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	for each (CBoid *pBoid in m_boids)
		pBoid->Update(GetTime());
}

void CMyGame::OnDraw(CGraphics* g)
{
	if (CBoid::IsAttraction())
	{
		g->DrawHLine(CBoid::GetAttraction() + CVector(-5, 0), CBoid::GetAttraction().GetX() - 20, CColor::Red());
		g->DrawHLine(CBoid::GetAttraction() + CVector( 5, 0), CBoid::GetAttraction().GetX() + 20, CColor::Red());
		g->DrawVLine(CBoid::GetAttraction() + CVector(0, -5), CBoid::GetAttraction().GetY() - 20, CColor::Red());
		g->DrawVLine(CBoid::GetAttraction() + CVector(0,  5), CBoid::GetAttraction().GetY() + 20, CColor::Red());
	}

	for each (CSprite *pSprite in m_obstacles)
		pSprite->Draw(g);

	for each (CBoid *pBoid in m_boids)
		pBoid->Draw(g);
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	StartGame();	// this allows to start the game immediately
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
	CBoid::SetAttraction();

	for each (CBoid *pBoid in m_boids)
		delete pBoid;
	m_boids.clear();

	for (int i = 0; i < BOIDNUM; i++)
	{
//		CBoid *pBoid = new CBoid(rand() % GetWidth(), rand() % GetHeight(), GetTime(), m_boids, m_obstacles);
		CBoid *pBoid = new CBoid(50, 368, GetTime(), m_boids, m_obstacles);
		pBoid->SetDirection(rand() % 360);
		pBoid->SetSpeed(100);
		m_boids.push_back(pBoid);
	}

	for each (CSprite *pSprite in m_obstacles)
		delete pSprite;
	m_obstacles.clear();

	CSprite *pSprite;

//	pSprite = new CSpriteOval(512, 384, 50, 50, CColor::Black(), 0);
//	m_obstacles.push_back(pSprite);
	
	pSprite = new CSpriteRect(512, 125, 20, 250, CColor::Black(), 0);
	m_obstacles.push_back(pSprite);
	pSprite = new CSpriteRect(512, 643, 20, 250, CColor::Black(), 0);
	m_obstacles.push_back(pSprite);	

	pSprite = new CSpriteRect(256, 384, 100, 100, CColor::Black(), 0);
	m_obstacles.push_back(pSprite);	
	pSprite = new CSpriteRect(768, 384, 100, 100, CColor::Black(), 0);
	m_obstacles.push_back(pSprite);	

	pSprite = new CSpriteRect(256, 120, 40, 40, CColor::Black(), 0);
	m_obstacles.push_back(pSprite);	
	pSprite = new CSpriteRect(768, 120, 40, 40, CColor::Black(), 0);
	m_obstacles.push_back(pSprite);	
	pSprite = new CSpriteRect(256, 658, 40, 40, CColor::Black(), 0);
	m_obstacles.push_back(pSprite);	
	pSprite = new CSpriteRect(768, 658, 40, 40, CColor::Black(), 0);
	m_obstacles.push_back(pSprite);	
}

// called when Game is Over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_SPACE)
		PauseGame();
	if (sym == SDLK_F2)
		NewGame();
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
}


/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
	if (bLeft)
		CBoid::SetAttraction(CVector(x, y));
	else
		CBoid::SetAttraction();
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
	CBoid::SetAttraction(CVector(x, y));
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
	CBoid::SetAttraction();
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
