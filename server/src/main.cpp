#include <memory>
#include <string>
#include <iostream>

#include <grpc++/grpc++.h>

#include "bto/ir_service.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
// using grpc::ServerContext;
// using grpc::Status;

class IRServiceImpl final : public bto::IRService::Service {
    virtual ::grpc::Status Write(::grpc::ServerContext* context, const ::bto::WriteRequest* request, ::bto::Result* response) override {
        std::cout << "Write function" << std::endl;
        response->set_code(200);
        return ::grpc::Status::OK;
    }
};

void run_server() {
    std::string server_address("0.0.0.0:50051");

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    // Register "service" as the instance through which we'll communicate with clients.
    // In this case it corresponds to an *synchronous* service.
    IRServiceImpl service;
    builder.RegisterService(&service);

    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown.
    // Note that some other thread must be responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int ac, char **av) {
    run_server();
}
