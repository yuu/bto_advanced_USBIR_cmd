#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

enum PLARAIL_BAND {
    PLARAIL_BAND_BAND_A = 1,
    PLARAIL_BAND_BAND_B,
};

enum PLARAIL_DIRECTION {
    PLARAIL_DIRECTION_FORWARD = 1,
    PLARAIL_DIRECTION_BACKWARD,
};

enum Plarail {
    Plarail_StopA,
    Plarail_StopB,
    Plarail_Speed_UpAF,
    Plarail_Speed_UpAB,
    Plarail_Speed_UpBF,
    Plarail_Speed_UpBB,
    Plarail_Speed_DownA,
    Plarail_Speed_DownB,
};

struct btoir;

int writeUSBIR_Plarail_Stop(struct btoir *bto, uint band);
int writeUSBIR_Plarail_Speed_Up(struct btoir *bto, uint band, uint dir);
int writeUSBIR_Plarail_Speed_Down(struct btoir *bto, uint band);

#ifdef __cplusplus
}
#endif
