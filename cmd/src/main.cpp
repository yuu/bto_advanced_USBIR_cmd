#include <getopt.h>
#include <libusb.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "btoir.h"

#define OPTION_NUM 10

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

void setup_optargs(struct option options[]) {
    int fi;
    for (fi = 0; fi < OPTION_NUM - 2; fi++) {
        options[fi].name = PLAOPTIONlist[fi];
        options[fi].has_arg = no_argument;
        options[fi].flag = NULL;
        options[fi].val = 1;
    }

    options[OPTION_NUM - 2].name = "version";
    options[OPTION_NUM - 2].has_arg = no_argument;
    options[OPTION_NUM - 2].flag = NULL;
    options[OPTION_NUM - 2].val = 2;
    options[OPTION_NUM - 1].name = 0;
    options[OPTION_NUM - 1].has_arg = 0;
    options[OPTION_NUM - 1].flag = NULL;
    options[OPTION_NUM - 1].val = 0;
}

void usage(char *fname) {
    fprintf(stderr, "usage: %s <option>\n", fname);
    fprintf(stderr, "  -f <freq>\t-dオプションまたは -rオプションを指定した場合のみ使用できます。\n");
    fprintf(stderr, "           \t指定しない場合は%dになります。\n", IR_FREQ_DEFAULT);
    fprintf(stderr, "  -t {AEHA,NEC,SONY,MITSUBISHI}\n");
    fprintf(stderr, "  -c <code>\t家電協(AEHA)フォーマット、NECフォーマット、SONYフォーマット、三菱フォーマットの\n");
    fprintf(stderr, "           \tコードデータをこの -cオプション引数として指定します。\n");
    fprintf(stderr,
            "           \t書式は-dオプションと同じ 0xFF,0xFF,... です。必ず-tオプションとセットで指定します。\n");
    fprintf(stderr, "  -C <Code>\t家電協(AEHA)フォーマット、NECフォーマット、SONYフォーマット、三菱フォーマットの\n");
    fprintf(stderr, "           \tコードデータをこの -Cオプション引数として指定します。\n");
    fprintf(stderr, "           \t書式は0xの付かない16進文字列 FFFF... です。必ず-tオプションとセットで指定します。\n");
    fprintf(stderr, "  -d <data>\t受信設定または送信設定コンフィグレーションツールで、クリップボードに\n");
    fprintf(stderr, "           \tコピーボタンでコピーしたデータ、または、-gオプションで取得したデータが、\n");
    fprintf(stderr, "           \tこの -dオプション引数として使用可能です。\n");
    fprintf(stderr, "           \t-fオプションのみ追加で指定可能です。\n");
    fprintf(stderr, "  -r       \t受信開始を指令します。\n");
    fprintf(stderr, "           \t-fオプションのみ追加で指定可能です。\n");
    fprintf(stderr, "           \t受信設定または送信設定コンフィグレーションツールで取得できるデータが、\n");
    fprintf(stderr, "           \t本コマンドでも取得できます。\n");
    fprintf(stderr, "  -s       \t受信停止を指令します。\n");
    fprintf(stderr, "  -g       \t直前に受信を終えたデータが所得できます。\n");
    fprintf(stderr, "  --Plarail_StopA\t\tこのオプションは必ず単独で指定します。\n");
    fprintf(stderr, "  --Plarail_StopB\t\tこのオプションは必ず単独で指定します。\n");
    fprintf(stderr, "  --Plarail_Speed_UpAF\t\tこのオプションは必ず単独で指定します。\n");
    fprintf(stderr, "  --Plarail_Speed_UpAB\t\tこのオプションは必ず単独で指定します。\n");
    fprintf(stderr, "  --Plarail_Speed_UpBF\t\tこのオプションは必ず単独で指定します。\n");
    fprintf(stderr, "  --Plarail_Speed_UpBB\t\tこのオプションは必ず単独で指定します。\n");
    fprintf(stderr, "  --Plarail_Speed_DownA\t\tこのオプションは必ず単独で指定します。\n");
    fprintf(stderr, "  --Plarail_Speed_DownB\t\tこのオプションは必ず単独で指定します。\n");
    fprintf(stderr, "  --version\n");
    fprintf(stderr,
            "※ getopt_longモジュールの制限を回避する為、プラレール用のオプションは末尾まで正確に指定して下さい。\n\n");
    fprintf(stderr, "使い方の例\n");
    fprintf(stderr, "受信系\n");
    fprintf(stderr, "$ bto_advanced_USBIR_cmd -r         # (生データ)受信開始\n");
    fprintf(stderr, "$ bto_advanced_USBIR_cmd -s         # (生データ)受信停止\n");
    fprintf(stderr, "$ bto_advanced_USBIR_cmd -g | tee data.txt  # 生データ所得\n\n");
    fprintf(stderr, "送信系\n");
    fprintf(stderr, "$ bto_advanced_USBIR_cmd -d `cat data.txt`\n");
    fprintf(stderr, "$ bto_advanced_USBIR_cmd -t AEHA       -C 123456789ABC\n");
    fprintf(stderr, "$ bto_advanced_USBIR_cmd -t NEC        -C 08F6817E\n");
    fprintf(stderr, "$ bto_advanced_USBIR_cmd -t SONY       -C 08F6817E\n");
    fprintf(stderr, "$ bto_advanced_USBIR_cmd -t MITSUBISHI -C 08F6817E\n");
    fprintf(stderr, "$ bto_advanced_USBIR_cmd --Plarail_Speed_UpAF\n");
}

void version(char *fname) {
    fprintf(stderr, "%s\t%s\n", fname, APP_VERSION);
    fprintf(stderr, "Copyright (C) 2015   Bit Trade One, LTD.\n");
    fprintf(stderr, "ライセンス:ADL   ADLの内容は:http://bit-trade-one.co.jp/adl/\n");
}

int main(int argc, char *argv[]) {
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

    btoir *bto = bto_open();
    libusb_device_handle *devh = bto->dev_handle;

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

    bto_close(bto);

    return ret;
}
