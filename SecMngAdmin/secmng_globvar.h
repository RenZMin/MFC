
// secmng_globvar.h
#ifndef SECMNG_GLOB_VAR_H_
#define SECMNG_GLOB_VAR_H_

#include "stdafx.h"

//����Դȫ�ֱ���
CString	g_dbSource, g_dbUser, g_dbpwd;

//��������ȫ�ֱ���
CDatabase	myDB;
CDatabase	*g_pDB = NULL;

//�����ļ�ȫ�ֱ���
CString	g_SecMngIniName = "secmngadmin.ini";

#endif