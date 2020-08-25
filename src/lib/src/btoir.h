#pragma once

#include "type.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APP_VERSION "1.0.0"

#define MAX_BYTE_ARRAY_SIZE 9600

#define IR_FREQ_MIN 25000  // 赤外線周波数設定最小値 25KHz
#define IR_FREQ_MAX 50000  // 赤外線周波数設定最大値 50KHz
#define IR_FREQ_DEFAULT 38000

enum IR_FORMAT {
    IR_FORMAT_INVALID = -1,
    IR_FORMAT_AEHA = 1,
    IR_FORMAT_NEC,
    IR_FORMAT_SONY,
    IR_FORMAT_MITSUBISHI,
};

struct btoir;

struct btoir *bto_open();
void bto_close(struct btoir *bto);

int bto_write_code(struct btoir *bto, enum IR_FORMAT format_type, const uint *code, int code_len);
int bto_write(struct btoir *bto, uint freq, const uint *data, uint data_count);

int bto_rec_start(struct btoir *bto, uint freq);
int bto_rec_stop(struct btoir *bto);
int bto_dump_record(struct btoir *bto, byte data[], uint data_buff_len, uint *bit_len);

#ifdef __cplusplus
}
#endif
