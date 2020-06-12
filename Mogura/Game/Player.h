#pragma once
class Player:public IGameObject
{
public:
	Player();
	~Player();

	bool Start();
	void Update();

	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSkinModelRender* m_skinModelHantei = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_AttackPosition = CVector3::Zero;
	CQuaternion m_feverrot = CQuaternion::Identity;
	CQuaternion m_rotition=CQuaternion::Identity;
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 m_scale = { 4.0f,5.0f,4.0f };
	CVector3 m_AttackScale = CVector3::One * 3.3f;
	prefab::CFontRender* m_FeverFont = nullptr;
	CVector4 m_FontColor = { 0.0f,0.0f,0.0f,0.0f };
	CVector2 m_FontPosition = { -300.0f,-50.0f };
	float FontScale = 2.0f;
	bool attack = false;
	bool Delete = false;
	int cooltime = 0;
	int holdtime = 0;
	int fever = 0;
	float m_timer = 0;
	float mm_timer = 0;
	prefab::CSoundSource* m_soundsource = nullptr;
	bool Fiver = false;
	prefab::CEffect* m_FeverStart = nullptr;
	prefab::CEffect* m_FeverEnd = nullptr;

	prefab::CSpriteRender* m_FiverTimer = nullptr;
	CVector3 m_FeverScale = CVector3::One;

	CVector3 m_TimerPosition = { -300.0f,280.0f,0.0f };
	CVector4 m_ZeroColor = { 1.0f,1.0f,1.0f,0.0f };
	CVector4 m_OneColor = { 1.0f,1.0f,1.0f,1.0f };
	float TimeScaleTimer = 0.0f;
};
