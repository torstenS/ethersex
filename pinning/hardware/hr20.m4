
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


dnl *******************************************************************************
dnl *  LCD Layout:
dnl *
dnl *        B|B|B|B|B|B|B|B|B|B|B |B |B |B |B |B |B |B |B |B |B |B |B |B |    
dnl *        0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|    
dnl *                                                                          
dnl *        ---------------------------BAR24------------------------------    
dnl *                                                                          
dnl *      Auto      3A         2A                  1A         0A       SUN    
dnl *             3F    3B   2F    2B            1F    1B   0F    0B           
dnl *      Manu      3g         2g       Col2       1g         0g       MOON   
dnl *             3E    3C   2E    2C            1E    1C   0E    0C           
dnl *      Prog      3D         2D       Col1       1D         0D       STAR   
dnl *                                                                          
dnl *******************************************************************************

// LCD_SEG:_xx for LCD_SetSeg   // LCDDR | AtMega169 |  LCD_Data[]
#define LCD_SEG_B0          0   //  0, 0 |  SEG000   |  [0], BIT 0
                                //  0, 1 |  SEG001   |  [0], BIT 1
#define LCD_SEG_B1          2   //  0, 2 |  SEG002   |  [0], BIT 2
#define LCD_SEG_B2          3   //  0, 3 |  SEG003   |  [0], BIT 3
#define LCD_SEG_B3          4   //  0, 4 |  SEG004   |  [0], BIT 4
#define LCD_SEG_B4          5   //  0, 5 |  SEG005   |  [0], BIT 5
#define LCD_SEG_B5          6   //  0, 6 |  SEG006   |  [0], BIT 6
#define LCD_SEG_B6          7   //  0, 7 |  SEG007   |  [0], BIT 7
#define LCD_SEG_B7          8   //  1, 0 |  SEG008   |  [1], BIT 0
#define LCD_SEG_B8          9   //  1, 1 |  SEG009   |  [1], BIT 1
#define LCD_SEG_B9         10   //  1, 2 |  SEG010   |  [1], BIT 2
#define LCD_SEG_BAR24      11   //  1, 3 |  SEG011   |  [1], BIT 3
#define LCD_SEG_B14        12   //  1, 4 |  SEG012   |  [1], BIT 4
#define LCD_SEG_B15        13   //  1, 5 |  SEG013   |  [1], BIT 5
#define LCD_SEG_B16        14   //  1, 6 |  SEG014   |  [1], BIT 6
#define LCD_SEG_B17        15   //  1, 7 |  SEG015   |  [1], BIT 7
#define LCD_SEG_B18        16   //  2, 0 |  SEG016   |  [2], BIT 0
#define LCD_SEG_B19        17   //  2, 1 |  SEG017   |  [2], BIT 1
#define LCD_SEG_B20        18   //  2, 2 |  SEG018   |  [2], BIT 2
#define LCD_SEG_B21        19   //  2, 3 |  SEG019   |  [2], BIT 3
#define LCD_SEG_B22        20   //  2, 4 |  SEG020   |  [2], BIT 4
#define LCD_SEG_B23        21   //  2, 5 |  SEG021   |  [2], BIT 5
//*****************************************************************
#define LCD_SEG_AUTO       24   //  5, 0 |  SEG100   |  [3], BIT 0
                                //  5, 1 |  SEG101   |  [3], BIT 1
#define LCD_SEG_PROG       26   //  5, 2 |  SEG102   |  [3], BIT 2
#define LCD_SEG_3F         27   //  5, 3 |  SEG103   |  [3], BIT 3
#define LCD_SEG_3G         28   //  5, 4 |  SEG104   |  [3], BIT 4
#define LCD_SEG_3A         29   //  5, 5 |  SEG105   |  [3], BIT 5
#define LCD_SEG_3B         30   //  5, 6 |  SEG106   |  [3], BIT 6
#define LCD_SEG_2F         31   //  5, 7 |  SEG107   |  [3], BIT 7
#define LCD_SEG_2G         32   //  6, 0 |  SEG108   |  [4], BIT 0
#define LCD_SEG_2A         33   //  6, 1 |  SEG109   |  [4], BIT 1
#define LCD_SEG_2B         34   //  6, 2 |  SEG110   |  [4], BIT 2
#define LCD_SEG_COL2       35   //  6, 3 |  SEG111   |  [4], BIT 3
#define LCD_SEG_1F         36   //  6, 4 |  SEG112   |  [4], BIT 4
#define LCD_SEG_1G         37   //  6, 5 |  SEG113   |  [4], BIT 5
#define LCD_SEG_1A         38   //  6, 6 |  SEG114   |  [4], BIT 6
#define LCD_SEG_1B         39   //  6, 7 |  SEG115   |  [4], BIT 7
#define LCD_SEG_0F         40   //  7, 0 |  SEG116   |  [5], BIT 0
#define LCD_SEG_0G         41   //  7, 1 |  SEG117   |  [5], BIT 1
#define LCD_SEG_0A         42   //  7, 2 |  SEG118   |  [5], BIT 2
#define LCD_SEG_0B         43   //  7, 3 |  SEG119   |  [5], BIT 3
#define LCD_SEG_SNOW       44   //  7, 4 |  SEG120   |  [5], BIT 4
#define LCD_SEG_SUN        45   //  7, 5 |  SEG121   |  [5], BIT 5
//*****************************************************************
                                // 10, 0 |  SEG200   |  [6], BIT 0
                                // 10, 1 |  SEG201   |  [6], BIT 1
#define LCD_SEG_MANU       50   // 10, 2 |  SEG202   |  [6], BIT 2
#define LCD_SEG_3E         51   // 10, 3 |  SEG203   |  [6], BIT 3
#define LCD_SEG_3D         52   // 10, 4 |  SEG204   |  [6], BIT 4
#define LCD_SEG_B11        53   // 10, 5 |  SEG205   |  [6], BIT 5
#define LCD_SEG_3C         54   // 10, 6 |  SEG206   |  [6], BIT 6
#define LCD_SEG_2E         55   // 10, 7 |  SEG207   |  [6], BIT 7
#define LCD_SEG_2D         56   // 11, 0 |  SEG208   |  [7], BIT 0
#define LCD_SEG_B10        57   // 11, 1 |  SEG209   |  [7], BIT 1
#define LCD_SEG_2C         58   // 11, 2 |  SEG210   |  [7], BIT 2
#define LCD_SEG_COL1       59   // 11, 3 |  SEG211   |  [7], BIT 3
#define LCD_SEG_1E         60   // 11, 4 |  SEG212   |  [7], BIT 4
#define LCD_SEG_1D         61   // 11, 5 |  SEG213   |  [7], BIT 5
#define LCD_SEG_B13        62   // 11, 6 |  SEG214   |  [7], BIT 6
#define LCD_SEG_1C         63   // 11, 7 |  SEG215   |  [7], BIT 7
#define LCD_SEG_0E         64   // 12, 0 |  SEG216   |  [8], BIT 0
#define LCD_SEG_0D         65   // 12, 1 |  SEG217   |  [8], BIT 1
#define LCD_SEG_B12        66   // 12, 2 |  SEG218   |  [8], BIT 2
#define LCD_SEG_0C         67   // 12, 3 |  SEG219   |  [8], BIT 3
                                // 12, 4 |  SEG220   |  [8], BIT 4
#define LCD_SEG_MOON       69   // 12, 5 |  SEG221   |  [8], BIT 5
//*****************************************************************

