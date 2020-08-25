#include "plarail.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "btoir.h"

static int writeUSBIRData_Ushort(struct btoir *bto, uint freq, ushort udata[], uint bit_len, uint ele_num) {
    uint fi;
    int ji;
    uint dataCount = bit_len * 4;
    uint *data = malloc(dataCount);
    memset(data, 0x00, dataCount);

    // dataCountではなくele_num*2なのは、要素数が足りない場合に対応する為
    for (fi = 0; fi < ele_num * 2; fi++) {
        ji = fi / 2;

        if (fi % 2)
            data[fi] = udata[ji] & 0xFF;
        else
            data[fi] = (udata[ji] >> 8) & 0xFF;
    }

    return bto_write(bto, freq, data, dataCount);
}

int writeUSBIR_Plarail_Stop(struct btoir *bto, uint band) {
    int i_ret = -1;
    bool b_err = false;
    ushort *code = NULL;  // 送信データ
    ushort code_A_STOP[] = {0x0016, 0x001D, 0x0016, 0x001D, 0x0016, 0x001D, 0x0016, 0x001D, 0x0034, 0x0013, 0x0034,
                            0x0013, 0x0034, 0x0013, 0x0034, 0x0280, 0x0016, 0x001D, 0x0016, 0x001D, 0x0016, 0x001D,
                            0x0016, 0x001D, 0x0034, 0x0013, 0x0034, 0x0013, 0x0034, 0x0013, 0x0034, 0x0000};
    ushort code_B_STOP[] = {0x0016, 0x001D, 0x0016, 0x001D, 0x0016, 0x001D, 0x0016, 0x001D, 0x0034, 0x0013, 0x0034,
                            0x0013, 0x0034, 0x0013, 0x0034, 0x0280, 0x0016, 0x001D, 0x0016, 0x001D, 0x0016, 0x001D,
                            0x0016, 0x001D, 0x0034, 0x0013, 0x0034, 0x0013, 0x0034, 0x0013, 0x0034, 0x0000};
    if (band == PLARAIL_BAND_BAND_A) {
        code = code_A_STOP;
    } else if (band == PLARAIL_BAND_BAND_B) {
        code = code_B_STOP;
    } else {
        i_ret = 2;
        b_err = true;
    }

    if (b_err == false) {
        // USB DEVICEへ送信 パラメータ[USB DEVICEハンドル、周波数、送信赤外線コード、赤外線コードのビット長、要素数]
        i_ret = writeUSBIRData_Ushort(bto, IR_FREQ_DEFAULT, code, 16, 32);
        if (i_ret != 0) {
            i_ret = 3;
        }
    }
    return i_ret;
}

int writeUSBIR_Plarail_Speed_Up(struct btoir *bto, uint band, uint dir) {
    int i_ret = -1;
    bool b_err = false;
    // 送信データ ON時間とOFF時間の組み合わせ
    ushort *code = NULL;  // 送信データ
    ushort code_A_UP_F[] = {0x0016, 0x001D, 0x0016, 0x001D, 0x0016, 0x001D, 0x0034, 0x0013, 0x0034, 0x0013, 0x0034,
                            0x0013, 0x0034, 0x0013, 0x0013, 0x0280, 0x0016, 0x001D, 0x0016, 0x001D, 0x0016, 0x001D,
                            0x0034, 0x0013, 0x0034, 0x0013, 0x0034, 0x0013, 0x0034, 0x0013, 0x0016, 0x0000};
    ushort code_A_UP_B[] = {0x0016, 0x001D, 0x0016, 0x001D, 0x0034, 0x0013, 0x0016, 0x001D, 0x0034, 0x0013, 0x0034,
                            0x0013, 0x0016, 0x001D, 0x0034, 0x0280, 0x0016, 0x001D, 0x0016, 0x001D, 0x0034, 0x0013,
                            0x0016, 0x001D, 0x0034, 0x0013, 0x0034, 0x0013, 0x0016, 0x001D, 0x0034, 0x0000};
    ushort code_B_UP_F[] = {0x0016, 0x001D, 0x0034, 0x0013, 0x0016, 0x001D, 0x0034, 0x0013, 0x0034, 0x0013, 0x0016,
                            0x001D, 0x0034, 0x0013, 0x0013, 0x0280, 0x0016, 0x001D, 0x0034, 0x0013, 0x0016, 0x001D,
                            0x0034, 0x0013, 0x0034, 0x0013, 0x0016, 0x001D, 0x0034, 0x0013, 0x0016, 0x0000};
    ushort code_B_UP_B[] = {0x0016, 0x001D, 0x0034, 0x0013, 0x0034, 0x0013, 0x0016, 0x001D, 0x0034, 0x0013, 0x0016,
                            0x001D, 0x0016, 0x001D, 0x0034, 0x0280, 0x0016, 0x001D, 0x0034, 0x0013, 0x0034, 0x0013,
                            0x0016, 0x001D, 0x0034, 0x0013, 0x0016, 0x001D, 0x0016, 0x001D, 0x0034, 0x0000};

    if (band == PLARAIL_BAND_BAND_A) {
        if (dir == PLARAIL_DIRECTION_FORWARD) {
            code = code_A_UP_F;
        } else if (dir == PLARAIL_DIRECTION_BACKWARD) {
            code = code_A_UP_B;
        } else {
            i_ret = 3;
            b_err = true;
        }
    } else if (band == PLARAIL_BAND_BAND_B) {
        if (dir == PLARAIL_DIRECTION_FORWARD) {
            code = code_B_UP_F;
        } else if (dir == PLARAIL_DIRECTION_BACKWARD) {
            code = code_B_UP_B;
        } else {
            i_ret = 3;
            b_err = true;
        }
    } else {
        i_ret = 2;
        b_err = true;
    }

    if (b_err == false) {
        // USB DEVICEへ送信 パラメータ[USB DEVICEハンドル、周波数、送信赤外線コード、赤外線コードのビット長、要素数]
        i_ret = writeUSBIRData_Ushort(bto, IR_FREQ_DEFAULT, code, 16, 32);
        if (i_ret != 0) {
            i_ret = 4;
        }
    }
    return i_ret;
}

int writeUSBIR_Plarail_Speed_Down(struct btoir *bto, uint band) {
    int i_ret = -1;
    bool b_err = false;
    // 送信データ ON時間とOFF時間の組み合わせ
    ushort *code = NULL;  // 送信データ
    ushort code_A_DOWN_F[] = {0x0016, 0x001D, 0x0016, 0x001D, 0x0034, 0x0013, 0x0034, 0x0013, 0x0034, 0x0013, 0x0034,
                              0x0016, 0x0013, 0x001D, 0x0013, 0x0280, 0x0016, 0x001D, 0x0016, 0x001D, 0x0034, 0x0013,
                              0x0034, 0x0013, 0x0034, 0x0013, 0x0034, 0x0013, 0x0016, 0x001D, 0x0016, 0x0000};
    ushort code_B_DOWN_F[] = {0x0016, 0x001D, 0x0034, 0x0013, 0x0034, 0x0013, 0x0034, 0x0013, 0x0034, 0x0013, 0x0016,
                              0x001D, 0x0016, 0x001D, 0x0013, 0x0280, 0x0016, 0x001D, 0x0034, 0x0013, 0x0034, 0x0013,
                              0x0034, 0x0013, 0x0034, 0x0013, 0x0016, 0x001D, 0x0016, 0x001D, 0x0016, 0x0000};

    if (band == PLARAIL_BAND_BAND_A) {
        code = code_A_DOWN_F;
        // if (dir == PLARAIL_DIRECTION.FORWARD)
        //{
        //    code = code_A_DOWN_F;
        //}
        // else if (dir == PLARAIL_DIRECTION.BACKWARD)
        //{
        //    code = code_B_DOWN_F;
        //}
        // else
        //{
        //    i_ret = 3;
        //    b_err = true;
        //}
    } else if (band == PLARAIL_BAND_BAND_B) {
        code = code_B_DOWN_F;
        // if (dir == PLARAIL_DIRECTION.FORWARD)
        //{
        //    code = code_B_DOWN_F;
        //}
        // else if (dir == PLARAIL_DIRECTION.BACKWARD)
        //{
        //    code = code_B_DOWN_B;
        //}
        // else
        //{
        //    i_ret = 3;
        //    b_err = true;
        //}
    } else {
        i_ret = 2;
        b_err = true;
    }

    if (b_err == false) {
        // USB DEVICEへ送信 パラメータ[USB DEVICEハンドル、周波数、送信赤外線コード、赤外線コードのビット長、要素数]
        i_ret = writeUSBIRData_Ushort(bto, IR_FREQ_DEFAULT, code, 16, 32);
        if (i_ret != 0) {
            i_ret = 3;
        }
    }
    return i_ret;
}
