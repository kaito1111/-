#pragma once
class GameManager;
class StageClare:public IGameObject
{
public:
	StageClare();
	~StageClare();

	bool Start();
	void Update();

	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CFontRender* m_FontRender;
	prefab::CSkinModelRender* m_SkinModelRender = nullptr;
	CVector3 m_SpritePosition = { 0.0f,1000.0f,0.0f };
	CVector2 m_FontPosition = { -500.0f,1000.0f };
	CVector3 m_Position = { 1000.0f,-100.0f,-50.0f };
	CVector3 m_scale = CVector3::One * 2;
	CVector3 m_EffectScale = CVector3::One * 5;
	prefab::CEffect* m_Efect = nullptr;
	CQuaternion m_Rot = CQuaternion::Identity;
	prefab::CSoundSource* m_SS = nullptr;
	prefab::CSoundSource* m_Sound = nullptr;
	bool PS = false;
	float m_Timer = 3.0f;
	prefab::CSpriteRender* m_SpriteRender = nullptr;
	CVector4 m_SpriteColor = { 1.0f,1.0f,1.0f,0.0f };
	bool Change = false;
};

