#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cli.h>
#include "bl808_dma.h"
#include "helper_mem.h"


static DMA_Chan_Type dmaChs[]={DMA_CH0,DMA_CH1,DMA_CH2,DMA_CH3,DMA_CH4,DMA_CH5,DMA_CH6,DMA_CH7};

static DMA_Trans_Width_Type    srcTransWidth[]={DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_8BITS,
    DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_8BITS,
    DMA_TRNS_WIDTH_16BITS,DMA_TRNS_WIDTH_16BITS,DMA_TRNS_WIDTH_16BITS,DMA_TRNS_WIDTH_16BITS, DMA_TRNS_WIDTH_16BITS,
    DMA_TRNS_WIDTH_16BITS,DMA_TRNS_WIDTH_32BITS,DMA_TRNS_WIDTH_32BITS, DMA_TRNS_WIDTH_32BITS,DMA_TRNS_WIDTH_32BITS,
    DMA_TRNS_WIDTH_32BITS};

static DMA_Burst_Size_Type     srcBurstSize[]={ DMA_BURST_SIZE_1, DMA_BURST_SIZE_4, DMA_BURST_SIZE_4, DMA_BURST_SIZE_8,
    DMA_BURST_SIZE_8, DMA_BURST_SIZE_16,DMA_BURST_SIZE_16,DMA_BURST_SIZE_16, DMA_BURST_SIZE_1, DMA_BURST_SIZE_4,
    DMA_BURST_SIZE_4, DMA_BURST_SIZE_8, DMA_BURST_SIZE_8, DMA_BURST_SIZE_8, DMA_BURST_SIZE_1, DMA_BURST_SIZE_1,
    DMA_BURST_SIZE_4, DMA_BURST_SIZE_4, DMA_BURST_SIZE_4};
static uint32_t transLen[]={4, 1, 52, 53, 54, 55, 56, 68, 128, 130, 161, 1000, 1001, 1004, 1008, 4081, 4092, 4094, 4095};

static DMA_Trans_Width_Type    dstTransWidth[]={DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_32BITS,
    DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_16BITS,DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_16BITS,DMA_TRNS_WIDTH_32BITS,
    DMA_TRNS_WIDTH_16BITS,DMA_TRNS_WIDTH_16BITS,DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_16BITS, DMA_TRNS_WIDTH_8BITS,
    DMA_TRNS_WIDTH_32BITS,DMA_TRNS_WIDTH_32BITS,DMA_TRNS_WIDTH_8BITS, DMA_TRNS_WIDTH_32BITS, DMA_TRNS_WIDTH_16BITS,
    DMA_TRNS_WIDTH_8BITS};

static DMA_Burst_Size_Type     dstBurstSize[]={DMA_BURST_SIZE_1, DMA_BURST_SIZE_4, DMA_BURST_SIZE_1, DMA_BURST_SIZE_8,
    DMA_BURST_SIZE_4, DMA_BURST_SIZE_16, DMA_BURST_SIZE_8, DMA_BURST_SIZE_4, DMA_BURST_SIZE_1, DMA_BURST_SIZE_4, 
    DMA_BURST_SIZE_8, DMA_BURST_SIZE_8, DMA_BURST_SIZE_16, DMA_BURST_SIZE_4, DMA_BURST_SIZE_1, DMA_BURST_SIZE_4, 
    DMA_BURST_SIZE_4, DMA_BURST_SIZE_8, DMA_BURST_SIZE_16};


static void init_dma_cfg(DMA_Channel_Cfg_Type *chCfg)
{
    chCfg->dir = DMA_TRNS_M2M;
    chCfg->ch = DMA_CH0;
    chCfg->srcAddrInc = DMA_MINC_ENABLE;
    chCfg->destAddrInc = DMA_MINC_ENABLE;
    chCfg->srcPeriph = DMA_REQ_NONE;
    chCfg->dstPeriph = DMA_REQ_NONE;

    chCfg->srcTransfWidth = DMA_TRNS_WIDTH_32BITS;
    chCfg->dstTransfWidth = DMA_TRNS_WIDTH_32BITS;
    chCfg->srcBurstSize = DMA_BURST_SIZE_16;
    chCfg->dstBurstSize = DMA_BURST_SIZE_16;
}

static void start_dma_trans(DMA_Channel_Cfg_Type *chCfg)
{
    DMA_Enable(DMA2_ID);
    DMA_Channel_Disable(DMA2_ID, chCfg->ch);
    DMA_Channel_Init(DMA2_ID, chCfg);
    DMA_Channel_Enable(DMA2_ID, chCfg->ch);
    while (DMA_Channel_Is_Busy(DMA2_ID, chCfg->ch) == SET) {
//        aos_cli_printf("waiting for completed\r\n");
    }
}

static void init_mem(uint8_t* pSrcMem, uint8_t* pDstMem, uint32_t len)
{
    uint32_t i=0;

    memset(pSrcMem,0,len+3);
    memset(pDstMem,0,len+3);

    for(i=0;i<len;i++) {
        pSrcMem[i]=i+1;
    }

#if CPU_CA5
    dcache_clean(pSrcMem, len);
    dcache_clean(pDstMem, len);
#endif
}

static int check_mem(uint8_t *pSrcMem, uint8_t *pDstMem, uint32_t len)
{
    int i;

#if CPU_CA5
    dcache_invalid(pDstMem, len);
#endif

    for (i = 0; i < len; i++) {
        if(pSrcMem[i] != pDstMem[i]) {
            aos_cli_printf("check mem fail at 0x%p (offset %d), read 0x%02x, expect 0x%02x\r\n", 
                &pDstMem[i], i, pDstMem[i], pSrcMem[i]);
            return -1;
        }
    }

    return 0;
}

static int do_dma_copy(DMA_Channel_Cfg_Type *chCfg)
{
    /* Trans length * srcTransfWidth = total bytes */
    int nBytes = (1 << chCfg->srcTransfWidth) * chCfg->transfLength;

    aos_cli_printf("[DMA copy] ch %d, s_width %d, s_bsize %d, d_width %d, d_bsize %d, trans_len %u, total %u bytes\r\n",
        chCfg->ch,
        chCfg->srcTransfWidth,
        chCfg->srcBurstSize,
        chCfg->dstTransfWidth,
        chCfg->dstBurstSize,
        chCfg->transfLength,
        nBytes);

    init_mem((uint8_t*)(uintptr_t)chCfg->srcDmaAddr, (uint8_t*)(uintptr_t)chCfg->destDmaAddr, nBytes);
    start_dma_trans(chCfg);

    return check_mem((uint8_t*)(uintptr_t)chCfg->srcDmaAddr, (uint8_t*)(uintptr_t)chCfg->destDmaAddr, nBytes);
}

static void test_dma_all_cfg(uint8_t *pSrcMem, uint8_t *pDstMem)
{
    uint32_t i,j;
    DMA_Channel_Cfg_Type chCfg;

    init_dma_cfg(&chCfg);
    chCfg.srcDmaAddr = (uint32_t)(uintptr_t)pSrcMem;
    chCfg.destDmaAddr = (uint32_t)(uintptr_t)pDstMem;

    for(i=0; i<1/*i<sizeof(dmaChs)/sizeof(dmaChs[0])*/; i++) {
        for(j=0; j<sizeof(srcTransWidth)/sizeof(srcTransWidth[0]); j++) {
            chCfg.ch = dmaChs[i];
            chCfg.srcTransfWidth = srcTransWidth[j];
            chCfg.srcBurstSize = srcBurstSize[j];
            chCfg.dstTransfWidth = dstTransWidth[j];
            chCfg.dstBurstSize = dstBurstSize[j];
            chCfg.transfLength = transLen[j];

            if (do_dma_copy(&chCfg) != 0) {
                aos_cli_printf("test_dma_all_cfg failed!\r\n");
                BL_ABORT();
            }
        }
    }

    aos_cli_printf("test_dma_all_cfg pass!\r\n");
}

static void test_memcpy(uint8_t *pSrcMem, uint8_t *pDstMem, uint32_t nBytes)
{
    aos_cli_printf("test_memcpy start...\r\n");

    init_mem(pSrcMem, pDstMem, nBytes);

    memcpy(pDstMem, pSrcMem, nBytes);
    
    if (check_mem(pSrcMem, pDstMem, nBytes) != 0) {
        aos_cli_printf("DMA trans failed!\r\n");
        BL_ABORT();
    }

    aos_cli_printf("test_memcpy pass!\r\n");
}

static void mem_auto_test_cmd(char *buf, int len, int argc, char **argv)
{
    aos_cli_printf("[test DMA copy over VRAM]\r\n");
    test_dma_all_cfg((uint8_t *)0x70010000, (uint8_t *)0x70020000);
    aos_cli_printf("[test DMA copy over DRAM]\r\n");
    test_dma_all_cfg((uint8_t *)0x88010000, (uint8_t *)0x88020000);
    aos_cli_printf("[test memcpy over DRAM]\r\n");
    test_memcpy((uint8_t *)0x88000004, (uint8_t *)0x88200004, 0x200000);
}

static void mem_dma_cmd(char *buf, int len, int argc, char **argv)
{
    int nBytes;
    DMA_Channel_Cfg_Type chCfg;

    if (argc < 4) {
        aos_cli_printf("usage: mem_dma [srcAddr] [dstAddr] [nBytes] ([s_width] [s_bsize] [d_width] [d_bsize])\r\n");
        return;
    }

    init_dma_cfg(&chCfg);

    chCfg.srcDmaAddr = strtoul(argv[1], NULL, 16);
    chCfg.destDmaAddr = strtoul(argv[2], NULL, 16);
    nBytes = strtoul(argv[3], NULL, 16);

    if (argc > 4) {
        chCfg.srcTransfWidth = atoi(argv[4]);
    }
    if (argc > 5) {
        chCfg.srcBurstSize = atoi(argv[5]);
    }
    if (argc > 6) {
        chCfg.dstTransfWidth = atoi(argv[6]);
    }
    if (argc > 7) {
        chCfg.dstBurstSize = atoi(argv[7]);
    }

    chCfg.transfLength = nBytes / (1 << chCfg.srcTransfWidth);

    if (do_dma_copy(&chCfg) != 0) {
        aos_cli_printf("DMA cmd failed!\r\n");
        BL_ABORT();
    }

    aos_cli_printf("DMA cmd okay!\r\n");
}

static void mem_bandw_cmd(char *buf, int len, int argc, char **argv)
{
    int i, nBytes, times = 1;
    uint8_t *dstAddress, *srcAddress;
    TickType_t start_time_ms, elapse_time;

    if (argc < 4) {
        aos_cli_printf("usage: mem_bandw [srcAddr] [dstAddr] [nBytes] [times]\r\n");
        return;
    }

    srcAddress = (uint8_t *)strtoul(argv[1], NULL, 16);
    dstAddress = (uint8_t *)strtoul(argv[2], NULL, 16);
    nBytes = strtoul(argv[3], NULL, 16);
    if (argc == 5) {
        times = atoi(argv[4]);
    }

    aos_cli_printf("src addr: 0x%x\r\n", srcAddress);
    aos_cli_printf("dst addr: 0x%x\r\n", dstAddress);
    aos_cli_printf("chunk size: %d KB (0x%x)\r\n", nBytes/1024, nBytes);
    aos_cli_printf("loop times: %d\r\n", times);
    aos_cli_printf("copy start...\r\n");

    start_time_ms = xTaskGetTickCount();
    for (i = 0; i < times; i++) {
        memcpy(dstAddress, srcAddress, nBytes);
    }
    elapse_time = (xTaskGetTickCount() - start_time_ms);

    aos_cli_printf("copy done, speed is %.2f MB/s\r\n", (float)nBytes * times / elapse_time / 1000);
}

static void mem_bandw_dma_cmd(char *buf, int len, int argc, char **argv)
{
    int i, nBytes, times = 1;
    DMA_Channel_Cfg_Type chCfg;
    uint32_t dstAddress, srcAddress;
    TickType_t start_time_ms, elapse_time;

    if (argc < 4) {
        aos_cli_printf("usage: mem_bandw [srcAddr] [dstAddr] [nBytes] [times]\r\n");
        return;
    }

    srcAddress = strtoul(argv[1], NULL, 16);
    dstAddress = strtoul(argv[2], NULL, 16);
    nBytes = strtoul(argv[3], NULL, 16);
    if (argc == 5) {
        times = atoi(argv[4]);
    }

    aos_cli_printf("src addr: 0x%x\r\n", srcAddress);
    aos_cli_printf("dst addr: 0x%x\r\n", dstAddress);
    aos_cli_printf("chunk size: %d KB (0x%x)\r\n", nBytes/1024, nBytes);
    aos_cli_printf("loop times: %d\r\n", times);
    aos_cli_printf("copy start...\r\n");

    init_dma_cfg(&chCfg);

    chCfg.srcDmaAddr = srcAddress;
    chCfg.destDmaAddr = dstAddress;
    chCfg.transfLength = nBytes / (1 << chCfg.srcTransfWidth);

    aos_cli_printf("[DMA copy] ch %d, s_width %d, s_bsize %d, d_width %d, d_bsize %d, trans_len %u, total %u bytes\r\n",
        chCfg.ch,
        chCfg.srcTransfWidth,
        chCfg.srcBurstSize,
        chCfg.dstTransfWidth,
        chCfg.dstBurstSize,
        chCfg.transfLength,
        nBytes);

    start_time_ms = xTaskGetTickCount();
    for (i = 0; i < times; i++) {
        start_dma_trans(&chCfg);
    }
    elapse_time = (xTaskGetTickCount() - start_time_ms);

    aos_cli_printf("copy done, speed is %.2f MB/s\r\n", (float)nBytes * times / elapse_time / 1000);
}

const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
        { "mem_bandw", "test mem bandwidth", mem_bandw_cmd },
        { "mem_bandw_dma", "test mem bandwidth", mem_bandw_dma_cmd },
        { "mem_dma", "test dma copy", mem_dma_cmd },
        { "mem_auto_test", "auto test memory load/store", mem_auto_test_cmd },
};                                                                                   

int helper_mem_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user) / sizeof(cmds_user[0]));
    return 0;
}

