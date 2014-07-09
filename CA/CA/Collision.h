#pragma once

#include "BaseType.h"
#include "Utility.hpp"

class CollisionImpl : public singleton<CollisionImpl>
{
   friend class singleton<CollisionImpl>;
private :
   CollisionImpl();
   virtual ~CollisionImpl();

public :
   // character to water;
   bool operator ()(const Point& charpos, const LONG& size, const Point& objpos);
   //// rectangle to circle
   //bool operator ()(const Rect& rc, const Point& pt, const LONG& r);
   //// rectangle to rectangle
   //bool operator ()(const Rect& rc1, const Rect& rc2);
};

#define Collision CollisionImpl::GetReference()