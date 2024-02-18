/*
	Auxiliary code for HM01B0 camera
*/

#include "pico/stdlib.h"
#include "../compiler.h"
#include "arducam/arducam.h"

#define LIB_AUX_HM01B0_INIT    1
#define LIB_AUX_HM01B0_CAPTURE 2
#define LIB_AUX_HM01B0_DRAW 3
#define LIB_AUX_HM01B0_REG_WRITE 4
//#define LIB_AUX_HM01B0_REG_READ 5
#define LIB_AUX_HM01B0_ZOOM 6

void hm01b0_init(uint8_t* buff);
void hm01b0_capture(void);
void hm01b0_draw(void);
void hm01b0_reg_write(uint16_t reg, uint8_t value);
// uint8_t hm01b0_reg_read(uint16_t reg);
void hm01b0_zoom(int x_start, int y_start);

int hm01b0_init_statement(void){
	// The first argument is the pointer to video buffer (324*324 bytes)
	return argn_function(LIB_AUXCODE,
		ARG_INTEGER<<ARG1 |
		LIB_AUX_HM01B0_INIT<<LIBOPTION);
}

int hm01b0_capture_statement(void){
	return argn_function(LIB_AUXCODE,
		LIB_AUX_HM01B0_CAPTURE<<LIBOPTION);
}

int hm01b0_draw_statement(void){
	return argn_function(LIB_AUXCODE,
		LIB_AUX_HM01B0_DRAW<<LIBOPTION);
}

int hm01b0_reg_write_statement(void){
	// The first argument is register number.
	// The second argument is value;
	return argn_function(LIB_AUXCODE,
		ARG_INTEGER<<ARG1 |
		ARG_INTEGER<<ARG2 |
		LIB_AUX_HM01B0_REG_WRITE<<LIBOPTION);
}

int hm01b0_zoom_statement(void){
	// The first argument is X.
	// The second argument is Y;
	return argn_function(LIB_AUXCODE,
		ARG_INTEGER<<ARG1 |
		ARG_INTEGER<<ARG2 |
		LIB_AUX_HM01B0_ZOOM<<LIBOPTION);
}

/*
int hm01b0_reg_read_function(void){
	// The first argument is register number.
	return argn_function(LIB_AUXCODE,
		ARG_INTEGER<<ARG1 |
		LIB_AUX_HM01B0_REG_READ<<LIBOPTION);
}
*/

int aux_statements(void){
	if (instruction_is("HM01B0_INIT")) return hm01b0_init_statement();
	if (instruction_is("HM01B0_CAPTURE")) return hm01b0_capture_statement();
	if (instruction_is("HM01B0_DRAW")) return hm01b0_draw_statement();
	if (instruction_is("HM01B0_REG_WRITE")) return hm01b0_reg_write_statement();
	if (instruction_is("HM01B0_ZOOM")) return hm01b0_zoom_statement();
	return ERROR_STATEMENT_NOT_DETECTED;
}
int aux_int_functions(void){
//	if (instruction_is("HM01B0_REG_READ(")) return hm01b0_reg_read_function();
	return ERROR_STATEMENT_NOT_DETECTED;
}
int aux_str_functions(void){
	return ERROR_STATEMENT_NOT_DETECTED;
}
int aux_float_functions(void){
	return ERROR_STATEMENT_NOT_DETECTED;
}
int lib_aux(int r0, int r1, int r2){
	switch(r2){
		case LIB_AUX_HM01B0_INIT:
			hm01b0_init((uint8_t*)r0);
			break;
		case LIB_AUX_HM01B0_CAPTURE:
			hm01b0_capture();
			break;
		case LIB_AUX_HM01B0_DRAW:
			hm01b0_draw();
			break;
		case LIB_AUX_HM01B0_REG_WRITE:
			hm01b0_reg_write((uint16_t)r1, (uint8_t) r0);
			break;
/*
		case LIB_AUX_HM01B0_REG_READ:
			return hm01b0_reg_read((uint16_t) r0);
*/
		case LIB_AUX_HM01B0_ZOOM:
			hm01b0_zoom(r1, r0);
			break;
		default:
			break;
	}
	return r0;
}
