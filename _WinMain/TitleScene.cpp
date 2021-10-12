#include "TitleScene.h"
#include "Config.h"
#include "Image.h"

HRESULT TitleScene::Init()
{
	//¹®ÀÚ¿­·Î Image/BattleCity/Title.bmp

	 

	ImageManager::GetSingleton()->AddImage("Image/BattleCity/Title.bmp", WIN_SIZE_X, WIN_SIZE_Y);
	backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Title.bmp");

	return S_OK;
}

void TitleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_SPACE))
	{
		SceneManager::GetSingleton()->ChangeScene("ÀüÅõ¾À", "·Îµù¾À");
		return;
	}
}

void TitleScene::Render(HDC hdc)
{
	if (backGround)
		backGround->Render(hdc);

}

void TitleScene::Release()
{
	SAFE_DELETE(arg);
}
