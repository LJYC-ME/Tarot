cmake_minimum_required(VERSION 3.30)

project("Tarot"
        LANGUAGES       CXX)

set(CMAKE_CXX_STANDARD 20)

option(OP_EnableTest "" ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_GENERATOR "ninja")
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

add_library(Tarot
            ${TAROT_MODULES})
target_sources(Tarot
               PRIVATE
               FILE_SET tarot_modules TYPE CXX_MODULES
               FILES ${TAROT_MODULES}
)

if (${OP_EnableTest})
    add_executable(Tarot-Sandbox
            "${PROJECT_SOURCE_DIR}/Test/Sandbox.ixx")
    target_sources(Tarot-Sandbox
            PRIVATE
            FILE_SET tarot_sandbox_modules TYPE CXX_MODULES
            FILES "${PROJECT_SOURCE_DIR}/Test/Sandbox.ixx"
    )
endif()
