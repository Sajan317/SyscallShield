#ifndef NAMESPACE_MANAGER_HPP
#define NAMESPACE_MANAGER_HPP

#include <string>

class NamespaceManager {
public:
    NamespaceManager();

    bool createPIDNamespace();

    std::string getStatus() const;

private:
    std::string status;
};

#endif
