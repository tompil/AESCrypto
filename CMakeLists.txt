cmake_minimum_required(VERSION 3.9)
project(CryptoAES)

set(CMAKE_CXX_STANDARD 17)
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()


add_executable(CryptoAES test/key_expander_test.cpp include/key_expander.h src/key_expander.cpp include/word.h src/word.cpp test/word_test.cpp)
include_directories(include)
target_link_libraries(CryptoAES ${CONAN_LIBS})
