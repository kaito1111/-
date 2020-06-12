#include "stdafx.h"
#include "ground.h"
#include "GameManager.h"


ground::ground()
{
}


ground::~ground()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(m_soundsource);
}

bool ground::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/ground.cmo");
	m_position.y = -1.0f;
	m_position.x = -350.0f;
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(m_scale);
	m_skinModelRender->SetShadowReceiverFlag(true);

	m_soundsource = NewGO<prefab::CSoundSource>(0);
	m_soundsource->InitStreaming(L"sound/bgm_maoudamashii_8bit13.wav");
	m_soundsource->SetVolume(0.3f);
	return true;
}

void ground::Update()
{
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->m_scale == 4.0f)
			{
				if (Pad(0).IsPress(enButtonB))
				{
					Delete = true;
				}
			}
			return true;
		});
	if (Delete) {
		m_position.y -= 10.0f;
	}
	if (m_position.y <= -1000.0f)
	{
		DeleteGO(this);
	}
	m_soundsource->Play(true);
	m_skinModelRender->SetPosition(m_position);
}
