
// cfg_op.h

#ifndef __CFG_OP_H__
#define __CFG_OP_H__


#ifdef  __cplusplus
extern "C" {
#endif

//获取配置项
int GetCfgItem(char *pFileName, char *pKey, char *pValue, int *pValueLen);

//写配置项 
int WriteCfgItem(char *pFileName, char *pItemName, char *pItemValue, int itemValueLen);


#ifdef  __cplusplus
}
#endif


#endif



