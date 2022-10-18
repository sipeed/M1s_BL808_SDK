#include <stdio.h>
#include <xram.h>

int bl_xram_user_ring_init(void)
{
    int ret = 0;
    if (XRAMHeadInit() == -1) {
        ret = -1;
        puts("Init XRAM head failed.\r\n");
    }
    ret = XRAMRingInit();

    return ret;
}

int bl_xram_user_ring_reset(void)
{
    return XRAMRingReset(XRAM_RING_ID_RPC);
}

int bl_xram_user_ring_write(void *data, size_t len)
{
    return XRAMRingWrite(XRAM_RING_ID_RPC, data, len);
}

int bl_xram_user_ring_read(void *data, size_t len)
{
    return XRAMRingRead(XRAM_RING_ID_RPC, data, len);
}
