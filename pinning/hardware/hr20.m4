
dnl Block pins used by LCD ...
define(`port_mask_A', eval(port_mask_A | 0xF7))dnl
define(`port_mask_C', eval(port_mask_C | 0xFF))dnl
define(`port_mask_D', eval(port_mask_D | 0xFE))dnl
define(`port_mask_G', eval(port_mask_G | 0x07))dnl



dnl Motor
pin(MOTOR_POS, PB7, OUTPUT)
pin(MOTOR_NEG, PB4, OUTPUT)
pin(MOTOR_DIRP, PG3, OUTPUT)
pin(MOTOR_DIRN, PG4, OUTPUT)

dnl Stellrad
pin(STELLRAD_A, PB6)
pin(STELLRAD_B, PB5)

dnl Taster
pin(TASTE_AUTO, PB3)
pin(TASTE_PROG, PB2)
pin(TASTE_GRAD, PB1)
pin(MONTIERT, PB0)

dnl Lichtschranke
pin(LICHTSCHRANKE_ENABLE, PE3, OUTPUT)
pin(LICHTSCHRANKE_SENSE, PE4)

dnl Temperaturfuehler
pin(TEMP_ENABLE, PF3, OUTPUT)
pin(TEMP_SENSE, PF2)
