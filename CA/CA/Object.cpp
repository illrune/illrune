#include "Object.h"

Object::Object(const int& t, const bool& b)
   : m_nType(t), m_bBreakable(b), m_bNeedToClean(false)
{
}
Object::~Object()
{
}

void Object::SetPosition(const Point& pt)
{
   m_ptPos = pt;
}
void Object::SetObjectPosition(const Point& pt)
{
	m_ptPos.x = (pt.x/40)*40 + 20;
	m_ptPos.y = (pt.y/40)*40 + 20;
}

Point Object::GetPosition() const
{
   return m_ptPos;
}

int Object::type() const
{
   return m_nType;
}
int Object::WhatItem() const
{
	// todo?
	return 0;
}
bool Object::IsBreakable() const
{
   return m_bBreakable;
}

bool Object::IsNeedToClean() const
{
   return m_bNeedToClean;
}
void Object::SetNeedToClean()
{
   m_bNeedToClean = true;
}

Point& Object::pos()
{
   return m_ptPos;
}
