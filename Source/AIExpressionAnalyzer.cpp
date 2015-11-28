#include "../PreInclude.h"
#include "../Include/AIExpressionAnalyzer.h"
#include "../Include/AIBrain.h"
#include "../Include/IAIGlobalFunc.h"


using namespace std;


AISYSTEM_SPACE_BEGIN

CExpressionAnalyzer::CExpressionAnalyzer(void)
{
}

CExpressionAnalyzer::~CExpressionAnalyzer(void)
{
}


/*  
@	���ܣ�	��ʼ��
@	������	
@	����ֵ��
@	ע��	
*/
void CExpressionAnalyzer::Init( void )
{
	// ��ʼ�����������ȼ�
	memset( m_iOptPriority, 9999, sizeof( m_iOptPriority ) );
	m_iOptPriority[EToken_Not]			= 1;
	m_iOptPriority[EToken_Neg]			= 1;
	m_iOptPriority[EToken_Mul]			= 2;
	m_iOptPriority[EToken_Div]			= 2;
	m_iOptPriority[EToken_Add]			= 3;
	m_iOptPriority[EToken_Sub]			= 4;
	m_iOptPriority[EToken_Equal]		= 5;
	m_iOptPriority[EToken_NotEqual]		= 5;
	m_iOptPriority[EToken_Less]			= 5;
	m_iOptPriority[EToken_Greater]		= 5;
	m_iOptPriority[EToken_LessEqual]	= 5;
	m_iOptPriority[EToken_GreaterEqual]	= 5;
	m_iOptPriority[EToken_And]			= 6;
	m_iOptPriority[EToken_Or]			= 7;
	m_iOptPriority[EToken_BracketClose] = 8;
	m_iOptPriority[EToken_BracketOpen]	= 8;
}

/*  
@	���ܣ�	�������ʽ�ַ��������ر��ʽ
@	������	lpszString:	Ҫ�����ı��ʽ�ַ���
@	����ֵ�����ʽָ��
@	ע��	
*/
CExpression *CExpressionAnalyzer::Analyse( const TLexTokens & allTokens, CAIBrain *pBrain, const char *lpszString /*= NULL*/ )
{
	int nTokens = (int)allTokens.size();

	// ���δ����ջ�����������ƥ��
	int nBracket = 0;
	CStack<CExpToken> ExpTokens;
	for( int i = nTokens-1; i >= 0; -- i )
	{
		static CExpToken token;
		token.m_bIsExp = false;
		token.m_pExp = NULL;
		token.m_Token = allTokens[i];

		if( token.m_Token.m_eTokenType == EToken_BracketOpen )
			++ nBracket;
		if( token.m_Token.m_eTokenType == EToken_BracketClose )
			-- nBracket;

		ExpTokens.Push( token );
	}
	// ���Ų�ƥ��
	if( nBracket != 0 )
	{
		OutPutErrorMsg( "���ʽ�Ƿ���( ���Ų�ƥ�� )" );
		return NULL;
	}

	CStack<CExpToken>	TokenStack;

	CExpToken curToken;
	CExpToken nextToken;
	CExpToken topToken;
	bool bHasNext = false;
	bool bHasTop = false;

	// ����ֻ��һ�������������
	if( ExpTokens.Size() == 1 )
	{
		curToken = ExpTokens.Pop();
		if( IsOptTarget( curToken.m_Token.m_eTokenType ) )
		{
			topToken.m_bIsExp = false;
			topToken.m_pExp = NULL;
			topToken.m_Token.m_eTokenType = EToken_And;
			topToken.m_Token.m_strTokenString = "&&";
			return BuildExpression( topToken, curToken, curToken, pBrain );
		}
	}

	// ��ʼ����
	while( true )
	{
		// ��ǰ���ڴ���ļǺ�
		curToken = ExpTokens.Pop();
		// ��һ��Ҫ����ļǺ�
		if( ExpTokens.Empty() )
			bHasNext = false;
		else
		{
			nextToken = ExpTokens.Pop();
			bHasNext = true;
		}
		// ջ���ļǺ�
		if( TokenStack.Empty() )
			bHasTop = false;
		else
		{
			bHasTop = true;
			topToken = TokenStack.Pop();
		}

		// ���δ����ջ�ʹ���ջ�����ˣ��򷵻ص�ǰ�Ǻŵı��ʽ
		if( !bHasTop && !bHasNext )
		{
			if( !curToken.m_bIsExp )
			{
				OutPutErrorMsg( "���ʽ�Ƿ���( %s )", lpszString );
				Clear();
				return NULL;		
			}
			return curToken.m_pExp;
		}

		// ���ջ��û�еĻ���ֱ�ӷ���ջ��
		if( ! bHasTop )
		{
			TokenStack.Push( curToken );
			if( bHasNext )
				ExpTokens.Push( nextToken );
			continue;
		}

		// �����ǰ������ǲ�������ֱ�ӷ���ջ��
		if( ! curToken.m_bIsExp && IsOpt( curToken.m_Token.m_eTokenType ) )
		{
			if( bHasTop )
				TokenStack.Push( topToken );
			TokenStack.Push( curToken );
			if( bHasNext )
				ExpTokens.Push( nextToken );
			continue;
		}

		// ����������ţ�ֱ�ӷ���ջ��
		if( curToken.m_Token.m_eTokenType == EToken_BracketOpen )
		{
			if( bHasTop )
				TokenStack.Push( topToken );
			TokenStack.Push( curToken );
			if( bHasNext )
				ExpTokens.Push( nextToken );
			continue;
		}

		// ���ջ���������ţ���һ���������ţ���ȥ������
		if( topToken.m_Token.m_eTokenType == EToken_BracketOpen && nextToken.m_Token.m_eTokenType == EToken_BracketClose )
		{
			ExpTokens.Push( curToken );
			continue;
		}

		// ���ջ���������ţ�ֱ�ӷ���ջ��
		if( topToken.m_Token.m_eTokenType == EToken_BracketOpen )
		{
			if( bHasTop )
				TokenStack.Push( topToken );
			TokenStack.Push( curToken );
			if( bHasNext )
				ExpTokens.Push( nextToken );
			continue;
		}

		// ����ǲ��������߱��ʽ�Ļ�
		if( curToken.m_bIsExp || IsOptTarget( curToken.m_Token.m_eTokenType ) )
		{
			// ���ջ���ǿ��Ҳ��������������ʧ��
			if( bHasTop && ! topToken.m_bIsExp && ! IsOpt( topToken.m_Token.m_eTokenType ) )
			{
				OutPutErrorMsg( "���ʽ�Ƿ���( %s )", lpszString );
				Clear();
				return NULL;
			}

			// �����һ���ǿ��Ҳ��������������ʧ��
			if( bHasNext && ! nextToken.m_bIsExp && ! IsOpt( nextToken.m_Token.m_eTokenType ) )
			{
				OutPutErrorMsg( "���ʽ�Ƿ���( %s )", lpszString );
				Clear();
				return NULL;
			}

			// ����ջ���� - �ţ����⴦��һ��
			// ���ջ������һ�������ǲ��������߱��ʽ�Ļ�������˫Ŀ�ļ���
			// �������һ����Ŀ�ĸ���
			if( topToken.m_Token.m_eTokenType == EToken_Sub )
			{
				if( TokenStack.Empty() )
					topToken.m_Token.m_eTokenType = EToken_Neg;
				else
				{
					CExpToken token = TokenStack.Top();
					if( !( token.m_bIsExp || !token.m_bIsExp && IsOptTarget( token.m_Token.m_eTokenType ) ) )
						topToken.m_Token.m_eTokenType = EToken_Neg;
				}
			}

			// ���ջ����һ����Ŀ�������������ʽ
			if( IsSingleOpt( topToken.m_Token.m_eTokenType) )
			{
				if( bHasNext )
					ExpTokens.Push( nextToken );
				CExpToken Exp;
				Exp.m_bIsExp = true;
				Exp.m_pExp = BuildExpression( topToken, curToken, pBrain );
				if( NULL == Exp.m_pExp )
				{
					OutPutErrorMsg( "���ʽ�Ƿ���( %s )", lpszString );
					Clear();
					return NULL;
				}
				ExpTokens.Push( Exp );
				continue;
			}

			// ���ջ����һ��˫Ŀ�����������һ����������ȼ���������������ʽ
			if( IsCoupleOpt( topToken.m_Token.m_eTokenType ) )
			{
				if(  ( ! nextToken.m_bIsExp && m_iOptPriority[topToken.m_Token.m_eTokenType] <= m_iOptPriority[nextToken.m_Token.m_eTokenType] )
					|| nextToken.m_bIsExp )
				{
					if( TokenStack.Empty() )
					{
						OutPutErrorMsg( "���ʽ�Ƿ���( %s )", lpszString );
						Clear();
						return NULL;
					}
					if( bHasNext )
						ExpTokens.Push( nextToken );
					CExpToken Left, Exp;
					Left = TokenStack.Pop();
					Exp.m_bIsExp = true;
					Exp.m_pExp = BuildExpression( topToken, Left, curToken, pBrain );
					if( NULL == Exp.m_pExp )
					{
						OutPutErrorMsg( "���ʽ�Ƿ���( %s )", lpszString );
						Clear();
						return NULL;
					}
					ExpTokens.Push( Exp );
					continue;
				}
				// ����Ĳ����������ȼ�����ǰ��ģ���ջ
				else
				{
					if( bHasTop )
						TokenStack.Push( topToken );
					TokenStack.Push( curToken );
					if( bHasNext )
						ExpTokens.Push( nextToken );
					continue;
				}
			}

			// ����������Ǵ����
			OutPutErrorMsg( "���ʽ�Ƿ���( %s )", lpszString );
			Clear();
			return NULL;

		}

	}
	return NULL;
}

/*  
@	���ܣ�	�������
@	������	
@	����ֵ��
@	ע��	�������ʧ�ܣ�����Ҫ���������һЩ����
*/
void CExpressionAnalyzer::Clear( void )
{
	CExpression* pExp = NULL;
	for( int i = 0; i < (int)m_pAllExpression.size(); ++ i )
	{
		pExp = m_pAllExpression[i];
		if( pExp )
			delete pExp;
	}
	m_pAllExpression.clear();
}

/*  
@	���ܣ�	����һ�����ʽ	��Ŀ
@	������	Opt:	���������ʽ����
			right:	�Ҳ��������ʽ����
@	����ֵ�������ı��ʽ��ָ��
@	ע��	
*/
CExpression *CExpressionAnalyzer::BuildExpression(const CExpToken &Opt, const CExpToken &right, CAIBrain *pBrain )
{
	CExpression *pNewExp = new CExpression;

	switch( Opt.m_Token.m_eTokenType )
	{
	case EToken_Not:	
		pNewExp->m_eOptType = EOptType_Not;
		pNewExp->m_strExp = "!";
		break;

	case EToken_Neg:	
		pNewExp->m_eOptType = EOptType_Neg;
		pNewExp->m_strExp = "-";
		break;
	default:
		delete pNewExp;	
		OutPutErrorMsg( "���ʽ�Ƿ� ������" );
		return NULL;
	}		

	double dValue = 0;

	if( right.m_bIsExp )
	{
		pNewExp->m_RData.m_eType = EDataType_Expression;
		pNewExp->m_strExp += "Exp";
		pNewExp->m_RData.m_Data.m_pExpression = right.m_pExp;
		EraseExpression( right.m_pExp );
	}
	else if( right.m_Token.m_eTokenType == EToken_Identifier )
	{
		if( pBrain )
		{
			pNewExp->m_RData.m_eType = EDataType_Property;
			pNewExp->m_RData.m_Data.m_pProperty = pBrain->FindProperty( right.m_Token.m_strTokenString );
			if( NULL == pNewExp->m_RData.m_Data.m_pProperty )
			{
				delete pNewExp;
				OutPutErrorMsg( "���ʽ�Ƿ��� ���Բ����� %s ", right.m_Token.m_strTokenString.c_str() );
				return NULL;
			}
		}
	}
	else
	{
		dValue = atof( right.m_Token.m_strTokenString.c_str() );
		pNewExp->m_strExp += right.m_Token.m_strTokenString;

		switch( right.m_Token.m_eTokenType )
		{
		case EToken_Float:
			pNewExp->m_RData.m_eType = EDataType_Float;
			pNewExp->m_RData.m_Data.m_fData = (float)dValue;
			break;

		case EToken_Int:
		case EToken_Long:
			pNewExp->m_RData.m_eType = EDataType_Long;
			pNewExp->m_RData.m_Data.m_lData = (long)dValue;
			break;

		case EToken_UnsignedInt:
		case EToken_UnsignedLong:
			pNewExp->m_RData.m_eType = EDataType_UnsignedLong;
			pNewExp->m_RData.m_Data.m_ulData = (unsigned long )dValue;
			break;

		default:
			delete pNewExp;
			OutPutErrorMsg( "���ʽ�Ƿ��� �޷�ʶ�����������" );
			return NULL;
		}
	}

	m_pAllExpression.push_back( pNewExp );
	return pNewExp;
}

/*  
@	���ܣ�	����һ�����ʽ  ˫Ŀ
@	������	Opt:	���������ʽ����
			left:	����������ʽ����
			right:	�Ҳ��������ʽ����
@	����ֵ�������ı��ʽ��ָ��
@	ע��	
*/
CExpression *CExpressionAnalyzer::BuildExpression(const CExpToken &Opt, const CExpToken &left, const CExpToken &right, CAIBrain *pBrain )
{
	CExpression *pNewExp = new CExpression;

	double dValue;

	// �������
	if( left.m_bIsExp )
	{
		pNewExp->m_LData.m_eType = EDataType_Expression;
		pNewExp->m_LData.m_Data.m_pExpression = left.m_pExp;
		pNewExp->m_strExp = "Exp";
		EraseExpression( left.m_pExp );
	}
	else if( left.m_Token.m_eTokenType == EToken_Identifier )
	{
		if( pBrain )
		{
			pNewExp->m_LData.m_eType = EDataType_Property;
			pNewExp->m_LData.m_Data.m_pProperty = pBrain->FindProperty( left.m_Token.m_strTokenString );
			if( NULL == pNewExp->m_LData.m_Data.m_pProperty )
			{
				delete pNewExp;
				OutPutErrorMsg( "���ʽ�Ƿ��� ���Բ����� %s ", left.m_Token.m_strTokenString.c_str() );
				return NULL;
			}
		}
	}
	else
	{
		dValue = atof( left.m_Token.m_strTokenString.c_str() );
		pNewExp->m_strExp = left.m_Token.m_strTokenString;

		switch( left.m_Token.m_eTokenType )
		{
		case EToken_Float:
			pNewExp->m_LData.m_eType = EDataType_Float;
			pNewExp->m_LData.m_Data.m_fData = (float)dValue;
			break;

		case EToken_Int:
		case EToken_Long:
			pNewExp->m_LData.m_eType = EDataType_Long;
			pNewExp->m_LData.m_Data.m_lData = (long)dValue;
			break;

		case EToken_UnsignedInt:
		case EToken_UnsignedLong:
			pNewExp->m_LData.m_eType = EDataType_UnsignedLong;
			pNewExp->m_LData.m_Data.m_ulData = (unsigned long )dValue;
			break;

		default:
			delete pNewExp;
			OutPutErrorMsg( "���ʽ�Ƿ��� �޷�ʶ�����������" );
			return NULL;
		}
	}


	switch( Opt.m_Token.m_eTokenType )
	{
	case EToken_And:
		pNewExp->m_eOptType = EOptType_And;
		pNewExp->m_strExp += "&&";
		break;
	case EToken_Or:
		pNewExp->m_eOptType = EOptType_Or;
		pNewExp->m_strExp += "||";
		break;
	case EToken_Equal:
		pNewExp->m_eOptType = EOptType_Equal;
		pNewExp->m_strExp += "==";
		break;
	case EToken_NotEqual:
		pNewExp->m_eOptType = EOptType_NotEqual;
		pNewExp->m_strExp += "!=";
		break;
	case EToken_Less:
		pNewExp->m_eOptType = EOptType_Less;
		pNewExp->m_strExp += "<";
		break;
	case EToken_Greater:
		pNewExp->m_eOptType = EOptType_Greater;
		pNewExp->m_strExp += ">";
		break;
	case EToken_LessEqual:
		pNewExp->m_eOptType = EOptType_LessEqual;
		pNewExp->m_strExp += "<=";
		break;
	case EToken_GreaterEqual:
		pNewExp->m_eOptType = EOptType_GreaterEqual;
		pNewExp->m_strExp += ">=";
		break;
	case EToken_Add:
		pNewExp->m_eOptType = EOptType_Add;
		pNewExp->m_strExp += "+";
		break;
	case EToken_Sub:
		pNewExp->m_eOptType = EOptType_Sub;
		pNewExp->m_strExp += "-";
		break;
	case EToken_Mul:
		pNewExp->m_eOptType = EOptType_Mul;
		pNewExp->m_strExp += "*";
		break;
	case EToken_Div:
		pNewExp->m_eOptType = EOptType_Div;
		pNewExp->m_strExp += "/";
		break;

	default:
		delete pNewExp;	
		OutPutErrorMsg( "���ʽ�Ƿ� ������" );
		return NULL;
	}


	// �Ҳ�����
	if( right.m_bIsExp )
	{
		pNewExp->m_RData.m_eType = EDataType_Expression;
		pNewExp->m_RData.m_Data.m_pExpression = right.m_pExp;
		pNewExp->m_strExp += "Exp";
		EraseExpression( right.m_pExp );
	}
	else if( right.m_Token.m_eTokenType == EToken_Identifier )
	{
		if( pBrain )
		{
			pNewExp->m_RData.m_eType = EDataType_Property;
			pNewExp->m_RData.m_Data.m_pProperty = pBrain->FindProperty( right.m_Token.m_strTokenString );
			if( NULL == pNewExp->m_RData.m_Data.m_pProperty )
			{
				delete pNewExp;
				OutPutErrorMsg( "���ʽ�Ƿ��� ���Բ����� %s ", right.m_Token.m_strTokenString.c_str() );
				return NULL;
			}
		}
	}
	else
	{
		dValue = atof( right.m_Token.m_strTokenString.c_str() );
		pNewExp->m_strExp += right.m_Token.m_strTokenString;

		switch( right.m_Token.m_eTokenType )
		{
		case EToken_Float:
			pNewExp->m_RData.m_eType = EDataType_Float;
			pNewExp->m_RData.m_Data.m_fData = (float)dValue;
			break;

		case EToken_Int:
		case EToken_Long:
			pNewExp->m_RData.m_eType = EDataType_Long;
			pNewExp->m_RData.m_Data.m_lData = (long)dValue;
			break;

		case EToken_UnsignedInt:
		case EToken_UnsignedLong:
			pNewExp->m_RData.m_eType = EDataType_UnsignedLong;
			pNewExp->m_RData.m_Data.m_ulData = (unsigned long )dValue;
			break;

		default:
			delete pNewExp;
			OutPutErrorMsg( "���ʽ�Ƿ��� �޷�ʶ�����������" );
			return NULL;
		}
	}

	m_pAllExpression.push_back( pNewExp );
	return pNewExp;
}

void CExpressionAnalyzer::EraseExpression(CExpression *pExp)
{
	int size = (int)m_pAllExpression.size();
	for( int i = 0; i < size; ++ i )
	{
		if( pExp == m_pAllExpression[i] )
		{
			m_pAllExpression[i] = NULL;
			return;
		}
	}
}


AISYSTEM_SPACE_END