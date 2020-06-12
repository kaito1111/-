#pragma once
class StageClear;
class GameOver;
class GameManager :public IGameObject
{
public:
	GameManager();
	~GameManager();

	bool Start();
	void Update();

	prefab::CFontRender* m_FontRender = nullptr;
	prefab::CSpriteRender* m_BackGroundRender = nullptr;
	prefab::CFontRender* m_FR = nullptr;
	prefab::CFontRender* m_FinishFont = nullptr;
	prefab::CDirectionLight* m_light = nullptr;
	CVector3 m_LightPotition = { 0.0f,0.707,-200.0f };
	CVector3 m_CameraTrget = { 50.0f, 70.0f, 0.0f };
	CVector3 m_CameraPosition = { 50.0f, 500.0f, -300.0f };
	CVector2 m_position = { 300.0f,250.0f };
	CVector2 m_Position = { -600.0f,250.0f };
	CVector4 m_color = CVector4::Black;
	CVector4 m_Color = { 1.0f,0.0f,0.0f,1.0f };
	CVector4 m_StartColor = { 1.0f,1.0f,1.0f,0.0f };
	CVector4 m_UnderStartColor = { 0.0f,0.0f,0.0f,0.0f };
	int Count = 0;
	float m_colorTimer = 0.0f;
	float m_StartTime = 3.0f;
	wchar_t kill[128];
	wchar_t StartTime[128];
	bool setcolor = false;
	float m_scale = 0.5f;
	bool practice = false;
	bool DFont = false;
	bool Easy = false;
	bool Normal = false;
	bool Hard = false;
	bool GameStart = false;
	bool InitText = false;
	bool Newgo = false;
	int MoguraCount = 0;
	int KingMoguraCount = 0;
	int MetooruCount = 0;
	prefab::CSpriteRender* m_UnderTimer = nullptr;

	prefab::CSpriteRender* m_Timer = nullptr;
	CVector3 m_TimerScale = CVector3::One;

	CVector3 m_TimerPosition = { -300.0f,280.0f,0.0f };
	CVector4 m_ZeroColor = { 1.0f,1.0f,1.0f,0.0f };
	CVector4 m_OneColor= { 1.0f,1.0f,1.0f,1.0f };
	float TimeScaleTimer = 0.0f;
	bool Delete = false;

	int Blink = 0;
	CVector4 m_SetColor = { 1.0f,1.0f,1.0f,1.0f };
	bool Sound = false;
};

