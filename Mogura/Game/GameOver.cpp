#include "stdafx.h"
#include "GameOver.h"
#include "StartTitle.h"
#include "GameManager.h"
#include "Game.h"
#include "otalScore.h"

GameOver::GameOver()
{
}


GameOver::~GameOver()
{
	DeleteGO(m_spriteRender);
	DeleteGO(m_skinModelRender);
	DeleteGO(m_CommentFontRender);
	DeleteGO(m_skinmodel);
	DeleteGO(m_SpriteRender);
}

bool GameOver::Start()
{
	m_rot.SetRotationDeg(CVector3::AxisY, 180.0f);
	CVector4 m_color = CVector4::Black;
	m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"../Resource/sprite/Game_Over.dds", 480.0f, 250.0f, true);
	m_spriteRender->SetPosition(m_SpritePosition);
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(2);
	m_skinModelRender->Init(L"modelData/mogura.cmo");
	m_skinModelRender->SetPosition(m_Position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetRotation(m_rot);
	m_skinmodel = NewGO<prefab::CSkinModelRender>(2);
	m_skinmodel->Init(L"modelData/hammer.cmo");
	m_skinmodel->SetScale(m_scale);
	m_skinmodel->SetPosition(m_Position);
	m_CommentFontRender = NewGO<prefab::CFontRender>(1);
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->Count < 20)
			{
				CVector3 m_Hammar = { 1000.0f,0.0f,0.0f };
				m_skinmodel->SetPosition(m_Hammar);
			}
			if (m_Manager->Count >= 20)
			{
				CQuaternion m_rot = CQuaternion::Identity;
				m_rot.SetRotationDeg(CVector3::AxisZ, 15.0f);
				m_skinmodel->SetPosition(m_HPosition);
				m_skinmodel->SetRotation(m_rot);
			}
			if (m_Manager->Count < 10)
			{
				m_CommentFontRender->SetText(L"負けは次に繋がるチャンス。\nほな(帰らせて）頂きます。");
			}
			if (m_Manager->Count >= 10 && m_Manager->Count < 30)
			{
				m_CommentFontRender->SetText(L"たかがもぐら叩き\nそう思ってないですか？\nだったら次も負けますよ。\nほな(帰らせて）頂きます。");

			}if (m_Manager->Count >= 30)
			{
				m_CommentFontRender->SetText(L"なんで負けたか\n次のゲームまでに考えて\nおいてください。\nほな(帰らせて）頂きます。");
			}
			return true;
		});
	m_CommentFontRender->SetColor(m_color);
	m_CommentFontRender->SetPosition(m_position);
	m_CommentFontRender->SetScale(2.0f);
	m_SS = NewGO < prefab::CSoundSource>(0);
	m_SS->Init(L"sound/GameOverSE.wav");
	m_SS->Play(false);
	MainCamera().SetTarget(CVector3::Zero);
	MainCamera().SetPosition({ 0.0f,0.0f,-200.0f });
	MainCamera().Update();
	m_SpriteRender = NewGO<prefab::CSpriteRender>(0);
	m_SpriteRender->Init(L"sprite/White.dds", 480.0f, 250.0f);
	m_SpriteRender->SetMulColor(m_ChangeColor);
	return true;
}

void GameOver::Update()
{
	m_SpritePosition.y -= 30.0f;
	if (m_SpritePosition.y <= 0.0f)
	{
		m_SpritePosition.y = 0.0f;
	}
	m_position.y -= 20.0f;
	if (m_position.y <= 100.0f)
	{
		m_position.y = 100.0f;
	}
	CVector3 m_movespeed = CVector3::Zero;
	if (m_Position.y == -90.0f)
	{
		timer += GameTime().GetFrameDeltaTime();
	}
	if (timer >= 5.0f)
	{
		m_movespeed.y = -20.0f;
	}
	else
	{
		m_movespeed.y = 10.0f;
	}
	m_Position += m_movespeed;
	m_HPosition += m_movespeed;
	if (m_Position.y >= -90.0f)
	{
		m_Position.y = -90.0f;
	}
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->Count >= 30)
			{
				m_skinmodel->SetPosition(m_HPosition);
			}
			return true;
		});
	m_skinModelRender->SetPosition(m_Position);
	if (Pad(0).IsTrigger(enButtonA))
	{
		Change = true;
	}
	if (Change)
	{
		m_ChangeColor.w += 0.1f;
	}
	if (m_ChangeColor.w >= 0.8f)
	{
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
		
			NewGO<StartTitle>(0,"StartTitle");
			NewGO<TotalScore>(0, "TotalScore");
		QueryGOs<TotalScore>("TotalScore", [&](TotalScore* m_Total)->bool
			{
				m_Total->m_Position.x = 2050.0f;
				return true;
			});
		DeleteGO(this);
	}
	m_SpriteRender->SetMulColor(m_ChangeColor);
	m_CommentFontRender->SetPosition(m_position);
	m_spriteRender->SetPosition(m_SpritePosition);

}
