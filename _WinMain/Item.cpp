#include "Item.h"

#include "Image.h"

HRESULT Item::Init()
{
	pos.x = 280.0f;
	pos.y = 386.0f;

	bodySize = 32;

	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = pos.x + (bodySize / 2);
	shape.bottom = pos.y + (bodySize / 2);

	//아이템 랜덤 설정 0 : 헬멧, 1 : 시계, 2 : 삽, 3 : 별, 4 : 수류탄, 5 : 탱크
	srand(time(NULL));
	currItem = rand() % 6;

	bExistItem = false;

	//헬멧 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item1.bmp", bodySize, bodySize, 1, 1, true, RGB(255, 0, 255));
	mpImgHelmet = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item1.bmp");
	if (mpImgHelmet == nullptr)
	{
		return E_FAIL;
	}
	//시계 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item2.bmp", bodySize, bodySize, 1, 1, true, RGB(255, 0, 255));
	mpImgWatch = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item2.bmp");
	if (mpImgWatch == nullptr)
	{
		return E_FAIL;
	}
	//삽 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item3.bmp", bodySize, bodySize, 1, 1, true, RGB(255, 0, 255));
	mpImgShovel = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item3.bmp");
	if (mpImgShovel == nullptr)
	{
		return E_FAIL;
	}
	//별 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item4.bmp", bodySize, bodySize, 1, 1, true, RGB(255, 0, 255));
	mpImgStar = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item4.bmp");
	if (mpImgStar == nullptr)
	{
		return E_FAIL;
	}
	//수류탄 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item5.bmp", bodySize, bodySize, 1, 1, true, RGB(255, 0, 255));
	mpImgGrenade = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item5.bmp");
	if (mpImgGrenade == nullptr)
	{
		return E_FAIL;
	}
	//탱크 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item6.bmp", bodySize, bodySize, 1, 1, true, RGB(255, 0, 255));
	mpImgTank = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item6.bmp");
	if (mpImgTank == nullptr)
	{
		return E_FAIL;
	}

	tempElapsedCount = 0;

	return S_OK;
}

void Item::Update()
{
	if (!bExistItem)
	{
		currItem = rand() % 6;
	}
}

void Item::Render(HDC hdc)
{
	if (bExistItem)
	{
		switch (currItem)
		{
		case 0:
			mpImgHelmet->Render(hdc, pos.x, pos.y);
			functionItem = ecFunctionItem::HELMET;
			break;
		case 1:
			mpImgWatch->Render(hdc, pos.x, pos.y);
			functionItem = ecFunctionItem::WATCH;
			break;
		case 2:
			mpImgShovel->Render(hdc, pos.x, pos.y);
			functionItem = ecFunctionItem::SHOVEL;
			break;
		case 3:
			mpImgStar->Render(hdc, pos.x, pos.y);
			functionItem = ecFunctionItem::STAR;
			break;
		case 4:
			mpImgGrenade->Render(hdc, pos.x, pos.y);
			functionItem = ecFunctionItem::GRENADE;
			break;
		case 5:
			mpImgTank->Render(hdc, pos.x, pos.y);
			functionItem = ecFunctionItem::TANK;
			break;
		default:
			currItem = rand() % 6;
		}
	}
}

void Item::Release()
{
}
