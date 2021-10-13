#include "Item.h"

#include "Image.h"

/*
	�� : ���� ��ũ�� ��ȭ�ȴ�. ��� �� �ӻ���(2����) �� ���� ��ũ(2���� + �ı��� ���� + ȸ�� ��� �ı�). 
		 ���� ��ũ ���°� ���� ����Ͽ� �ƹ� �������� ���� �������⿡ ���� ��ٰ� �Ǽ��� ��ɺθ� �ı��Ͽ� �����ϴ� ���̵��� �� �־���. 
		 �翬�� �Ҹ�������, ���� ��ũ�� ��ȭ�� ���¿��� �� ��ũ�� ������ �޾� �ı��� ��� �ٽ� 1�ܰ� ��ũ�� �ʱ�ȭ�ȴ�.
	����ź : ȭ����� �� ��ũ�� �����Ų��.[6]
	��ũ : 1UP.
	�� : �����ð� ���� ��ɺ� �ֺ��� ���� ȸ�� ������� ���ϸ�, �ð���� �Ŀ� ��ɺ� �ֺ��� ���� ȸ���ȴ�. 
		 ����� ��ȭ�� ȸ�� ����� ���� ������ ��� �ı� ����(��). 
		 ��, �� ����Ʈ������ ���� ���� ���� �ʿ��� ��ɺ� ������ ȸ�� ������� ���� ��� �� �������� �԰� ���� �ð��� ����Ǹ� �Ϲ� ���� ������� �ǵ��ư��� ������, 
		 ���� ���� ����� ����� �Ǿ� �� ��쿣 �Ϻη� �� �������� �� �Դ� ��쵵 ����.
	�ð� : ���� �ð� ���� �� ��ũ�� �������� �����.
	��� : ���� �ð� ���� ���� ��ũ�� �ֺ��� �踮� ���� ���� ���°� �ȴ�.
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

	//������ ���� ����
	srand(time(NULL));
	selectItem = rand() % 6;

	//��� �̹���
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item1.bmp", bodySize, bodySize, 1, 1, true, RGB(255, 0, 255));
	mpImgHelmet = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item1.bmp");
	if (mpImgHelmet == nullptr)
	{
		return E_FAIL;
	}
	//�ð� �̹���
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item2.bmp", bodySize, bodySize, 1, 1, true, RGB(255, 0, 255));
	mpImgWatch = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item2.bmp");
	if (mpImgWatch == nullptr)
	{
		return E_FAIL;
	}
	//�� �̹���
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item3.bmp", bodySize, bodySize, 1, 1, true, RGB(255, 0, 255));
	mpImgShovel = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item3.bmp");
	if (mpImgShovel == nullptr)
	{
		return E_FAIL;
	}
	//�� �̹���
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item4.bmp", bodySize, bodySize, 1, 1, true, RGB(255, 0, 255));
	mpImgStar = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item4.bmp");
	if (mpImgStar == nullptr)
	{
		return E_FAIL;
	}
	//����ź �̹���
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Item/Item5.bmp", bodySize, bodySize, 1, 1, true, RGB(255, 0, 255));
	mpImgGrenade = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Item/Item5.bmp");
	if (mpImgGrenade == nullptr)
	{
		return E_FAIL;
	}
	//��ũ �̹���
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
