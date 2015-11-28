/********************************************************************
// FileName: d:\work\FKAISystem\Include\IAIGlobalFunc.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  ������Ҫ������ȫ�ֵĺ���
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

AISYSTEM_SPACE_BEGIN

class IAIBehaviorFactory;


/*  
@	���ܣ�	����״̬�������ļ���Ŀ¼
@	������	dtrDirectory:	Ŀ¼
@	����ֵ��
@	ע��	
*/
FKAISYSTEM_FUN void SetStateFilesDirectory( const std::string & strDirectory );

/*
@	���ܣ�	������Ϊ״̬����
@	������	pFactory ��Ϊ״̬����
@	����ֵ��	
@	ע��
*/
FKAISYSTEM_FUN bool SetBehaviorFactory( IAIBehaviorFactory *pFactory );

/*
@	���ܣ�	���ô����������
@	������	�û��Զ��庯��ָ��
@	����ֵ��	
@	ע��
*/
typedef void (*AIPErrorMsgReceiver)( const char *lpszErrorMsg );
FKAISYSTEM_FUN void RegisterErrorMsgReceiver( AIPErrorMsgReceiver pFunc );

FKAISYSTEM_FUN void OutPutErrorMsg( char * format, ... );


AISYSTEM_SPACE_END