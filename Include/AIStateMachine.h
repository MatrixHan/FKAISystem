/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIStateMachine.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AIStateDefine.h"


AISYSTEM_SPACE_BEGIN

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CAIStateMachine
+   ���ܣ�	״̬��
+   ����:	ÿ��AI���󶼻���һ��״̬��������������Ϊ��
����һ��״̬���Ļ��࣬ÿ�����͵Ķ���Ӧ�������Լ���״̬
�����ͣ�����״̬�������Լ���AI����
-----------------------------------------------------------------
*****************************************************************/
class CAIBrain;
class CAIMachineTable;

class CAIStateMachine
{
	////////////////////////////////////////////
	//	��Ԫ������
public:
	friend class CAIState;

	////////////////////////////////////////////
	//	����/����
public:
	CAIStateMachine( CAIBrain * pMaster );
	~CAIStateMachine(void);

	////////////////////////////////////////////
	//	�ⲿ�ӿ�
public:

	/*  
	@	���ܣ�	����״̬��
	@	������	strMachineName:			״̬��������
				strMachineTableName:	״̬���������
	@	����ֵ�������ɹ�������true�����򷵻�false
	@	ע��	�������״̬�������ñ����ҵ����״̬������������
	*/
	bool Build( const std::string & strMachineTableName, const std::string & strMachineName );

	/*  
	@	���ܣ�	����״̬��
	@	������	strMachineName:	״̬��������
				pMachineTable:	״̬�����ָ��
	@	����ֵ�������ɹ�������true�����򷵻�false
	@	ע��	�������״̬�������ñ����ҵ����״̬������������
	*/
	bool Build( CAIMachineTable *pMachineTable, const std::string & strMachineName );

	/*  
	@	���ܣ�	�������е�״̬
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	bool LinkStates( void );

	/*  
	@	���ܣ�	����״̬��
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	bool StartUp( void );

	/*  
	@	���ܣ�	ֹͣ״̬��
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	bool ShutDown( void );

	/*  
	@	���ܣ�	����״̬��
	@	������	fElapsedTimes	:��ȥ��ʱ��
	@	����ֵ��
	@	ע��	
	*/
	void Update( float fElapsedTimes );

	/*  
	@	���ܣ�	��ͣ
	@	������	
	@	����ֵ��
	@	ע��	������Ҫ����AI����ʱ����ͣ�������統û������ܿ���ʱ��������ͣ��
	*/
	void Pause( void )
	{
		m_eMachineState = ESMachineState_Sleeping;
	}

	/*  
	@	���ܣ�	�ָ�AI��ִ��
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void Resume( void )
	{
		m_eMachineState = ESMachineState_Running;
	}

	/*  
	@	���ܣ�	����һ��״̬
	@	������	strStateName:	״̬������
	@	����ֵ��״ָ̬��
	@	ע��	
	*/
	CAIState * FindState( const std::string & strStateName );

	/*  
	@	���ܣ�	������Ǹ���״̬��������״̬���ĸ�״̬
	@	������	pState:	��״ָ̬��
	@	����ֵ��
	@	ע��	
	*/
	void SetParentState( CAIState *pState )
	{
		m_pParentState = pState;
	}

	/*  
	@	���ܣ�	��ѯ״̬��������
	@	������	
	@	����ֵ��״̬����������ָ��
	@	ע��	
	*/
	CAIBrain * GetMaster( void )
	{
		return m_pMaster;
	}

	/*  
	@	���ܣ�	����״̬��������
	@	������	
	@	����ֵ��״̬����������ָ��
	@	ע��	
	*/
	void GetMaster( CAIBrain * pMaster )
	{
		m_pMaster = pMaster;
	}

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
	EStateMachineState		m_eMachineState;	// ״̬��������״̬
	CAIState				*m_pActiveState;	// ��ǰ����ִ�е�״̬
	CAIState				*m_pParentState;	// ������״̬����һ����״̬���Ļ����������ĸ�״̬
	CAIBrain				*m_pMaster;			// ״̬��������
	std::string				m_strName;			// ״̬��������
	CAIState				*m_pDefaultState;	// ״̬����Ĭ������״̬
#pragma warning(disable:4251)
	std::map<std::string,CAIState*>	m_pStates;	// ״̬
#pragma warning(default:4251)
};



AISYSTEM_SPACE_END