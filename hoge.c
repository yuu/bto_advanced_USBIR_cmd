#include "hoge.h"

int writeUSBIRData(struct libusb_device_handle *devh, uint freq, byte data[], uint bit_len, uint data_count)
{
uint fi;
byte outbuffer[BUFF_SIZE];
byte inbuffer[BUFF_SIZE];
int BytesWritten = 0;
int BytesRead = 0;
bool error_flag = false;
uint send_bit_num = 0;
uint send_bit_pos = 0;                  // 送信セット済みビット位置
uint set_bit_size = 0;

// ↓元にしたソース:USBIR.csから独自に拡張した箇所。data_count/2が奇数の場合に対応。引数bit_lenは使用しない。代わりに追加した引数data_countを使う。
send_bit_num = data_count / 4 + (data_count % 4)/2; // 送信ビット数　リーダーコード + コード + 終了コード

// パラメータチェック
if (devh == NULL &&
	freq < IR_FREQ_MIN &&
	IR_FREQ_MAX < freq &&
	send_bit_num < 1 &&
	(IR_SEND_DATA_MAX_LEN * 8) < send_bit_num)
{
	return -1;
}

// データセット
while (true)
{
    outbuffer[0] = 0x34;
    //送信総ビット数
    outbuffer[1] = (byte)((send_bit_num >> 8) & 0xFF);
    outbuffer[2] = (byte)(send_bit_num & 0xFF);
    outbuffer[3] = (byte)((send_bit_pos >> 8) & 0xFF);
    outbuffer[4] = (byte)(send_bit_pos & 0xFF);
    if (send_bit_num > send_bit_pos)
    {
        set_bit_size = send_bit_num - send_bit_pos;
        if (set_bit_size > IR_SEND_DATA_USB_SEND_MAX_LEN)
        {
            set_bit_size = IR_SEND_DATA_USB_SEND_MAX_LEN;
        }
    }
    else
    {   // 送信データなし
        set_bit_size = 0;
    }
    outbuffer[5] = (byte)(set_bit_size & 0xFF);

    if (set_bit_size < 1)
        break;

    // データセット
    // 赤外線コードコピー
    for (fi = 0; fi < set_bit_size; fi++)
    {
        // ON Count
        outbuffer[6 + (fi * 4)] = data[send_bit_pos * 4];
        outbuffer[6 + (fi * 4) + 1] = data[(send_bit_pos * 4) + 1];
        // OFF Count
        outbuffer[6 + (fi * 4) + 2] = data[(send_bit_pos * 4) + 2];
        outbuffer[6 + (fi * 4) + 3] = data[(send_bit_pos * 4) + 3];
        send_bit_pos++;
    }
    if(libusb_interrupt_transfer(devh, BTO_EP_OUT, outbuffer, BUFF_SIZE ,&BytesWritten, 5000) == 0)
    {
        //Now get the response packet from the firmware.
        if(libusb_interrupt_transfer(devh, BTO_EP_IN, inbuffer, BUFF_SIZE, &BytesRead, 5000) == 0)
        {
            //INBuffer[0] is an echo back of the command (see microcontroller firmware).
            //INBuffer[1] contains the I/O port pin value for the pushbutton (see microcontroller firmware).  
            if (inbuffer[0] == 0x34 && inbuffer[1] != 0x00)
                error_flag = true; // NG
        }
        else
        {
            // NG
            error_flag = true;
        }
    }
    else
    {
        // NG
        error_flag = true;
    }
} // end of while

// データ送信要求セット
if (error_flag == true)
    return -3; // データセットエラー

outbuffer[0] = 0x35;		//0x81 is the "Get Pushbutton State" command in the firmware
outbuffer[1] = (byte)((freq >> 8) & 0xFF);
outbuffer[2] = (byte)(freq & 0xFF);
outbuffer[3] = (byte)((send_bit_num >> 8) & 0xFF);
outbuffer[4] = (byte)(send_bit_num & 0xFF);
BytesRead = 0;

//To get the pushbutton state, first, we send a packet with our "Get Pushbutton State" command in it.
if(libusb_interrupt_transfer(devh, BTO_EP_OUT, outbuffer, BUFF_SIZE ,&BytesWritten, 5000) != 0)
    return -4; // NG

//Now get the response packet from the firmware.
if(libusb_interrupt_transfer(devh, BTO_EP_IN, inbuffer, BUFF_SIZE, &BytesRead, 5000) != 0)
    return -5; // NG

//INBuffer[0] is an echo back of the command (see microcontroller firmware).
//INBuffer[1] contains the I/O port pin value for the pushbutton (see microcontroller firmware).  
if (inbuffer[0] == 0x35 && inbuffer[1] == 0x00)
    return 0;

return -1;
}
