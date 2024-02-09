/*
	Auxiliary code for HM01B0 camera
*/

#include "pico/stdlib.h"
#include "arducam/arducam.h"

static 	struct arducam_config config;

void hm01b0_init(uint8_t* image_buf){
	config.sccb = i2c0;
	config.sccb_mode = I2C_MODE_16_8;
	config.sensor_address = 0x24;
	config.pin_sioc = PIN_CAM_SIOC;     // GPIO5
	config.pin_siod = PIN_CAM_SIOD;     // GPIO6
	config.pin_resetb = PIN_CAM_RESETB; // GPIO2
	config.pin_xclk = PIN_CAM_XCLK;     // GPIO3
	config.pin_vsync = 27;              // PIN_CAM_VSYNC;
	config.pin_y2_pio_base = 1;         // PIN_CAM_Y2_PIO_BASE;

	config.pio = pio0;
	config.pio_sm = 0;

	config.dma_channel = 0;
	config.image_buf = image_buf;
	config.image_buf_size = 324*324;

	arducam_init(&config);
	gpio_init(config.pin_vsync);
}

void hm01b0_capture(void){
	arducam_capture_frame(&config);
}

