#include <fstream>
#include <algorithm>

#include "cmdline.h"

#include <grpc++/grpc++.h>
#include "bto/ir_service.grpc.pb.h"

#include <google/protobuf/repeated_field.h>
#include <google/protobuf/port_def.inc>

class ParserBuilder {
public:
    ParserBuilder() : p(new cmdline::parser()) {}

    ~ParserBuilder() {}

    cmdline::parser fin() {
        return *p;
    }

    ParserBuilder &cmdline_parser() {
        p->add<std::string>("host", 'h', "host name", false, "localhost");
        p->add<int>("port", 'p', "port number", false, 50051, cmdline::range(1, 65535));
        return *this;;
    }

    ParserBuilder &subcmd_write() {
        p->add("write", '\0', "send data");
        p->add<std::string>("file", 'f', "file path for send data", false);
        return *this;
    }

    ParserBuilder &subcmd_rec() {
        p->add("rec-start", '\0', "record start");
        p->add("rec-stop", '\0', "record stop");
        return *this;
    }

    ParserBuilder &subcmd_dump() {
        p->add("dump", '\0', "dump record to stdout");
        return *this;
    }

private:
    cmdline::parser *p;
};

class IRServiceClient {
public:
    IRServiceClient(std::shared_ptr<grpc::Channel> channel)
        : stub_(bto::IRService::NewStub(channel)) {}

    void write(std::istream &in) {
        grpc::ClientContext ctx;
        bto::WriteRequest req;
        bto::WriteResponse res;

        uint32_t x = 0;
        std::string y;
        while (std::getline(in, y, ',')) {
            x = std::stoi(y.data(), nullptr, 16);
            req.add_data(x);
        }

        req.set_frequency(38000);

        grpc::Status status = this->stub_->Write(&ctx, req, &res);
        if (status.ok()) {
            std::cerr << "OK" << std::endl;
            std::cerr << res.code() << std::endl;
            return;
        }

        std::cerr << "NG" << std::endl;
        std::cerr << status.error_code() << ": " << status.error_message() << std::endl;
    }

    void rec_start() {
        grpc::ClientContext ctx;
        bto::RecStartRequest req;
        bto::RecStartResponse res;

        req.set_frequency(38000);
        grpc::Status status = this->stub_->RecStart(&ctx, req, &res);
        if (status.ok()) {
            std::cerr << "OK" << std::endl;
            std::cerr << res.code() << std::endl;
            return;
        }
        std::cerr << "NG" << std::endl;
    }

    void rec_stop() {
        grpc::ClientContext ctx;
        bto::RecStopRequest req;
        bto::RecStopResponse res;

        grpc::Status status = this->stub_->RecStop(&ctx, req, &res);
        if (status.ok()) {
            std::cerr << "OK" << std::endl;
            std::cerr << res.code() << std::endl;
            return;
        }
        std::cerr << "NG" << std::endl;
    }

    void dump() {
        grpc::ClientContext ctx;
        bto::DumpRecordRequest req;
        bto::DumpRecordResponse res;

        grpc::Status status = this->stub_->DumpRecord(&ctx, req, &res);
        if (status.ok()) {
            std::cerr << "OK" << std::endl;
            std::cerr << res.code() << std::endl;
            print_csv(res.data());
            return;
        }
        std::cerr << "NG" << std::endl;
    }

    void print_csv(const PROTOBUF_NAMESPACE_ID::RepeatedField<PROTOBUF_NAMESPACE_ID::uint32> & data) {
        std::cout << *data.begin();
        for (auto &&x : data) {
            std::cout << ", " << std::hex << x;
        }
        std::cout << std::endl;
    }

private:
    std::unique_ptr<bto::IRService::Stub> stub_;
};

int main(int argc, char **argv) {
    auto p = ParserBuilder()
        .cmdline_parser()
        .subcmd_write()
        .subcmd_rec()
        .subcmd_dump()
        .fin();
    p.parse_check(argc, argv);

    std::stringstream fmt;
    fmt << p.get<std::string>("host") << ":" << p.get<int>("port");
    const auto addr = fmt.str();
    std::cerr << "connect: " << addr << std::endl;

    auto chan = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    IRServiceClient client(chan);

    const auto is_write = p.exist("write");
    const auto is_recs = p.exist("rec-start");
    const auto is_rece = p.exist("rec-stop");
    const auto is_dump = p.exist("dump");
    if (is_write) {
        auto fpath = p.get<std::string>("file");
        std::fstream fs;
        fs.open(fpath, std::fstream::in);
        if (!fs.is_open()) {
            std::cerr << "open error" << std::endl;
            return 1;
        }
        client.write(fs);
    } else if (is_recs) {

    } else if (is_rece) {

    } else if (is_dump) {

    } else {
        std::cerr << p.usage() << std::endl;
    }

    return 0;
}
