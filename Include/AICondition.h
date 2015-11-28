/********************************************************************
// FileName: d:\work\FKAISystem\Include\AICondition.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ��������������
*********************************************************************/

//#pragma once

//--------------------------------------------------------------------
//
//#include "AIStateDefine.h"
//
//
//AISYSTEM_SPACE_BEGIN
//
//class CProperty;
//
//
//
///****************************************************************
//+	CLASS
//-----------------------------------------------------------------
//+   ����:	CAICondition
//+   ����:	�����࣬ʵ���ж�����
//+   ����:	
//-----------------------------------------------------------------
//*****************************************************************/
//class CAICondition
//{
//	enum ERefType
//	{
//		ERT_Dword = 0,
//		ERT_Float,
//		ERT_Int,
//		ERT_Property,
//		ERT_End
//	};
//	union URefData
//	{
//		DWORD		m_dwData;
//		float		m_fData;
//		int			m_iData;
//		CProperty	*m_pProperty;
//	};
//
//	////////////////////////////////////////////
//	//	���ݳ�Ա
//private:
//	CProperty				*m_pProperty;	// ����������
//	EAIStateTestOperator	m_eOpType;		// ���Բ�������
//	URefData				m_RefData[2];	// �ο�����
//	ERefType				m_eRefType[2];	// �������ݵ�����
//
//	typedef bool (CAICondition::*CompFunc)(void);
//	static CompFunc		s_CompFunc[EAISTestOperator_End];			// ���Ժ���ָ������
//
//	////////////////////////////////////////////
//	//	����/����
//public:
//	CAICondition( void );
//	~CAICondition( void );
//
//
//	////////////////////////////////////////////
//	//	�����ӿ�
//public:
//	/*  
//	@	���ܣ�	��������
//	@	������	fElapsedTimes:	��ȥ��ʱ��
//	@	����ֵ���Ƿ����
//	@	ע��	
//	*/
//	bool Test( float fElapsedTimes );
//
//	/*  
//	@	���ܣ�	���������Ƚϲ���
//	@	������	pProperty:	����
//				eOpType:	��������
//				fRefValue0:	���Բο�ֵ0
//				fRefValue1:	���Բο�ֵ1
//	@	����ֵ��
//	@	ע��	
//	*/
//	void SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, DWORD fRefValue0, DWORD fRefValue1 = 0 );
//
//	/*  
//	@	���ܣ�	���������Ƚϲ���
//	@	������	pProperty:	����
//				eOpType:	��������
//				fRefValue0:	���Բο�ֵ0
//				fRefValue1:	���Բο�ֵ1
//	@	����ֵ��
//	@	ע��	
//	*/
//	void SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, float fRefValue0, float fRefValue1 = .0f );
//
//	/*  
//	@	���ܣ�	���������Ƚϲ���
//	@	������	pProperty:		����
//				eOpType:		��������
//				pRefProperty:	�ο�����
//	@	����ֵ��
//	@	ע��	
//	*/
//	void SetParam( CProperty *pProperty, EAIStateTestOperator eOpType, CProperty *pRefProperty0, CProperty *pRefProperty1 = NULL );
//
//
//	////////////////////////////////////////////
//	//	�ڲ��ӿ�
//protected:
//
//	/*  
//	@	���ܣ�	������ԱȽϺ���
//	@	������	
//	@	����ֵ��
//	@	ע��	
//	*/
//	bool _TestAllways( void )		{ return true;	}
//	bool _TestNever( void )			{ return false;	}
//	bool _TestLess( void );		
//	bool _TestGreate( void );
//	bool _TestEqual( void );
//	bool _TestLessEqual( void );
//	bool _TestGreateEqual( void );
//	bool _TestNotEqual( void );
//	bool _TestInner( void );
//	bool _TestOutter( void );
//};
//
//
//
//AISYSTEM_SPACE_END