/********************************************************************
// FileName: d:\work\FKAISystem\Include\AILexicalDefine.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  �ʷ�����Ԥ����ĳ���������������
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN


/****************************************************************
+	ENUM
-----------------------------------------------------------------	
+   ����:	�������еĴʷ�����״̬
-----------------------------------------------------------------
*****************************************************************/
enum ELexState
{
	ELexState_Start = 0,				// �ʷ�������ʼ״̬

	//--��ֵ����״̬
	ELexState_Int,						// ����ֵ״̬
	ELexState_Float,					// ����ֵ״̬

	//--��ʶ������״̬
	ELexState_Identifier,				// ��ʶ��״̬

	//--�ָ�������״̬
	ELexState_Delimiter,				// �ָ���״̬

	//--�ַ�������״̬
	ELexState_String,					// �ַ�������״̬
	ELexState_StringEscape,				// �ַ���ת�崦��״̬
	ELexState_StringEnd,				// �ַ����������״̬

	//--���������״̬
	ELexState_Operator,					// ���������״̬

	ELexState_End
};




/****************************************************************
+	ENUM
-----------------------------------------------------------------	
+   ����:	�������еļǺ�����
-----------------------------------------------------------------
*****************************************************************/
enum EToken
{
	EToken_Complete = 0,					// �������ַ�������

	//--��������
	EToken_NumericBegin,					// ��ʼ������ֵ��������
	EToken_Int,								// ��������
	EToken_Float,							// ��������
	EToken_UnsignedInt,						// �޷���������
	EToken_Long,							// ������
	EToken_UnsignedLong,					// �޷��ų�����
	EToken_NumericEnd,						// ����������ֵ��������

	//--��ʶ������
	EToken_Identifier,						// ��ʶ������

	//--�ؼ���
	EToken_KeywordBegin,					// �ؼ��ֶ��忪ʼ
	EToken_If,								// if
	EToken_Else,							// else
	EToken_Switch,							// switch
	EToken_Case,							// case
	EToken_While,							// while
	EToken_Do,								// do
	EToken_Continue,						// continue
	EToken_Break,							// break
	EToken_True,							// true
	EToken_False,							// false
	EToken_Return,							// return
	EToken_KeywordEnd,						// �ؼ��ֶ������

	//--�ָ�������
	EToken_DelimiterBegin,					// ��ʼ����ָ���
	EToken_BracketOpen,						// �����ŷָ�������
	EToken_BracketClose,					// �����ŷָ�������
	EToken_DelimiterEnd,					// ��������ָ���

	//--�ַ�������
	EToken_String,							// �ַ�������

	EToken_ArithmeticBegin,					//	��������忪ʼ
	//--���������
	EToken_Add,								// + 
	EToken_Sub,								// - 
	EToken_Mul,								// * 
	EToken_Div,								// / 
	EToken_Mod,								// % 
	EToken_Exp,								// ^ 
	EToken_Inc,								// ++
	EToken_Dec,								// --
	EToken_AssignAdd,						// +=
	EToken_AssignSub,						// -=
	EToken_AssignMul,						// *=
	EToken_AssignDiv,						// /=
	EToken_AssignMod,						// %=
	EToken_AssignExp,						// ^=
	EToken_Neg,								// ��

	//--λ����

	//--�߼������
	EToken_Not,								// �߼���
	EToken_And,								// �߼���
	EToken_Or,								// �߼���
	
	//--��ϵ�����
	EToken_Equal,							// ����
	EToken_NotEqual,						// ������
	EToken_Less,							// С��
	EToken_Greater,							// ����
	EToken_LessEqual,						// С�ڵ���
	EToken_GreaterEqual,					// ���ڵ���

	EToken_ArithmeticEnd,					// ������������

	EToken_Invalid
};


/****************************************************************
+	STRUCT
-----------------------------------------------------------------
+   ����:	STokenType
+   ����:	�Ǻ�����
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
struct STokenType
{
	char			m_szToken[32];	// �Ǻ��ַ���
	EToken			m_eTokenType;	// �Ǻ�����
	unsigned long	m_ulIdentifier;	// ��ʶ��
};




/****************************************************************
+	DEFINE
-----------------------------------------------------------------	
+   ����:	�������еķָ���
-----------------------------------------------------------------
*****************************************************************/
#define NUM_DELIMITER EToken_DelimiterEnd - EToken_DelimiterBegin - 1	// �����������
extern STokenType G_Delimiters[NUM_DELIMITER];							// �������
/*  
@	���ܣ�	�ж��ַ��ǲ���һ�������
@	������	ch:	Ҫ�жϵ��ַ�
@	����ֵ������Ƿָ�������true
@	ע��	
*/
EToken GetDelimiterType( char ch );



/****************************************************************
+	DEFINE
-----------------------------------------------------------------	
+   ����:	����ؼ��ֱ�
-----------------------------------------------------------------
*****************************************************************/
#define NUM_KEYWORDS	EToken_KeywordEnd - EToken_KeywordBegin - 1		// �ؼ��ֵ�����
extern STokenType G_Keywords[NUM_KEYWORDS];								// ���еĹؼ���

/*  
@	���ܣ�	��ʼ���ؼ��ֱ�
@	������	
@	����ֵ��
@	ע��	
*/
bool InitKeywordsTable( void );

/*  
@	���ܣ�	��ѯ�ؼ�������
@	������	lpszStr:	Ҫ��ѯ���ַ�
@	����ֵ������ַ����ǹؼ��֣�����true
@	ע��	
*/
EToken GetKeywordType( const char *lpszStr );



/****************************************************************
+	DEFINE
-----------------------------------------------------------------	
+   ����:	���������
-----------------------------------------------------------------
*****************************************************************/
#define NUM_OPT	EToken_ArithmeticEnd - EToken_ArithmeticBegin - 1		// �����������
extern STokenType G_OptTokensTable[NUM_OPT];							// �������

/*  
@	���ܣ�	��ʼ���������
@	������	
@	����ֵ��
@	ע��	
*/
bool InitOptTokensTable( void );

/*  
@	���ܣ�	ȡ�õ�ǰ�ļǺ�����
@	������	lpszToken:	�ַ���
@	����ֵ�������һ����������������ͣ����򷵻� EToken_Invalid
@	ע��	
*/
EToken GetOptTokenType( const char *lpszToken );

/*  
@	���ܣ�	�ж��ǲ���һ��������ַ�
@	������	ch:	�ַ�
@	����ֵ������ַ�����Ϊ������Ŀ�ͷ���򷵻�true�����򷵻�false
@	ע��	
*/
bool IsOptChar( char ch );


/*  
@	���ܣ�	�ж�һ����ֵ������
@	������	
@	����ֵ��
@	ע��	
*/
EToken GetIntType( const char *lpszInt );

/*  
@	���ܣ�	�ж�һ�����ݵ�����
@	������	
@	����ֵ��
@	ע��	
*/
template <typename T>
bool IsType( double dValue, T value );



AISYSTEM_SPACE_END