#include <getopt.h>
#include <libusb.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "btoir.h"

int main(int argc, char *argv[]) {
    libusb_context *ctx = NULL;
    int ret = 1;
    struct option *options;
    int option_index;
    int freq_flag = 0;
    int type_flag = 0;
    char type_arg[20] = "\0";
    int code_flag = 0;
    int Code_flag = 0;
    char Code_arg[600] = "\0";
    char hex_buff[5] = "\0";
    int str_len = 0;
    int data_flag = 0;
    int pla_flag = 0;
    int read_flag = 0;
    int stop_flag = 0;
    int get_flag = 0;
    char *s;
    byte *data = NULL;
    uint dataCount = 0;
    byte *code = NULL;
    uint codeCount = 0;
    char *endPtr;
    int placounter = 0, plaindex;
    int fi, typeindex = -1;
    uint ibit_len = 0;

    options = new option[OPTION_NUM];
    setup_optargs(options);
    while ((ret = getopt_long(argc, argv, "f:t:c:C:d:rsgh", options, &option_index)) != -1) {
        switch (ret) {
        case 1:
            pla_flag = 1;
            placounter++;
            plaindex = option_index;
            break;
        case 2:
            version(argv[0]);
            exit(0);
        case 'd':
            data_flag = 1;
            while ((s = strtok(optarg, ", ")) != NULL) {
                optarg = NULL;
                if (data != NULL) {
                    delete data;
                    data = new byte[dataCount + 1];
                } else {
                    data = new byte[dataCount + 1];
                }
                data[dataCount++] = (byte)strtol(s, &endPtr, 0);
            }
            break;
        case 'c':
            code_flag = 1;
            while ((s = strtok(optarg, ", ")) != NULL) {
                optarg = NULL;
                if (code != NULL) {
                    delete code;
                    code = new byte[codeCount + 1];
                } else {
                    code = new byte[codeCount + 1];
                }
                code[codeCount++] = (byte)strtol(s, &endPtr, 0);
            }
            break;
        case 'C':
            Code_flag = 1;
            strcpy(Code_arg, optarg);
            break;
        case 'f':
            freq_flag = 1;
            frequency = atoi(optarg);
            break;
        case 't':
            type_flag = 1;
            strcpy(type_arg, optarg);
            break;
        case 'r':
            read_flag = 1;
            break;
        case 's':
            stop_flag = 1;
            break;
        case 'g':
            get_flag = 1;
            break;
        case 'h':
            usage(argv[0]);
            exit(0);
            break;
        default:
            usage(argv[0]);
            exit(1);
            break;
        }
    }

    if ((!type_flag) && (!freq_flag) && (!code_flag) && (!Code_flag) && (!data_flag) && (!pla_flag) && (!read_flag) &&
        (!stop_flag) && (!get_flag)) {
        usage(argv[0]);
        exit(1);
    } else if ((code_flag || Code_flag) && data_flag) {
        fprintf(stderr, "エラー: -dオプションと-cまたは-Cオプションとは同時に指定できません。\n");
        exit(1);
    } else if (code_flag && Code_flag) {
        fprintf(stderr, "エラー: -cオプションと-Cオプションとは同時に指定できません。\n");
        exit(1);
    } else if (freq_flag && (code_flag || Code_flag)) {
        fprintf(stderr, "エラー: -rまたは-Cオプションと-fオプションは同時に指定できません。\n");
        exit(1);
    } else if ((code_flag || Code_flag || data_flag) && (read_flag || stop_flag || get_flag)) {
        fprintf(stderr,
                "エラー: "
                "送信系専用のオプション：-c、-C、-dオプションと受信系専用のオプション：-r、-s、-"
                "gオプションは同時に指定できません。\n");
        exit(1);
    } else if ((read_flag && stop_flag) || (stop_flag && get_flag) || (read_flag && get_flag)) {
        fprintf(stderr, "エラー: -rオプション、-sオプション、-gオプションは同時に指定できません。\n");
        exit(1);
    } else if (freq_flag && (stop_flag || get_flag)) {
        fprintf(stderr, "エラー: -sまたは-gオプションと-fオプションは同時に指定できません。\n");
        exit(1);
    } else if (((!type_flag) && (code_flag || Code_flag)) || (((!code_flag) && (!Code_flag)) && type_flag)) {
        fprintf(stderr, "エラー: -tオプションと-cまたは-Cオプションとは必ずセットで指定して下さい。\n");
        exit(1);
    } else if (((!data_flag) || (!read_flag)) && freq_flag) {
        fprintf(stderr, "エラー: -fオプションは-dオプションまたは-rオプションを指定した場合のみ使用できます。\n");
        exit(1);
    } else if (pla_flag && (freq_flag || type_flag || data_flag || code_flag || read_flag || stop_flag || get_flag)) {
        fprintf(stderr, "エラー: プラレール赤外線命令オプションは単独で指定して下さい。\n");
        exit(1);
    } else if (stop_flag && (freq_flag || type_flag || data_flag || code_flag || read_flag || get_flag)) {
        fprintf(stderr, "エラー: -sオプションは単独で指定して下さい。\n");
        exit(1);
    } else if (placounter > 1) {
        fprintf(stderr, "エラー: プラレール赤外線命令オプションは単独で指定して下さい。\n");
        exit(1);
    } else if (type_flag) {
        for (fi = 0; fi < FORMAT_NUM; fi++) {
            if ((ret = strcmp(type_arg, FORMATlist[fi])) == 0) {
                typeindex = fi;
                break;
            }
        }
        if (typeindex < 0) {
            fprintf(stderr, "エラー: 正しい赤外線フォーマットのタイプを指定して下さい。\n");
            exit(1);
        }
        typeindex++;  // enumの方は1から開始だから
    }

    if (data_flag) {
        if ((dataCount % 2) != 0) {
            fprintf(stderr, "エラー: データの総数は偶数である必要があります。: %d\n", dataCount);
            exit(1);
        }
    } else if (Code_flag) {
        str_len = strlen(Code_arg);
        if ((str_len % 2) != 0) {
            fprintf(stderr, "エラー: コード長は2の倍数である必要があります。: %d\n", str_len);
            exit(1);
        }
        for (fi = 0; fi < str_len / 2; fi++) {
            strcpy(hex_buff, "0x");
            strncat(hex_buff, &Code_arg[fi * 2], 2);

            if (code != NULL) {
                delete code;
                code = new byte[codeCount + 1];
            } else {
                code = new byte[codeCount + 1];
            }
            code[codeCount++] = (byte)strtol(hex_buff, &endPtr, 0);
        }
    }

    /* libusb initialize*/
    ret = libusb_init(&ctx);
    if (ret < 0) {
        perror("libusb_init\n");
        exit(1);
    }

    /* open device */
    libusb_device_handle *devh = open_device(ctx);

    if (data_flag) {
        if ((ret = writeUSBIRData(devh, frequency, data, dataCount / 4, dataCount)) < 0)
            fprintf(stderr, "error %d\n", ret);
    } else if (code_flag || Code_flag) {
        if ((ret = writeUSBIR(devh, typeindex, code, codeCount * 8)) < 0)
            fprintf(stderr, "error %d\n", ret);
    } else if (read_flag) {
        if ((ret = recUSBIRData_Start(devh, frequency)) < 0)
            fprintf(stderr, "error %d\n", ret);
        else
            fprintf(stdout, "受信を開始しました。\n");
    } else if (stop_flag) {
        if ((ret = recUSBIRData_Stop(devh)) < 0)
            fprintf(stderr, "error %d\n", ret);
        else
            fprintf(stdout, "受信を停止しました。\n");
    } else if (get_flag) {
        data = new byte[MAX_BYTE_ARRAY_SIZE];

        if ((ret = readUSBIRData(devh, data, MAX_BYTE_ARRAY_SIZE, &ibit_len)) < 0)
            fprintf(stderr, "error %d\n", ret);
        else {
            fprintf(stderr, "取得したbyte配列の要素数:%d\n", ibit_len * 4);
            if (ibit_len > 0) {
                for (fi = 0; fi < ibit_len * 4 - 1; fi++)
                    fprintf(stdout, "0x%02x,", data[fi]);
                fprintf(stdout, "0x%02x", data[ibit_len * 4 - 1]);
            }
        }
    } else if (pla_flag) {
        switch (plaindex) {
        case Plarail_StopA:
            if ((ret = writeUSBIR_Plarail_Stop(devh, PLARAIL_BAND_BAND_A)) < 0)
                fprintf(stderr, "error %d\n", ret);
            break;
        case Plarail_StopB:
            if ((ret = writeUSBIR_Plarail_Stop(devh, PLARAIL_BAND_BAND_B)) < 0)
                fprintf(stderr, "error %d\n", ret);
            break;
        case Plarail_Speed_UpAF:
            if ((ret = writeUSBIR_Plarail_Speed_Up(devh, PLARAIL_BAND_BAND_A, PLARAIL_DIRECTION_FORWARD)) < 0)
                fprintf(stderr, "error %d\n", ret);
            break;
        case Plarail_Speed_UpAB:
            if ((ret = writeUSBIR_Plarail_Speed_Up(devh, PLARAIL_BAND_BAND_A, PLARAIL_DIRECTION_BACKWARD)) < 0)
                fprintf(stderr, "error %d\n", ret);
            break;
        case Plarail_Speed_UpBF:
            if ((ret = writeUSBIR_Plarail_Speed_Up(devh, PLARAIL_BAND_BAND_B, PLARAIL_DIRECTION_FORWARD)) < 0)
                fprintf(stderr, "error %d\n", ret);
            break;
        case Plarail_Speed_UpBB:
            if ((ret = writeUSBIR_Plarail_Speed_Up(devh, PLARAIL_BAND_BAND_B, PLARAIL_DIRECTION_BACKWARD)) < 0)
                fprintf(stderr, "error %d\n", ret);
            break;
        case Plarail_Speed_DownA:
            if ((ret = writeUSBIR_Plarail_Speed_Down(devh, PLARAIL_BAND_BAND_A)) < 0)
                fprintf(stderr, "error %d\n", ret);
            break;
        case Plarail_Speed_DownB:
            if ((ret = writeUSBIR_Plarail_Speed_Down(devh, PLARAIL_BAND_BAND_B)) < 0)
                fprintf(stderr, "error %d\n", ret);
            break;
        default:
            break;
        }
    }

    /* close device */
    close_device(ctx, devh);
    return ret;
}
