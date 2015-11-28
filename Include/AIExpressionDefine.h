/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIExpressionDefine.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ������ʽ�����õ���һЩ����
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AILexicalAnalyzer.h"


AISYSTEM_SPACE_BEGIN

class CExpression;
class CProperty;


/****************************************************************
+	STRUCT
-----------------------------------------------------------------
+   ����:	CExpToken
+   ����:	һ�����ʽ����
+   ����:	���б��ʽ����ʱ��������������������Ϊ��������
-----------------------------------------------------------------
*****************************************************************/
struct CExpToken
{
	bool		m_bIsExp;		// �Ƿ���һ�����ʽ
	CToken		m_Token;		// �Ǻŵ��ʡ�
	CExpression	*m_pExp;		// ���ʽ
};


/****************************************************************
+	ENUM
-----------------------------------------------------------------
+   ����:	EDataType
+   ����:	�������ʽ���������͵�ö��
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
enum EDataType
{
	EDataType_Float,		// ��������
	EDataType_Long,			// ��������
	EDataType_UnsignedLong,	// �޷��ų�������
	EDataType_Property,		// ���ԣ���ʶ��
	EDataType_Expression,	// ���ʽ
	EDataType_End
};

/****************************************************************
+	ENUM
-----------------------------------------------------------------
+   ����:	EOptType
+   ����:	�������ʽ�������͵�ö��
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
enum EOptType
{
	EOptType_Not,			// !
	EOptType_Equal,			// ==
	EOptType_NotEqual,		// !=
	EOptType_Less,			// <
	EOptType_Greater,		// >
	EOptType_LessEqual,		// <=
	EOptType_GreaterEqual,	// >=
	EOptType_And,			// &&
	EOptType_Or,			// ||
	EOptType_Add,			// +
	EOptType_Sub,			// -
	EOptType_Mul,			// *
	EOptType_Div,			// /
	EOptType_Neg,			// ��
	EOptType_End
};


/****************************************************************
+	STRUCT
-----------------------------------------------------------------
+   ����:	SData
+   ����:	�洢һ�����ʽ�Ĳ���������
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
class SData
{
	////////////////////////////////////////////
	//	���ݳ�Ա
public:
	EDataType	m_eType;				// ����������
	union UData							// ����������������
	{
		float			m_fData;		// ��������
		long			m_lData;		// ����������
		unsigned long	m_ulData;		// �޷��ų���������
		CProperty		*m_pProperty;	// ����
		CExpression		*m_pExpression;	// ���ʽ
	};
	UData		m_Data;					// ������


	////////////////////////////////////////////
	//	����/����
public:
	SData( void )
	{
		m_eType = EDataType_End;
		m_Data.m_ulData = 0;
	}
	~SData( void ){};
	void Release( void );

	////////////////////////////////////////////
	//	��������
public:

	bool CalculateLogic( void );
	double CalculateNumeric( void );

	/*  
	@	���ܣ�	�����߼������
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	bool operator !  ( );
	bool operator && ( const SData &data );
	bool operator || ( const SData &data );

	/*  
	@	���ܣ�	���رȽ������
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	bool operator == ( const SData &data );
	bool operator != ( const SData &data );
	bool operator >  ( const SData &data );
	bool operator >= ( const SData &data );
	bool operator <  ( const SData &data );
	bool operator <= ( const SData &data );

	/*  
	@	���ܣ�	�������������
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	double operator + ( const SData &data );
	double operator - ( const SData &data );
	double operator * ( const SData &data );
	double operator / ( const SData &data );
	double operator - ();

};


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CExpression
+   ����:	���ʽ����ִ�е�λ
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
class CExpression
{
	////////////////////////////////////////////
	//	��Ԫ����
	friend class CExpressionAnalyzer;

	////////////////////////////////////////////
	//	���ݳ�Ա
private:
	SData		m_LData;	// �������
	SData		m_RData;	// �Ҳ�����
	EOptType	m_eOptType;	// ��������
	std::string m_strExp;

public:
	CExpression(void);
	~CExpression(void);
	void Release( void );

	////////////////////////////////////////////
	//	�����ӿ�
public:
	/*  
	@	���ܣ�	ִ�б��ʽ
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	double operator ()();
	double Execute( void )			{ return (*this)(); }

protected:
	typedef double(CExpression::*CompFunc)(void);
	static CompFunc	s_pCompFuncs[EOptType_End];
	static bool s_CompFuncInited;

	double Not( void )			{	return !m_RData;	}
	double And( void )			{	return m_LData && m_RData;	}
	double Or( void )			{	return m_LData || m_RData;	}
	double Equal( void )		{	return m_LData == m_RData;	}
	double NotEqual( void )		{	return m_LData != m_RData;	}
	double Less( void )			{	return m_LData < m_RData;	}
	double LeeeEqual( void )	{	return m_LData <= m_RData;	}
	double Greater( void )		{	return m_LData > m_RData;	}
	double GreaterEqual( void )	{	return m_LData >= m_RData;	}
	double Add( void )			{	return m_LData + m_RData;	}
	double Sub( void )			{	return m_LData - m_RData;	}
	double Mul( void )			{	return m_LData * m_RData;	}
	double Div( void )			{	return m_LData / m_RData;	}
	double Neg( void )			{	return - m_RData;	}
};

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CStack
+   ����:	ʵ��һ��ջģ��
+   ����:	��˫�˶���ʵ��
-----------------------------------------------------------------
*****************************************************************/
template< typename T >
class CStack
{
private:
	std::deque<T>	m_Stack;	// ˫�˶���
public:
	/*  
	@	���ܣ�	��һ��Ԫ����ջ
	@	������	t:	Ҫ��ջ��Ԫ��
	@	����ֵ��
	@	ע��	
	*/
	void Push( const T & t )
	{
		m_Stack.push_back( t );
	}

	/*  
	@	���ܣ�	��ջһ��Ԫ��
	@	������	
	@	����ֵ����ջ��Ԫ��
	@	ע��	
	*/
	const T & Pop( void )
	{
		static T t;
		if( m_Stack.size() != 0 )
		{
			deque<T>::reverse_iterator iter = m_Stack.rbegin();
			t = *iter;
			m_Stack.pop_back();
		}
		return t;
	}

	/*  
	@	���ܣ�	��ѯջ��Ԫ��
	@	������	
	@	����ֵ��ջ��Ԫ��
	@	ע��	
	*/
	const T & Top( void )
	{
		static T t;
		deque<T>::reverse_iterator iter = m_Stack.rbegin();
		t = *iter;
		return t;
	}

	/*  
	@	���ܣ�	�ж�ջ�Ƿ�Ϊ��
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	bool Empty( void )
	{
		return ( (int)m_Stack.size() == 0 );
	}

	size_t Size( void )
	{
		return m_Stack.size();
	}

};


AISYSTEM_SPACE_END