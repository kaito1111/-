#include "stdafx.h"
#include "Level.h"
#include "Descript.h"
#include "StartTitle.h"
#include "GameManager.h"
#include "otalScore.h"
#include "Game.h"

Level::Level()
{
}

Level::~Level()
{
	DeleteGO(m_SpriteRender);
	DeleteGO(m_YajirusiSR);
}

bool Level::Start()
{
	m_SpriteRender = NewGO < prefab::CSpriteRender>(1);
	m_SpriteRender->Init(L"sprite/Level.dds", 1280.0f, 720.0f);
	m_SpriteRender->SetPosition(m_LevelSpritePosition);
	m_YajirusiSR = NewGO<prefab::CSpriteRender>(2);
	m_YajirusiSR->Init(L"sprite/yajirusi.dds", 256.0f, 144.0f);
	m_YajirusiSR->SetPosition(m_YajirusiPosition);

	return true;
}

void Level::Update()
{
	timar++;
	Timar += GameTime().GetFrameDeltaTime();
	CVector3 m_MoveSpeed = CVector3::Zero;
	if (timar >= 10)
	{
		if (Pad(0).GetLStickYF() >= 0.5f)
		{
			m_YajirusiPosition.y += 130.0f;
			timar = 0;
		}
		if (Pad(0).GetLStickYF() <= -0.5f)
		{
			m_YajirusiPosition.y -= 130.0f;
			timar = 0;
		}
		if (m_YajirusiPosition.y >= -10.0f)
		{
			m_YajirusiPosition.y = -10.0f;
		}
		if (m_YajirusiPosition.y <= -270.0f)
		{
			m_YajirusiPosition.y = -270.0f;
		}
	}
	m_MoveSpeed.x = 50.0f;
	if (Timar >= 1.0f)
	{
		if (Pad(0).IsTrigger(enButtonA))
		{
			if (m_YajirusiPosition.y == -10.0f)
			{
				if (!Play)
				{
					prefab::CSoundSource* m_SS = NewGO<prefab::CSoundSource>(0);
					m_SS->Init(L"sound/Select.wav");
					m_SS->Play(false);
					Play = true;
				}
				QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
					{
						m_Manager->Easy = true;
						return true;
					});
			}
			if (m_YajirusiPosition.y == -140.0f)
			{
				if (!Play)
				{
					prefab::CSoundSource* m_SS = NewGO<prefab::CSoundSource>(0);
					m_SS->Init(L"sound/Select.wav");
					m_SS->Play(false);
					Play = true;
				}
				QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
					{
						m_Manager->Normal = true;
						return true;
					});
			}
			if (m_YajirusiPosition.y == -270.0f)
			{
				if (!Play)
				{
					prefab::CSoundSource* m_SS = NewGO<prefab::CSoundSource>(0);
					m_SS->Init(L"sound/Select.wav");
					m_SS->Play(false);
					Play = true;
				}
				QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
					{
						m_Manager->Hard = true;
						return true;
					});
			}
		}
		if (Pad(0).IsTrigger(enButtonX))
		{
			if (!Newgo)
			{
				if (!Play)
				{
					prefab::CSoundSource* m_SS = NewGO<prefab::CSoundSource>(0);
					m_SS->Init(L"sound/Cancel.wav");
					m_SS->Play(false);
					Play = true;
				}
				QueryGOs<StartTitle>("StartTitle", [&](StartTitle* m_Start)->bool
					{
						m_Start->m_Position.x = -1500.0f;
						m_Start->m_position.x = -2050.0f;
						m_Start->m_ScorePosition.x = -2050.0f;
						m_Start->timer = 0.0f;
						m_Start->normal = false;
						m_Start->Newgo = false;
						m_Start->Play = false;
						m_Start->practicu = false;
						return true;
					});
				NewGO<TotalScore>(0, "TotalScore");
				QueryGOs<TotalScore>("TotalScore", [&](TotalScore* m_Total)->bool
					{
						m_Total->m_Position.x = -2050.0f;
						return true;
					});
				QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
					{
						m_Manager->Delete = true;
						return true;
					});
				Newgo = true;
			}
		}
	}
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->Easy || m_Manager->Normal || m_Manager->Hard)
			{
				if (!Newgo) {
					QueryGOs<Game>("Game", [&](Game* m_Game)->bool
						{
							NewGO<Descript>(0, "Descript");
							return true;
						});

					swich = true;
					Newgo = true;
				}
				m_MoveSpeed.x = -50.0f;
			}
			return true;
		});
	m_LevelSpritePosition += m_MoveSpeed;
	m_YajirusiPosition += m_MoveSpeed;
	if (m_LevelSpritePosition.x >= 0.0f)
	{
		m_LevelSpritePosition.x = 0.0f;
	}
	if (m_YajirusiPosition.x >= -550.0f)
	{
		m_YajirusiPosition.x = -550.0f;
	}
	QueryGOs<StartTitle>("StartTitle", [&](StartTitle* m_Start)->bool
		{
			if (m_Start->m_Position.x >= 0.0f)
			{
				DeleteGO(this);
				return true;
			}
		});
	m_YajirusiSR->SetPosition(m_YajirusiPosition);
	m_SpriteRender->SetPosition(m_LevelSpritePosition);
	if (m_LevelSpritePosition.x < -1500.0f)
	{
		DeleteGO(this);
	}
}
