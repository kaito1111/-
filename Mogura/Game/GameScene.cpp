#include "stdafx.h"
#include "GameScene.h"
#include "Player.h"
#include "MoguraGenerator.h"
#include "ground.h"
#include "GameManager.h"
#include "PracticalMode.h"
#include "tkEngine/light/tkPointLight.h"
#include "tkEngine/light/tkDirectionLight.h"

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
	DeleteGO(m_SR);
}

bool GameScene::Start()
{
	MainCamera().SetTarget({ 50.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 50.0f, 500.0f, -300.0f });
	MainCamera().Update();
	NewGO<Player>(0, "player");
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (!m_Manager->practice)
			{
				NewGO<MoguraGenerator>(0, "mogurageneretor");
			}
			return true;
		});
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			m_Manager->GameStart = true;
			return true;
		});
	NewGO<ground>(0, "ground");
	m_SR = NewGO<prefab::CSpriteRender>(5);
	m_SR->Init(L"sprite/White.dds", 1280.0f, 720.0f);
	m_SR->SetMulColor(m_Color);
	shadow::OminiDirectionShadowMap().SetLightPosition(CVector3::Zero);
	shadow::OminiDirectionShadowMap().SetDistanceAffectedByLight(1000);
	shadow::OminiDirectionShadowMap().Disable();
	m_Light = NewGO<prefab::CDirectionLight>(0);
	m_Light->SetDirection({ 0.0,-0.707f,-0.7070f });
	m_Light->SetColor({ 2.0f,2.0f,2.0f,1.0f });

	return true;
}

void GameScene::Update()
{
	if (m_Color.w >= 0.0f && !StartGame) {
		m_Color.w += 0.05f;
	}
	else {
		m_Color.w = -0.05f;
	}
	if (m_Color.w >= 1.0f) {
		StartGame = true;
	}
	if (m_Color.w < 0.0f) {
		DeleteGO(this);
	}
	m_SR->SetMulColor(m_Color);
}
