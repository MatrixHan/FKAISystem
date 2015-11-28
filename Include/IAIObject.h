/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAIObject.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  AI������
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN


class CAIBrain;

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	IAIObject
+   ����:	AI����Ļ��࣬��Ϸ�����Ҫʹ��AIϵͳ������Ϸ�е�AI����
			����Ӹ�������������ʵ��ע�����Լ��ķ���
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
class FKAISYSTEM_API IAIObject
{
	////////////////////////////////////////////
	//	���ݳ�Ա
private:
	CAIBrain	*m_pAIBrain;		// ����


	////////////////////////////////////////////
	//	����/����
public:
	IAIObject( void );
	virtual ~IAIObject( void ){}

	////////////////////////////////////////////
	//	����
public:
	/*  
	@	���ܣ�	��ʼ��AIϵͳ�������������ԣ�ע������
	@	������	strStateMachineName:	״̬��������
	@	����ֵ�������ɹ��Ļ�����ȥ true
	@	ע��	
	*/
	bool InitAISystem( const std::string & strStateMachineName );

	/*  
	@	���ܣ�	����AI
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void AIUpdate( float fElapsedTimes );

	/*  
	@	���ܣ�	����AI
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void AIStartUp( void );

	/*  
	@	���ܣ�	ֹͣAI
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void AIShutDown( void );

	/*  
	@	���ܣ�	��ͣAI
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void AIPause( void );

	/*  
	@	���ܣ�	�ָ�AI������
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void AIResume( void );

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

	////////////////////////////////////////////
	//	˽�з���
protected:
	/*  
	@	���ܣ�	ע�����е�����
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	virtual void _RegisterProperties( void ) {};
};








AISYSTEM_SPACE_END