#include <iostream>
#include <memory>
#include <string>

#include <grpc++/ext/proto_server_reflection_plugin.h>
#include <grpc++/grpc++.h>

#include "bto/ir_service.grpc.pb.h"
#include "btoir.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class IRServiceImpl final : public bto::IRService::Service {
    Status Write(ServerContext* context, const bto::WriteRequest* request, bto::Result* response) override {
        const auto data = reinterpret_cast<const byte*>(request->data().c_str());
        const auto length = request->data().length();

        const auto ret = bto_write(nullptr, request->frequency(), data, length);
        response->set_code(ret);

        return Status::OK;
    }

    Status RecStart(ServerContext* context, const bto::RecStartRequest* request, bto::Result* response) override {
        const auto ret = bto_rec_start(nullptr, request->frequency());
        response->set_code(ret);

        return Status::OK;
    }

    Status RecStop(ServerContext* context, const bto::Empty* request, bto::Result* response) override {
        const auto ret = bto_rec_stop(nullptr);
        response->set_code(ret);

        return Status::OK;
    }

    Status DumpRecord(ServerContext* context, const bto::Empty* request, bto::DumpRecordResponse* response) override {
        uint actual_size = 0;
        auto data = new byte[MAX_BYTE_ARRAY_SIZE];
        const auto ret = bto_dump_record(nullptr, data, MAX_BYTE_ARRAY_SIZE, &actual_size);
        // response->set_data(data);

        return Status::OK;
    }
};

void run_server() {
    std::string server_address("0.0.0.0:50051");

    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
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

int main(int ac, char** av) {
    run_server();
}
