#ifndef DNS_RESOLVER_H
#define DNS_RESOLVER_H

#include <vector>
#include <string>

class DnsResolver {
public:
    static std::vector<std::string> resolve(const std::string& hostname);
};

#endif // DNS_RESOLVER_H header
