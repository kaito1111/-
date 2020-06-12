#include "stdafx.h"
#include "Descript.h"
#include "GameScene.h"
#include "Level.h"
#include "GameManager.h"
#include "StartTitle.h"
#include  "PracticalMode.h"
#include "otalScore.h"

Descript::Descript()
{
}

Descript::~Descript()
{
	DeleteGO(m_Spritender);
	DeleteGO(m_SS);
}

bool Descript::Start()
{
	m_Spritender = NewGO<prefab::CSpriteRender>(0);
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool {
		if (m_Manager->Easy) {
			m_Spritender->Init(L"sprite/EasySetumei.dds", 1280.0f, 720.0f);
		}
		if (m_Manager->Normal) {
			m_Spritender->Init(L"sprite/NormalSetumei.dds", 1280.0f, 720.0f);
		}
		if (m_Manager->Hard) {
			m_Spritender->Init(L"sprite/HardSetumei.dds", 1280.0f, 720.0f);
		}
		if (m_Manager->practice) {
			m_Spritender->Init(L"sprite/PracticalMode.dds", 1280.0f, 720.0f);
		}
		return true;
		});
	return true;
}

void Descript::Update()
{
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (!m_Manager->practice)
			{
				timer += GameTime().GetFrameDeltaTime();
				if (timer >= 1.0f)
				{
					if (Pad(0).IsTrigger(enButtonX))
					{
						if (!Delete)
						{
							prefab::CSoundSource* m_Serect = NewGO<prefab::CSoundSource>(0);
							m_Serect->Init(L"sound/Cancel.wav");
							m_Serect->Play(false);

							NewGO<Level>(0, "Level");
							QueryGOs<Level>("Level", [&](Level* m_Level)->bool
								{
									m_Level->m_LevelSpritePosition.x = -1400.0f;
									m_Level->m_YajirusiPosition.x = -2050.0f;
									m_Level->Newgo = false;
									m_Level->Play = false;
									return true;
								});
							Delete = true;
						}
						timer = 0;
						m_Manager->Easy = false;
						m_Manager->Normal = false;
						m_Manager->Hard = false;
						return true;
					}

					if (Pad(0).IsTrigger(enButtonA))
					{
						if (!Newgo)
						{
							prefab::CSoundSource* m_Serect = NewGO<prefab::CSoundSource>(0);
							m_Serect->Init(L"sound/Select.wav");
							m_Serect->Play(false);


							NewGO<GameScene>(1, "GameScene");
							Newgo = true;
						}
						timer = 0;
					}
				}
			}
			else
			{
				timer += GameTime().GetFrameDeltaTime();
				if (timer >= 1.0f)
				{
					if (Pad(0).IsTrigger(enButtonX))
					{
						if (!Delete)
						{
							prefab::CSoundSource* m_Serect = NewGO<prefab::CSoundSource>(0);
							m_Serect->Init(L"sound/Cancel.wav");
							m_Serect->Play(false);
							NewGO<TotalScore>(0, "TotalScore");
							Delete = true;
							QueryGOs<StartTitle>("StartTitle", [&](StartTitle* m_Start)->bool
								{
									m_Start->m_Position.x = -1400.0f;
									m_Start->m_position.x = -2050.0f;
									m_Start->m_ScorePosition.x = -2050.0f;
									m_Start->timer = 0.0f;
									m_Start->Newgo = false;
									m_Start->practicu = false;
									m_Start->Play = false;
									m_Start->Disdeletego = true;
									return true;
								});
							QueryGOs< TotalScore>("TotalScore", [&](TotalScore* m_Total)->bool
								{
									m_Total->m_Position.x = -1500.0f;
									return true;
								});
							QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
								{
									m_Manager->Delete = true;
									return true;
								});
						}

					}
					if (Pad(0).IsTrigger(enButtonA))
					{
						if (!Newgo)
						{
							prefab::CSoundSource* m_SS = NewGO<prefab::CSoundSource>(0);
							m_SS->Init(L"sound/Select.wav");
							m_SS->Play(false);
							NewGO<GameScene>(1, "GameScene");
							Newgo = true;
						}
						timer = 0;
					}
				}
			}
			return true;
		});
	QueryGOs< GameScene>("GameScene", [&](GameScene* m_Game)->bool
		{
			if (m_Game->m_Color.w >= 0.8f)
			{
				DeleteGO(this);
			}
			return true;
		});
	QueryGOs<Level>("Level", [&](Level* m_Level)->bool
		{
			if (m_Level->m_LevelSpritePosition.x >= 0.0f)
			{
				DeleteGO(this);
			}
			return true;
		});
	QueryGOs<StartTitle>("StartTitle", [&](StartTitle* m_Start)->bool
		{
			if (Newgo)
			{
				m_Start->Delete = true;
			}
			if (m_Start->m_Position.x >= 0.0f)
			{
				DeleteGO(this);
			}
			return true;
		});
	if (Deletego)
	{
		DeleteGO(this);
	}
}
