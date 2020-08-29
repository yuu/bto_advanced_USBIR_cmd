#include <fstream>
#include <algorithm>

#include "cmdline.h"

#include <grpc++/grpc++.h>
#include "bto/ir_service.grpc.pb.h"

#include <google/protobuf/repeated_field.h>
#include <google/protobuf/port_def.inc>

cmdline::parser parser_build(int argc, char **argv) {
    cmdline::parser p;
    p.add<std::string>("host", 'h', "host name", false, "localhost");
    p.add<int>("port", 'p', "port number", false, 50051, cmdline::range(1, 65535));
    p.add<std::string>("file", 'f', "file path for send data", true, "");
    p.parse_check(argc, argv);

    return p;
}

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
    auto p = parser_build(argc, argv);

    std::stringstream fmt;
    fmt << p.get<std::string>("host") << ":" << p.get<int>("port");
    const auto addr = fmt.str();
    std::cerr << "connect: " << addr << std::endl;

    auto chan = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    IRServiceClient client(chan);

    auto fpath = p.get<std::string>("file");
    std::fstream fs;
    fs.open(fpath, std::fstream::in);
    if (!fs.is_open()) {
        std::cerr << "open error" << std::endl;
    }

    client.write(fs);

    return 0;
}
