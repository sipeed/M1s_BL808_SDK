#ifndef __MM_SYSTEM_H__
#define __MM_SYSTEM_H__

int MM_System_Init(void);
int MM_System_Bind(int frmSrcChnID, int encChnID);
int MM_System_UnBind(int frmSrcChnID, int encChnID);

#endif /* __MM_SYSTEM_H__ */
