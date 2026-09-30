#include "policy_engine.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>

PolicyEngine::PolicyEngine()
{
}

std::vector<std::string> PolicyEngine::split(
    const std::string &text,
    char delimiter) const
{

    std::vector<std::string> values;

    std::stringstream stream(text);
    std::string item;

    while (std::getline(stream, item, delimiter))
    {

        if (!item.empty())
        {
            values.push_back(item);
        }
    }

    return values;
}

SecurityPolicy PolicyEngine::getDefaultPolicy() const
{

    SecurityPolicy policy;

    policy.name = "default";

    policy.allowedSyscalls = {
        "read",
        "write",
        "exit",
        "exit_group"};

    policy.restrictedSyscalls = {
        "ptrace",
        "mount",
        "reboot"};

    return policy;
}

bool PolicyEngine::loadPolicyFromFile(
    const std::string &filePath,
    SecurityPolicy &policy) const
{

    std::ifstream file(filePath);

    if (!file.is_open())
    {
        return false;
    }

    SecurityPolicy loadedPolicy;

    std::string line;

    while (std::getline(file, line))
    {

        if (line.empty() || line[0] == '#')
        {
            continue;
        }

        std::size_t separator = line.find('=');

        if (separator == std::string::npos)
        {
            continue;
        }

        std::string key =
            line.substr(0, separator);

        std::string value =
            line.substr(separator + 1);

        if (key == "policy_name")
        {

            loadedPolicy.name = value;
        }
        else if (key == "allowed_syscalls")
        {

            loadedPolicy.allowedSyscalls =
                split(value, ',');
        }
        else if (key == "restricted_syscalls")
        {

            loadedPolicy.restrictedSyscalls =
                split(value, ',');
        }
    }

    file.close();

    if (loadedPolicy.name.empty())
    {
        return false;
    }

    policy = loadedPolicy;

    return true;
}

bool PolicyEngine::validatePolicy(
    const SecurityPolicy &policy,
    std::string &errorMessage) const
{

    if (policy.name.empty())
    {

        errorMessage =
            "Policy name cannot be empty";

        return false;
    }

    if (policy.allowedSyscalls.empty())
    {

        errorMessage =
            "Allowed syscall list cannot be empty";

        return false;
    }

    if (policy.restrictedSyscalls.empty())
    {

        errorMessage =
            "Restricted syscall list cannot be empty";

        return false;
    }

    for (const auto &allowed :
         policy.allowedSyscalls)
    {

        if (std::find(
                policy.restrictedSyscalls.begin(),
                policy.restrictedSyscalls.end(),
                allowed) != policy.restrictedSyscalls.end())
        {

            errorMessage =
                "Syscall appears in both allowed and restricted lists: " + allowed;

            return false;
        }
    }

    errorMessage =
        "Policy validation successful";

    return true;
}