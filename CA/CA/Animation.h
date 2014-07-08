#pragma once

#include <list>
#include "BaseType.h"
#include "Image.h"

class Animation
{
	typedef std::list<Image*> ShotType;
public :
	Animation();
	~Animation();

	void AddShot(Image* shot);

	void Update(DWORD tick);
	void Draw(HDC hdc);

	void SetDelay(DWORD delay);
	void SetRect(const Rect& rc);
	void SetLoop(bool _bLoop = true);

private :
	ShotType shotlist;

	unsigned int index;

	DWORD update_dt;
	DWORD update_delay;

	Rect rcDest;

	bool bLoop;

	bool bDoNotDraw;
};
