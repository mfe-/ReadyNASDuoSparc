/* Utility Functions */
void readynas_msleep(int msec);

/* LCD Functions */
int  readynas_lcd_is_supported(void);
int  readynas_check_lcd_backlight(void);
void readynas_lcd_off(void);
void readynas_lock_lcd_brightness(void);
void readynas_unlock_lcd_brightness(void);
void readynas_lcd_dimmy(void);
void readynas_lcd_sharp(void);
void readynas_lcd_clear(void);
void readynas_lcd_disp_line(int line, char *text);

/* PSU status functions */
int get_psu_power_status(int psu); // Returns 1 for good, anything else is bad
