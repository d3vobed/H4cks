cmake_minimum_required(VERSION 3.14)

project(DnsLoadBalancer)

find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

add_executable(dns_load_balancer main.cpp load_balancer.cpp dns_resolver.cpp)

target_link_libraries(dns_load_balancer gRPC::grpc++ gRPC::grpc++_reflection protobuf::libprotobuf)
