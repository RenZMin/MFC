
// secmng_globvar.h
#ifndef SECMNG_GLOB_VAR_H_
#define SECMNG_GLOB_VAR_H_

#include "stdafx.h"

//数据源全局变量
CString	g_dbSource, g_dbUser, g_dbpwd;

//连接数据全局变量
CDatabase	myDB;
CDatabase	*g_pDB = NULL;

//配置文件全局变量
CString	g_SecMngIniName = "secmngadmin.ini";

#endif