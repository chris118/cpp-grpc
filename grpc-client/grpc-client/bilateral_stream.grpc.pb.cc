// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: bilateral_stream.proto

#include "bilateral_stream.pb.h"
#include "bilateral_stream.grpc.pb.h"

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
namespace bilateralstream {

static const char* BidirectionalStream_method_names[] = {
  "/bilateralstream.BidirectionalStream/SayHello",
};

std::unique_ptr< BidirectionalStream::Stub> BidirectionalStream::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< BidirectionalStream::Stub> stub(new BidirectionalStream::Stub(channel));
  return stub;
}

BidirectionalStream::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_SayHello_(BidirectionalStream_method_names[0], ::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::bilateralstream::Message, ::bilateralstream::Message>* BidirectionalStream::Stub::SayHelloRaw(::grpc::ClientContext* context) {
  return ::grpc_impl::internal::ClientReaderWriterFactory< ::bilateralstream::Message, ::bilateralstream::Message>::Create(channel_.get(), rpcmethod_SayHello_, context);
}

void BidirectionalStream::Stub::experimental_async::SayHello(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::bilateralstream::Message,::bilateralstream::Message>* reactor) {
  ::grpc_impl::internal::ClientCallbackReaderWriterFactory< ::bilateralstream::Message,::bilateralstream::Message>::Create(stub_->channel_.get(), stub_->rpcmethod_SayHello_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::bilateralstream::Message, ::bilateralstream::Message>* BidirectionalStream::Stub::AsyncSayHelloRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc_impl::internal::ClientAsyncReaderWriterFactory< ::bilateralstream::Message, ::bilateralstream::Message>::Create(channel_.get(), cq, rpcmethod_SayHello_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::bilateralstream::Message, ::bilateralstream::Message>* BidirectionalStream::Stub::PrepareAsyncSayHelloRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc_impl::internal::ClientAsyncReaderWriterFactory< ::bilateralstream::Message, ::bilateralstream::Message>::Create(channel_.get(), cq, rpcmethod_SayHello_, context, false, nullptr);
}

BidirectionalStream::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      BidirectionalStream_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< BidirectionalStream::Service, ::bilateralstream::Message, ::bilateralstream::Message>(
          std::mem_fn(&BidirectionalStream::Service::SayHello), this)));
}

BidirectionalStream::Service::~Service() {
}

::grpc::Status BidirectionalStream::Service::SayHello(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::bilateralstream::Message, ::bilateralstream::Message>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace bilateralstream
