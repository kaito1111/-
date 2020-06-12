#include "stdafx.h"
#include "PracticalMode.h"
#include "Player.h"
#include "GameManager.h"
#include "Mogura.h"
#include "KingMogura.h"
#include "Metooru.h"
#include "FeintMogura.h"

PracticalMode::PracticalMode()
{
}

PracticalMode::~PracticalMode()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			DeleteGO(m_SMR[i][j]);
		}
	}
}

bool PracticalMode::Start()
{
	CVector3 m_Position = { 1000.0f,0.0f,0.0f };
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			m_SMR[i][j] = nullptr;
			m_SMR[i][j] = NewGO<prefab::CSkinModelRender>(0);
			m_SMR[i][j]->Init(L"modelData/Hole.cmo");
			m_SMR[i][j]->SetScale(m_Scale);
			m_SMR[i][j]->SetPosition(m_Position);
		}
	}
	int j = 0;
	for (int i = 0; i < 3; i++)//00,10,11,12,23
	{
		CVector3 m_position = { -314.0f,0.0f,13.0f };
		m_position.x += 381.0f * i;
		if (m_position.x == 67.0f)
		{
			for (j = 0; j < 3; j++)
			{
				m_position.z = 220.0f * j + 13;//x,-314,67,448,z,-197,13,223
				if (j == 2)
				{
					m_position.z = -197.0f;
				}
				m_SMR[i][j]->SetPosition(m_position);
			}
		}
		m_SMR[i][j]->SetPosition(m_position);
	}
	for (int i = 3; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (!j == 2)
			{
				m_SMR[i][j]->SetPosition(m_Position);
			}
		}
	}

	return true;
}

void PracticalMode::Update()
{
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->m_StartTime <= 0.0f)
			{
				timer++;
				Kingtimer++;
				Mettimer++;
				FeintTimer++;
			}
			return true;
		});
	if (Kingtimer >= KingTimer)
	{
		KingMogura* m_Mogura = NewGO< KingMogura>(0, "KingMogura");
		Kingtimer = 0;
		do {
			sporn = Random().GetRandInt() % Masu + 1;
		} while (spornNo[sporn] != 0);
		switch (sporn)
		{
		case 1:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 2:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 3:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 4:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 5:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 6:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 7:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 8:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 9:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 10:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 11:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 12:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 13:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 14:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 15:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 16:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 17:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 18:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 19:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 20:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 21:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 22:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 23:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 24:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 25:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = 185.0f;
			break;
		default:
			DeleteGO(m_Mogura);
			break;
		}
		m_Mogura->spornNo = sporn;
		spornNo[sporn] = 1;
	}
	if (FeintTimer >= 200)
	{
		FeintMogura* m_Mogura = NewGO< FeintMogura>(0, "FeintMogura");
		FeintTimer = 0;
		do {
			sporn = Random().GetRandInt() % Masu + 1;
		} while (spornNo[sporn] != 0);
		switch (sporn)
		{
		case 1:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 2:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 3:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 4:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 5:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 6:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 7:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 8:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 9:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 10:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 11:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 12:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 13:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 14:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 15:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 16:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 17:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 18:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 19:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 20:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 21:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 22:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 23:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 24:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 25:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = 185.0f;
			break;
		default:
			DeleteGO(m_Mogura);
			break;
		}
		m_Mogura->spornNo = sporn;
		spornNo[sporn] = 1;
	}
	if (timer >= 200)
	{
		Mogura* m_Mogura = NewGO<Mogura>(0, "Mogura");
		timer = 0;
		do {
			sporn = Random().GetRandInt() % Masu + 1;
		} while (spornNo[sporn] != 0);
		switch (sporn)
		{
		case 1:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 2:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 3:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 4:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 5:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 6:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 7:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 8:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 9:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 10:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 11:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 12:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 13:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 14:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 15:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 16:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 17:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 18:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 19:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 20:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 21:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 22:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 23:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 24:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 25:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = 185.0f;
			break;
		default:
			DeleteGO(m_Mogura);
			break;
		}
		m_Mogura->spornNo = sporn;
		spornNo[sporn] = 1;
	}
	if (Mettimer >= MetTimer) {
		Metooru* m_Mogura = NewGO<Metooru>(0, "Metooru");
		Mettimer = 0;
		do {
			sporn = Random().GetRandInt() % Masu + 1;
		} while (spornNo[sporn] != 0);
		switch (sporn)
		{
		case 1:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 2:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 3:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 4:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 5:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 6:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 7:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 8:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 9:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 10:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 11:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 12:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 13:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 14:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 15:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 16:
			m_Mogura->m_position.x = 55.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 17:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -17.0f;
			break;
		case 18:
			m_Mogura->m_position.x = -312.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 19:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = -125.0f;
			break;
		case 20:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 21:
			m_Mogura->m_position.x = 435.0f;
			m_Mogura->m_position.z = 78.0f;
			break;
		case 22:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 23:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = -222.0f;
			break;
		case 24:
			m_Mogura->m_position.x = 245.5f;
			m_Mogura->m_position.z = 185.0f;
			break;
		case 25:
			m_Mogura->m_position.x = -131.5f;
			m_Mogura->m_position.z = 185.0f;
			break;
		default:
			DeleteGO(m_Mogura);
			break;
		}
		m_Mogura->spornNo = sporn;
		spornNo[sporn] = 1;
	}
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->Count >= 5)
			{
				if (Masu == 5)
				{
					for (int i = 3; i < 5; i++)//30,40,13,14
					{
						for (int j = 0; j < 2; j++)
						{
							m_position = { -314.0f,0.0f,-197.0f };
							if (j == 0) {
								if (i == 3)
								{
									m_position.z = 223.0f;
								}
								if (i == 4)
								{

									m_position.x = 448.0f;
									m_position.z = 223.0f;
								}
								m_SMR[i][j]->SetPosition(m_position);
							}
							else {
								if (i == 3)
								{
									m_position.x = 448.0f;
								}
								m_SMR[j][i]->SetPosition(m_position);
							}
						}

					}
					Masu = 9;
				}
			}
			if (m_Manager->Count >= 10)
			{
				if (Masu == 9)
				{
					for (int i = 4; i < 5; i++)//41,42,43,44
					{
						for (int j = 1; j < 5; j++)
						{
							if (i == 4)
							{
								if (j == 1)
								{
									m_position.x = -123.5f;
									m_position.z = 118.0f;
								}
								if (j == 2)
								{
									m_position.x = -123.5f;
									m_position.z = -92.0f;
								}
								if (j == 3)
								{
									m_position.x = 257.5f;
									m_position.z = 118.0f;
								}
								if (j == 4)
								{
									m_position.x = 257.5f;
									m_position.z = -92.0f;
								}
							}
							m_SMR[i][j]->SetPosition(m_position);
						}
					}
					Masu = 13;
				}
			}
			if (m_Manager->Count >= 20)
			{
				if (Masu == 13)
				{
					for (int i = 2; i < 3; i++)//21,22,20,24
					{
						for (int j = 0; j < 4; j++)
						{
							if (j == 2)
							{
								m_position.x = -123.5f;
								m_position.z = 13.0f;
							}
							if (j == 1)
							{
								m_position.x = 67.0f;
								m_position.z = 118.0f;
							}
							if (j == 3)
							{
								j = 4;
								m_position.x = 67.0f;
								m_position.z = -92.0f;
							}
							if (j == 0)
							{
								m_position.x = 257.5f;
								m_position.z = 13.0f;
							}
							m_SMR[i][j]->SetPosition(m_position);
						}
					}
					Masu = 17;
				}
			}
			if (m_Manager->Count >= 40)
			{
				if (Masu == 17)
				{
					for (int i = 3; i < 4; i++)//31,32,33,34
					{
						for (int j = 1; j < 5; j++)
						{
							m_position = { -314.0f,0.0f,-197.0f };

							if (j == 1)
							{
								m_position.z = 118.0f;
							}
							if (j == 2)
							{
								m_position.z = -92.0f;

							}
							if (j == 3)
							{
								m_position.x = 448.0f;
								m_position.z = 118.0f;
							}
							if (j == 4)
							{
								m_position.x = 448.0f;
								m_position.z = -92.0f;
							}

							m_SMR[i][j]->SetPosition(m_position);
						}
					}
					Masu = 21;
				}
			}
			if (m_Manager->Count >= 60)
			{
				if (Masu == 21)
				{
					for (int i = 0; i < 1; i++)//01,02,03,04
					{
						for (int j = 1; j < 5; j++)
						{
							m_position = { -314.0f,0.0f,-197.0f };
							if (j == 1)
							{
								m_position.x = -123.5f;
								m_position.z = 223.0f;
							}
							if (j == 2)
							{
								m_position.x = -123.5f;
							}
							if (j == 3)
							{
								m_position.x = 257.5f;
								m_position.z = 223.0f;
							}
							if (j == 4)
							{
								m_position.x = 257.5f;
							}

							m_SMR[i][j]->SetPosition(m_position);
						}
					}
					Masu = 25;
				}
			}
			return true;
		});
	QueryGOs<GameManager>("GameManager", [&](GameManager* m_Manager)->bool
		{
			if (m_Manager->m_scale == 4.0f)
			{
				if (Pad(0).IsPress(enButtonB))
				{
					Delete = true;
				}
			}
			return  true;
		});
	if (m_position.y <= -10000.0f)
	{
		DeleteGO(this);
	}
	if (Delete)
	{
		m_position.y -= 10.0f;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				m_SMR[i][j]->SetPosition(m_position);
			}
		}
	}
}