#include "Box.h"

Box::Box()
: Object(OBJ_BOX, true)
{
}
Box::~Box()
{
}
void Box::Input(DWORD)
{
}
void Box::Update(DWORD)
{
}
void Box::Draw(HDC hdc)
{
	HBRUSH hBrush = ::CreateSolidBrush(RGB(220,180,80));
	HBRUSH hOldBrush = ::Select(hdc,hBrush);

	::Rectangle(hdc, pos().x - 20, pos().y - 20, pos().x + 20, pos().y + 20);

	::Select(hdc,hOldBrush);
	::DeleteObject(hBrush);
}

bool Box::IsCollide(Object* obj)
{
	// TODO
	if (obj->type() == OBJ_WATER)
	{
		Point pt = obj->GetPosition();

		return Collision(pos(), 20, pt);
	}
	return false;
}

void Box::DoBreak()
{
	if (!IsNeedToClean())
	{
		int BoxItem = rand()%5;
		// ���ڰ� �μ��� �� 5���� 1 Ȯ���� �������� ����

		// ���� ������ ����
		if (BoxItem == 0)
		{
			Count* pCount= new Count;

			pCount->SetObjectPosition(pos());

			ObjectDepot.push(pCount);
		}
		// �Ŀ� ������ ����
		else if (BoxItem == 1)
		{
			Power* pPower= new Power;

			pPower->SetObjectPosition(pos());

			ObjectDepot.push(pPower);
		}
		// ���ǵ� ������ ����
		else if (BoxItem == 2)
		{
			Speed* pSpeed= new Speed;

			pSpeed->SetObjectPosition(pos());

			ObjectDepot.push(pSpeed);
		}

		// �� �ܿ��� �� ����

		SetNeedToClean();
	}
}