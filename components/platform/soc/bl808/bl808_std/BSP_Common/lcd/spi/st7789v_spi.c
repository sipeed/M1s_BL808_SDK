#include "st7789v_spi.h"
#include "bl808_glb.h"
#include "bl808_spi.h"

#define LCD_CS_PIN                  (GLB_GPIO_PIN_12)
#define LCD_MOSI_PIN                (GLB_GPIO_PIN_25)
#define LCD_SCLK_PIN                (GLB_GPIO_PIN_19)
#define LCD_DC_PIN                  (GLB_GPIO_PIN_13)
#define LCD_BL_PIN                  (GLB_GPIO_PIN_11)
#define LCD_RST_PIN                 (GLB_GPIO_PIN_24)

#define LCD_DC_H                    GLB_GPIO_Write(LCD_DC_PIN,1) 
#define LCD_DC_L                    GLB_GPIO_Write(LCD_DC_PIN,0) 
#define LCD_BL_H                    GLB_GPIO_Write(LCD_BL_PIN,1) 
#define LCD_BL_L                    GLB_GPIO_Write(LCD_BL_PIN,0) 
#define LCD_RST_H                   GLB_GPIO_Write(LCD_RST_PIN,1) 
#define LCD_RST_L                   GLB_GPIO_Write(LCD_RST_PIN,0) 

static int lcd_gpio_init(void)
{
    GLB_GPIO_Cfg_Type cfg;

    cfg.pullType = GPIO_PULL_NONE;
    cfg.drive = 0;
    cfg.smtCtrl = 1;

    uint8_t gpiopins[] = {LCD_CS_PIN, LCD_MOSI_PIN, LCD_SCLK_PIN};
    cfg.gpioMode = GPIO_MODE_AF;
    cfg.gpioFun = GPIO_FUN_SPI1;
    for (int i = 0; i < sizeof(gpiopins)/sizeof(gpiopins[0]); i ++)
    {
        cfg.gpioPin = gpiopins[i];
        GLB_GPIO_Init(&cfg);
    }

    cfg.gpioMode = GPIO_MODE_OUTPUT;
    cfg.gpioFun = GPIO_FUN_GPIO;
    cfg.outputMode = GPIO_OUTPUT_VALUE_MODE;
    cfg.gpioPin = LCD_DC_PIN;
    GLB_GPIO_Init(&cfg);

    cfg.gpioPin = LCD_BL_PIN;
    GLB_GPIO_Init(&cfg);
    LCD_BL_H;

    cfg.gpioPin = LCD_RST_PIN;
    GLB_GPIO_Init(&cfg);

    return 0;
}

static int lcd_gpio_deinit(void)
{
	/* GPIO Init */
    GLB_GPIO_Cfg_Type cfg;
    cfg.pullType = GPIO_PULL_NONE;
    cfg.drive = 0;
    cfg.smtCtrl = 1;

    uint8_t gpiopins[] = {LCD_MOSI_PIN, LCD_SCLK_PIN, LCD_CS_PIN, LCD_DC_PIN, LCD_BL_PIN, LCD_RST_PIN};
    cfg.gpioMode = GPIO_MODE_INPUT;
    cfg.gpioFun = GPIO_FUN_GPIO;
    cfg.outputMode = GPIO_PULL_NONE;
    for (int i = 0; i < sizeof(gpiopins)/sizeof(gpiopins[0]); i ++)
    {
        cfg.gpioPin = gpiopins[i];
        GLB_GPIO_Init(&cfg);
    }
	return 0;
}

static int lcd_spi_init(int id)
{
    SPI_CFG_Type spiCfg = { 0 };
    SPI_FifoCfg_Type fifoCfg = { 0 };
    
    /* Enable spi interrupt*/
    SPI_IntMask(id, SPI_INT_ALL, MASK);
    SPI_Disable(id, SPI_WORK_MODE_MASTER);
    GLB_Set_DSP_SPI_0_ACT_MOD_Sel(GLB_SPI_PAD_ACT_AS_MASTER);
    SPI_SetClock(id, 80 * 1000 * 1000);
    /* Set SPI clock */
    SPI_ClockCfg_Type clockCfg = {
        1, /* Length of start condition */
        1, /* Length of stop condition */
        2, /* Length of data phase 0,affecting clock */
        1, /* Length of data phase 1,affecting clock */
        1  /* Length of interval between frame */
    };
    SPI_ClockConfig(id, &clockCfg);

    spiCfg.continuousEnable = 1;
    spiCfg.bitSequence = SPI_BIT_INVERSE_MSB_FIRST;
    spiCfg.byteSequence = SPI_BYTE_INVERSE_BYTE0_FIRST;
    spiCfg.clkPolarity = SPI_CLK_POLARITY_HIGH;
    spiCfg.clkPhaseInv = SPI_CLK_PHASE_INVERSE_1;
    spiCfg.frameSize = SPI_FRAME_SIZE_8;
    spiCfg.deglitchEnable = 0;

    /* SPI config */
    SPI_Init(id, &spiCfg);
    SPI_SetDeglitchCount(id, 1);

    fifoCfg.txFifoThreshold = 4;
    fifoCfg.txFifoDmaEnable = ENABLE;
    fifoCfg.rxFifoThreshold = 4;
    fifoCfg.rxFifoDmaEnable = ENABLE;

    SPI_FifoConfig(id, &fifoCfg);
    /* Enable spi master mode */
    SPI_Enable(id, SPI_WORK_MODE_MASTER);
    return 0;
}

// port
static void port_lcd_init(void)
{
    lcd_gpio_init();
    lcd_spi_init(SPI1_ID);
}

static void port_lcd_deinit(void)
{
    lcd_gpio_deinit();
}

static void port_lcd_send_cmd(uint8_t cmd)
{
    LCD_DC_L;
    SPI_SendData(SPI1_ID, &cmd, 1, SPI_TIMEOUT_ENABLE);
}

static void port_lcd_send_bytes(uint8_t *data, int len)
{
    LCD_DC_H;
    SPI_SendData(SPI1_ID, data, len, SPI_TIMEOUT_ENABLE);
}

static void port_lcd_send_byte(uint8_t data)
{
    LCD_DC_H;
    SPI_SendData(SPI1_ID, &data, 1, SPI_TIMEOUT_ENABLE);
}

static void port_lcd_send_bytes2(uint8_t *data, int len)
{
    SPI_SendData(SPI1_ID, data, len, SPI_TIMEOUT_ENABLE);
}

static void port_lcd_set_rst(int en)
{
    if (en)
        LCD_RST_H;
    else
        LCD_RST_L;
}

static void port_lcd_set_bl(int en)
{
    if (en)
        LCD_BL_H;
    else
        LCD_BL_L;
}

static void port_lcd_set_dc(int en)
{
    if (en)
        LCD_DC_H;
    else
        LCD_DC_L;
}


/***************************************************************************/
#define SOFTWARE_RESET 0x01
#define SLEEP_OFF 0x11
#define DISPALY_ON 0x29
#define HORIZONTAL_ADDRESS_SET 0x2A
#define VERTICAL_ADDRESS_SET 0x2B
#define MEMORY_WRITE 0x2C
#define PIXEL_FORMAT_SET 0x3A
#define INVERSION_DISPALY_ON 0x21
#define MEMORY_ACCESS_CTL 0x36
#define WRITE_BRIGHTNESS_CTL 0x55
#define WRITE_MIN_BRIGHTNESS 0x5E

typedef void (*callback_t)(void);
typedef struct {
    uint16_t hight;
    uint16_t width;
    uint16_t area_x;
    uint16_t area_y;
    uint16_t area_w;
    uint16_t area_h;
    volatile uint8_t is_busy;
    volatile callback_t cb;
    uint8_t dir;
} mf_lcd_private_t;
static mf_lcd_private_t private;

static struct {
    uint8_t length;
    uint8_t ms_delay;
    uint8_t data[6];
} spi_lcd_init_sequence[] = {{0x01, 0x06, {SOFTWARE_RESET}},
                             {0x01, 0x06, {SLEEP_OFF}},
                             {0x02, 0x02, {PIXEL_FORMAT_SET, 0x55}},
                             {0x01, 0x0f, {INVERSION_DISPALY_ON}},
                             {0x01, 0x00, {DISPALY_ON}},
                             {0x00, 0x00, {}}};

static void st7789v_spi_init_seq(void)
{
    port_lcd_set_rst(0);
    CPU_MTimer_Delay_US(10 * 1000);
    port_lcd_set_rst(1);
    CPU_MTimer_Delay_US(10 * 1000);

    for (uint8_t i = 0; spi_lcd_init_sequence[i].length; i++) {
        port_lcd_send_cmd(spi_lcd_init_sequence[i].data[0]);
        if (spi_lcd_init_sequence[i].length > 1) {
            port_lcd_send_bytes(spi_lcd_init_sequence[i].data + 1, spi_lcd_init_sequence[i].length - 1);
        }
        if (spi_lcd_init_sequence[i].ms_delay > 0) {
            CPU_MTimer_Delay_MS(spi_lcd_init_sequence[i].ms_delay);
        }
    }
}

static void _mf_lcd_init(void)
{
    port_lcd_init();
    st7789v_spi_init_seq();
}

/**
 * @brief Init
 *
 * @return
 */
int st7789v_spi_init(void)
{
    private.width = ST7789V_SPI_W;
    private.hight = ST7789V_SPI_H;
    private.dir = 0;
    _mf_lcd_init();
    return 0;
}

/**
 * @brief Deinit
 * @return
 */
int st7789v_spi_deinit(void)
{
    port_lcd_deinit();
    return 0;
}

void st7789v_spi_async_callback_register(void (*callback)(void)) { private.cb = callback; }

int st7789v_spi_set_dir(uint8_t dir, uint8_t mir_flag) 
{
    uint8_t data = 0x00;
    private.dir = dir;

    if(private.dir == 0){
        data = 0x00;
    }else if(private.dir == 1){
        data = 0x60;
    }

    port_lcd_send_cmd(MEMORY_ACCESS_CTL);
    port_lcd_send_bytes(&data, 1);

    return private.dir; 
}

int st7789v_spi_set_area(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
    uint8_t data[4] = {0};
    if(private.dir == 0){
        x += ST7789V_SPI_OFFSET_X;
        y += ST7789V_SPI_OFFSET_Y;
    }else if(private.dir == 1){
        x += ST7789V_SPI_OFFSET_Y;
        y += ST7789V_SPI_OFFSET_X;
    }

    data[0] = (uint8_t)(x >> 8);
    data[1] = (uint8_t)(x);
    data[2] = (uint8_t)((x + w - 1) >> 8);
    data[3] = (uint8_t)((x + w - 1));
    port_lcd_send_cmd(HORIZONTAL_ADDRESS_SET);
    port_lcd_send_bytes(data, 4);

    data[0] = (uint8_t)(y >> 8);
    data[1] = (uint8_t)(y);
    data[2] = (uint8_t)((y + h - 1) >> 8);
    data[3] = (uint8_t)((y + h - 1));
    port_lcd_send_cmd(VERTICAL_ADDRESS_SET);
    port_lcd_send_bytes(data, 4);

    port_lcd_send_cmd(MEMORY_WRITE);
    port_lcd_set_dc(1);
    return 0;
}

int st7789v_spi_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    private.is_busy = 1;
    st7789v_spi_set_area(x, y, 1, 1);
    port_lcd_send_bytes2((uint8_t *)&color, 2);
    if (private.cb) private.cb();
    private.is_busy = 0;
    return 0;
}

/**
 * @brief Lcd draw area
 * @return
 */
int st7789v_spi_draw_area(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    private.is_busy = 1;
    uint16_t w = x2 - x1 + 1;
    uint16_t h = y2 - y1 + 1;
    st7789v_spi_set_area(0, 0, w, h);
    for (int i = 0; i < w * h; i++) {
        while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPI1_BASE, SPI_FIFO_CONFIG_1), SPI_TX_FIFO_CNT) < 2)
            ;
        BL_WR_REG(SPI1_BASE, SPI_FIFO_WDATA, (color >> 8) & 0xff);
        BL_WR_REG(SPI1_BASE, SPI_FIFO_WDATA, color & 0xff);
    }
    if (private.cb) private.cb();
    private.is_busy = 0;
    return 0;
}

void st7789v_spi_draw_picture_nonblocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t *picture)
{
    private.is_busy = 1;
    uint16_t w = x2 - x1 + 1;
    uint16_t h = y2 - y1 + 1;
    st7789v_spi_set_area(x1, y1, w, h);
    port_lcd_send_bytes2((uint8_t *)picture, w * h * 2);
    if (private.cb) private.cb();
    private.is_busy = 0;
}

void st7789v_spi_draw_picture_blocking(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t *picture)
{
    private.is_busy = 1;
    uint16_t w = x2 - x1 + 1;
    uint16_t h = y2 - y1 + 1;
    st7789v_spi_set_area(x1, y1, w, h);
    port_lcd_send_bytes2((uint8_t *)picture, w * h * 2);
    if (private.cb) private.cb();
    private.is_busy = 0;
}

int st7789v_spi_draw_is_busy(void) { return private.is_busy; }

/**
 * @brief Lcd clear
 * @return
 */
int st7789v_spi_clear(uint32_t color)
{
    private.is_busy = 1;
    st7789v_spi_set_area(0, 0, private.width, private.hight);
    for (int i = 0; i < private.width * private.hight; i++) {
        while (BL_GET_REG_BITS_VAL(BL_RD_REG(SPI1_BASE, SPI_FIFO_CONFIG_1), SPI_TX_FIFO_CNT) < 2)
            ;
        BL_WR_REG(SPI1_BASE, SPI_FIFO_WDATA, (color >> 8) & 0xff);
        BL_WR_REG(SPI1_BASE, SPI_FIFO_WDATA, color & 0xff);
    }
    if (private.cb) private.cb();
    private.is_busy = 0;
    return 0;
}
