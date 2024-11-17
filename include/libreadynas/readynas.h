#include <libreadynas_lgpl/readynas.h>

#define DISK_MISSING			0
#define DISK_OKAY			1
#define DISK_SYNC			2
#define DISK_FAIL			3

#define SHELL_STRING_FILE_PATH		"/frontview/bin/lang/%s/strings"
#define FV_STRING_FILE_PATH		"/frontview/ui/resource/language/%s/Combined.str"
#define MAX_TRANSLATIONS		10
#define MAX_TRANSLATED_SIZE		512
#define TAG_NO_TRANSLATE		0
#define TAG_TRANSLATE_DONE		1
#define LINE_BUFFER_SIZE		1024
#define TRANSLATION_TEMP_BUF_SIZE	1024
#define TRANSLATION_BUF_SIZE		1024

#define SERVICES_FILE			"/etc/default/services"
#define FV_LOG_FILE			"/var/log/frontview/status.log-new"
#define DISK_INFO_CACHE			"/ramfs/disk_info"

#define BOOTING_FLAG			"/.boottime"

#define ADMIN_UID			98
#define ADMIN_GID			98

#define LOG_SEVERITY_INFO		1
#define LOG_SEVERITY_ERROR		3

/* General definitions */
#define RN3200_CPU_MODEL		23
#define NV6_CPU_MODEL			15
#define NVX_CPU_MODEL			21
#define NVX_FAN_1			"/sys/class/hwmon/hwmon0/device/fan1_input"
#define NVX_FAN_2			"/sys/class/hwmon/hwmon0/device/fan2_input"

#define NV6_FRONT_USB_PATH		"/devices/pci0000:00/0000:00:1a.7/usb1/1-2/1-2:1"
#define NVX_FRONT_USB_PATH		"/devices/pci0000:00/0000:00:1d.7/usb1/1-2/1-2.3"

typedef enum systypes {
	UNKNOWN=0,
	NV6,
	NVX,
	RN2100,
	RN3200
} systypes;

typedef enum vendors {
	INTEL,
	INFRANT
} vendors;

struct hdinfo {
	char devname[16];
	int channel;
	char model[41];
	char serial[21];
	char firmware[9];
	int write_cache_enabled;
};

/* Utility Functions */
// mode should be either "w" for [over]write, or "a" for append.
void readynas_echo(const char *string, const char *path, const char *mode);
char *trim(char *str);
float celcius_to_farenheit(float temp);
int copy_file(const char *src, const char *dst);
int move_file(const char *src, const char *dst);
int is_mountpoint(const char *path);
int read_from_sysfs(char *file, char *buf, int buflen);
char *translate_string(char *lang, char *string);
int send_email_alert(char *subject, char *mesg, char *lang);
int log_status(int severity, char *mesg);
void raidiator_syslog(int level, const char *message);
int compact_string(char *s);
int exists(char *path, char type);

/* LCD Functions */
// LCD functions have been moved to libreadynas_lgpl for use in GPL programs.
int update_lcd_disk_status(void);

/* Disk Functions */
int disk_is_down(char *devname);
void enable_smart(const char *devname);
int get_ata_errors(char *devname);
int get_disk_temp(char *devname);
int start_smart_test(const char *devname); // Returns the suggested wait time before polling for results, or -1 if there is a failure
int start_smart_extended_test(const char *devname); // Returns the suggested wait time in seconds before polling for results, or -1 if there is a failure
int smart_test_failed(const char *devname); // Returns 1 if SMART detected a failure
char *find_boot_device(void);
void toggle_flash(int enable, char *devname);
int get_disk_channel(char *devname); // Returns the zero-based channel number of a given sd node (eg. sda, /dev/sda, or /sys/block/sda)
char *get_disk_dev(int chan);
int get_disk_raid_status(char *devname);
int get_disk_info(char *devname, struct hdinfo *id);

/* Network Functions */
char *get_mac_address(char *iface);
void get_sys_ip(char *buf);
void get_iface_ip(char *iface, char *buf);

/* Configuration file functions */
char *get_shell_var(char *file, char *tag);
int get_shell_var_as_int(char *file, char *var);
char *get_boot_info(char *tag);
int get_boot_info_as_int(char *tag);
char *get_fv_services_setting(char *setting);
int update_services(char *key, char *val); /* Returns 1 on success, 0 on failure */

/* ReadyNAS System functions */
systypes get_systype(void);
int rn3200_disk_led_mode(int disk, int mode);

void read_random_sectors(int fd);

/* Disk LED/LCD functions */
void readynas_lcd_disp_disk_std(int disk);
void readynas_lcd_disp_disk_failed(int disk);
void readynas_lcd_disp_disk_blank(int disk);
void readynas_lcd_disp_disk_build(int disk);
void readynas_lcd_disp_disk_locate(int disk);

