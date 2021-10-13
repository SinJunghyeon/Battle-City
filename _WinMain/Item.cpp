#include "Item.h"

#include "Image.h"
HRESULT Item::Init()
{
	pos.x = WIN_SIZE_X / 2;
	pos.y = WIN_SIZE_Y / 2;

	bodySize = 16;

	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = pos.x + (bodySize / 2);
	shape.bottom = pos.y + (bodySize / 2);

	//헬멧 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item1.bmp", 16, 16, 1, 1, true, RGB(255, 0, 255));
	mpImgHelmet = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item1.bmp");
	if (mpImgHelmet == nullptr)
	{
		return E_FAIL;
	}
	//시계 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item2.bmp", 16, 16, 1, 1, true, RGB(255, 0, 255));
	mpImgWatch = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item2.bmp");
	if (mpImgWatch == nullptr)
	{
		return E_FAIL;
	}
	//삽 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item3.bmp", 16, 16, 1, 1, true, RGB(255, 0, 255));
	mpImgShovel = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item3.bmp");
	if (mpImgShovel == nullptr)
	{
		return E_FAIL;
	}
	//별 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item4.bmp", 16, 16, 1, 1, true, RGB(255, 0, 255));
	mpImgStar = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item4.bmp");
	if (mpImgStar == nullptr)
	{
		return E_FAIL;
	}
	//수류탄 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item5.bmp", 16, 16, 1, 1, true, RGB(255, 0, 255));
	mpImgGrenade = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item5.bmp");
	if (mpImgGrenade == nullptr)
	{
		return E_FAIL;
	}
	//탱크 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item6.bmp", 16, 16, 1, 1, true, RGB(255, 0, 255));
	mpImgTank = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item6.bmp");
	if (mpImgTank == nullptr)
	{
		return E_FAIL;
	}
	return S_OK;
}

void Item::Update()
{
}

void Item::Render(HDC hdc)
{
	mpImgHelmet->Render(hdc, pos.x - 60, pos.y);
	mpImgWatch->Render(hdc, pos.x - 40, pos.y);
	mpImgShovel->Render(hdc, pos.x - 20, pos.y);
	mpImgStar->Render(hdc, pos.x + 20, pos.y);
	mpImgGrenade->Render(hdc, pos.x + 40, pos.y);
	mpImgTank->Render(hdc, pos.x + 60, pos.y);
}

void Item::Release()
{
}
