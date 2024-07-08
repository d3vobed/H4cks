#include "dns_resolver.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <stdexcept>

std::vector<std::string> DnsResolver::resolve(const std::string& hostname) {
    std::vector<std::string> result;
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    addrinfo* res;
    if (getaddrinfo(hostname.c_str(), nullptr, &hints, &res) != 0) {
        throw std::runtime_error("DNS resolution failed");
    }
    
    for (addrinfo* p = res; p != nullptr; p = p->ai_next) {
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &((sockaddr_in*)p->ai_addr)->sin_addr, ip, sizeof(ip));
        result.push_back(ip);
    }
    
    freeaddrinfo(res);
    return result;
}
