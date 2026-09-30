# SyscallShield Architecture

## 1. Overview

SyscallShield follows a modular security-engine architecture.

The main application acts as the security controller and coordinates:

- Policy management
- Process management
- Seccomp enforcement
- Capability reduction
- Namespace isolation
- Runtime monitoring
- Security reporting
- Linux driver interface

---

## 2. High-Level Architecture

```text
                    +----------------------+
                    |     SyscallShield    |
                    |      main.cpp        |
                    +----------+-----------+
                               |
                               v
                    +----------------------+
                    |    Policy Engine     |
                    | Load + Validate      |
                    +----------+-----------+
                               |
                               v
                    +----------------------+
                    |  Process Manager     |
                    +----------+-----------+
                               |
             +-----------------+-----------------+
             |                 |                 |
             v                 v                 v
       +-----------+     +-----------+     +-----------+
       |  Seccomp  |     |Capability |     |Namespace  |
       |  Manager  |     |  Manager  |     |  Manager  |
       +-----+-----+     +-----+-----+     +-----+-----+
             |                 |                 |
             +-----------------+-----------------+
                               |
                               v
                    +----------------------+
                    | Protected Process    |
                    +----------+-----------+
                               |
                               v
                    +----------------------+
                    |  Runtime Monitor     |
                    +----------+-----------+
                               |
                               v
                    +----------------------+
                    |  Security Report     |
                    +----------------------+

                    Kernel Integration
                           |
                           v
                  +-------------------+
                  | Driver Interface  |
                  +---------+---------+
                            |
                            v
                    /dev/syscallshield
                            |
                            v
                    Linux Kernel Driver