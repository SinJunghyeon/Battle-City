#include "GameOverScene.h"
#include "Image.h"

HRESULT GameOverScene::Init()
{
    ImageManager::GetSingleton()->AddImage("Image/BattleCity/Text/Gameover.bmp", WIN_SIZE_X, WIN_SIZE_Y);
    gameOver = ImageManager::GetSingleton()->FindImage("Image/BattleCity/Text/Gameover.bmp");

    return S_OK;
}

void GameOverScene::Update()
{
    if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_RETURN))
    {
        SceneManager::GetSingleton()->ChangeScene("titleS");
    }
}

void GameOverScene::Render(HDC hdc)
{
    gameOver->Render(hdc, WIN_SIZE_X / 2, WIN_SIZE_Y / 2);
}

void GameOverScene::Release()
{
}
