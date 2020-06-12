#pragma once
class ground:public IGameObject
{
public:
	ground();
	~ground();

	bool Start();
	void Update();

	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_scale = { 6.0f,1.0f,5.0f };
	prefab::CSoundSource* m_soundsource = nullptr;
	bool Delete = false;
};

