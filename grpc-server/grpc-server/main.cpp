//
//  main.cpp
//  grpc-server
//
//  Created by 王晓鹏 on 2020/4/19.
//  Copyright © 2020 王晓鹏. All rights reserved.
//

#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "helloworld.grpc.pb.h"
#include "bilateral_stream.grpc.pb.h"


using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

using bilateralstream::Message;
using bilateralstream::BidirectionalStream;

class BidirectionalStreamImpl final : public BidirectionalStream::Service {
    
public:
    BidirectionalStreamImpl() {
        index = 0;
    }
    Status SayHello(ServerContext* context,
                     ServerReaderWriter<Message, Message>* stream) override {
        Message msg;
        while (stream->Read(&msg)) {
             std::cout << "BidirectionalStreamImpl Got message " << msg.content() << std::endl;
            std::unique_lock<std::mutex> lock(mu_);
            
            Message newMsg;
            newMsg.set_content(msg.content() + "-" + std::to_string(index));
            index++;
            
            std::cout << "BidirectionalStreamImpl Send message " << newMsg.content() << std::endl;
            stream->Write(newMsg);
        }
        return Status::OK;
    }
    
private:
    std::mutex mu_;
    int index;
};


// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service {
    Status SayHello(ServerContext* context, const HelloRequest* request,
                    HelloReply* reply) override {
        std::string prefix("Hello ");
        std::cout << "GreeterServiceImpl Got message " << request->name() << std::endl;

        reply->set_message(prefix + request->name());
        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    
    GreeterServiceImpl service;
    BidirectionalStreamImpl service2;

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    builder.RegisterService(&service2);

    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    
    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}
int main(int argc, const char * argv[]) {
    RunServer();
    
    return 0;
}
