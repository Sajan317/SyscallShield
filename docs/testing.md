# SyscallShield Testing Documentation

## 1. Testing Overview

SyscallShield is tested by building the application, executing the security engine, and verifying the behavior of the configured security controls.

The testing focuses on:

- Policy loading and validation
- Seccomp system-call restriction
- Linux capability reduction
- Namespace availability
- Protected process execution
- Runtime security monitoring
- Security reporting
- Driver interface detection

---

## 2. Build Testing

The project is built using CMake.

### Build Command

```bash
cd ~/SyscallShield/build
cmake --build .

