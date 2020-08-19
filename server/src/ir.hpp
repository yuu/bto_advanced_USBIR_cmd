#pragma once

#include "btoir.h"

class IR {
public:
    IR() : bto(nullptr) {
        this->bto = bto_open();
    }

    ~IR() {
        bto_close(this->bto);
    };

    int32_t write(uint freq, const std::string &data) {
        const auto d = reinterpret_cast<const byte*>(data.c_str());
        const auto length = data.length();

        return bto_write(this->bto, freq, d, length);
    }

    int32_t rec_start(uint freq) {
        return bto_rec_start(this->bto, freq);
    }

    int32_t rec_stop() {
        return bto_rec_stop(this->bto);
    }

    int32_t dump_record(byte *data, uint length, uint *actual_size) {
        return bto_dump_record(this->bto, data, length, actual_size);
    }

    btoir *bto;
};
