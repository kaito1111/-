#pragma once
class Metooru:public IGameObject
{
public:
	Metooru();
	~Metooru();

	bool Start();
	void Update();

	prefab::CSkinModelRender* m_skinModelRender = nullptr;
	prefab::CEffect* m_EF = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_movespeed = CVector3::Zero;
	CVector3 m_scale = CVector3::One * 4;
	CQuaternion m_rotition = CQuaternion::Identity;
	int timar = 0;
	int spornNo = 1;
	bool deleteMogura = false;
	bool InitEffect = false;
	prefab::CSoundSource* m_SS = nullptr;
};