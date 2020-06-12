#include "stdafx.h"
#include "StartTitle.h"
#include "PracticalMode.h"
#include "Level.h"
#include "GameManager.h"
#include "Descript.h"
#include "Game.h"

StartTitle::StartTitle()
{
}


StartTitle::~StartTitle()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_SR);
	DeleteGO(m_HighFont);
	DeleteGO(m_soundsource);
}

bool StartTitle::Start()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 0.0f, 500.0f, -200.0f });
	MainCamera().Update();
	m_spriteRender = NewGO<prefab::CSpriteRender>(3);
	m_spriteRender->Init(L"sprite/start title.dds", 1280.0f, 720.0f);
	m_soundsource->InitStreaming(L"sound/candybouquet.wav");
	m_soundsource->SetVolume(0.3f);
	m_soundsource->Play(true);
	m_SR = NewGO<prefab::CSpriteRender>(4);
	m_SR->Init(L"sprite/yajirusi.dds", 256.0f, 144.0f);
	m_SR->SetPosition(m_position);

	m_HighFont = NewGO<prefab::CFontRender>(4);
	wchar_t Score[128];
	QueryGOs<Game>("Game", [&](Game* m_Game)->bool {
		swprintf_s(Score, L"ハイスコア%d", m_Game->HighScore);
		return true;
		});
	m_HighFont->SetText(Score);
	m_HighFont->SetColor(m_ScoreColor);
	m_HighFont->SetPosition(m_ScorePosition);
	m_HighFont->SetScale(ScoreScale);
	return true;
}

void StartTitle::Update()
{
	timer += GameTime().GetFrameDeltaTime();
	m_Position.x += 50.0f;
	m_position.x += 50.0f;
	m_ScorePosition.x += 50.0f;
	if (m_Position.x > 0.0f)
	{
		m_Position.x = 0.0f;
	}
	if (m_position.x > -550.0f)
	{
		m_position.x = -550.0f;
	}
	if (m_ScorePosition.x > -500.0f) {
		m_ScorePosition.x = -500.0f;
	}
	if (timer >= 1.0f)
	{
		if (Pad(0).GetLStickYF() >= 0.5f)
		{
			m_position.y = -40.0f;
		}
		if (Pad(0).GetLStickYF() <= -0.5f)
		{
			m_position.y = -170.0f;
		}

		if (Pad(0).IsTrigger(enButtonA))
		{
			Disdeletego = false;
			if (m_position.y == -40.0f)
			{
				normal = true;
			}
			if (m_position.y == -170.0f)
			{
				practicu = true;
			}
			if (!Play)
			{
				prefab::CSoundSource* m_SS = NewGO<prefab::CSoundSource>(0);
				m_SS->Init(L"sound/Select.wav");
				m_SS->Play(false);
				Play = true;
			}
		}
	}
	if (normal)
	{
		if (!Newgo)
		{
			NewGO<GameManager>(0, "GameManager");
			NewGO<Level>(0, "Level");
			QueryGOs<Level>("Level", [&](Level* m_Level)->bool
				{
					m_Level->Newgo = false;
					return true;
				});
			Newgo = true;
		}
		m_ScorePosition.x -= 100.0f;
		m_Position.x -= 100.0f;
		m_position.x -= 100.0f;
		/*if (m_Position.x <= -1500.0f)
		{
			DeleteGO(this);
		}*/
	}
	if (practicu)
	{
		if (!Newgo)
		{
			NewGO<GameManager>(2, "GameManager");
			NewGO<PracticalMode>(1, "PrecticalMode");
			NewGO<Descript>(4, "Descript");
			QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
				{
					m_Manager->practice = true;
					return true;
				});
			Newgo = true;
		}
		m_ScorePosition.x -= 100.0f;
		m_Position.x -= 100.0f;
		m_position.x -= 100.0f;
		/*if (m_Position.x <= -1500.0f)
		{
			DeleteGO(this);
		}*/
	}
	/*if (Disdeletego)
	{
		QueryGOs<Descript>("Descript", [&](Descript* m_Des)->bool
			{
				m_Des->Deletego = true;
				return true;
			});
	}*/
	if (Delete)
	{
		DeleteGO(this);
	}
	m_soundsource->Play(true);
	m_HighFont->SetPosition(m_ScorePosition);
	m_spriteRender->SetPosition(m_Position);
	m_SR->SetPosition(m_position);
}
