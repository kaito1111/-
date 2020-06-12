#pragma once
class Descript;
class StartTitle :public IGameObject
{
public:
	StartTitle();
	~StartTitle();

	bool Start();
	void Update();

	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSoundSource* m_soundsource = NewGO<prefab::CSoundSource>(0);
	prefab::CSpriteRender* m_SR = nullptr;
	CVector3 m_position = { -550.0f,-40.0f,0.0f };
	CVector3 m_Position = CVector3::Zero;
	bool Newgo = false;
	float timer = 0.0f;
	bool practicu = false;
	bool normal = false;

	prefab::CFontRender* m_HighFont = nullptr;
	float ScoreScale = 2.0f;
	CVector2 m_ScorePosition = { -500.0f,-340.0f };
	CVector4 m_ScoreColor = { 1.0f,0.1f,1.0f ,1.0f };

	bool Delete = false;
	bool Play = false;
	bool Disdeletego = false;
};

