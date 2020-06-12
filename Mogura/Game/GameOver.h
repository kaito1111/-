#pragma once
class GameManager;
class GameOver:public IGameObject
{
public:
	GameOver();
	~GameOver();

	bool Start();
	void Update();

	prefab::CSpriteRender* m_spriteRender = nullptr;
	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CSkinModelRender* m_skinmodel = nullptr;
	prefab::CFontRender* m_CommentFontRender = nullptr;
	prefab::CSoundSource* m_SS = nullptr;
	CVector3 m_SpritePosition = { 0.0f,1000.0f,0.0f };
	CVector3 m_Position = {110.0f,-1000.0f,-50.0f };
	CVector3 m_HPosition = { 80.0f,-90.0f,-50.0f };
	CVector2 m_position = { -500.0f,1000.0f };
	CQuaternion m_rot = CQuaternion::Identity;
	CVector3 m_scale = CVector3::One * 2;
	float FontScale = 2.0f;
	float timer = 0.0f;
	prefab::CSpriteRender* m_SpriteRender = nullptr;
	CVector4 m_ChangeColor = { 1.0f,1.0f,1.0f,0.0f };
	bool Change = false;
	bool Newgo = false;
};

