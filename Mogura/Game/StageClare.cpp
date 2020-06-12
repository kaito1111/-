#include "stdafx.h"
#include "StageClare.h"
#include "GameManager.h"
#include "StartTitle.h"
#include "Game.h"
#include "otalScore.h"

StageClare::StageClare()
{
}


StageClare::~StageClare()
{
	DeleteGO(m_FontRender);
	DeleteGO(m_spriteRender);
	DeleteGO(m_Efect);
	DeleteGO(m_SpriteRender);
}

bool StageClare::Start()
{
	m_spriteRender = NewGO<prefab::CSpriteRender>(3);
	m_spriteRender->Init(L"sprite/Game_Clear.dds", 480.0f, 250.0f, true);
	m_spriteRender->SetPosition(m_SpritePosition);
	m_FontRender = NewGO<prefab::CFontRender>(2);
	m_FontRender->SetText(L"‚â‚é‚â‚ñB");
	m_FontRender->SetScale(3.0f);
	m_FontRender->SetPosition(m_FontPosition);
	CVector4 m_Color = CVector4::Black;
	m_FontRender->SetColor(m_Color);
	m_SkinModelRender = NewGO<prefab::CSkinModelRender>(2);
	m_SkinModelRender->Init(L"modelData/moguri.cmo");
	m_SkinModelRender->SetPosition(m_Position);
	m_SkinModelRender->SetScale(m_scale);
	CQuaternion m_Rot = CQuaternion::Identity;
	m_Rot.SetRotationDeg(CVector3::AxisY, 180.0f);
	m_SkinModelRender->SetRotation(m_Rot);
	m_Efect = NewGO<prefab::CEffect>(2);
	m_Efect->Play(L"effect/kemuri.efk");
	m_Rot.SetRotationDeg(CVector3::AxisX, -90.0f);
	m_Efect->SetRotation(m_Rot);
	m_Efect->SetScale(m_EffectScale);
	m_Efect->SetPosition(m_Position);
	m_SS = NewGO<prefab::CSoundSource>(0);
	m_SS->Init(L"sound/backboostar.wav");
	m_Sound = NewGO<prefab::CSoundSource>(0);
	m_Sound->Init(L"sound/GameClareSE.wav");
	m_Sound->Play(false);
	MainCamera().SetTarget(CVector3::Zero);
	MainCamera().SetPosition({ 0.0f,0.0f,-200.0f });
	MainCamera().Update();
	m_SpriteRender = NewGO<prefab::CSpriteRender>(0);
	m_SpriteRender->Init(L"sprite/White.dds", 480.0f, 250.0f);
	m_SpriteRender->SetMulColor(m_SpriteColor);
	return true;
}

void StageClare::Update()
{
	m_SpritePosition.y -= 30.0f;
	if (m_SpritePosition.y <= 0.0f)
	{
		m_SpritePosition.y = 0.0f;
	}
	m_FontPosition.y -= 20.0f;
	if (m_FontPosition.y <= 100.0f)
	{
		m_FontPosition.y = 100.0f;
	}
	m_Position.x -= 10.0f;
	if (m_Position.x <= 100.0f) 
	{
		m_Position.x = 100.0f;
	}
	if (m_Position.x == 100.0f)
	{
		m_Timer -= GameTime().GetFrameDeltaTime();
		if (m_Timer <= 0.0f)
		{
			m_Position.y += 20.0f;
			m_SkinModelRender->SetPosition(m_Position);
			m_Efect->SetPosition(m_Position);
			if (!PS) 
			{
				m_SS->Play(false);
				PS = true;
			}
		}
	}
	if (m_Timer <= -1.0f)
	{
		if (Pad(0).IsTrigger(enButtonA))
		{
			Change = true;
		}
	}
	if (Change) {
		m_SpriteColor.w += 0.1f;
	}
	if (m_SpriteColor.w >= 0.8f) 
	{
		NewGO<TotalScore>(0, "TotalScore");
		QueryGOs<TotalScore>("TotalScore", [&](TotalScore* m_Total)->bool
			{
				m_Total->m_Position.x = 2050.0f;
				return true;
			});
		QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
			{
				QueryGOs<Game>("Game", [&](Game* m_Game)->bool
					{
						if (m_Manager->Count > m_Game->HighScore)
						{
							m_Game->HighScore = m_Manager->Count;
						}
						return true;
					});
				return true;
			});
		NewGO<StartTitle>(0, "StartTitle");

		DeleteGO(this);
	}
	/*m_camerapojition.x = Pad(0).GetLStickXF() * 20.0f;
	m_camerapojition.y = Pad(0).GetLStickYF() * 20.0f;
	MainCamera().SetPosition(m_camerapojition);
	MainCamera().Update();*/
	m_SpriteRender->SetMulColor(m_SpriteColor);
	m_FontRender->SetPosition(m_FontPosition);
	m_spriteRender->SetPosition(m_SpritePosition);
	m_SkinModelRender->SetPosition(m_Position);
}
