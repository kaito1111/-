#include "stdafx.h"
#include "Metooru.h"
#include "GameManager.h"
#include "PracticalMode.h"
#include "MoguraGenerator.h"
Metooru::Metooru()
{
}

Metooru::~Metooru()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_EF);
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

bool Metooru::Start()
{
	CQuaternion m_rot2 = CQuaternion::Identity;
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/Metooru.cmo");
	m_rot2.SetRotationDeg(CVector3::AxisY, 180.0f);
	m_rotition.Multiply(m_rot2);
	m_position.y = -100.0f;
	m_SS = NewGO<prefab::CSoundSource>(0);
	m_SS->Init(L"sound/backboostar.wav");
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rotition);
	m_skinModelRender->SetShadowCasterFlag(true);
	return true;
}

void Metooru::Update()
{
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->m_TimerScale.x <= 0.0f)
			{
				DeleteGO(this);
				if (!m_Manager->practice)
				{
					MoguraGenerator* m_Manager = FindGO<MoguraGenerator>("mogurageneretor");
					m_Manager->UnLock(spornNo);
				}
				else {
					PracticalMode* m_Plactical = FindGO< PracticalMode>("PrecticalMode");
					m_Plactical->UnLock(spornNo);
				}
			}
			return true;
		});
	m_movespeed.y = 20.0f;
	if (timar >= 140.0f)
	{
		m_movespeed.y = -30.0f;
	}
	if (m_position.y < -100.0f || m_position.y>1000.0f)
	{
		DeleteGO(m_SS);
		DeleteGO(this);
	}
	if (m_position.y == 20.0f)
	{
		m_position.y = 0.0f;
		timar++;
	}
	if (deleteMogura)
	{
		if (!InitEffect)
		{
			m_EF = NewGO<prefab::CEffect>(0);
			m_EF->Play(L"effect/kemuri.efk");
			CQuaternion qRot = CQuaternion::Identity;
			qRot.SetRotationDeg(CVector3::AxisX, -90.0f);
			m_EF->SetScale(m_scale * 10.0f);
			m_EF->SetPosition(m_position);
			m_EF->SetRotation(qRot);
			InitEffect = true;
		}
		m_SS->SetPosition(m_position);
		m_SS->Play(false);
		m_movespeed.y = 30.0f;
	}
	m_position += m_movespeed;
	if (InitEffect)
	{
		m_EF->SetPosition(m_position);
		m_EF->Update();
	}
	m_skinModelRender->SetPosition(m_position);
}
