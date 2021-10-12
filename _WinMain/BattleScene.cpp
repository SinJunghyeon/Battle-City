#include "BattleScene.h"
#include "Image.h"
#include "Tank.h"
#include "EnemyManager.h"

HRESULT BattleScene::Init()
{
	Sleep(3000);

	// 적 매니저
	enemyMgr = new EnemyManager;
	enemyMgr->Init();

	// 배경 이미지
	ImageManager::GetSingleton()->AddImage("Image/BattleCity/mapImage.bmp", WIN_SIZE_X, WIN_SIZE_Y);

	backGround = ImageManager::GetSingleton()->FindImage("Image/BattleCity/mapImage.bmp");
	if (backGround == nullptr)
	{
		cout << "Image/bin.bmp 파일 로드에 실패했다." << endl;

		return E_FAIL;
	}

	return S_OK;
}

void BattleScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_ESCAPE))
	{
		SceneManager::GetSingleton()->ChangeScene("타이틀씬");
		return;
	}

	if (rocket)
		rocket->Update();

	if (enemyMgr)
		enemyMgr->Update();
}

void BattleScene::Render(HDC hdc)
{
	if (backGround)
		backGround->Render(hdc);

	if (rocket)
		rocket->Render(hdc);

	if (enemyMgr)
		enemyMgr->Render(hdc);
}

void BattleScene::Release()
{
	SAFE_RELEASE(enemyMgr);
}
