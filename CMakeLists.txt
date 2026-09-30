cmake_minimum_required(VERSION 3.16)

project(SyscallShield VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(syscallshield
    src/main.cpp
    src/system_info.cpp
    src/policy_engine.cpp
    src/seccomp_manager.cpp
    src/process_manager.cpp
    src/capability_manager.cpp
    src/namespace_manager.cpp
    src/runtime_monitor.cpp
    src/security_report.cpp
    src/driver_interface.cpp
)

target_link_libraries(syscallshield
    seccomp
    cap
)
