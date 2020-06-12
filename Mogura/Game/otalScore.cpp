#include "stdafx.h"
#include "otalScore.h"
#include "GameManager.h"

TotalScore::TotalScore()
{
}

TotalScore::~TotalScore()
{
	DeleteGO(m_Score);
}

bool TotalScore::Start()
{
	FILE* fp = NULL;
	TotalScore m_TotalScore;
	fp = fopen("Total.bi", "rb");
	if (fp != NULL) {
		fread(&Total, sizeof(int), 1, fp);
		fclose(fp);
	}
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			Total += m_Manager->Count;
			return true;
		});
	fp = fopen("Total.bi", "wb");
	fwrite(&Total, sizeof(int), 1, fp);
	fclose(fp);
	m_Score = NewGO<prefab::CFontRender>(5);
	wchar_t ScoreText[256];
	swprintf_s(ScoreText, L"¡“ú‚ÌƒXƒRƒA %d", Total);
	m_Score->SetText(ScoreText);
	m_Score->SetPosition(m_Position);
	CVector4 m_Color = CVector4::Black;
	m_Score->SetColor(m_Color);
	float Scale = 2.5f;
	m_Score->SetScale(Scale);
	return true;
}

void TotalScore::Update()
{
	CVector3 m_MoveSpeed = { 50.0f,0.0f,0.0f };
	timer += GameTime().GetFrameDeltaTime();
	if (timer >= 1.0f)
	{
		if (Pad(0).IsTrigger(enButtonA))
		{
			Delete = true;
		}
	}
	if (Delete)
	{
		m_MoveSpeed.x = -50.0f;
	}
	m_Position.x += m_MoveSpeed.x;
	if (m_Position.x >= -410.0f)
	{
		m_Position.x = -410.0f;
	}
	if (m_Position.x <= -3000.0f)
	{
		DeleteGO(this);
	}
	m_Score->SetPosition(m_Position);
}