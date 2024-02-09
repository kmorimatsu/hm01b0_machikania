# Default Auxiliary CMakeLists definition

add_library(aux_files
	auxcode/auxcode.c
	auxcode/hm01b0.c
	auxcode/arducam/arducam.c
)
target_link_libraries(aux_files 
	pico_stdlib
	hardware_dma
	hardware_i2c
	hardware_pio
	hardware_pwm
)
pico_generate_pio_header(aux_files ${CMAKE_CURRENT_LIST_DIR}/image.pio)
