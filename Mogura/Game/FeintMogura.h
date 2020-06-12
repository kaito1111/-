#pragma once
class FeintMogura:public IGameObject
{
public:
	FeintMogura();
	~FeintMogura();

	bool Start();
	void Update();

	prefab::CSkinModelRender* m_SkinModel = nullptr;
	CVector3 m_position = CVector3::Zero;
	CVector3 m_movespeed = CVector3::Zero;
	CVector3 m_scale = CVector3::One * 4;
	CQuaternion m_rotition = CQuaternion::Identity;
	int timar = 0;
	int spornNo = 1;
	bool deleteMogura = false;
	CShadowCaster_SkinModel* m_SkinModelShadow = nullptr;
};

