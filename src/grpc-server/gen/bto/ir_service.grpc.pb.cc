// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: bto/ir_service.proto

#include "bto/ir_service.pb.h"
#include "bto/ir_service.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace bto {

static const char* IRService_method_names[] = {
  "/bto.IRService/Write",
  "/bto.IRService/RecStart",
  "/bto.IRService/RecStop",
  "/bto.IRService/DumpRecord",
};

std::unique_ptr< IRService::Stub> IRService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< IRService::Stub> stub(new IRService::Stub(channel));
  return stub;
}

IRService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_Write_(IRService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_RecStart_(IRService_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_RecStop_(IRService_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_DumpRecord_(IRService_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status IRService::Stub::Write(::grpc::ClientContext* context, const ::bto::WriteRequest& request, ::bto::Result* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Write_, context, request, response);
}

void IRService::Stub::experimental_async::Write(::grpc::ClientContext* context, const ::bto::WriteRequest* request, ::bto::Result* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Write_, context, request, response, std::move(f));
}

void IRService::Stub::experimental_async::Write(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::bto::Result* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_Write_, context, request, response, std::move(f));
}

void IRService::Stub::experimental_async::Write(::grpc::ClientContext* context, const ::bto::WriteRequest* request, ::bto::Result* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Write_, context, request, response, reactor);
}

void IRService::Stub::experimental_async::Write(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::bto::Result* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_Write_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::bto::Result>* IRService::Stub::AsyncWriteRaw(::grpc::ClientContext* context, const ::bto::WriteRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::bto::Result>::Create(channel_.get(), cq, rpcmethod_Write_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::bto::Result>* IRService::Stub::PrepareAsyncWriteRaw(::grpc::ClientContext* context, const ::bto::WriteRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::bto::Result>::Create(channel_.get(), cq, rpcmethod_Write_, context, request, false);
}

::grpc::Status IRService::Stub::RecStart(::grpc::ClientContext* context, const ::bto::RecStartRequest& request, ::bto::Result* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_RecStart_, context, request, response);
}

void IRService::Stub::experimental_async::RecStart(::grpc::ClientContext* context, const ::bto::RecStartRequest* request, ::bto::Result* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_RecStart_, context, request, response, std::move(f));
}

void IRService::Stub::experimental_async::RecStart(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::bto::Result* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_RecStart_, context, request, response, std::move(f));
}

void IRService::Stub::experimental_async::RecStart(::grpc::ClientContext* context, const ::bto::RecStartRequest* request, ::bto::Result* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_RecStart_, context, request, response, reactor);
}

void IRService::Stub::experimental_async::RecStart(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::bto::Result* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_RecStart_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::bto::Result>* IRService::Stub::AsyncRecStartRaw(::grpc::ClientContext* context, const ::bto::RecStartRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::bto::Result>::Create(channel_.get(), cq, rpcmethod_RecStart_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::bto::Result>* IRService::Stub::PrepareAsyncRecStartRaw(::grpc::ClientContext* context, const ::bto::RecStartRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::bto::Result>::Create(channel_.get(), cq, rpcmethod_RecStart_, context, request, false);
}

::grpc::Status IRService::Stub::RecStop(::grpc::ClientContext* context, const ::bto::Empty& request, ::bto::Result* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_RecStop_, context, request, response);
}

void IRService::Stub::experimental_async::RecStop(::grpc::ClientContext* context, const ::bto::Empty* request, ::bto::Result* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_RecStop_, context, request, response, std::move(f));
}

void IRService::Stub::experimental_async::RecStop(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::bto::Result* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_RecStop_, context, request, response, std::move(f));
}

void IRService::Stub::experimental_async::RecStop(::grpc::ClientContext* context, const ::bto::Empty* request, ::bto::Result* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_RecStop_, context, request, response, reactor);
}

void IRService::Stub::experimental_async::RecStop(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::bto::Result* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_RecStop_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::bto::Result>* IRService::Stub::AsyncRecStopRaw(::grpc::ClientContext* context, const ::bto::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::bto::Result>::Create(channel_.get(), cq, rpcmethod_RecStop_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::bto::Result>* IRService::Stub::PrepareAsyncRecStopRaw(::grpc::ClientContext* context, const ::bto::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::bto::Result>::Create(channel_.get(), cq, rpcmethod_RecStop_, context, request, false);
}

::grpc::Status IRService::Stub::DumpRecord(::grpc::ClientContext* context, const ::bto::Empty& request, ::bto::DumpRecordResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_DumpRecord_, context, request, response);
}

void IRService::Stub::experimental_async::DumpRecord(::grpc::ClientContext* context, const ::bto::Empty* request, ::bto::DumpRecordResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DumpRecord_, context, request, response, std::move(f));
}

void IRService::Stub::experimental_async::DumpRecord(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::bto::DumpRecordResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc_impl::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_DumpRecord_, context, request, response, std::move(f));
}

void IRService::Stub::experimental_async::DumpRecord(::grpc::ClientContext* context, const ::bto::Empty* request, ::bto::DumpRecordResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_DumpRecord_, context, request, response, reactor);
}

void IRService::Stub::experimental_async::DumpRecord(::grpc::ClientContext* context, const ::grpc::ByteBuffer* request, ::bto::DumpRecordResponse* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc_impl::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_DumpRecord_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::bto::DumpRecordResponse>* IRService::Stub::AsyncDumpRecordRaw(::grpc::ClientContext* context, const ::bto::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::bto::DumpRecordResponse>::Create(channel_.get(), cq, rpcmethod_DumpRecord_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::bto::DumpRecordResponse>* IRService::Stub::PrepareAsyncDumpRecordRaw(::grpc::ClientContext* context, const ::bto::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncResponseReaderFactory< ::bto::DumpRecordResponse>::Create(channel_.get(), cq, rpcmethod_DumpRecord_, context, request, false);
}

IRService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      IRService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< IRService::Service, ::bto::WriteRequest, ::bto::Result>(
          [](IRService::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::bto::WriteRequest* req,
             ::bto::Result* resp) {
               return service->Write(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      IRService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< IRService::Service, ::bto::RecStartRequest, ::bto::Result>(
          [](IRService::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::bto::RecStartRequest* req,
             ::bto::Result* resp) {
               return service->RecStart(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      IRService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< IRService::Service, ::bto::Empty, ::bto::Result>(
          [](IRService::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::bto::Empty* req,
             ::bto::Result* resp) {
               return service->RecStop(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      IRService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< IRService::Service, ::bto::Empty, ::bto::DumpRecordResponse>(
          [](IRService::Service* service,
             ::grpc_impl::ServerContext* ctx,
             const ::bto::Empty* req,
             ::bto::DumpRecordResponse* resp) {
               return service->DumpRecord(ctx, req, resp);
             }, this)));
}

IRService::Service::~Service() {
}

::grpc::Status IRService::Service::Write(::grpc::ServerContext* context, const ::bto::WriteRequest* request, ::bto::Result* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status IRService::Service::RecStart(::grpc::ServerContext* context, const ::bto::RecStartRequest* request, ::bto::Result* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status IRService::Service::RecStop(::grpc::ServerContext* context, const ::bto::Empty* request, ::bto::Result* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status IRService::Service::DumpRecord(::grpc::ServerContext* context, const ::bto::Empty* request, ::bto::DumpRecordResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace bto

