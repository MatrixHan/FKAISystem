/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAITriggerFactory.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  �û��Զ��崥��������
*********************************************************************/

//#pragma once

//--------------------------------------------------------------------
//
//#pragma warning(disable:4251)
//
//AISYSTEM_SPACE_BEGIN
//
///****************************************************************
//+	CLASS
//-----------------------------------------------------------------
//+   ����:	IAITriggerFactory
//+   ���ܣ�	���������������� �û��Զ��崥���� �Ĵ�������
//+   ����:	
//-----------------------------------------------------------------
//*****************************************************************/
//class CAITrigger;
//class CAITriggerData;
//
//class FKAISYSTEM_API IAITriggerFactory
//{
//	////////////////////////////////////////////
//	//	���Ͷ���
//	typedef CAITrigger* (*FuncCreateTrigger)( CAICustomTriggerParams *pTriggerData );
//	typedef std::map<unsigned int,FuncCreateTrigger> TCreatorDictionary;
//
//	////////////////////////////////////////////
//	//	���ݳ�Ա
//protected:
//	TCreatorDictionary	m_TriggerCreators;	// ������������
//	unsigned int		m_uiConditionID;	// ��������������ID
//
//	////////////////////////////////////////////
//	//	����/����
//public:
//	IAITriggerFactory(void);
//	~IAITriggerFactory(void);
//
//	////////////////////////////////////////////
//	//	�����ӿ�
//public:
//
//	/*  
//	@	���ܣ�	��ȡ�����������ľ�̬ʵ��
//	@	������	
//	@	����ֵ��
//	@	ע��	
//	*/
//	static IAITriggerFactory *Instance( void );
//
//	/*  
//	@	���ܣ�	��ʼ��
//	@	������	
//	@	����ֵ��ע�����еĴ�����������
//	@	ע��	�û���Ҫʵ���������
//	*/
//	virtual bool Init( void ){ return false; };
//
//	/*  
//	@	���ܣ�	����һ��������
//	@	������	pBehaviorParams:	�������Ĳ���
//	@	����ֵ��������AI
//	@	ע��	
//	*/
//	CAITrigger *CreateTrigger( CAICustomTriggerParams *pTriggerData = NULL );
//
//	/*  
//	@	���ܣ�	����һ��������
//	@	������	pTrigger:	������ָ��
//	@	����ֵ��
//	@	ע��	
//	*/
//	virtual void DestoryTrigger( CAITrigger *pTrigger ){};
//
//	/*  
//	@	���ܣ�	����һ������������ID
//	@	������	strName:	��Ϊ������
//	@	����ֵ��ID
//	@	ע��	
//	*/
//	unsigned int GenerateID( const std::string & strName );
//
//	/*  
//	@	���ܣ�	��ѯ��������������ID
//	@	������	strName:	��������������
//	@	����ֵ��
//	@	ע��	
//	*/
//	unsigned int GetConditionTypeID( void );
//
//	////////////////////////////////////////////
//	//	�ڲ��ӿ�
//protected:
//	/*  
//	@	���ܣ�	ע��һ��������������
//	@	������	strName:	������������������
//				pCreator:	������������ָ��
//	@	����ֵ������Ѿ�����������������ˣ�����ʧ��
//	@	ע��	
//	*/
//	bool _RegisterCreator( const std::string & strName, FuncCreateTrigger pCreator );
//
//	/*  
//	@	���ܣ�	ע��һ��������������
//	@	������	strName:	Ҫע���Ĵ�����������������
//	@	����ֵ��
//	@	ע��	
//	*/
//	void _UnregisterCreator( const std::string & strName );
//
//};
//
//
//AISYSTEM_SPACE_END
//
//#pragma warning(default:4251)