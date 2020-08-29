#pragma once

#include <memory>
#include <string>

#include "bto/ir_service.grpc.pb.h"

#include "btoir.h"
#include "ir.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

template <class IR>
class IRServiceImpl final : public bto::IRService::Service {
public:
    IRServiceImpl(std::unique_ptr<IR> ir)
        : bto::IRService::Service()
        , ir(std::move(ir)) {}

    Status Write(ServerContext* context,
                 const bto::WriteRequest* request,
                 bto::WriteResponse* response) override {
        const auto length = request->data().size();
        const auto data = request->data().data();

        const auto ret = ir->write(request->frequency(), data, length);
        response->set_code(ret);

        return Status::OK;
    }

    Status RecStart(ServerContext* context,
                    const bto::RecStartRequest* request,
                    bto::RecStartResponse* response) override {
        const auto ret = ir->rec_start(request->frequency());
        response->set_code(ret);

        return Status::OK;
    }

    Status RecStop(ServerContext* context,
                   const bto::RecStopRequest* request,
                   bto::RecStopResponse* response) override {
        const auto ret = ir->rec_stop();
        response->set_code(ret);

        return Status::OK;
    }

    Status DumpRecord(ServerContext* context,
                      const bto::DumpRecordRequest* request,
                      bto::DumpRecordResponse* response) override {
        auto data = std::make_unique<byte[]>(MAX_BYTE_ARRAY_SIZE);

        uint actual_size = 0;
        const auto ret = ir->dump_record(data.get(), MAX_BYTE_ARRAY_SIZE, &actual_size);
        response->set_code(ret);

        const auto max = actual_size * 4;
        for (int32_t i = 0; i < max; ++i) {
            response->add_data(data[i]);
        }

        return Status::OK;
    }

private:
    std::unique_ptr<IR> ir;
};
