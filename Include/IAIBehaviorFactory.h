/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAIBehaviorFactory.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ��Ϊ���� 
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#pragma warning(disable:4251)

AISYSTEM_SPACE_BEGIN

//--------------------------------------------------------------------

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	IAIBehaviorFactory
+   ���ܣ�	AI����������AI�Ĵ�������
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
class IAIBehavior;
class CBehaviorParams;
class IAIObject;

class FKAISYSTEM_API IAIBehaviorFactory
{
	////////////////////////////////////////////
	//	�ڲ����Ͷ���
public:
	typedef IAIBehavior* (*FuncCreateBehavior)( CBehaviorParams *pBehaviorParams );	// ��Ϊ������ָ������
	typedef std::map<unsigned int,FuncCreateBehavior> TCreatorDictionary;			// ��Ϊ�ֵ�����
	static IAIBehaviorFactory *s_pFactory;

	////////////////////////////////////////////
	//	����/����
public:
	IAIBehaviorFactory(void);
	~IAIBehaviorFactory(void);

	////////////////////////////////////////////
	//	�����ӿ�
public:

	/*  
	@	���ܣ�	��ȡAI�����ľ�̬ʵ��
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	static IAIBehaviorFactory *Instance( void );

	/*  
	@	���ܣ�	��ʼ��
	@	������	
	@	����ֵ��ע�����е���Ϊ������
	@	ע��	�û���Ҫʵ���������
	*/
	virtual bool Init( void ){ return false; };

	/*  
	@	���ܣ�	����һ��AI��Ϊ
	@	������	pAIObject:		Ϊ�ĸ�AI���󴴽���Ϊ
				pBehaviorParams:��Ϊ�Ĳ���
	@	����ֵ��������AI
	@	ע��	
	*/
	IAIBehavior *CreateBehavior( IAIObject *pAIObject, CBehaviorParams *pBehaviorParams = NULL );

	/*  
	@	���ܣ�	����һ����Ϊ
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	virtual void DestoryBehavior( IAIBehavior *pBehavior ){};

	/*  
	@	���ܣ�	����һ����Ϊ����ID
	@	������	strName:	��Ϊ������
	@	����ֵ��ID
	@	ע��	
	*/
	unsigned int GenerateID( const std::string & strName );

	////////////////////////////////////////////
	//	�ڲ��ӿ�
protected:
	/*  
	@	���ܣ�	ע��һ����Ϊ������
	@	������	strName:	��Ϊ������������
				pCreator:	��Ϊ������ָ��
	@	����ֵ������Ѿ�����������������ˣ�����ʧ��
	@	ע��	
	*/
	bool _RegisterCreator( const std::string & strName, FuncCreateBehavior pCreator );

	/*  
	@	���ܣ�	ע��һ����Ϊ������
	@	������	strName:	Ҫע������Ϊ������������
	@	����ֵ��
	@	ע��	
	*/
	void _UnregisterCreator( const std::string & strName );


	////////////////////////////////////////////
	//	�ڲ��ӿ�
protected:

	////////////////////////////////////////////
	//	���ݳ�Ա
protected:
	TCreatorDictionary	m_BehaviorCreators;	// ��Ϊ������
};


//--------------------------------------------------------------------

AISYSTEM_SPACE_END


#pragma warning(default:4251)