#include "load_balancer.h"
#include "dns_resolver.h"
#include <stdexcept>

grpc::Status LoadBalancer::BalanceLoad(grpc::ServerContext* context, const BalanceRequest* request, BalanceResponse* response) {
    const std::string& service_name = request->service_name();
    
    if (service_map.find(service_name) == service_map.end()) {
        service_map[service_name] = DnsResolver::resolve(service_name);
        round_robin_counter[service_name] = 0;
    }
    
    if (service_map[service_name].empty()) {
        return grpc::Status(grpc::StatusCode::UNAVAILABLE, "No available servers");
    }
    
    size_t& counter = round_robin_counter[service_name];
    const std::vector<std::string>& servers = service_map[service_name];
    
    response->set_ip(servers[counter]);
    response->set_port(80); // Assuming HTTP
    
    counter = (counter + 1) % servers.size();
    
    return grpc::Status::OK;
}
