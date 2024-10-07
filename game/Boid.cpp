#include "stdafx.h"
#include "Boid.h"

CVector CBoid::c_attraction;
bool CBoid::c_bAttraction = false;

CBoid::CBoid(Sint16 x, Sint16 y, Uint32 time, CSpriteList &boids, CSpriteList &pObstacles)
	: CSprite(x, y, "ant.gif", time)
{
	m_pBoids = &boids;
	m_pObstacles = &pObstacles;
}

CBoid::~CBoid()
{
}

CFVector CBoid::separate(double radius)
{
	CFVector vec;
	int count = 0;
	for each (CBoid *pBoid in *m_pBoids)
		if (pBoid != this && Distance(pBoid) <= radius && Distance(pBoid) > 0)
		{
			vec += CFVector(GetPosition() - pBoid->GetPosition()).SetLength(100);
			count++;
		}

	if (count == 0)
		return CFVector(0, 0);
	else
		return vec / count;
}

CFVector CBoid::align(double radius)
{
	CFVector vec;
	int count = 0;
	for each (CBoid *pBoid in *m_pBoids)
		if (pBoid != this && Distance(pBoid) <= radius && Distance(pBoid) > 0)
		{
			vec += CFVector(pBoid->GetXVelocity(), pBoid->GetYVelocity());
			count++;
		}

	if (count == 0)
		return CFVector(0, 0);
	else
		return vec / count;
}

CFVector CBoid::cohesion(double radius)
{
	CFVector vec;
	int count = 0;
	for each (CBoid *pBoid in *m_pBoids)
		if (pBoid != this && Distance(pBoid) <= radius && Distance(pBoid) > 0)
		{
			vec += pBoid->GetPosition();
			count++;
		}

	if (count == 0)
		return CFVector(0, 0);
	else
		return vec / count - GetPosition();
}

CFVector CBoid::border(double radius)
{
	CFVector vec;
	if (GetX() <= 2 * radius)
		vec.m_x = (2 * radius - GetX()) * abs(GetXVelocity()) / radius;
	if (GetY() <= 2 * radius)
		vec.m_y = (2 * radius - GetY()) * abs(GetYVelocity()) / radius;
	if (GetX() >= 1024 - 2 * radius)
		vec.m_x = (1024 - 2 * radius - GetX()) * abs(GetXVelocity()) / radius;
	if (GetY() >= 768 - 2 * radius)
		vec.m_y = (768 - 2 * radius - GetY()) * abs(GetYVelocity()) / radius;

	return vec.Limit(100);
}

CFVector CBoid::obstacle(double radius)
{
	CFVector vec;
	int count = 0;


	CRectangle rect;
	for each (CSprite *pSprite in *m_pObstacles)
	{
		pSprite->GetBoundingRect(rect);
		rect.Grow(2 * (Uint16)radius);

		if (rect.Contains(GetCenter()))
		{
			if (GetX() < pSprite->GetLeft())
				vec.m_x = (pSprite->GetLeft() - 2 * radius - GetX()) * abs(GetXVelocity()) / radius;
			if (GetX() > pSprite->GetRight())
				vec.m_x = (pSprite->GetRight() + 2 * radius - GetX()) * abs(GetXVelocity()) / radius;
			if (GetY() > pSprite->GetTop())
				vec.m_y = (pSprite->GetTop() + 2 * radius - GetY()) * abs(GetYVelocity()) / radius;
			if (GetY() < pSprite->GetBottom())
				vec.m_y = (pSprite->GetBottom() - 2 * radius - GetY()) * abs(GetYVelocity()) / radius;

			count++;
		}
	}

	if (count == 0)
		return CFVector(0, 0);
	else
		return (vec / count).Limit(100);
}

CFVector CBoid::attract(CFVector p)
{
	return (p - GetPosition()).SetLength(100);
}

void CBoid::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	double r = 25;

	CFVector sep = separate(r);
	CFVector ali = align(r * 2);
	CFVector coh = cohesion(r * 2);
	sep *= 1.5;
	ali *= 0.0;
	coh *= 0.0;
	CFVector vec = sep + ali + coh;

	CFVector bor = border(r);
	CFVector obs = obstacle(r);
	bor *= 2.0;
	obs *= 2.0;
	vec += bor + obs;

	CFVector att;
	if (IsAttraction()) att = attract(GetAttraction());
	att *= 0.2;
	vec += att;


	SetVelocity(GetXVelocity() + vec.GetX(), GetYVelocity() + vec.GetY());

	if (GetSpeed() > 100) 
		SetSpeed(100);

	SetRotation(GetDirection() - 90.0);
	CSprite::OnUpdate(time, deltaTime);
}
