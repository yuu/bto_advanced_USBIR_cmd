#include <fstream>

#include "cmdline.h"

#include <grpc++/grpc++.h>
#include "bto/ir_service.grpc.pb.h"

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
            std::cout << std::hex << y;
            x = std::stoi(y.data(), nullptr, 16);
            req.add_data(x);
        }
        std::cout << std::endl;

        req.set_frequency(38000);

        grpc::Status status = this->stub_->Write(&ctx, req, &res);
        if (status.ok()) {
            std::cout << "OK" << std::endl;
            std::cout << res.code() << std::endl;
            return;
        }

        std::cout << "NG" << std::endl;
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }

private:
    std::unique_ptr<bto::IRService::Stub> stub_;
};

int main(int argc, char **argv) {
    auto p = parser_build(argc, argv);

    std::stringstream fmt;
    fmt << p.get<std::string>("host") << ":" << p.get<int>("port");
    const auto addr = fmt.str();
    std::cout << "connect: " << addr << std::endl;

    auto chan = grpc::CreateChannel(addr, grpc::InsecureChannelCredentials());
    IRServiceClient client(chan);

    auto fpath = p.get<std::string>("file");
    std::fstream fs;
    fs.open(fpath, std::fstream::in);
    if (!fs.is_open()) {
        std::cout << "open error" << std::endl;
    }

    client.write(fs);

    return 0;
}
