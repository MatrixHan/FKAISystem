/********************************************************************
// FileName: d:\work\FKAISystem\Include\AITrigger.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ����������
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN

class CAIState;
class CAIStateMachine;
class IAIObject;
class CExpression;
class CAITriggerData;
class CAIBrain;



/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CAITrigger
+   ����:	AI����Ĵ�����
+   ����:	�ṩ�����Ĵ������½ӿ�
-----------------------------------------------------------------
*****************************************************************/
class CAITrigger
{
	////////////////////////////////////////////
	//	���ݳ�Ա
protected:
	CExpression		*m_pExpression;		// �������ʽ
	CAIState		*m_pParentState;	// ������״̬
	CAIState		*m_pNextState;		// ��������ʱҪ�л�������һ��״̬
	std::string		m_strNextStateName;	// ��һ��״̬������
	std::string		m_strExp;

	////////////////////////////////////////////
	//	����/����
public:
	CAITrigger( void );
	~CAITrigger( void );

	////////////////////////////////////////////
	//	�����ӿ�
public:
	/*  
	@	���ܣ�	����������
	@	������	pTriggerData:	����������
	@	����ֵ���Ƿ�ɹ�
	@	ע��	
	*/
	bool Build( CAITriggerData *pTriggerData, CAIBrain *pAIObject, CAIState *pParentState );

	/*  
	@	���ܣ�	����������
	@	������	
	@	����ֵ�����������������������true�����򷵻�false
	@	ע��	
	*/
	bool TouchOff( float fElapsedTimes );

	/*  
	@	���ܣ�	���ô�����������״̬
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void SetParentState( CAIState *pState )
	{
		m_pParentState = pState;
	}

	/*  
	@	���ܣ�	���ô�����������Ҫ��ת���ĸ�״̬
	@	������	pNextState:	��һ��״̬
	@	����ֵ��
	@	ע��	
	*/
	void SetNextState( CAIState *pNextState )
	{
		m_pNextState = pNextState;
	}

	/*  
	@	���ܣ�	
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	CAIState * GetNextState( void )	{ return m_pNextState; }

	/*  
	@	���ܣ�	��ѯ��������������
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	IAIObject * GetTriggerOwner( void );


	/*  
	@	���ܣ�	������һ��״̬
	@	������	pMachine:	������״̬��
	@	����ֵ���Ƿ�ɹ�
	@	ע��	
	*/
	bool LinkState( CAIStateMachine *pMachine );

};





AISYSTEM_SPACE_END

