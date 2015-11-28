/********************************************************************
// FileName: d:\work\FKAISystem\Include\AIStateInfoManager.h
// Date:     2007/11/24
// Author:   FreeKnightDuzhi
// Comment:  
*********************************************************************/

#pragma once

//--------------------------------------------------------------------

#include "AIStateDefine.h"

#pragma warning(disable:4251)


AISYSTEM_SPACE_BEGIN


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CAITriggerData
+   ���ܣ�	�ṹ�壬���津���������ݣ��Լ�������������״̬
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
class CAITriggerData
{
	////////////////////////////////////////////
	//	���ݳ�Ա
public:
	std::string					m_strExpression;	// �������ʽ
	std::string					m_strNextStateName;	// ��������ʱ��ת����״̬������
};


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CAIStateData
+   ���ܣ�	�洢״̬����
+   ����:	
-----------------------------------------------------------------
*****************************************************************/
class CAIStateData
{
	////////////////////////////////////////////
	//	���ݳ�Ա
public:
	std::string					m_strName;	// ״̬������
	unsigned int				m_uiAIID;	// ״̬��AI����ID
	std::string					m_AIParams;	// ״̬��AI����
	std::vector<CAITriggerData>	m_Triggers;	// ״̬�Ĵ�����
	std::string					m_strSubStateMachineName;	// ��״̬������
};


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CAIMachineData
+   ���ܣ�	����һ��״̬��
+   ����:	����һ��״̬�������е�״̬
-----------------------------------------------------------------
*****************************************************************/
class CAIMachineData
{
	////////////////////////////////////////////
	//	�ⲿ�ӿ�
public:
	/*  
	@	���ܣ�	����һ��״̬
	@	������	strStateName:	״̬������
	@	����ֵ��״ָ̬��
	@	ע��	
	*/
	CAIStateData * FindState( const std::string & strStateName );

	////////////////////////////////////////////
	//	���ݳ�Ա
public:
	std::string							m_strName;			// ״̬��������
	std::string							m_strDefaultState;	// ״̬����Ĭ������״̬
	std::map<std::string,CAIStateData>	m_StateMap;			// ״̬���������е�״̬
};


/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CAIMachineTable
+   ���ܣ�	����һϵ�е�״̬��
+   ����:	ÿ��AI���״̬��������һ���ļ��
			����ౣ����ļ����������ݣ�������״̬ʱ��
-----------------------------------------------------------------
*****************************************************************/
class CAIMachineTable
{
	////////////////////////////////////////////
	//	�ⲿ�ӿ�
public:
	/*  
	@	���ܣ�	����һ��״̬��
	@	������	strMachineName:	״̬��������
	@	����ֵ�����ҵ���״̬������ָ��
	@	ע��	
	*/
	CAIMachineData * FindMachine( const std::string & strMachineName );

	////////////////////////////////////////////
	//	���ݳ�Ա
public:
	std::string								m_strName;		// ״̬���������
	std::map<std::string,CAIMachineData>	m_MachineMap;	// ״̬�����������е�״̬��
	std::string								m_strMainMachine;	// ��״̬��������
};

/****************************************************************
+	CLASS
-----------------------------------------------------------------
+   ����:	CAIStateInfoManager
+   ���ܣ�	�������е�״̬����
+   ����:	1��	ÿ��״̬������һ��AI��(��ĳ�����)��AIϵͳ��������һ��
				AI��ʱ���������ѯ��Ӧ��AIϵͳ��������״̬��
			2��	������
-----------------------------------------------------------------
*****************************************************************/
class TiXmlElement;

class CAIStateInfoManager
{
	////////////////////////////////////////////
	//	����/����
public:
	CAIStateInfoManager(void);
	~CAIStateInfoManager(void);

	////////////////////////////////////////////
	//	�ⲿ�ӿ�
public:

	/*  
	@	���ܣ�	��ø���ĵ���ʵ��
	@	������	
	@	����ֵ������ĵ���ʵ��
	@	ע��	
	*/
	static CAIStateInfoManager * Instance( void );

	/*  
	@	���ܣ�	����һ��״̬����
	@	������	strMachineName:	Ҫ���ҵ�״̬���������
	@	����ֵ��״̬����ָ�룬���û���ҵ�������NULL
	@	ע��	
	*/
	CAIMachineTable * FindMachineTable( const std::string & strMachineTableName );

	/*  
	@	���ܣ�	
	@	������	
	@	����ֵ��
	@	ע��	
	*/
	bool Initialize( void )
	{
		return _LoadInfo();
	}

	/*  
	@	���ܣ�	����״̬�������ļ���·��
	@	������	strFilePath:	·������
	@	����ֵ��
	@	ע��	
	*/
	void SetAIFileDirectory( const std::string & strFilePath );

	////////////////////////////////////////////
	//	�ڲ��ӿ�
protected:
	/*  
	@	���ܣ�	��AIĿ¼�������е�״̬��
	@	������	
	@	����ֵ���Ƿ�ɹ�
	@	ע��	
	*/
	bool _LoadInfo( void );

	/*  
	@	���ܣ�	��ָ���ļ�����һ��״̬��
	@	������	strFileName:	״̬���ļ���
	@	����ֵ���Ƿ�ɹ�
	@	ע��	
	*/
	bool _LoadInfoFromFile( const std::string & strFileName );

	/*  
	@	���ܣ�	���ļ�����һ��״̬��
	@	������	pMachine:		״̬�����ļ�����ָ��
				MachineTable:	�����״̬��������
	@	����ֵ���Ƿ�ɹ�
	@	ע��	
	*/
	bool _LoadMachine( TiXmlElement *pMachine, CAIMachineTable &MachineTable );

	/*  
	@	���ܣ�	���ļ�����һ��״̬
	@	������	pState:			״̬���ļ�����ָ��
				MachineData:	״̬���������״̬������
	@	����ֵ���Ƿ�ɹ�
	@	ע��	
	*/
	bool _LoadState( TiXmlElement *pState, CAIMachineData &MachineData );

	/*  
	@	���ܣ�	���ļ����봥����
	@	������	pTrigger:	���������ļ�����ָ��
				StateData:	״̬��������������
	@	����ֵ���Ƿ�ɹ�
	@	ע��	
	*/
	bool _LoadTrigger( TiXmlElement *pTrigger, CAIStateData &StateData );

	////////////////////////////////////////////
	//	���ݳ�Ա
private:
	std::map<std::string,CAIMachineTable>	m_MachineTableMap;	// ״̬����ı���Ϊÿ��AI�����AI�ж��״̬������һ��״̬�����������ﱣ������AI�����״̬�����Ǳ�ı���
	bool									m_bInited;			// �Ƿ��ʼ��
	std::string								m_strFilePath;		// AI�ļ�·��
};


AISYSTEM_SPACE_END


#pragma warning(default:4251)