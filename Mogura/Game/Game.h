#pragma once

#include "tkEngine/graphics/effect/tkEffect.h"
#include "tkEngine/physics/tkPhysicsGhostObject.h"
#include "tkEngine/character/tkCharacterController.h"

class Game : public IGameObject
{
public:
	Game();
	~Game();

	bool Start();
	void Update();

	int HighScore = 0;
	prefab::CDirectionLight* m_directionlight = nullptr;
	//prefab::CSkinModelRender* m_skinModelRender = nullptr;		//スキンモデルレンダラー。
};

