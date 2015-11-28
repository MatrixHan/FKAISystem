/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAIBehavior.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ������Ϊ����
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CAIBehabior
+   ����:	��Ϊ�Ļ���
+   ����:	
-----------------------------------------------------------------
*****************************************************************/

class IAIObject;

class FKAISYSTEM_API IAIBehavior
{
	friend class IAIBehaviorFactory;

	////////////////////////////////////////////
	//	����/��������
public:
	IAIBehavior(void);
	~IAIBehavior(void);

	////////////////////////////////////////////
	//	�ⲿ�ӿ�
public:

	/*  
	@	���ܣ�	����AI����һЩ���µĲ��ԣ��������û�ʵ�ֵĸ��·���
	@	������	fElpasedTimes:	��ȥ��ʱ��
	@	����ֵ��������Ϊ��ִ��״̬
	@	ע��	
	*/
	EAIBehaviorState RealUpdate( float fElpasedTimes );

	/*  
	@	���ܣ�	����AI������
	@	������	fElpasedTimes:	��ȥ��ʱ��
	@	����ֵ��������Ϊ��ִ��״̬
	@	ע��	����һ�����麯������Ҫ��������ʵ��
	*/
	virtual EAIBehaviorState Update( float fElpasedTimes ) = 0;

	/*  
	@	���ܣ�	������Ϊ����һЩ��Ϊ�ĳ�ʼ��
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	virtual bool OnStartUp( void ) = 0;

	/*  
	@	���ܣ�	ֹͣ��Ϊ����һЩ�ƺ���
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	virtual void OnShutDown( void ) = 0;

	/*  
	@	���ܣ�	ֹͣ��Ϊ������������ֹͣ��������ֹͣ��׼��	
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void Stop( void )
	{
		m_bStopped = true;
	}

	////////////////////////////////////////////
	//	
public:

	/*  
	@	���ܣ�	����AI������
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void SetAIType( unsigned int uiType )
	{
		m_uiAIType = uiType;
	}

	unsigned int GetAIType( )
	{
		return m_uiAIType;
	}

	/*  
	@	���ܣ�	����AI������
	@	������	pMaster:	����
	@	����ֵ��
	@	ע��	
	*/
	void SetMaster( IAIObject *pMaster )
	{
		m_pAIObject = pMaster;
	}

	IAIObject * GetMaster( void )
	{
		return m_pAIObject;
	}


	////////////////////////////////////////////
	//	���ݳ�Ա
protected:
	unsigned int	m_uiAIType;	// AI������
	IAIObject*		m_pAIObject;// AI������
	bool			m_bStopped;	// AI��ǿ����ֹ��
};

//--------------------------------------------------------------------

AISYSTEM_SPACE_END