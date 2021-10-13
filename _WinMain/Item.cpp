#include "Item.h"

#include "Image.h"

/*
	별 : 마이 탱크가 강화된다. 노멀 → 속사포(2연사) → 슈퍼 탱크(2연사 + 파괴력 증가 + 회색 블록 파괴). 
		 슈퍼 탱크 상태가 되자 흥분하여 아무 생각없이 포를 여기저기에 마구 쏘다가 실수로 사령부를 파괴하여 자폭하는 아이들이 꼭 있었다. 
		 당연한 소리겠지만, 마이 탱크가 강화된 상태에서 적 탱크의 공격을 받아 파괴될 경우 다시 1단계 탱크로 초기화된다.
	수류탄 : 화면상의 적 탱크를 전멸시킨다.[6]
	탱크 : 1UP.
	삽 : 일정시간 동안 사령부 주변의 벽이 회색 블록으로 변하며, 시간경과 후엔 사령부 주변의 벽도 회복된다. 
		 참고로 변화한 회색 블록은 슈탱 상태일 경우 파괴 가능(…). 
		 단, 맵 컨스트럭션을 통해 직접 만든 맵에서 사령부 주위를 회색 블록으로 만든 경우 삽 아이템을 먹고 일정 시간이 경과되면 일반 갈색 블록으로 되돌아가기 때문에, 
		 맵을 만든 노력이 헛수고가 되어 이 경우엔 일부러 이 아이템을 안 먹는 경우도 많다.
	시계 : 일정 시간 동안 적 탱크의 움직임이 멈춘다.
	헬멧 : 일정 시간 동안 마이 탱크의 주변에 배리어가 쳐진 무적 상태가 된다.
*/

HRESULT Item::Init()
{
	pos.x = WIN_SIZE_X / 2;
	pos.y = WIN_SIZE_Y / 2;

	bodySize = 32;

	shape.left = pos.x - (bodySize / 2);
	shape.top = pos.y - (bodySize / 2);
	shape.right = pos.x + (bodySize / 2);
	shape.bottom = pos.y + (bodySize / 2);

	//아이템 랜덤 설정
	srand(time(NULL));
	selectItem = rand() % 6;

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
	return S_OK;
}

void Item::Update()
{
}

void Item::Render(HDC hdc)
{
	Rectangle(hdc, shape.left, shape.top, shape.right, shape.bottom);

	switch (selectItem)
	{
	case 0:
		mpImgHelmet->Render(hdc, pos.x, pos.y);
		break;
	case 1:
		mpImgWatch->Render(hdc, pos.x, pos.y);
		break;
	case 2:
		mpImgShovel->Render(hdc, pos.x, pos.y);
		break;
	case 3:
		mpImgStar->Render(hdc, pos.x, pos.y);
		break;
	case 4:
		mpImgGrenade->Render(hdc, pos.x, pos.y);
		break;
	case 5:
		mpImgTank->Render(hdc, pos.x, pos.y);
		break;
	default:
		selectItem = rand() % 6;
	}
}

void Item::Release()
{
}
