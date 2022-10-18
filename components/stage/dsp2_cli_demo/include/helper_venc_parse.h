#ifndef __HELPER_VENC_PARSE_H__
#define __HELPER_VENC_PARSE_H__

typedef enum {
    VENC_PARSE_READ = 0,
    VENC_PARSE_WRITE,
    VENC_PARSE_DUMP,
    VENC_PARSE_LOAD,
} VENC_PARSE_TYPE;

void setChnId(int chnid);
int parse_venc_cmd(char* module, char* argv_reg, char* argv_val, int payload_len_in, char* ret_string);

#endif /* __HELPER_VENC_PARSE_H__ */

