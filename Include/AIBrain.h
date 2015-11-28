/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIBrain.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ����AI����Ĵ�����,�ͻ������е�AI����Ҫ���������Ϊһ����Ա
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CAIBrain
+   ����:	AI����Ĵ���
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
class CAIStateMachine;
class CProperty;
class CPropertySet;
class IAIObject;

class CAIBrain
{
	////////////////////////////////////////////
	//	���ݳ�Ա
private:
	CPropertySet	*m_pPropertySet;	// ���Լ�
	CAIStateMachine	*m_pStateMachine;	// ״̬��
	IAIObject		*m_pAIObject;		// AI����

	int			m_eBehaviorState;	// ��ǰ����Ϊ״̬
	static int	s_eExecuting;
	static int	s_eInterrupt;
	static int	s_eFailed;
	static int	s_eSucced;

	////////////////////////////////////////////
	//	����/��������
public:
	CAIBrain( IAIObject *pAIObject );
	virtual ~CAIBrain( void );

	////////////////////////////////////////////
	//	�����ӿ�
public:
	/*  
	@	���ܣ�	���½ӿ�
	@	������	fElapsedTimes:	��ȥ��ʱ��
	@	����ֵ��
	@	ע��	����״̬��
	*/
	void Update( float fElapsedTimes );

	/*  
	@	���ܣ�	��������
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void StartUp( void );

	/*  
	@	���ܣ�	ֹͣ���ԵĹ���
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void ShutDown( void );

	/*  
	@	���ܣ�	�ô�����ͣ
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void Pause( void );

	/*  
	@	���ܣ�	�ָ����ԵĶ���
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void Resume( void );

	/*  
	@	���ܣ�	����״̬��
	@	������	strStateMachineName:	״̬��������
	@	����ֵ���Ƿ�ɹ�
	@	ע��	
	*/
	bool LoadStateMachine( const std::string strStateMachineName );

	/*  
	@	���ܣ�	ע�����ԣ�����һ��ID
	@	������	
	@	����ֵ������ID��0��ʾע��ʧ��
	@	ע��	
	*/
	unsigned long RegisterProperty( const std::string & strName, int *pValue );
	unsigned long RegisterProperty( const std::string & strName, float *pValue );
	unsigned long RegisterProperty( const std::string & strName, bool *pValue );
	unsigned long RegisterProperty( const std::string & strName, unsigned long *pValue );
	unsigned long RegisterProperty( const std::string & strName, std::string *pValue );

	/*  
	@	���ܣ�	����һ������
	@	������	strName:	���Ե�����
	@	����ֵ������ָ��
	@	ע��	
	*/
	CProperty *FindProperty( const std::string & strName );

	/*  
	@	���ܣ�	��ѯAI����
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	IAIObject *GetAIObject( void )	{ return m_pAIObject; }

	/*  
	@	���ܣ�	
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void SetCurBehaviorState( EAIBehaviorState eState )
	{
		m_eBehaviorState = (int)eState;
	}

	/*  
	@	���ܣ�	�ж�ָ����Ϊ�Ƿ�����ִ��
	@	������	strBehaviorName:	��Ϊ������
	@	����ֵ������ִ����Ϊ����true�����򷵻�false
	@	ע��	
	*/
	bool IsBehaviorRunning( const std::string &strBehaviorName );

	/*  
	@	���ܣ�	ǿ����ֹһ����Ϊ
	@	������	uiBehaviorTypeID:	Ҫ��ֹ����Ϊ��ID
	@	����ֵ�������ǰ״̬����ִ����Ϊ������ֹ������true�����򷵻�false
	@	ע��	
	*/
	bool StopBehavior( const std::string &strBehaviorName );
	
};




AISYSTEM_SPACE_END