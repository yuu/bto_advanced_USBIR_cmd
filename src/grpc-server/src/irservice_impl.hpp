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

    Status Write(ServerContext* context, const bto::WriteRequest* request, bto::WriteResponse* response) override {
        const auto length = request->data().size();
        const auto data = request->data().data();

        const auto ret = ir->write(request->frequency(), data, length);
        response->set_code(ret);

        return Status::OK;
    }

private:
    std::unique_ptr<IR> ir;
};
