# SyscallShield

## Adaptive Seccomp, Capability & Namespace Security Policy Engine

SyscallShield is a Linux runtime security engine developed in C++.

It combines multiple Linux security mechanisms to protect processes and reduce their attack surface.

## Security Components

### Seccomp
Restricts system calls available to a protected process.

### Linux Capabilities
Reduces process privileges by dropping unnecessary capabilities such as `CAP_NET_RAW`.

### Linux Namespaces
Provides process isolation when supported by the current Linux environment.

### Policy Engine
Loads and validates security policies from an external configuration file.

### Runtime Monitor
Records security events with timestamps and severity levels.

### Security Report
Provides a summary of the security controls applied during execution.

### Driver Interface
Detects the `/dev/syscallshield` device and provides the user-space interface for the Linux kernel driver.

## Architecture

```text
                 SyscallShield
                       |
                +------+------+
                | Policy      |
                | Engine      |
                +------+------+
                       |
                +------+------+
                | Security    |
                | Controller  |
                +------+------+
                       |
        +--------------+--------------+
        |              |              |
     Seccomp      Capabilities   Namespaces
        |              |              |
        +--------------+--------------+
                       |
                Protected Process
                       |
                Runtime Monitor
                       |
                Security Report
                       |
                Driver Interface
                       |
                /dev/syscallshield