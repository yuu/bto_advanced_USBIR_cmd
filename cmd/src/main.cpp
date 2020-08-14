#include <getopt.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <vector>
#include <functional>
#include <tuple>
#include <memory>
#include <string>
#include <stdexcept>

#include "btoir.h"

#define OPTION_NUM 10
#define FORMAT_NUM 4

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

static const char *FORMATlist[FORMAT_NUM] = {
    "AEHA",
    "NEC",
    "SONY",
    "MITSUBISHI"
};

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args) {
    size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if ( size <= 0 ) { throw std::runtime_error("Error during formatting."); }
    std::unique_ptr<char[]> buf(new char[ size ]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

std::unique_ptr<struct option[]> setup_optargs() {
    auto options = std::make_unique<struct option[]>(OPTION_NUM);

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

    return options;
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
    int freq_flag = 0;
    int type_flag = 0;
    int code_flag = 0;
    int Code_flag = 0;
    int str_len = 0;
    int data_flag = 0;
    int pla_flag = 0;
    int read_flag = 0;
    int stop_flag = 0;
    int get_flag = 0;
    byte *data = NULL;
    uint dataCount = 0;
    byte *code = NULL;
    uint codeCount = 0;
    char *endPtr;
    int placounter = 0, plaindex;
    IR_FORMAT typeindex = IR_FORMAT_INVALID;

    {
        auto optionss = setup_optargs();
        auto options = optionss.get();
        int ret = 1;
        int option_index;
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
            case 'd': {
                char *s;
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
            }
            case 'c': {
                char *s;
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
            }
            case 'C': {
                Code_flag = 1;
                str_len = strlen(optarg);
                char hex_buff[5] = "\0";
                for (auto fi = 0; fi < str_len / 2; fi++) {
                    strcpy(hex_buff, "0x");
                    strncat(hex_buff, &optarg[fi * 2], 2);

                    if (code != NULL) {
                        delete code;
                        code = new byte[codeCount + 1];
                    } else {
                        code = new byte[codeCount + 1];
                    }
                    code[codeCount++] = (byte)strtol(hex_buff, &endPtr, 0);
                }
                break;
            }
            case 'f':
                freq_flag = 1;
                frequency = atoi(optarg);
                break;
            case 't': {
                type_flag = 1;
                const auto ret =
                    std::find_if(std::begin(FORMATlist), std::end(FORMATlist),
                                 [optarg = optarg](auto ele) { return strcmp(optarg, ele) == 0; });
                const auto i = std::distance(std::begin(FORMATlist), ret);
                if (i >= FORMAT_NUM)
                    typeindex = IR_FORMAT_INVALID;
                else
                    typeindex = static_cast<IR_FORMAT>(i+1);
                break;
            }
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
    }

#define RTH(cond, msg) \
    [freq_flag, type_flag, code_flag, Code_flag, data_flag, pla_flag, read_flag, stop_flag, get_flag, placounter, dataCount, typeindex, str_len] \
        () { return std::make_tuple((cond), msg); }

    using namespace std::string_literals;
    const std::vector<std::function<std::tuple<bool, std::string>()>> rules = {
        RTH((code_flag || Code_flag) && data_flag, "エラー: -dオプションと-cまたは-Cオプションとは同時に指定できません。\n"s),
        RTH(code_flag && Code_flag, "エラー: -cオプションと-Cオプションとは同時に指定できません。\n"),
        RTH(freq_flag && (code_flag || Code_flag), "エラー: -rまたは-Cオプションと-fオプションは同時に指定できません。\n"s),
        RTH((code_flag || Code_flag || data_flag) && (read_flag || stop_flag || get_flag),
            "エラー: 送信系専用のオプション：-c、-C、-dオプションと受信系専用のオプション：-r、-s、-gオプションは同時に指定できません。\n"s),
        RTH((read_flag && stop_flag) || (stop_flag && get_flag) || (read_flag && get_flag), "エラー: -rオプション、-sオプション、-gオプションは同時に指定できません。\n"s),
        RTH(freq_flag && (stop_flag || get_flag), "エラー: -sまたは-gオプションと-fオプションは同時に指定できません。\n"s),
        RTH(((!type_flag) && (code_flag || Code_flag)) || (((!code_flag) && (!Code_flag)) && type_flag), "エラー: -tオプションと-cまたは-Cオプションとは必ずセットで指定して下さい。\n"s),
        RTH(((!data_flag) || (!read_flag)) && freq_flag, "エラー: -fオプションは-dオプションまたは-rオプションを指定した場合のみ使用できます。\n"s),
        RTH(pla_flag && (freq_flag || type_flag || data_flag || code_flag || read_flag || stop_flag || get_flag), "エラー: プラレール赤外線命令オプションは単独で指定して下さい。\n"s),
        RTH(stop_flag && (freq_flag || type_flag || data_flag || code_flag || read_flag || get_flag), "エラー: -sオプションは単独で指定して下さい。\n"s),
        RTH(placounter > 1, "エラー: プラレール赤外線命令オプションは単独で指定して下さい。\n"),
        RTH(data_flag && ((dataCount % 2) != 0), string_format("エラー: データの総数は偶数である必要があります。: %d\n", dataCount)),
        RTH(type_flag && typeindex == IR_FORMAT_INVALID, "エラー: 正しい赤外線フォーマットのタイプを指定して下さい。\n"s),
        RTH(Code_flag && (str_len % 2) != 0, string_format("エラー: コード長は2の倍数である必要があります。: %d\n", str_len)),
    };
#undef RTH

    if ((!type_flag) && (!freq_flag) && (!code_flag) && (!Code_flag) && (!data_flag) && (!pla_flag) && (!read_flag) &&
        (!stop_flag) && (!get_flag)) {
        usage(argv[0]);
        exit(1);
    }

    for (const auto rule : rules) {
        if (const auto ret = rule(); std::get<0>(ret)) {
            fprintf(stderr, "%s", std::get<1>(ret).c_str());
            exit(1);
        }
    }

    btoir *bto = bto_open();
    if (bto == nullptr) {
        exit(1);
    }

    const auto command =
        [=]() {
            int ret = 1;
            if (data_flag) {
                if ((ret = writeUSBIRData(bto, frequency, data, dataCount)) < 0)
                    fprintf(stderr, "error %d\n", ret);
                return ret;
            }
            if (code_flag || Code_flag) {
                if ((ret = writeUSBIR(bto, typeindex, code, codeCount * 8)) < 0)
                    fprintf(stderr, "error %d\n", ret);
                return ret;
            }
            if (read_flag) {
                if ((ret = recUSBIRData_Start(bto, frequency)) < 0)
                    fprintf(stderr, "error %d\n", ret);
                else
                    fprintf(stdout, "受信を開始しました。\n");
                return ret;
            }
            if (stop_flag) {
                if ((ret = recUSBIRData_Stop(bto)) < 0)
                    fprintf(stderr, "error %d\n", ret);
                else
                    fprintf(stdout, "受信を停止しました。\n");
                return ret;
            }
            if (get_flag) {
                auto data = new byte[MAX_BYTE_ARRAY_SIZE];
                uint ibit_len = 0;
                if ((ret = readUSBIRData(bto, data, MAX_BYTE_ARRAY_SIZE, &ibit_len)) < 0)
                    fprintf(stderr, "error %d\n", ret);
                else {
                    fprintf(stderr, "取得したbyte配列の要素数:%d\n", ibit_len * 4);
                    if (ibit_len > 0) {
                        for (auto fi = 0; fi < ibit_len * 4 - 1; fi++)
                            fprintf(stdout, "0x%02x,", data[fi]);
                        fprintf(stdout, "0x%02x", data[ibit_len * 4 - 1]);
                    }
                }
                return ret;
            }
            if (pla_flag) {
                switch (plaindex) {
                case Plarail_StopA:
                    if ((ret = writeUSBIR_Plarail_Stop(bto, PLARAIL_BAND_BAND_A)) < 0)
                        fprintf(stderr, "error %d\n", ret);
                    break;
                case Plarail_StopB:
                    if ((ret = writeUSBIR_Plarail_Stop(bto, PLARAIL_BAND_BAND_B)) < 0)
                        fprintf(stderr, "error %d\n", ret);
                    break;
                case Plarail_Speed_UpAF:
                    if ((ret = writeUSBIR_Plarail_Speed_Up(bto, PLARAIL_BAND_BAND_A, PLARAIL_DIRECTION_FORWARD)) < 0)
                        fprintf(stderr, "error %d\n", ret);
                    break;
                case Plarail_Speed_UpAB:
                    if ((ret = writeUSBIR_Plarail_Speed_Up(bto, PLARAIL_BAND_BAND_A, PLARAIL_DIRECTION_BACKWARD)) < 0)
                        fprintf(stderr, "error %d\n", ret);
                    break;
                case Plarail_Speed_UpBF:
                    if ((ret = writeUSBIR_Plarail_Speed_Up(bto, PLARAIL_BAND_BAND_B, PLARAIL_DIRECTION_FORWARD)) < 0)
                        fprintf(stderr, "error %d\n", ret);
                    break;
                case Plarail_Speed_UpBB:
                    if ((ret = writeUSBIR_Plarail_Speed_Up(bto, PLARAIL_BAND_BAND_B, PLARAIL_DIRECTION_BACKWARD)) < 0)
                        fprintf(stderr, "error %d\n", ret);
                    break;
                case Plarail_Speed_DownA:
                    if ((ret = writeUSBIR_Plarail_Speed_Down(bto, PLARAIL_BAND_BAND_A)) < 0)
                        fprintf(stderr, "error %d\n", ret);
                    break;
                case Plarail_Speed_DownB:
                    if ((ret = writeUSBIR_Plarail_Speed_Down(bto, PLARAIL_BAND_BAND_B)) < 0)
                        fprintf(stderr, "error %d\n", ret);
                    break;
                default:
                    break;
                }
                return ret;
            }
            return ret;
        };

    const auto ret = command();

    bto_close(bto);

    return ret;
}
