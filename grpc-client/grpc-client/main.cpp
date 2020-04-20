//
//  main.cpp
//  grpc-client
//
//  Created by 王晓鹏 on 2020/4/19.
//  Copyright © 2020 王晓鹏. All rights reserved.
//


#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include<chrono>


#include <grpcpp/grpcpp.h>

#include "helloworld.grpc.pb.h"
#include "bilateral_stream.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;

using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

using bilateralstream::Message;
using bilateralstream::BidirectionalStream;

class GreeterClient {
public:
    GreeterClient(std::shared_ptr<Channel> channel)
    : stub_(Greeter::NewStub(channel)),
    stub2_(BidirectionalStream::NewStub(channel)){}
    
    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    std::string SayHello(const std::string& user) {
        // Data we are sending to the server.
        HelloRequest request;
        request.set_name(user);
        
        // Container for the data we expect from the server.
        HelloReply reply;
        
        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;
        
        // The actual RPC.
        Status status = stub_->SayHello(&context, request, &reply);
        
        // Act upon its status.
        if (status.ok()) {
            return reply.message();
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
            << std::endl;
            return "RPC failed";
        }
    }
    
    void SayHello2() {
        ClientContext context;
        std::shared_ptr<ClientReaderWriter<Message, Message> > stream(stub2_->SayHello(&context));
        
        std::thread writer([stream]() {
            while (true) {
                Message msg;
                msg.set_content("hello");
                
                std::cout << "Send message " << msg.content() << std::endl;
                stream->Write(msg);
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            }
         
//            stream->WritesDone();
        });
        
        Message msg;
        while (stream->Read(&msg)) {
            std::cout << "Got message " << msg.content() << std::endl;
        }
        writer.join();
        Status status = stream->Finish();
        if (!status.ok()) {
            std::cout << "BidirectionalStream rpc failed." << std::endl;
        }
    }

    
private:
    std::unique_ptr<Greeter::Stub> stub_;
    std::unique_ptr<BidirectionalStream::Stub> stub2_;

};
int main(int argc, const char * argv[]) {
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    GreeterClient greeter(grpc::CreateChannel(
                                              "127.0.0.1:50051", grpc::InsecureChannelCredentials()));
    std::string user("world");
    std::string reply = greeter.SayHello(user);
    std::cout << "Greeter received: " << reply << std::endl;
    
    greeter.SayHello2();
    
    
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    return 0;
}
