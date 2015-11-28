// TestFKAISystem.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "TestFKAISystem/stdafx.h"
#include "../Include/IAIGlobalFunc.h"
#include "Monster.h"

float                   g_fTimeFromLastFrame    = 0.0f;
float					g_fAccumTime			= 0.0f;
unsigned int			g_dwSleepTime           = 0;

void OutPut( const char* p_szInfo )
{
	std::cout << p_szInfo << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// ע�����ص�����
	FKAISystem::RegisterErrorMsgReceiver( OutPut );
	// ��ʼ��״̬����
	FKAISystem::SetStateFilesDirectory( "Bin/Data/AIScript" );


	CMonster* pMonster = new CMonster();
	pMonster->Init("״̬��������");
	for( ;; )
	{
		// ��ȡ֡���ʱ��
		static float lastTime = 0;
		lastTime = g_fAccumTime;
		g_fAccumTime = (float)timeGetTime() / 1000.0f;
		g_fTimeFromLastFrame = g_fAccumTime - lastTime;

		//���֡������
		if (g_fTimeFromLastFrame>0.2f)
			g_fTimeFromLastFrame = 0.2f;

		// ÿ֡���CPU����ʱ��
		if(g_dwSleepTime > 0) Sleep(g_dwSleepTime);

		pMonster->Update( g_fTimeFromLastFrame );
	}
	pMonster->Destory();
	return 0;
}

