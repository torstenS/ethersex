
dnl Block pins used by LCD ...
define(`port_mask_A', eval(port_mask_A | 0xF7))dnl
define(`port_mask_C', eval(port_mask_C | 0xFF))dnl
define(`port_mask_D', eval(port_mask_D | 0xFE))dnl
define(`port_mask_G', eval(port_mask_G | 0x07))dnl



dnl Motor
pin(MOTOR_POS, PB7, OUTPUT)
pin(MOTOR_NEG, PB6, OUTPUT)
pin(MOTOR_DIRP, PG3, OUTPUT)
pin(MOTOR_DIRN, PG4, OUTPUT)

dnl Stellrad
pin(STELLRAD_A, PB5)
pin(STELLRAD_B, PB4)

dnl Taster
pin(TASTE_AUTO, PB3)
pin(TASTE_PROG, PB2)
pin(TASTE_GRAD, PB1)
pin(MONTIERT, PB0)

dnl Lichtschranke (not declared OUTPUT to not touch USART0 pins)
pin(LICHTSCHRANKE_ENABLE1, PE3)
pin(LICHTSCHRANKE_ENABLE2, PE2)
pin(LICHTSCHRANKE_SENSE, PE1)

dnl Temperaturfuehler
pin(TEMP_ENABLE, PF2, OUTPUT)
pin(TEMP_SENSE, PF0)
