#include "stdafx.h"
#include "GameManager.h"
#include "StageClare.h"
#include "GameOver.h"
#include "PracticalMode.h"
#include "Level.h"
#include "Descript.h"
#include "PracticalEND.h"
#include "Player.h"

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
	DeleteGO(m_FontRender);
	DeleteGO(m_FR);
	DeleteGO(m_UnderTimer);
	DeleteGO(m_Timer);
}

bool GameManager::Start()
{
	m_FontRender = NewGO<prefab::CFontRender>(3);
	m_FontRender->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	m_FontRender->SetPosition(m_Position);
	m_FontRender->SetScale(1.0f);

	m_FR = NewGO<prefab::CFontRender>(0);
	swprintf_s(StartTime, L"%.0f", m_StartTime);
	m_FR->SetText(StartTime);
	m_FR->SetColor({ 1.0f,0.0f,0.0f,1.0f });
	m_FR->SetScale(2.0f);

	m_FinishFont = NewGO<prefab::CFontRender>(1);
	m_FinishFont->SetText(L"èIóπÅIÅI");
	m_FinishFont->SetPosition({ -250.0f,-100.0f });
	m_FinishFont->SetColor({ 0.0f,0.0f,0.0f,0.0f });
	m_FinishFont->SetScale(m_scale);

	m_BackGroundRender = NewGO<prefab::CSpriteRender>(0);
	m_BackGroundRender->Init(L"sprite/BackGround.dds", 2500.0f, 1000.0f, true);
	m_BackGroundRender->SetPosition({ 00.0f,0.0f,350.0f });

	m_UnderTimer = NewGO < prefab::CSpriteRender>(0);
	m_UnderTimer->Init(L"sprite/UnderTimer.dds", 700, 100);
	m_UnderTimer->SetPosition(m_TimerPosition);
	m_UnderTimer->SetPivot({ 0.0f,0.5f });
	m_UnderTimer->SetMulColor(m_ZeroColor);

	m_Timer = NewGO < prefab::CSpriteRender>(4);
	m_Timer->Init(L"sprite/Timer.dds", 700, 100);
	m_Timer->SetPosition(m_TimerPosition);
	m_Timer->SetPivot({ 0.0f,0.5f });
	m_Timer->SetMulColor(m_ZeroColor);

	/*m_TimerScale.x = 0.1f;
	m_Timer->SetScale(m_TimerScale);*/
	/*CQuaternion m_GroundRot = CQuaternion::Identity;
	m_GroundRot.SetRotationDeg(CVector3::AxisX, 90.0f);
	m_BackGroundRender->SetRotation(m_GroundRot);
	m_BackGroundRender->SetScale({ 40.0f,1.0f,40.0f });*/
	return true;
}

void GameManager::Update()
{
	if (GameStart)
	{
		if (!InitText)
		{
			m_FontRender->SetText(kill);
			InitText = true;
		}
		if (m_TimerScale.x == 0.1f)
		{
			Blink = 1;
		}
		if (Blink == 1)
		{
			m_OneColor.w = -0.1f;
			m_SetColor.w += m_OneColor.w;
			if (m_SetColor.w <= 0.0f)
			{
				Blink = 2;
			}
			m_Timer->SetMulColor(m_OneColor);
		}
		if (Blink == 2)
		{
			m_OneColor.w = 0.1f;
			m_SetColor.w += m_OneColor.w;
			if (m_SetColor.w >= 1.0f)
			{
				Blink = 1;
			}
			m_Timer->SetMulColor(m_OneColor);
		}
		m_colorTimer += GameTime().GetFrameDeltaTime();
		m_StartTime -= GameTime().GetFrameDeltaTime();
		m_StartColor.w += 0.01f;
		m_UnderStartColor.w += 0.01f;
		m_UnderTimer->SetMulColor(m_UnderStartColor);
		m_Timer->SetMulColor(m_StartColor);
		if (m_StartTime < 0.0f)
		{
			if (!setcolor)
			{
				m_FR->SetColor({ 0.0f,0.0f,0.0f,0.0f });
				setcolor = true;
			}
			QueryGOs<Player>("player", [&](Player* m_player)->bool
				{
					if (m_player->fever >= 20)
					{
						m_Timer->SetMulColor(m_ZeroColor);
					}
					else
					{
						m_TimerScale.x -= 1.0f / 3600.0f;
					}
					return true;
				});
		}
		//âeÇéŒÇﬂÇ…óéÇ∆Ç∑ÅB
		if (m_StartTime <= 0.0f)
		{
			m_StartTime = 0.0f;
			//m_FinishFont->SetColor({ 0.0f,0.0f,0.0f,1.0f });
		}
		if (m_TimerScale.x <= 0.0f)
		{
			if (!DFont)
			{
				m_FinishFont->SetColor({ 0.0f,1.0f,1.0f,1.0f });
			}
			if (!Sound)
			{
				prefab::CSoundSource* m_SS = NewGO<prefab::CSoundSource>(0);
				m_SS->Init(L"sound/whistle.wav");
				m_SS->Play(false);
				Sound = true;
			}
			m_scale += 0.1f;
			if (m_scale >= 4.0f)
			{
				m_scale = 4.0f;
				if (Pad(0).IsTrigger(enButtonB))
				{
					DFont = true;
				}
			}
			if (DFont)
			{
				m_CameraTrget.y -= 1.4f;
				m_CameraTrget.x -= 1.0f;
				m_CameraPosition.x -= 1.0f;
				m_CameraPosition.y -= 10.0f;
				m_CameraPosition.z += 0.2f;
				if (m_CameraTrget.x <= 0.0f || m_CameraPosition.y <= 70.0f)
				{
					if (practice)
					{
						if (!Newgo)
						{
							NewGO<PracticalEND>(1); 
							DeleteGO(m_FinishFont);
							Newgo = true;
						}

					}
					else
					{
						if (!Newgo)
						{
							if (Easy)
							{
								if (Count >= 20)
								{
									NewGO<StageClare>(1, "StageClare");
								}
								if (Count < 20)
								{
									NewGO<GameOver>(1, "GameOver");
								}
							}
							if (Normal)
							{
								if (Count >= 30)
								{
									NewGO<StageClare>(1, "StageClare");

								}
								if (Count < 30)
								{
									NewGO<GameOver>(1, "GameOver");
								}
							}
							if (Hard)
							{
								if (Count >= 50)
								{
									NewGO<StageClare>(1, "StageClare");

								}
								if (Count < 50)
								{
									NewGO<GameOver>(1, "GameOver");
								}
							}

							DeleteGO(m_FinishFont);
							Newgo = true;
						}

					}
				}

				else
				{
					MainCamera().SetTarget(m_CameraTrget);
					MainCamera().SetPosition(m_CameraPosition);
					MainCamera().Update();
				}
			}
		}
		/*	if (Pad(0).IsTrigger(enButtonA) && DFont)
			{
				DeleteGO(this);

			}*/

		if (Newgo)
		{
			m_TimerPosition.y += 10.0f;
		}
		swprintf_s(kill, L"%dïC", Count);
		m_FontRender->SetText(kill);
		m_FontRender->SetColor(m_color);
		m_FontRender->SetPosition(m_Position);
		m_FontRender->SetScale(2.0f);
		swprintf_s(StartTime, L"%.0f", m_StartTime);
		m_FR->SetText(StartTime);
		m_FinishFont->SetScale(m_scale);
		m_Timer->SetScale(m_TimerScale);
		m_UnderTimer->SetPosition(m_TimerPosition);
		m_Timer->SetPosition(m_TimerPosition);
	}
	QueryGOs<StageClare>("StageClare", [&](StageClare* m_Clare)->bool
		{
			if (m_Clare->m_Timer <= -1.0f)
			{
				if (Pad(0).IsPress(enButtonA))
				{
						DeleteGO(this);
				}
			}
			return true;
		});
	QueryGOs<GameOver>("GameOver", [&](GameOver* m_Over)->bool
		{
			if (m_Over->Change)
			{
				DeleteGO(this);
			}
			return true;
		});
	if (Delete)
	{
		DeleteGO(this);
	}
}