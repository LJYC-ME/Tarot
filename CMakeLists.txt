cmake_minimum_required(VERSION 3.30)

project("Tarot"
        LANGUAGES       CXX)

set(CMAKE_CXX_STANDARD          20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

option(OP_EnableDynamicLibrary  "Build Dynamic Library."            OFF)
option(OP_EnableTest            "Build Testing Sandbox Project."    ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "Using Clang++")
    set(CMAKE_CXX_SCAN_FOR_MODULES ON)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fmodules")

    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-stdlib=libc++" HAS_LIBCPP)

    if (HAS_LIBCPP)
        message(STATUS "Using Libc++")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++ -D_LIBCPP_VERSION")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -stdlib=libc++")
    else()
        message(STATUS "libc++ is recommended in conjunction with clang. Please install the libc++ development headers, provided e.g. by the packages 'libc++-dev' and 'libc++abi-dev' on Debian/Ubuntu.")
    endif()
endif()

file(GLOB_RECURSE TAROT_MODULES "${PROJECT_SOURCE_DIR}/Modules/*.ixx")

if (NOT ${OP_EnableDynamicLibrary})
    message(STATUS "Using Tarot Static Library.")
    add_library(Tarot STATIC)
else()
    message(STATUS "Using Tarot Dynamic Library.")
    add_library(Tarot SHARED)
endif()

target_compile_definitions(Tarot PUBLIC TAROT_API=export)
target_sources(Tarot
        PUBLIC
        FILE_SET tarot_modules TYPE CXX_MODULES
        FILES ${TAROT_MODULES})

if (${OP_EnableTest})
    message(STATUS "Testing Tarot.")
    file(GLOB_RECURSE TAROT_SANDBOX_MODULES "${PROJECT_SOURCE_DIR}/Sandbox/*.ixx")

    add_executable(Tarot-Sandbox)

    target_sources(Tarot-Sandbox
            PRIVATE
            FILE_SET tarot_sandbox_modules TYPE CXX_MODULES
            FILES ${TAROT_SANDBOX_MODULES}
    )

    target_link_libraries(Tarot-Sandbox PRIVATE Tarot)
endif()
