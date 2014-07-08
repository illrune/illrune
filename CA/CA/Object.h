#pragma once

#include <Windows.h>
#include "GameDev.h"

enum Object_type_id
{
   OBJ_NONE,
   OBJ_CHARACTER,
   OBJ_BLOCK,
   OBJ_BOX,
   OBJ_WATERBOMB,
   OBJ_WATER,
   OBJ_ITEM_SPEED,
   OBJ_ITEM_POWER,
   OBJ_ITEM_COUNT,
};

class ObjectManager;

class Object
{
   friend class ObjectManager;
protected :
   Object(const int& t, const bool& b);
   virtual ~Object();

public :
   virtual void Input(DWORD) = 0;
   virtual void Update(DWORD) = 0;
   virtual void Draw(HDC) = 0;

   virtual bool IsCollide(Object* ) = 0;

   void SetPosition(const Point& );
   void SetObjectPosition(const Point& );
   Point GetPosition() const;

   int type() const;
   int WhatItem() const;

   bool IsBreakable() const;
   virtual void DoBreak() = 0;

   bool IsNeedToClean() const;
   void SetNeedToClean();

protected :
   Point& pos();

private :
   Point m_ptPos;

   bool m_bBreakable;
   int m_nType;

   bool m_bNeedToClean;
};

#include <set>

class ObjectManager : public singleton<ObjectManager>
{
   friend class singleton<ObjectManager>;
private :
   ObjectManager();
   virtual ~ObjectManager();

public :
   void Attach(HWND);

   void Input(DWORD);
   void Update(DWORD);
   void Draw(HDC);

   void push(Object*);
   void pop(Object*);

   void clear();

private :
   void _clean();

private :
   HWND hOwner;

   std::set<Object*> depot;
};

#define ObjectDepot ObjectManager::GetReference()