cmake_minimum_required(VERSION 3.9)
project(CryptoAES)

set(CMAKE_CXX_STANDARD 17)
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()


add_executable(CryptoAES test/expanded_key_tests.cpp include/expanded_key.h src/expanded_key.cpp include/defs.h include/utils.h src/utils.cpp test/utils_tests.cpp)
include_directories(include)
target_link_libraries(CryptoAES ${CONAN_LIBS})
