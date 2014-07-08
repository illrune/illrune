#include "Animation.h"

Animation::Animation()
: index(0)
, update_dt(0), update_delay(100)
, bLoop(false), bDoNotDraw(false)
{
}
Animation::~Animation()
{
	ShotType::iterator it;
	for (it = shotlist.begin(); it != shotlist.end(); )
	{
		delete *it;
		it = shotlist.erase(it);
	}
}

void Animation::AddShot(Image* shot)
{
	shotlist.push_back(shot);
}

void Animation::Update(DWORD tick)
{
	if (bDoNotDraw) return;

	if (update_dt > update_delay)
	{
		int count = update_dt / update_delay;

		for (int i = 0; i < count; i++)
		{
			index++;
			if (index >= shotlist.size())
			{
				if (bLoop)
					index = 0;
				else
				{
					bDoNotDraw = true;
					break;
				}
			}
		}

		update_dt %= update_delay;
	}
	update_dt += tick;
}
void Animation::Draw(HDC hdc)
{
	if (bDoNotDraw) return;

	ShotType::iterator it = shotlist.begin();
	std::advance(it, index);

	(*it)->SetRect(rcDest);
	(*it)->Draw(hdc);
}

void Animation::SetDelay(DWORD delay)
{
	update_delay = delay;
}
void Animation::SetRect(const Rect& rc)
{
	rcDest = rc;
}
void Animation::SetLoop(bool _bLoop/*=true*/)
{
	bLoop = _bLoop;
}

