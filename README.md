protoc --cpp_out=. helloworld.proto  
protoc --grpc_out=. --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin helloworld.proto  


protoc --cpp_out=. bilateral_stream.proto  
protoc --grpc_out=. --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin bilateral_stream.proto  