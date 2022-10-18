#include <stdio.h>
#include <string.h>
#include <sys/fcntl.h>

#include <FreeRTOS.h>
#include <task.h>

#include <helper_amr.h>
#include <aos/kernel.h>
#include <vfs.h>
#include <cli.h>
#include <mt_codectype.h>
#include <mt_amrnbenc.h>

#define DEBUG_HEADER "[HELPER] [AMR]"

void *OAL_malloc(size_t size)
{
    static int count = 0;

    printf(DEBUG_HEADER "[%d] size %d\r\n", count++, size);
    return pvPortMallocDMA(size);
}

void OAL_free(void *ptr)
{
    vPortFree(ptr);
}

static void amr_cmd(char *buf, int len, int argc, char **argv) 
{
#define AMRNB_Enc_RECOMMENDED_INBUFFSIZE      320  //The recommended input buffer size of AMR-NB decoder
#define AMRNB_Enc_RECOMMENDED_OUTBUFFSIZE      500  //The recommended output buffer size of AMR-NB decoder
    int pcm_fd;
    int amr_fd;
    unsigned int frame = 0;

    void *pvAmrnbEnc = NULL; 
    MT_S32 RetVal; //return value
    MT_AMRNBENC_CONFIGINFO EncOpenOptions;
    MT_AMRNBENC_BUFFERINFO stBufferInfo;
    MT_AMRNBENC_ENCODESIDEINFO stSideInfo;
    MT_AMRNBENC_STREAMINFO stInfo;
    MT_U8  *s8InBuf;
    MT_U8  *s8OutBuf;
    MT_S32 s32InBufSize  = AMRNB_Enc_RECOMMENDED_INBUFFSIZE;
    MT_S32 s32OutBufSize = AMRNB_Enc_RECOMMENDED_OUTBUFFSIZE;
    MT_U32 usedsize=0;
    MT_U32 outputsize=0;
    MT_U32 nLicense;
    MT_S64 s64TimeIn = -1;
    MT_S64 s64TimeOut = -1;
    uint32_t ticks, tick_start, tick_end;

    pcm_fd = aos_open("/sdcard/2.pcm", 0);
    amr_fd = aos_open("/sdcard/2.amr", O_RDWR | O_CREAT | O_TRUNC);
    if (pcm_fd < 0) {
        puts(DEBUG_HEADER " open pcm source file failed. /sdcard/2.pcm\r\n");
        return;
    }
    if (amr_fd < 0) {
        puts(DEBUG_HEADER " open amr destination file failed. /sdcard/2.pcm\r\n");
        return;
    }

    /* Set AMR decoder open options according to user */
    memset(&EncOpenOptions, 0, sizeof(EncOpenOptions));
    EncOpenOptions.u32BitRate = MT_AMRNBENC_BR122;   
    EncOpenOptions.u32EncodeQuality = MT_AMRNBENC_GOOD;
    EncOpenOptions.u32EncSpeechTrack = MT_AMRNBENC_MONO;//MT_AMRNBENC_STEREO_LEFT;//
    EncOpenOptions.u32OpenFlags = MT_AMRNBENC_USE_AMR;// MT_AMRNBENC_USE_TEST_ITU;
    EncOpenOptions.u32VadOptions =MT_AMRNBENC_VADDEFAULT;//MT_AMRNBENC_VAD1;//MT_AMRNBENC_VAD2;// 


    s8InBuf = pvPortMallocDMA(AMRNB_Enc_RECOMMENDED_INBUFFSIZE);//set the input buffer size as the recommended size
    s8OutBuf = pvPortMallocDMA(AMRNB_Enc_RECOMMENDED_OUTBUFFSIZE);//set the output buffer size as the recommended size

    if (NULL == s8InBuf || NULL == s8OutBuf) {
        printf("[AMR] no MEM\r\n");
        return;
    }

    printf("[AMR] bitrate is %d, in buffer is %p, out buffer is %p\r\n", EncOpenOptions.u32BitRate, s8InBuf, s8OutBuf);
    RetVal = MT_AMRNBENC_Create(&pvAmrnbEnc, &nLicense, &EncOpenOptions);
    if (RetVal < 0) {
        printf("[AMR] Open error!\n");
        vPortFree(s8InBuf);
        vPortFree(s8OutBuf);
        return;
    }
    printf("[AMR] pvAmrnbEnc is created @%p, licenses is %08X\r\n", pvAmrnbEnc, nLicense);
    RetVal = MT_AMRNBENC_Get(pvAmrnbEnc, MT_AMRNBENC_PROPID_BUFFERINFO, &stBufferInfo, sizeof(stBufferInfo), &nLicense);
    RetVal = MT_AMRNBENC_Get(pvAmrnbEnc, MT_AMRNBENC_PROPID_STREAMINFO, &stInfo, sizeof(stInfo), &nLicense);

    if (EncOpenOptions.u32OpenFlags == MT_AMRNBENC_USE_AMR) {
        memcpy(s8InBuf, "#!AMR\n", 6);
        aos_write(amr_fd, s8InBuf, 6);
    }

    /* Start AMR encoding */
    printf("[AMR] Start time %ld ms\r\n", (long)aos_now_ms());
    ticks = 0;
    while ((s32InBufSize = aos_read(pcm_fd, s8InBuf, AMRNB_Enc_RECOMMENDED_INBUFFSIZE)) == AMRNB_Enc_RECOMMENDED_INBUFFSIZE) {
        frame++;
        tick_start = xTaskGetTickCount();
        RetVal = MT_AMRNBENC_Encode(pvAmrnbEnc,&stSideInfo,s8InBuf,s32InBufSize,&usedsize,s64TimeIn,s8OutBuf,s32OutBufSize,&outputsize,&s64TimeOut);
        tick_end = xTaskGetTickCount();
        ticks += (((int32_t)tick_end) - ((int32_t) tick_start));
        if (outputsize == 0) {
            printf("[AMR] Break when outputsize is zero\r\n");
            break;
        }
        aos_write(amr_fd, s8OutBuf, outputsize);
    }
    printf("[AMR] End time %ld ms\r\n", (long)aos_now_ms());
    printf("[AMR] Accu ticks %lu\r\n", ticks);
    printf("[AMR] pvAmrnbEnc is %p\r\n", pvAmrnbEnc);
    printf("[AMR] frames %lu\r\n", ticks);

    /*Don't release currently*/
    RetVal=MT_AMRNBENC_Destroy(pvAmrnbEnc);
    if (RetVal < 0) {
        printf("[AMR] Close Error\n");
    }
    aos_close(pcm_fd);//close the input file
    aos_close(amr_fd);//close the output file
    vPortFree(s8InBuf);
    vPortFree(s8OutBuf);
    return;
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    {"amr", "amr encode test", amr_cmd},
};                                                                                   

int helper_amr_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));          
    return 0;
}
