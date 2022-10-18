#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <timers.h>
#include <aos/kernel.h>
#include <aos/yloop.h>
#include <lwip/mem.h>
#include <lwip/memp.h>
#include <lwip/dhcp.h>
#include <lwip/tcpip.h>
#include <lwip/ip_addr.h>
#include <lwip/netifapi.h>
#include <lwip/sockets.h>
#include <lwip/netdb.h>
#include <lwip/tcp.h>
#include <lwip/err.h>

#include <cli.h>
#include <wifi_mgmr_ext.h>

#include <vfs_err.h>
#include <vfs_register.h>
#include <vfs.h>
#include <hal/soc/uart.h>

#include <device/vfs_uart.h>
#include <device/vfs_spi.h>

#include <sys/fcntl.h>

#include <utils_log.h>
#include <utils_fec.h>

#include <helper_wifi.h>
#include <helper_blfdt.h>

#include <bl60x_fw_api.h>
#include <bl_uart.h>
#include <bl_romfs.h>
#include <httpd.h>

#include <bl_timer.h>
#include <bl60x_ef_ctrl.h>

void bluart_user_entry(void *arg)
{
    int length;
    uint8_t buf_recv[128];
    const char *name = arg;

    int fd = aos_open(name, 0);

    log_info("%s-> fd = %d\r\n", name, fd);

    while (1) {
        length = aos_read(fd, buf_recv, sizeof(buf_recv));
        if (length > 0) {
            log_info("%s name.length = %d:\r\n", name, length);
            aos_write(fd, buf_recv, length);
        }
        vTaskDelay(10);
    }
}

void tc_spidma_master(char *buf, int len, int argc, char **argv)
{
    int spi_dev = -1;
    int i;
    int a = 0, b = 0;

    uint8_t *pbuf0_tx = NULL;
    uint8_t *pbuf0_rx = NULL;
    struct spi_ioc_transfer *pxfer = NULL;

    spi_dev = aos_open("/dev/spi0", 0);
    log_info("start open spi_dev = %d.\r\n", spi_dev);
    if (spi_dev < 0) {
        log_error("start open spi_dev = %d.\r\n", spi_dev);
        return;
    }

    /* setting SPI mode to 'mode 0' */
    i = IOCTL_SPI_MODE_0;
    a = aos_ioctl(spi_dev, IOCTL_SPI_IOC_WR_MODE, (unsigned long)&i);
    b = aos_ioctl(spi_dev, IOCTL_SPI_IOC_RD_MODE, (unsigned long)&i);
    if ((a != 0) || (b != 0)) {
        log_error("ERROR: SPI PORT FAIL TO SET IN MODE 0\n");
        aos_close(spi_dev);
        return;
    }

    /* setting SPI max clk (in Hz) */
    i = 250000;
    a = aos_ioctl(spi_dev, IOCTL_SPI_IOC_WR_MAX_SPEED_HZ, (unsigned long)&i);
    if (a != 0) {
        log_error("ERROR: SPI PORT FAIL TO SET SPEED\n");
        aos_close(spi_dev);
        return;
    }

    /* pxfer */
    {
        pbuf0_tx = pvPortMallocDMA(4096);
        pbuf0_rx = pvPortMallocDMA(4096);
        pxfer = pvPortMallocDMA(2 * (sizeof(struct spi_ioc_transfer)));

        if ((!pbuf0_tx) || (!pbuf0_rx) || (!pxfer)) {
            log_error("mem err.\r\n");
            return;
        }

        /* test xfer msg 1 */
        {
            memset(pbuf0_tx, 0x0f, 4096);
            for (i = 0; i < 4096; i++) {
                pbuf0_tx[i] = i;
            }
            memset(pbuf0_rx, 0x00, 4096);

            for (i = 0; i < 4; i++) {
                pxfer[0].tx_buf = (uint32_t)pbuf0_tx;
                pxfer[0].rx_buf = (uint32_t)pbuf0_rx;
                pxfer[0].len = 20;
                aos_msleep(1000);
                a = aos_ioctl(spi_dev, IOCTL_SPI_IOC_MESSAGE(1), (unsigned long)&pxfer[0]);
                if (a != 0) {
                    log_error("ERROR: SPI WRITE FAILURE\n");
                }
            }
        }
        vPortFreeDMA(pbuf0_tx);
        vPortFreeDMA(pbuf0_rx);
        vPortFreeDMA(pxfer);
    }

    aos_close(spi_dev);
}

void cmd_ipctrig(char *buf, int len, int argc, char **argv)
{
    int Int_Src_Type;
    uint32_t tmp;

    if (argc != 2) {
        log_error("arg err.\r\n");
        return;
    }

    Int_Src_Type = atoi(argv[1]);
    if ((0 > Int_Src_Type) || (15 < Int_Src_Type)) {
        log_error("Int_Src_Type = %d\r\n", Int_Src_Type);
        return;
    }

    tmp = (*((volatile uint32_t*)(0x4001C100)));
    tmp |= (1<<Int_Src_Type);

    log_info("Int_Src_Type = %d,  tmp = %ld\r\n", Int_Src_Type, tmp);

    (*((volatile uint32_t*)(0x4001C100))) = tmp;
}

void fault_test_by_div0(int value)
{
    int a = 100;

    printf("value = %d\r\n", value);

    a = a/value;

    printf("a = %d\r\n", a);
}

void cmd_fault(char *buf, int len, int argc, char **argv)
{
    int value;

    if (argc != 2) {
        log_error("arg err.\r\n");
        return;
    }

    /* bit4: DIV_0_TRP. */
    (* (volatile int *) 0xE000ED14) |= (1 << 4);    // SCB->CCR

    value = atoi(argv[1]);

    log_info("value = %d\r\n", value);

    fault_test_by_div0(value);
}



void tc_uart(char *buf, int len, int argc, char **argv)
{
    aos_task_new("bluart0_user", bluart_user_entry, "/dev/ttyS0", 2048);
    //aos_task_new("bluart1_user", bluart_user_entry, "/dev/ttyS1", 2048);
}


#include "utils_list.h"

typedef struct _task_list_pri {
    struct utils_list_hdr node;
    int fd;
    char name[32];
} task_list_pri_t;

static struct utils_list task_list;

static task_list_pri_t *g_alist = NULL;
static task_list_pri_t *g_blist = NULL;

static void demo_list_init(void)
{
    utils_list_init(&task_list);
}

static void demo_list_push(void)
{
    g_alist = pvPortMalloc(sizeof(task_list_pri_t));
    g_blist = pvPortMalloc(sizeof(task_list_pri_t));
    if ((NULL == g_alist) || (NULL == g_blist)) {
        log_error("mem error");
        return;
    }

    memset(g_alist, 0, sizeof(task_list_pri_t));
    g_alist->fd = 1;
    memcpy(g_alist->name, "listone", sizeof("listone"));
    log_info("push fd = %d, name = %s\r\n", g_alist->fd, g_alist->name);
    utils_list_push_back(&task_list, (struct utils_list_hdr *)g_alist);

    memset(g_blist, 0, sizeof(task_list_pri_t));
    g_blist->fd = 1;
    memcpy(g_blist->name, "listtwo", sizeof("listtwo"));
    log_info("push fd = %d, name = %s\r\n", g_blist->fd, g_blist->name);
    utils_list_push_back(&task_list, (struct utils_list_hdr *)g_blist);
}

static void demo_list_print(void)
{
    struct utils_list *list = &task_list;/* input */

    struct utils_list_hdr *tmp_list_hdr;
    task_list_pri_t *tmp;

    tmp_list_hdr = list->first;
    while(tmp_list_hdr != NULL) {
        tmp = (task_list_pri_t *)tmp_list_hdr;
        log_info("print fd = %d, name = %s\r\n", tmp->fd, tmp->name);
        tmp_list_hdr = tmp_list_hdr->next;
    }
}

static void demo_list_extract1(void)
{
    log_info("extract g_alist\r\n");
    utils_list_extract(&task_list, (struct utils_list_hdr *)g_alist);
}

static void demo_list_extract2(void)
{
    log_info("extract g_blist\r\n");
    utils_list_extract(&task_list, (struct utils_list_hdr *)g_alist);
}

void tc_list(char *buf, int len, int argc, char **argv)
{
    /* init */
    demo_list_init();

    /* push */
    demo_list_push();

    /* print */
    demo_list_print();

    /* extract */
    demo_list_extract1();

    /* print */
    demo_list_print();

    /* extract */
    demo_list_extract2();

    /* print */
    demo_list_print();
}

void cmd_tc_romfs(char *buf, int len, int argc, char **argv)
{
    test1_romfs();
}

void cmd_jpuart(char *buf, int len, int argc, char **argv)
{
    uint16_t i;

    while (1) {
        printf("flush_data:\r\n");
        for (i = 0; i < 100; i++) {
            printf ("%d",i);
        }
        bl_uart_flush(2);
        bl_uart_debug_early_init(9600);
        bl_uart_debug_early_init(4800);
        printf("\r\n");

        printf("noflush_data:\r\n");
        for (i = 0; i < 100; i++) {
            printf ("%d",i);
        }
        bl_uart_debug_early_init(9600);
        bl_uart_debug_early_init(4800);

        printf("\r\n");
        printf("TEST_END\r\n");

        vTaskDelay(1000);
   }
}

void cmd_tc_filename(char *buf, int len, int argc, char **argv)
{
    printf("This is file_path:%s\r\n",__FILE__);
    printf("This is filename_path:%s\r\n",__FILENAME__);
}

static void bl_timer_handler(bl_timer_id_t id, void *arg)
{
    uint32_t time_start, time_now;

    /*XXX caution: we are in the handler mode*/
    time_now = *(volatile uint32_t*)0x60B00120;
    time_start = (uint32_t)arg;
    printf("handler enter, %d, time diff %d\r\n",
            id,
            (int)time_now - (int)time_start
    );
}

static void cmd_timer_start(char *buf, int len, int argc, char **argv)
{
    void *now;

    /*start one loop timer with 1 second callback.*/
    bl_timer_init(0, BL_TIMER_TYPE_REPEAT, 1000000);
    now = (void*)*(volatile uint32_t*)0x60B00120;
    bl_timer_start(0, bl_timer_handler, now);
}

void cmd_httpd_init(char *buf, int len, int argc, char **argv)
{
    httpd_init();
}

#include <bl_https.h>
void cmd_efuse(char *buf, int len, int argc, char **argv)
{
    uint8_t mac[6];
    uint8_t capcode;
    int8_t poweroffset[14];

    if (SUCCESS == EF_Ctrl_Read_MAC_Address_Opt(mac, 1)) {
        log_info("read mac success.\r\n");
        log_buf(mac, 6);
    } else {
        log_info("read mac error.\r\n");
    }

    if (SUCCESS == EF_Ctrl_Read_CapCode(&capcode)) {
        log_info("read capcode success.\r\n");
        log_buf(&capcode, 1);
    } else {
        log_info("read capcode error.\r\n");
    }

    if (SUCCESS == EF_Ctrl_Read_PowerOffset(poweroffset)) {
        log_info("read poweroffset success.\r\n");
        log_buf(poweroffset, 14);
    } else {
        log_info("read poweroffset error.\r\n");
    }
}

void cmd_mfg(char *buf, int len, int argc, char **argv)
{
    char *cpubuf = "0mfg";
    memcpy(((char *)(0x4001F100)), cpubuf, 4);
}

void bluart_ioctl1_entry(void *arg)
{
    int res;
    char buf_recv[16];
    const char *name = arg;
    uart_ioc_waitread_t waitr_arg;
    int fd;

    fd = aos_open(name, 0);

    log_info("%s-> fd = %d\r\n", name, fd);

    while (1) {
        log_info("ready to read.\r\n");
        waitr_arg.buf = buf_recv;
        waitr_arg.read_size = sizeof(buf_recv);
        waitr_arg.timeout = 5000;
        res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRD_MODE, (unsigned long)(&waitr_arg));
        //res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRDFULL_MODE, (unsigned long)(&waitr_arg));
        if (res > 0) {
            log_info("%s name.length = %d:\r\n", name, res);
            aos_write(fd, buf_recv, res);
        }
    }
}

void bluart_ioctl2_entry(void *arg)
{
    int res;
    char buf_recv[16];
    const char *name = arg;
    uart_ioc_waitread_t waitr_arg;
    int fd;

    fd = aos_open(name, 0);

    log_info("%s-> fd = %d\r\n", name, fd);

    while (1) {
        //log_info("ready to read.\r\n");
        waitr_arg.buf = buf_recv;
        waitr_arg.read_size = sizeof(buf_recv);
        waitr_arg.timeout = 0;
        res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRD_MODE, (unsigned long)(&waitr_arg));
        //res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRDFULL_MODE, (unsigned long)(&waitr_arg));
        if (res > 0) {
            log_info("%s name.length = %d:\r\n", name, res);
            aos_write(fd, buf_recv, res);
        }
    }
}

void bluart_ioctl3_entry(void *arg)
{
    int res;
    char buf_recv[16];
    const char *name = arg;
    uart_ioc_waitread_t waitr_arg;
    int fd;

    fd = aos_open(name, 0);

    log_info("%s-> fd = %d\r\n", name, fd);

    while (1) {
        log_info("ready to read.\r\n");
        waitr_arg.buf = buf_recv;
        waitr_arg.read_size = sizeof(buf_recv);
        waitr_arg.timeout = AOS_WAIT_FOREVER;
        res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRD_MODE, (unsigned long)(&waitr_arg));
        //res = aos_ioctl(fd, IOCTL_UART_IOC_WAITRDFULL_MODE, (unsigned long)(&waitr_arg));
        if (res > 0) {
            log_info("%s name.length = %d:\r\n", name, res);
            aos_write(fd, buf_recv, res);
        }
    }
}

void cmd_tc_uart_ioctl(char *buf, int len, int argc, char **argv)
{
    if (argc != 2) {
        log_error("arg error.\r\n");
        return;
    }
    if (0 == memcmp(argv[1], "1", 1)) {
        aos_task_new("bluart_ioctl", bluart_ioctl1_entry, "/dev/ttyS0", 2048);
    } else if (0 == memcmp(argv[1], "2", 1)) {
        aos_task_new("bluart_ioctl", bluart_ioctl2_entry, "/dev/ttyS0", 2048);
    } else if (0 == memcmp(argv[1], "3", 1)) {
        aos_task_new("bluart_ioctl", bluart_ioctl3_entry, "/dev/ttyS0", 2048);
    }
}

void cmd_flushbps(char *buf, int len, int argc, char **argv)
{
    int fd;
    char test_buf1[] = "1234567890abcdefghigklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n";
    char test_buf2[] = "**************************************************************\r\n";

    fd = aos_open("/dev/ttyS0", 0);

    log_info("set 9600\r\n");
    aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 9600);

    /* use flush write. */
    log_info("use flush write.\r\n");
    aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 9600);
    aos_write(fd, test_buf1, sizeof(test_buf1));
    //aos_ioctl(fd, IOCTL_UART_IOC_FLUSH_MODE, 0);
    aos_sync(fd);
    aos_write(fd, test_buf2, sizeof(test_buf2));
    //aos_ioctl(fd, IOCTL_UART_IOC_FLUSH_MODE, 0);
    aos_sync(fd);
    aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 115200);
    aos_msleep(1000);
    aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 9600);
    aos_msleep(1000);

    /* no flush wirte */
    log_info("no flush write.\r\n");
    aos_write(fd, test_buf1, sizeof(test_buf1));
    aos_write(fd, test_buf2, sizeof(test_buf2));
    aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 115200);
    aos_msleep(1000);
    aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 9600);
    aos_msleep(1000);

    /* use 115200 */
    log_info("please change 115200\r\n");
    aos_ioctl(fd, IOCTL_UART_IOC_BAUD_MODE, 115200);
    aos_msleep(5000);
    aos_write(fd, test_buf1, sizeof(test_buf1));
    aos_write(fd, test_buf2, sizeof(test_buf2));
    log_info("end.\r\n");
}

// STATIC_CLI_CMD_ATTRIBUTE makes this(these) command(s) static
const static struct cli_command cmds_user[] STATIC_CLI_CMD_ATTRIBUTE = {
    { "tc_uart", "bl test uart", tc_uart},
    { "spitest", "tc_spidma_master", tc_spidma_master},
    { "ipctrig", "ipctrig 0~15", cmd_ipctrig},
    { "ipfault", "cmd_fault", cmd_fault},
    { "tc_list", "tc_list", tc_list},
    { "tc_romfs", "tc_romfs", cmd_tc_romfs},
    { "tc_jpuart", "tc_jpuart", cmd_jpuart},
    { "timer_start", "timer_start", cmd_timer_start},
    { "tc_httpd", "tc_httpd", cmd_httpd_init},
    { "tc_https", "tc_https", cmd_https_test},
    { "tc_efuse", "tc_efuse", cmd_efuse},
    { "tc_mfg", "tc_mfg", cmd_mfg},
    { "uartctl", "uartctl", cmd_tc_uart_ioctl},
    { "flushbps", "uartctl", cmd_flushbps},
    { "tc_filename", "tc_filename", cmd_tc_filename},
};

int helper_tc_cli_init(void)
{
    // static command(s) do NOT need to call aos_cli_register_command(s) to register.
    // However, calling aos_cli_register_command(s) here is OK but is of no effect as cmds_user are included in cmds list.
    // XXX NOTE: Calling this *empty* function is necessary to make cmds_user in this file to be kept in the final link.
    //return aos_cli_register_commands(cmds_user, sizeof(cmds_user)/sizeof(cmds_user[0]));
    return 0;
}
