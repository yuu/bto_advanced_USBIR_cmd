#pragma once

#include <memory>
#include <string>

#include "bto/ir_service.grpc.pb.h"

#include "ir.hpp"
#include "btoir.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

template <class IR>
class IRServiceImpl final : public bto::IRService::Service {
public:
    IRServiceImpl(std::unique_ptr<IR> ir)
        : bto::IRService::Service()
        , ir(std::move(ir)) {
    }

    Status Write(ServerContext* context, const bto::WriteRequest* request, bto::Result* response) override {
        const auto length = request->data().size();
        const auto data = request->data().data();

        const auto ret = ir->write(request->frequency(), data, length);
        response->set_code(ret);

        return Status::OK;
    }

    Status RecStart(ServerContext* context, const bto::RecStartRequest* request, bto::Result* response) override {
        const auto ret = ir->rec_start(request->frequency());
        response->set_code(ret);

        return Status::OK;
    }

    Status RecStop(ServerContext* context, const bto::Empty* request, bto::Result* response) override {
        const auto ret = ir->rec_stop();
        response->set_code(ret);

        return Status::OK;
    }

    Status DumpRecord(ServerContext* context, const bto::Empty* request, bto::DumpRecordResponse* response) override {
        uint actual_size = 0;
        auto data = new byte[MAX_BYTE_ARRAY_SIZE];
        const auto ret = ir->dump_record(data, MAX_BYTE_ARRAY_SIZE, &actual_size);
        // response->set_data(data);

        return Status::OK;
    }

private:
    std::unique_ptr<IR> ir;
};
