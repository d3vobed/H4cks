#ifndef LOAD_BALANCER_H
#define LOAD_BALANCER_H

#include <string>
#include <vector>
#include <map>
#include <grpcpp/grpcpp.h>
#include "load_balancer.grpc.pb.h"

class LoadBalancer final : public LoadBalancer::Service {
public:
    grpc::Status BalanceLoad(grpc::ServerContext* context, const BalanceRequest* request, BalanceResponse* response) override;

private:
    std::map<std::string, std::vector<std::string>> service_map;
    std::map<std::string, size_t> round_robin_counter;
};

#endif // LOAD_BALANCER_H
