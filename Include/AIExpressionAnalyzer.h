/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIExpressionAnalyzer.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ������ʽ������
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AIExpressionDefine.h"

AISYSTEM_SPACE_BEGIN

class CAIBrain;



/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CExpressionAnalyzer
+   ����:	�����������ַ�����ʾ�ı��ʽ�����ؿ�ִ�б��ʽָ��
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
class CExpressionAnalyzer
{
	////////////////////////////////////////////
	//	���ݳ�Ա
private:
	int m_iOptPriority[EToken_Invalid];			// ���������ȼ���
	std::vector<CExpression*>	m_pAllExpression;	// ���д����ı��ʽ

	////////////////////////////////////////////
	//	����/����
public:
	CExpressionAnalyzer(void);
	~CExpressionAnalyzer(void);

	////////////////////////////////////////////
	//	�����ӿ�
	/*  
	@	���ܣ�	��ʼ��
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	void Init( void );

	/*  
	@	���ܣ�	�������ʽ�ַ��������ر��ʽ
	@	������	lpszString:	Ҫ�����ı��ʽ�ַ���
	@	����ֵ�����ʽָ��
	@	ע��	
	*/
	CExpression *Analyse( const TLexTokens & allTokens, CAIBrain *pBrain, const char *lpszString /*= NULL*/ );

	/*  
	@	���ܣ�	�ж�һ���Ǻ������ǲ���һ��������
	@	������	eTokenType:	�Ǻ�����
	@	����ֵ��
	@	ע��	�������ֺͱ�ʶ��
	*/
	bool IsOptTarget( EToken eTokenType )
	{
		if( ( eTokenType > EToken_NumericBegin && eTokenType < EToken_NumericEnd )
			|| eTokenType == EToken_Identifier )
			return true;
		return false;
	}

	/*  
	@	���ܣ�	�ж�һ���Ǻ������ǲ���һ��������
	@	������	eTokenType:	�Ǻ�����
	@	����ֵ��
	@	ע��	�����������߼����Ƚϡ���������
	*/
	bool IsOpt( EToken eTokenType )
	{
		if( eTokenType >= EToken_Not && eTokenType <= EToken_GreaterEqual )
			return true;
		if( eTokenType == EToken_BracketOpen || eTokenType == EToken_BracketClose )
			return true;
		if( eTokenType >= EToken_Add && eTokenType <= EToken_Div )
			return true;
		if( eTokenType == EToken_Neg )
			return true;
		return false;
	}

	/*  
	@	���ܣ�	�ж�һ���������Ǻ������ǲ���һ����Ŀ������
	@	������	eTokenType:	�Ǻ�����
	@	����ֵ��
	@	ע��	�ǣ���
	*/
	bool IsSingleOpt( EToken eTokenType )
	{
		if( IsOpt( eTokenType ) && ( eTokenType == EToken_Not || eTokenType == EToken_Neg ) )
			return true;
		return false;
	}

	/*  
	@	���ܣ�	�ж�һ���������Ǻ��ǲ���һ��˫Ŀ������
	@	������	eTokenType:	�Ǻ�����
	@	����ֵ��
	@	ע��	���˷���������еĲ���������˫Ŀ��
	*/
	bool IsCoupleOpt( EToken eTokenType )
	{
		if( IsOpt( eTokenType ) && eTokenType != EToken_Not )
			return true;
		return false;
	}

	bool IsLogicOpt( EToken eTokenType )
	{
		if( eTokenType >= EToken_Not && eTokenType <= EToken_Or )
			return true;
		return false;
	}

	bool IsRelationOpt( EToken eTokenType )
	{
		if( eTokenType >= EToken_Equal && eTokenType <= EToken_GreaterEqual )
			return true;
		return false;
	}

	bool IsArithOpt( EToken eTokenType )
	{
		if( eTokenType >= EToken_Add && eTokenType <= EToken_Div )
			return true;
		if( eTokenType == EToken_Neg )
			return true;
		return false;
	}

	/*  
	@	���ܣ�	����һ�����ʽ  ˫Ŀ
	@	������	Opt:	���������ʽ����
				left:	����������ʽ����
				right:	�Ҳ��������ʽ����
	@	����ֵ�������ı��ʽ��ָ��
	@	ע��	
	*/
	CExpression *BuildExpression( const CExpToken &Opt, const CExpToken &left, const CExpToken & right, CAIBrain *pBrain );

	/*  
	@	���ܣ�	����һ�����ʽ	��Ŀ
	@	������	Opt:	���������ʽ����
				right:	�Ҳ��������ʽ����
	@	����ֵ�������ı��ʽ��ָ��
	@	ע��	
	*/
	CExpression *BuildExpression( const CExpToken &Opt, const CExpToken &right, CAIBrain *pBrain );

	/*  
	@	���ܣ�	�������
	@	������	
	@	����ֵ��
	@	ע��	�������ʧ�ܣ�����Ҫ���������һЩ����
	*/
	void Clear( );

	void EraseExpression( CExpression *pExp );
	
};



AISYSTEM_SPACE_END