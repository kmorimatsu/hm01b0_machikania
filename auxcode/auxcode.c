/*
	Auxiliary code for HM01B0 camera
*/

#include "pico/stdlib.h"
#include "../compiler.h"
#include "arducam/arducam.h"

#define LIB_AUX_HM01BO_INIT    1
#define LIB_AUX_HM01BO_CAPTURE 2

void hm01b0_init(uint8_t* buff);
void hm01b0_capture(void);

int hm01b0_init_statement(void){
	// The first argument is the pointer to video buffer (324*324 bytes)
	return argn_function(LIB_AUXCODE,
		ARG_INTEGER<<ARG1 |
		LIB_AUX_HM01BO_INIT<<LIBOPTION);
}

int hm01b0_capture_statement(void){
	return argn_function(LIB_AUXCODE,
		LIB_AUX_HM01BO_CAPTURE<<LIBOPTION);
}

int aux_statements(void){
	if (instruction_is("HM01BO_INIT")) return hm01b0_init_statement();
	if (instruction_is("HM01BO_CAPTURE")) return hm01b0_capture_statement();
	return ERROR_STATEMENT_NOT_DETECTED;
}
int aux_int_functions(void){
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
		case LIB_AUX_HM01BO_INIT:
			hm01b0_init((uint8_t*)r0);
			break;
		case LIB_AUX_HM01BO_CAPTURE:
			hm01b0_capture();
			break;
		default:
			break;
	}
	return r0;
}
