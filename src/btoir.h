#pragma once

#define APP_VERSION "1.0.0"

#define VENDOR_ID  0x22ea
#define PRODUCT_ID 0x003a
#define BTO_EP_IN  0x84
#define BTO_EP_OUT 0x04

typedef unsigned char byte;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char bool;
#define true	1
#define false	0

#define BUFF_SIZE 64
#define FORMAT_NUM 4
#define OPTION_NUM 10

#define IR_FREQ_MIN						25000	// 赤外線周波数設定最小値 25KHz
#define IR_FREQ_MAX						50000	// 赤外線周波数設定最大値 50KHz
#define IR_SEND_DATA_USB_SEND_MAX_LEN	14		// USB送信１回で送信する最大ビット数
#define IR_SEND_DATA_MAX_LEN			300		// 赤外線送信データ設定最大長[byte]

#define IR_FREQ_DEFAULT					38000
static uint frequency = IR_FREQ_DEFAULT;

#define MAX_BYTE_ARRAY_SIZE				9600

#define FORMAT_AEHA_READER_CODE			0x007B003D	// 家電協 Reader Code ON:3.2ms/26us=123(0x7B), OFF:1.6ms/26us=61(0x3D)
#define FORMAT_AEHA_BIT_OFF				0x000F000F	// 家電協 BitOFF ON:0.4ms/26us=15(0x0F), OFF:0.4ms/26us=15(0x0F)
#define FORMAT_AEHA_BIT_ON				0x000F002E	// 家電協 BitON  ON:0.4ms/26us=15(0x0F), OFF:1.2ms/26us=46(0x2E)
#define FORMAT_NEC_READER_CODE			0x015A00AD	// NEC Reader Code ON:9.0ms/26us=346(0x15A), OFF:4.5ms/26us=173(0xAD)
#define FORMAT_NEC_BIT_OFF				0x00160016	// NEC BitOFF ON:0.56ms/26us=22(0x16), OFF:0.56ms/26us=22(0x16)
#define FORMAT_NEC_BIT_ON				0x00160041	// NEC BitON  ON:0.56ms/26us=22(0x16), OFF:1.68ms/26us=65(0x41)
#define FORMAT_SONY_READER_CODE			0x005C0017	// SONY Reader Code ON:2.4ms/26us=92(0x5C), OFF:0.6ms/26us=23(0x17)
#define FORMAT_SONY_BIT_OFF				0x00170017	// SONY BitOFF ON:0.6ms/26us=23(0x17), OFF:0.6ms/26us=23(0x17)
#define FORMAT_SONY_BIT_ON				0x002E0017	// SONY BitON  ON:1.2ms/26us=46(0x2E), OFF:0.6ms/26us=23(0x17)
#define FORMAT_MITSU_READER_CODE		0x00000000	// MITSUBISHI Reader Code なし
#define FORMAT_MITSU_BIT_OFF			0x000F001F	// MITSUBISHI BitOFF ON:0.4ms/26us=15(0x0F), OFF:0.8ms/26us=31(0x1F)
#define FORMAT_MITSU_BIT_ON				0x000F004D	// MITSUBISHI BitON  ON:0.4ms/26us=15(0x0F), OFF:2.0ms/26us=77(0x4D)
#define FORMAT_STOP_CODE				0x00170619	// STOP CODE

enum
{
    IR_FORMAT_AEHA = 1,
    IR_FORMAT_NEC,
    IR_FORMAT_SONY,
    IR_FORMAT_MITSUBISHI
};

enum
{
    PLARAIL_BAND_BAND_A = 1,
    PLARAIL_BAND_BAND_B
};

enum
{
    PLARAIL_DIRECTION_FORWARD = 1,
    PLARAIL_DIRECTION_BACKWARD
};

enum
{
    Plarail_StopA,
    Plarail_StopB,
    Plarail_Speed_UpAF,
    Plarail_Speed_UpAB,
    Plarail_Speed_UpBF,
    Plarail_Speed_UpBB,
    Plarail_Speed_DownA,
    Plarail_Speed_DownB
};

static char FORMATlist[FORMAT_NUM][11] =
{
    "AEHA",
    "NEC",
    "SONY",
    "MITSUBISHI"
};

static char PLAOPTIONlist[OPTION_NUM-2][20] =
{
    "Plarail_StopA",
    "Plarail_StopB",
    "Plarail_Speed_UpAF",
    "Plarail_Speed_UpAB",
    "Plarail_Speed_UpBF",
    "Plarail_Speed_UpBB",
    "Plarail_Speed_DownA",
    "Plarail_Speed_DownB"
};

void close_device(libusb_context *ctx, libusb_device_handle *devh);
libusb_device_handle* open_device(libusb_context *ctx);
void setup_optargs(struct option options[]);
void usage(char *fname);
void version(char *fname);
int writeUSBIR(struct libusb_device_handle *devh, uint format_type, byte code[], int code_len);
int writeUSBIRCode(struct libusb_device_handle *devh, uint freq, uint reader_code, uint bit_0, uint bit_1, uint stop_code, byte code[], uint bit_len);
int writeUSBIRData(struct libusb_device_handle *devh, uint freq, byte data[], uint bit_len, uint data_count);
int writeUSBIRData_Ushort(struct libusb_device_handle *devh, uint freq, ushort data[], uint bit_len, uint ele_num);
int writeUSBIR_Plarail_Stop(struct libusb_device_handle *devh, uint band);
int writeUSBIR_Plarail_Speed_Up(struct libusb_device_handle *devh, uint band, uint dir);
int writeUSBIR_Plarail_Speed_Down(struct libusb_device_handle *devh, uint band);
int recUSBIRData_Start(struct libusb_device_handle *devh, uint freq);
int recUSBIRData_Stop(struct libusb_device_handle *devh);
int readUSBIRData(struct libusb_device_handle *devh, byte data[], uint data_buff_len, uint *bit_len);