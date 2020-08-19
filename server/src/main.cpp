#include <iostream>
#include <memory>
#include <string>

#include <grpc++/ext/proto_server_reflection_plugin.h>
#include <grpc++/grpc++.h>

#include "irservice_impl.hpp"

void run_server(IR *ir) {
    std::string server_address("0.0.0.0:50051");

    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());

    // Register "service" as the instance through which we'll communicate with clients.
    // In this case it corresponds to an *synchronous* service.
    IRServiceImpl service(std::move(std::unique_ptr<IR>(ir)));
    builder.RegisterService(&service);

    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown.
    // Note that some other thread must be responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int ac, char** av) {
    auto ir = new IR();
    assert(ir->bto != NULL);

    run_server(ir);
}
