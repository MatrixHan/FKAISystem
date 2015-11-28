/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIState.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ����һ��״̬
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AIStateDefine.h"


#pragma warning(disable:4251)


AISYSTEM_SPACE_BEGIN


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CState
+   ���ܣ�	��ʾ״̬����һ��״̬
+   ����:	״̬����һ��״̬��
			һ��״̬�����ɸ������������������������㴥��ʱ������һ��
			��Ϊ������������һ��״̬��
			һ��״̬�������Լ���״̬������û�д���������������ʱ����
			ִ���Լ���״̬����
-----------------------------------------------------------------
*****************************************************************/
class CAIStateMachine;
class CAITrigger;
class IAIBehavior;
class CAIBrain;
class CAIStateData;
class CAIMachineTable;
class CAIParams;
class CProperty;


class CAIState
{
	////////////////////////////////////////////
	//	��Ԫ������
public:
	friend class CAITrigger;

	////////////////////////////////////////////
	//	����/��������
public:
	CAIState( CAIStateMachine *pParent, CAIBrain *pMaster );
	~CAIState( void );

	////////////////////////////////////////////
	//	�ⲿ�ӿ�
public:

	/*  
	@	���ܣ�	����һ��״̬
	@	������	pStateData:	״̬������
	@	����ֵ���Ƿ�ɹ�
	@	ע��	
	*/
	bool Build( CAIStateData *pStateData, CAIMachineTable *pMachineTable );

	/*  
	@	���ܣ�	����״̬
	@	������	
	@	����ֵ��
	@	ע��	��һЩ��ʼ���Ĺ����������AI������AI
	*/
	void Enter( void );

	/*  
	@	���ܣ�	�뿪״̬
	@	������	
	@	����ֵ��
	@	ע��	�������Ϊ��ɾ��AI
	*/
	void Leave( void );

	/*  
	@	���ܣ�	״ִ̬��
	@	������	fElapsedTimes	:��ȥ��ʱ��
	@	����ֵ�����������״̬��ת��������һ��״̬
	@	ע��	�������е�״̬ת������������Ϊ��ִ��
	*/
	CAIState * Update( float fElapsedTimes );

	/*  
	@	���ܣ�	��ѯ״̬������
	@	������	
	@	����ֵ��״̬������
	@	ע��	
	*/
	const std::string & GetStateName( void )
	{
		return m_strName;
	}

	/*  
	@	���ܣ�	Ϊ���еĴ�����������һ��״̬
	@	������	pStateMachine:	������״̬��
	@	����ֵ���Ƿ�ɹ�
	@	ע��	
	*/
	bool LinkStates( CAIStateMachine *pMachine );

	/*  
	@	���ܣ�	ȡ�����ڵ��Ǹ�����
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	CAIBrain *GetBrain( void )	{ return m_pMaster; }

	/*  
	@	���ܣ�	�ж�ָ����Ϊ�Ƿ�����ִ��
	@	������	uiBehaviorTypeID:	��Ϊ������ID
	@	����ֵ��
	@	ע��	
	*/
	bool IsBehaviorRunning( unsigned int uiBehaviorTypeID );

	/*  
	@	���ܣ�	ǿ����ֹһ����Ϊ
	@	������	uiBehaviorTypeID:	Ҫ��ֹ����Ϊ��ID
	@	����ֵ�������ǰ״̬����ִ����Ϊ������ֹ������true�����򷵻�false
	@	ע��	
	*/
	bool StopBehavior( unsigned int uiBehaviorTypeID );


	////////////////////////////////////////////
	//	���ݳ�Ա
protected:
	CAIStateMachine				*m_pParentMachine;	// ״̬������״̬����ָ��
	std::string					m_strName;			// ״̬������
	CAIStateMachine				*m_pSubStateMachine;// ��״̬��
	std::vector<CAITrigger*>	m_pStateTriggers;	// ״̬�Ĵ�����
	CBehaviorParams				*m_pAIParams;		// ��Ϊ�Ĳ���
	IAIBehavior					*m_pBehavior;		// ��ǰ����ִ�е�AI��Ϊ
	CAIBrain					*m_pMaster;			// AI����
	std::vector<std::string>	m_strAIParams;
	std::vector<CProperty*>		m_ParamProp;
};



AISYSTEM_SPACE_END

#pragma warning(default:4251)