#pragma once
class PracticalEND :public IGameObject
{
public:
	PracticalEND();
	~PracticalEND();

	bool Start();
	void Update();

	prefab::CSpriteRender* m_SPR = nullptr;
	CVector3 m_SpritePosition = { 0.0f,1000.0f,0.0f };
	int AllKill = 0;
	prefab::CSkinModelRender* m_MoguraModelRender = nullptr;
	CVector3 m_MoguraPosition = { -50.0f,1000.0f,0.0f };
	CVector3 m_MoguraScale = CVector3::One * 2.0f;
	int MoguraKill = 0;
	int MoguraTimar = 0;
	prefab::CFontRender* m_MoguraKillFont = nullptr;
	CVector2 m_MoguraFontPosition = { -50.0f,1000.0f, };
	CVector4 m_Color = CVector4::Black;
	float FontScale = 3.5f;
	wchar_t MogurakillMoji[128];

	prefab::CSkinModelRender* m_KingModelRender = nullptr;
	CVector3 m_KingMoguraPosition = { -170.0f,1000.0f,0.0f };
	int KingMoguraKill = 0;
	int KingMoguraTimar = 0;
	prefab::CFontRender* m_KingMoguraKillFont = nullptr;
	CVector2 m_KingFontPosition = { -500.0f,1000.0f };
	wchar_t KingMogurakillMoji[128];

	prefab::CSkinModelRender* m_MetooruModelRender = nullptr;
	CVector3 m_MetooruPosition = { 80.0f,2000.0f,0.0f };
	int MetooruKill = 0;
	int MetooruTimar = 0;
	prefab::CFontRender* m_MetooruKillFont = nullptr;
	CVector2 m_MetooruFontPosition = { 400.0f,1000.0f };
	CVector3 m_MetooruFontScale = CVector3::One * 2;
	wchar_t MetoorukillMoji[128];

	prefab::CFontRender* m_Total = nullptr;
	wchar_t TotalMoji[128];
	int Total = 0;
	CVector2 m_TotalPojition = { -400.0f,1000.0f };

	prefab::CFontRender* m_Next = nullptr;
	CVector2 m_NextPosition = { 110.0f,-300.0f };
	CVector2 m_MoveSpeed = CVector2::Zero;
	CVector4 m_NextColor = { 0.0f,1.0f,0.0f,0.0f };
	float NextScale = 2.0f;

	prefab::CSpriteRender* m_SpriteRender = nullptr;
	CVector4 m_SpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	bool Change = false;
};