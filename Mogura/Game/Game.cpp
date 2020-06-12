#include "stdafx.h"
#include "Game.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "StartTitle.h"
#include "GameManager.h"
#include "otalScore.h"
//#include "Player.h"
//#include "MoguraGenerator.h"
//#include "ground.h"

CVector3 cameraPos = { 0.0f, 70.0f, 200.0f };
CVector3 cameraTarget;
Game::Game()
{
}


Game::~Game()
{
}
bool Game::Start()
{
	m_directionlight = NewGO<prefab::CDirectionLight>(0);
	m_directionlight->SetColor({ 5.0f,5.0f,5.0f,1.0f });
	m_directionlight->SetDirection({ 0.0f,-1.0f,0.0f });
	Engine().GetGraphicsEngine().GetLightManager().AddLight(m_directionlight);
	Engine().GetGraphicsEngine().GetTonemap().SetEnable(false);
	//ÉJÉÅÉâÇê›íËÅB
	/*MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 0.0f, 500.0f, -200.0f });
	MainCamera().Update();
	NewGO<Player>(0,"player");
	NewGO<MoguraGenerator>(0);
	NewGO<ground>(0);*/
	NewGO<TotalScore>(1, "TotalScore");
	NewGO<StartTitle>(1,"StartTitle");
	/*m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");*/
	
	return true;
}

void Game::Update()
{
	/*float speed = 1.0f;
	if (Pad(0).IsPress(enButtonB)) {
		speed *= 10.0f;
	}
	if (Pad(0).IsPress(enButtonUp)) {
		cameraPos.z -= speed;
	}
	if (Pad(0).IsPress(enButtonDown)) {
		cameraPos.z += speed;
	}

	MainCamera().SetPosition(cameraPos);*/
	//MainCamera().Update();
}
