#include "stdafx.h"
#include "FeintMogura.h"
#include "Player.h"
#include "GameManager.h"
#include "MoguraGenerator.h"
#include "PracticalMode.h"

FeintMogura::FeintMogura()
{
}

FeintMogura::~FeintMogura()
{
	DeleteGO(m_SkinModel);
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (!m_Manager->practice)
			{
				MoguraGenerator* m_Manager = FindGO<MoguraGenerator>("mogurageneretor");
				m_Manager->UnLock(spornNo);
			}
			else {
				PracticalMode* m_Plactical = FindGO< PracticalMode>("PrecticalMode");
				m_Plactical->UnLock(spornNo);
			}
			return true;
		});
}

bool FeintMogura::Start()
{
	m_SkinModel = NewGO<prefab::CSkinModelRender>(0);
	m_SkinModel->Init(L"modelData/mogura.cmo");
	m_rotition.SetRotationDeg(CVector3::AxisY, 180.0f);
	m_position.y = -100.0f;
	m_SkinModel->SetScale(m_scale);
	m_SkinModel->SetPosition(m_position);
	m_SkinModel->SetRotation(m_rotition);
	m_SkinModel->SetShadowCasterFlag(true);
	return true;
}

void FeintMogura::Update()
{
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->m_TimerScale.x <= 0.0f) {
				DeleteGO(this);
			}
			return true;
		});
	
	m_movespeed.y = 20.0f;
	if (timar >= 140.0f)
	{
		m_movespeed.y = -30.0f;
	}
	if (m_position.y < -100.0f)
	{
		DeleteGO(this);
	}
	if (m_position.y == 20.0f)
	{
		QueryGOs<Player>("player", [&](Player* m_Player)->bool
		{
			CVector3 Dis = m_Player->m_AttackPosition - m_position;
			if (Dis.Length() < 90.0f)
			{
				timar = 140.0f;
			}
			return true;
		});
		m_position.y = 0.0f;
		timar++;
	}
	m_position += m_movespeed;
	m_SkinModel->SetPosition(m_position);
}

