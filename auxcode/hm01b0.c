/*
	Auxiliary code for HM01B0 camera
*/

#include "pico/stdlib.h"
#include "arducam/arducam.h"
#include "../interface/graphlib.h"
#include "../interface/LCDdriver.h"

static 	struct arducam_config config;

void hm01b0_init(uint8_t* image_buf){
	config.sccb = i2c0;
	config.sccb_mode = I2C_MODE_16_8;
	config.sensor_address = 0x24;
	config.pin_sioc = PIN_CAM_SIOC;     // GPIO5
	config.pin_siod = PIN_CAM_SIOD;     // GPIO4
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

void hm01b0_draw(void){
	g_putbmpmn(0,0,324,240,config.image_buf);
	return;
}

void hm01b0_reg_write(uint16_t reg, uint8_t value){
	arducam_reg_write(&config, reg, value);
}

uint8_t hm01b0_reg_read(uint16_t reg){
	return arducam_reg_read(&config, reg);
}

void hm01b0_zoom(int x_start, int y_start){
	int x,y;
	char* buff=&config.image_buf[0];
	// Use valid values
	if (x_start<0) x_start=0;
	if (y_start<0) y_start=0;
	if (160<x_start) x_start=160;
	if (120<y_start) y_start=120;
	// Copy the area of interest to temporary area
	int read_area=y_start*324+x_start;
	int temp_area=240*324; // 84*324=27216 bytes free area (160*120=19200 bytes needed)
	for(y=y_start;y<y_start+120;y++){
		for(x=x_start;x<x_start+160;x++){
			buff[temp_area++]=buff[read_area++];
		}
		read_area+=164;
	}
	// Copy the temporary area to entier view
	char c;
	temp_area=240*324;
	int view_area=0;
	for(y=0;y<120;y++){
		for(x=0;x<160;x++){
			c=buff[temp_area++];
			buff[view_area+324]=c;
			buff[view_area++]=c;
			buff[view_area+324]=c;
			buff[view_area++]=c;
		}
		view_area+=328;
	}
}