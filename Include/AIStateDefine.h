/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIStateDefine.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  AI״̬�����Ͷ���
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN


/****************************************************************
+	ENUM
-----------------------------------------------------------------
+	����:	���Բ�����
-----------------------------------------------------------------
*****************************************************************/
//enum EAIStateTestOperator
//{
//	EAISTestOperator_Allways = 0,	// ����ͨ��
//	EAISTestOperator_Never,			// ��ԶΪ��
//	EAISTestOperator_Less,			// С��
//	EAISTestOperator_Greate,		// ����
//	EAISTestOperator_Equal,			// ����
//	EAISTestOperator_LessEqual,		// С�ڵ���
//	EAISTestOperator_GreateEqual,	// ���ڵ���
//	EAISTestOperator_NotEqual,		// ������
//	EAISTestOperator_Inner,			// �ڷ�Χ��
//	EAISTestOperator_Outter,		// �ڷ�Χ�� 
//	EAISTestOperator_End
//};


/****************************************************************
+	ENUM
-----------------------------------------------------------------
+	����:	״̬������״̬
-----------------------------------------------------------------
*****************************************************************/
enum EStateMachineState
{
	ESMachineState_Stopped = 0,	// ֹͣ״̬
	ESMachineState_Running,		// ����״̬
	ESMachineState_Sleeping,	// ����״̬
	ESMachineState_End
};




/*  
@	���ܣ�	��һ��������ת����DWORD���洢
@	������	fValue:	Ҫת���ĸ�����
@	����ֵ��ת�����DWORD��
@	ע��	
*/
inline DWORD F2DW( float fValue )
{
	return *((DWORD*)&fValue);
}

/*  
@	���ܣ�	��һ�����ض����ŷָ��������ַ���ת������������
@	������	vecNumbers:	��ȡ�������������� 
			strNumbers:	�����ַ���
			cSeparate:	�ָ���
@	����ֵ�����ط������������ֵĸ���
@	ע��	
*/
int Parse2Floats( std::vector<float> & vecNumbers, const std::string & strNumbers, char cSeparate = ',' );

int Parse2Strings( std::vector<std::string> &vecStrs, const std::string & strString, char cDeli = ',' );

bool IsNumeric( const std::string &str );


AISYSTEM_SPACE_END