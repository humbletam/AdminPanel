cmake_minimum_required(VERSION 4.0)
project(AdminPanel)

set(CMAKE_CXX_STANDARD 20)

add_executable(AdminPanel src/main.cpp
        src/core/AdminPanel.h
        src/core/AdminPanel.cpp
        src/core/exceptions/DomainExceptions.h
        src/core/repository/IUserRepository.h
        src/core/repository/InMemoryUserRepository.h
        src/core/repository/InMemoryUserRepository.cpp
        src/models/User/User.cpp
        src/models/User/User.h
        src/models/Listing/Listing.cpp
        src/models/Listing/Listing.h)
