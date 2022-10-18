#include <stdio.h>
#include <assert.h>
#include <xram_peripheral.h>
#include <xram_peri_flash.h>
#include <xram_peri_pwm.h>
#include <xram_peri_spi.h>
#include <xram_peri_common.h>
#include <xram.h>

void xram_operation_handle()
{
    struct xram_hdr rx_hdr;
    uint32_t bytes;

    while (1) {
        bytes = XRAMRingRead(XRAM_PERI_OP_QUEUE, &rx_hdr, XRAM_MSG_HDR);
        assert(bytes == XRAM_MSG_HDR);

        switch (rx_hdr.type) {
            case XRAM_PERI_TYPE_FLASH: {
                xram_flash_operation_handle(rx_hdr.len);
                break;
            }
            case XRAM_PERI_TYPE_PWM: {
                xram_pwm_operation_handle(rx_hdr.len);
                break;
            }
            case XRAM_PERI_TYPE_SPI: {
                xram_spi_operation_handle(rx_hdr.len);
                break;
            }
            default: {
                printf("xram operate type err.\r\n");
                break;
            }
        }
    }
}
