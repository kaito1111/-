#include "stdafx.h"
#include "Player.h"
#include "Mogura.h"
#include"StageClare.h"
#include "GameOver.h"
#include "GameManager.h"
#include "KingMogura.h"
#include "Metooru.h"

Player::Player()
{
}


Player::~Player()
{
	/*DeleteGO(m_spriteRender);*/
	DeleteGO(m_skinModelRender);
	DeleteGO(m_skinModelHantei);
}

bool Player::Start()
{
	/*m_spriteRender = NewGO<prefab::CSpriteRender>(0);
	m_spriteRender->Init(L"../Resource/sprite/Game_Over.dds",1280.0f,720.0f);*/
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/hammer.cmo");
	m_rot.SetRotationDeg(CVector3::AxisZ, -90.0f);
	m_feverrot.SetRotationDeg(CVector3::AxisZ, -90.0f);
	m_position.y = 20.0f;
	m_rot.Multiply(m_rotition);
	m_skinModelRender->SetRotation(m_rotition);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetShadowCasterFlag(true);
	m_skinModelHantei = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelHantei->Init(L"modelData/AttackZone.cmo");
	m_AttackPosition.x = m_position.x + 60.0f;
	m_skinModelHantei->SetScale(m_AttackScale);
	m_skinModelHantei->SetPosition(m_AttackPosition);
	m_skinModelHantei->SetShadowCasterFlag(true);
	m_FeverFont = NewGO<prefab::CFontRender>(1);
	m_FeverFont->SetText(L"フィーバー!!!");
	m_FeverFont->SetColor(m_FontColor);
	m_FeverFont->SetPosition(m_FontPosition);
	m_FeverFont->SetScale(FontScale);

	m_FiverTimer = NewGO < prefab::CSpriteRender>(1);
	m_FiverTimer->Init(L"sprite/FiverTime.dds", 700, 100);
	m_FiverTimer->SetPosition(m_TimerPosition);
	m_FiverTimer->SetMulColor(m_ZeroColor);
	m_FiverTimer->SetPivot({ 0.0f,0.5f });
	return true;
}

void Player::Update()
{
	mm_timer += GameTime().GetFrameDeltaTime();

	if (cooltime == 0) {
		QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
			{
				if (m_Manager->m_StartTime <= 0.0f)
				{
					if (Pad(0).IsTrigger(enButtonB))
					{
						m_soundsource = NewGO<prefab::CSoundSource>(0);
						m_soundsource->Init(L"sound/PikopikoHammer.wav");
						m_soundsource->SetPosition(m_position);
						m_soundsource->Play(false);
						holdtime++;
						cooltime++;
					}
				}
				return true;
			});
	}
	else
	{
		cooltime++;
	}
	if (holdtime > 0)
	{
		holdtime++;
		m_skinModelRender->SetRotation(m_rot);
	}
	else
	{
		m_skinModelRender->SetRotation(m_rotition);
	}

	if (holdtime == 30)
	{
		holdtime = 0;
	}
	if (cooltime >= 50)
	{
		cooltime = 0;
	}
	if (holdtime > 0) {
		QueryGOs<Mogura>("Mogura", [&](Mogura* m_mogura)->bool
			{
				CVector3 diff = m_mogura->m_position - m_position;
				diff.x += -140.0f;
				if (diff.Length() < 90.0f && m_mogura->m_position.y == 20)
				{
					m_mogura->deleteMogura = true;
					m_mogura->m_position.y = 40.0f;
					QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
						{
							m_Manager->Count++;
							if (m_Manager->practice)
							{
								m_Manager->MoguraCount++;
								m_Manager->m_TimerScale.x += 1.0f / 3600.0f;
							}
							return true;
						});
				}
				return true;
			});
		QueryGOs<KingMogura>("KingMogura", [&](KingMogura* m_King)->bool
			{
				CVector3 diff = m_King->m_position - m_position;
				diff.x += -140.0f;
				if (diff.Length() < 90.0f && m_King->m_position.y == 20)
				{
					m_King->deleteMogura = true;
					m_King->m_position.y = 40.0f;
					QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
						{
							m_Manager->Count++;
							m_Manager->Count++;
							if (m_Manager->practice)
							{
								m_Manager->KingMoguraCount++;
								m_Manager->m_TimerScale.x += 1.0f / 1800.0f;
							}
							return true;
						});
				}
				return true;
			});
		QueryGOs<Metooru>("Metooru", [&](Metooru* m_Met)->bool
			{
				CVector3 diff = m_Met->m_position - m_position;
				diff.x += -140.0f;
				if (diff.Length() < 90.0f && m_Met->m_position.y == 20)
				{
					m_Met->deleteMogura = true;
					m_Met->m_position.y = 40.0f;
					QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
						{
							m_Manager->Count--;
							if (m_Manager->practice)
							{
								m_Manager->MetooruCount++;
								m_Manager->m_TimerScale.x -= 1.0f / 3600.0f;
							}
							return true;
						});
				}
				return true;
			});
	}
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->m_scale == 4.0f)
			{
				if (Pad(0).IsPress(enButtonB))
				{
					Delete = true;
				}
			}
			else
			{
				if (holdtime == 0)
				{
					CVector3 offset = { -76.87f, 20.0f, 3.0f };
					//マップの半分のサイズ。
					CVector3 areaHalfSize = { 480.0f, 0.0f, 280.0f };
					m_position = CVector3::Zero;
					m_position.x = areaHalfSize.x * Pad(0).GetLStickXF();
					m_position.z = areaHalfSize.z * Pad(0).GetLStickYF();
					m_position += offset;
				}
				if (m_position.x > 290.0f)
				{
					m_position.x = 290.0;
				}
				if (m_position.x < -446.0f)
				{
					m_position.x = -446.0f;
				}
				if (m_position.z > 208.0f)
				{
					m_position.z = 208.0f;
				}
				if (m_position.z < -200.0f)
				{
					m_position.z = -200.0f;
				}
			}
			if (Delete)
			{
				m_position.y -= 20.0f;
				m_AttackPosition.y -= 20.0f;
			}
			if (!m_Manager->practice) {
				if (fever >= 20)
				{
					m_FontColor =CVector4::Yellow;
					m_FontPosition.y += 2.5f;
					
						if (m_FontPosition.y >= 250.0f)
						{
							m_FontPosition.y = 250.0f;
						}
					
					m_FeverFont->SetPosition(m_FontPosition);
					if (!Fiver)
					{
						m_FeverFont->SetColor(m_FontColor);
						m_FeverStart = NewGO<prefab::CEffect>(0);
						m_FeverStart->Play(L"effect/fever.efk");
						m_FeverStart->SetScale(CVector3::One * 40.0f);
						CVector3 m_FeverStartPosition = CVector3::Zero;
						m_FeverStartPosition.x = 50.0f;
						m_FeverStartPosition.y = 50.0f;
						m_FeverStart->SetPosition(m_FeverStartPosition);
						m_FeverScale = CVector3::One;
						m_FiverTimer->SetMulColor(m_OneColor);
						Fiver = true;
					}
					QueryGOs<Mogura>("Mogura", [&](Mogura* m_mogura)->bool
						{
							CVector3 diff = m_mogura->m_position - m_position;
							diff.x += -140.0f;
							if (diff.Length() < 50.0f && m_mogura->m_position.y == 20)
							{
								m_mogura->deleteMogura = true;
								m_mogura->m_position.y = 30.0f;
								m_Manager->Count++;
							}
							return true;
						});
					QueryGOs<KingMogura>("KingMogura", [&](KingMogura* m_mogura)->bool
						{
							CVector3 diff = m_mogura->m_position - m_position;
							diff.x += -140.0f;
							if (diff.Length() < 50.0f && m_mogura->m_position.y == 20)
							{
								m_mogura->deleteMogura = true;
								m_mogura->m_position.y = 30.0f;
								m_Manager->Count += 2;
							}
							return true;
						});
					QueryGOs<Metooru>("Metooru", [&](Metooru* m_mogura)->bool
						{
							CVector3 diff = m_mogura->m_position - m_position;
							diff.x += -140.0f;
							if (diff.Length() < 50.0f && m_mogura->m_position.y == 20)
							{
								m_mogura->deleteMogura = true;
								m_mogura->m_position.y = 30.0f;
								m_Manager->Count--;
							}
							return true;
						});
					m_timer++;
					if (m_timer < 450)
					{
						QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
							{
								m_Manager->m_TimerScale.x += 1.0f / 3600.0f;
								return true;
							});
						m_feverrot.Multiply(m_rot);
						m_skinModelRender->SetRotation(m_feverrot);
						mm_timer -= GameTime().GetFrameDeltaTime();
						m_FeverScale.x -= 1.0f / 450.0f;
						
						m_FiverTimer->SetMulColor(m_OneColor);
					}
					else
					{
						m_FontColor = { 0.0f, 0.0f, 0.0f, 0.0f };
						m_FeverFont->SetColor(m_FontColor);
						fever = 0;
						m_FontPosition.y = -50.0f;
						if (Fiver)
						{
							DeleteGO(m_FeverStart);
							m_FeverEnd = NewGO<prefab::CEffect>(0);
							m_FeverEnd->Play(L"effect/feverend.efk");
							CVector3 m_feverEndPosition = CVector3::Zero;
							m_feverEndPosition.y = 1000.0f;
							m_FeverEnd->SetScale(CVector3::One * 30.0f);
							m_FiverTimer->SetMulColor(m_ZeroColor);
							m_timer = 0;
							Fiver = false;
						}
					}
				}
			}
			return true;
		});
	if (mm_timer >= 10) {
		mm_timer = 0;
		fever--;
	}
	if (m_position.y <= -1000.0f)
	{
		DeleteGO(this);
	}
	m_FiverTimer->Update();
	m_AttackPosition = m_position;
	m_AttackPosition.x = m_position.x + 140.0f;
	m_skinModelHantei->SetPosition(m_AttackPosition);
	m_skinModelRender->SetPosition(m_position);
	m_FiverTimer->SetScale(m_FeverScale);
}