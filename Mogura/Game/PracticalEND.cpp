#include "stdafx.h"
#include "PracticalEND.h"
#include "GameManager.h"
#include "StartTitle.h"
#include "Game.h"
#include "otalScore.h"

PracticalEND::PracticalEND()
{
}

PracticalEND::~PracticalEND()
{
	DeleteGO(m_SPR);
	DeleteGO(m_MoguraModelRender);
	DeleteGO(m_MoguraKillFont);
	DeleteGO(m_KingModelRender);
	DeleteGO(m_KingMoguraKillFont);
	DeleteGO(m_MetooruModelRender);
	DeleteGO(m_MetooruKillFont);
	DeleteGO(m_Total);
	DeleteGO(m_Next);
	DeleteGO(m_SpriteRender);
}

bool PracticalEND::Start()
{
	CQuaternion m_rot = CQuaternion::Identity;
	m_rot.SetRotationDeg(CVector3::AxisY, -120.0f);
	m_SPR = NewGO<prefab::CSpriteRender>(0);
	m_SPR->Init(L"sprite/practicalEND.dds", 460.0f, 250.0f, true);
	m_SPR->SetPosition(m_SpritePosition);

	m_MoguraModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_MoguraModelRender->Init(L"modelData/mogura.cmo");
	m_MoguraModelRender->SetPosition(m_MoguraPosition);
	m_MoguraModelRender->SetScale(m_MoguraScale);
	m_MoguraModelRender->SetRotation(m_rot);

	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			MoguraKill = m_Manager->MoguraCount;
			return true;
		});
	m_MoguraKillFont = NewGO<prefab::CFontRender>(0);
	swprintf_s(MogurakillMoji, L"X%d", MoguraKill);
	m_MoguraKillFont->SetText(MogurakillMoji);
	m_MoguraKillFont->SetPosition(m_MoguraFontPosition);
	m_MoguraKillFont->SetScale(FontScale);
	m_MoguraKillFont->SetColor(m_Color);

	m_KingModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_KingModelRender->Init(L"modelData/KingMogura.cmo");
	m_KingModelRender->SetPosition(m_KingMoguraPosition);
	m_KingModelRender->SetScale(m_MoguraScale);
	m_KingModelRender->SetRotation(m_rot);

	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			KingMoguraKill = m_Manager->KingMoguraCount;
			return true;
		});
	m_KingMoguraKillFont = NewGO<prefab::CFontRender>(0);
	swprintf_s(KingMogurakillMoji, L"X%d", KingMoguraKill);
	m_KingMoguraKillFont->SetText(KingMogurakillMoji);
	m_KingMoguraKillFont->SetPosition(m_KingFontPosition);
	m_KingMoguraKillFont->SetScale(FontScale);
	m_KingMoguraKillFont->SetColor(m_Color);

	m_MetooruModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_MetooruModelRender->Init(L"modelData/Metooru.cmo");
	m_MetooruModelRender->SetPosition(m_MetooruPosition);
	m_MetooruModelRender->SetScale(m_MoguraScale);
	m_MetooruModelRender->SetRotation(m_rot);

	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			MetooruKill = m_Manager->MetooruCount;
			return true;
		});
	m_MetooruKillFont = NewGO<prefab::CFontRender>(0);
	swprintf_s(MetoorukillMoji, L"X%d", MetooruKill);
	m_MetooruKillFont->SetText(MetoorukillMoji);
	m_MetooruKillFont->SetPosition(m_MetooruFontPosition);
	m_MetooruKillFont->SetScale(FontScale);
	m_MetooruKillFont->SetColor(m_Color);

	MainCamera().SetTarget(CVector3::Zero);
	MainCamera().SetPosition({ 0.0f,0.0f,-200.0f });
	MainCamera().Update();

	m_Total = NewGO<prefab::CFontRender>(0);
	Total = KingMoguraKill + MoguraKill + MetooruKill;
	swprintf_s(TotalMoji, L"トータル%d匹", Total);
	m_Total->SetText(TotalMoji);
	m_Total->SetPosition(m_TotalPojition);
	m_Total->SetColor(m_Color);
	m_Total->SetScale(NextScale);

	m_Next = NewGO<prefab::CFontRender>(0);
	m_Next->SetText(L"Aボタン＞＞");
	m_Next->SetColor(m_NextColor);
	m_Next->SetScale(NextScale);
	m_Next->SetPosition(m_NextPosition);

	m_SpriteRender = NewGO<prefab::CSpriteRender>(0);
	m_SpriteRender->Init(L"sprite/White.dds", 460.0f, 250.0f);
	m_SpriteRender->SetMulColor(m_SpriteColor);

	return true;
}

void PracticalEND::Update()
{
	m_SpritePosition.y -= 10.0f;
	if (m_SpritePosition.y <= 0.0f)
	{
		m_SpritePosition.y = 0.0f;
		m_NextColor.w += 0.05f;
	}
	if (m_NextColor.w >= 1.0f)
	{
		m_NextColor.w = 1.0f;
	}

	m_MoguraPosition.y -= 10.0f;
	if (m_MoguraPosition.y <= -50.0f)
	{
		m_MoguraPosition.y = -50.0f;
	}

	m_MoguraFontPosition.y -= 10.0f;
	if (m_MoguraFontPosition.y <= -100.0f)
	{
		m_MoguraFontPosition.y = -100.0f;
	}
	m_MoguraKillFont->SetPosition(m_MoguraFontPosition);

	m_KingMoguraPosition.y -= 10.0f;
	if (m_KingMoguraPosition.y <= -50.0f)
	{
		m_KingMoguraPosition.y = -50.0f;
	}

	m_KingFontPosition.y -= 10.0f;
	if (m_KingFontPosition.y <= -100.0f)
	{
		m_KingFontPosition.y = -100.0f;
	}
	m_KingMoguraKillFont->SetPosition(m_KingFontPosition);

	m_MetooruPosition.y -= 10.0f;
	if (m_MetooruPosition.y <= -50.0f)
	{
		m_MetooruPosition.y = -50.0f;
	}
	m_MetooruFontPosition.y -= 10.0f;
	if (m_MetooruFontPosition.y <= -100.0f)
	{
		m_MetooruFontPosition.y = -100.0f;
	}
	m_MetooruKillFont->SetPosition(m_MetooruFontPosition);

	m_SPR->SetPosition(m_SpritePosition);
	m_MoguraModelRender->SetPosition(m_MoguraPosition);
	m_KingModelRender->SetPosition(m_KingMoguraPosition);
	m_MetooruModelRender->SetPosition(m_MetooruPosition);

	m_TotalPojition.y -= 15.0f;
	if (m_TotalPojition.y <= -300.0f) {
		m_TotalPojition.y = -300.0f;
	}
	m_Total->SetPosition(m_TotalPojition);
	
	if (m_NextPosition.x >= 150.0f)
	{
		m_MoveSpeed.x = -1.0f;
	}
	if (m_NextPosition.x <= 110.0f)
	{
		m_MoveSpeed.x = 1.0f;
	}

	m_NextPosition.x += m_MoveSpeed.x;
	m_Next->SetPosition(m_NextPosition);
	m_Next->SetColor(m_NextColor);
	if (m_NextColor.w == 1.0f)
	{
		if (Pad(0).IsPress(enButtonA))
		{
			Change = true;
		}
	}
	if (Change) {
		m_SpriteColor.w += 0.1;
	}
	if (m_SpriteColor.w >= 0.8f)
	{
		QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
			{
				QueryGOs<Game>("Game", [&](Game* m_Game)->bool
					{
						if (m_Manager->Count > m_Game->HighScore)
						{
							m_Game->HighScore = m_Manager->Count;
						}
						m_Manager->Delete = true;
						return true;
					});
				return true;
			});
		NewGO<StartTitle>(0, "StartTitle");
		NewGO<TotalScore>(0, "TotalScore");
		QueryGOs<TotalScore>("TotalScore", [&](TotalScore* m_Total)->bool
			{
				m_Total->m_Position.x = 2050.0f;
				return true;
			});
		DeleteGO(this);
	}
}