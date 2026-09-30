#ifndef POLICY_ENGINE_HPP
#define POLICY_ENGINE_HPP

#include <string>
#include <vector>

struct SecurityPolicy
{
    std::string name;
    std::vector<std::string> allowedSyscalls;
    std::vector<std::string> restrictedSyscalls;
};

class PolicyEngine
{
public:
    PolicyEngine();

    SecurityPolicy getDefaultPolicy() const;

    bool loadPolicyFromFile(
        const std::string &filePath,
        SecurityPolicy &policy) const;

    bool validatePolicy(
        const SecurityPolicy &policy,
        std::string &errorMessage) const;

private:
    std::vector<std::string> split(
        const std::string &text,
        char delimiter) const;
};

#endif