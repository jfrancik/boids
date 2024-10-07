#pragma once

#include "FVector.h"

class CBoid : public CSprite
{
	CSpriteList *m_pBoids;
	CSpriteList *m_pObstacles;
	
	static CVector c_attraction;
	static bool c_bAttraction;

public:
	CBoid(Sint16 x, Sint16 y, Uint32 time, CSpriteList &boids, CSpriteList &pObstacles);
	~CBoid(void);

	static void SetAttraction(CVector attr)		{ c_bAttraction = true; c_attraction = attr; }
	static void SetAttraction()					{ c_bAttraction = false; }
	static bool IsAttraction()					{ return c_bAttraction; }
	static CVector GetAttraction()				{ return c_attraction; }
	

	double Distance(CBoid *pBoid)		{ return GetPosition().Distance(pBoid->GetPosition()); }

	CFVector separate(double radius);
	CFVector align(double radius);
	CFVector cohesion(double radius);

	CFVector border(double radius);
	CFVector obstacle(double radius);

	CFVector attract(CFVector p);

	virtual void OnUpdate(Uint32 time, Uint32 deltaTime);
};
