#ifndef SECCOMP_MANAGER_HPP
#define SECCOMP_MANAGER_HPP

#include <string>

class SeccompManager {
public:
    SeccompManager();

    bool applyDefaultPolicy();

private:
    bool blockSyscall(const std::string& syscallName);
};

#endif
