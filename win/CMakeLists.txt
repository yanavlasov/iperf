cmake_minimum_required(VERSION 3.0)

project(iperf3)

set(IP3_SRC ${CMAKE_CURRENT_LIST_DIR}/../src)

# Windows specific sources of the iperf3 library
set(LIB_WIN_SRCS
    getopt.c
    getopt.h
    gettimeofday.c
    gettimeofday.h
    iperf_config.h
    random.h
    version.h
    neterror.c
    neterror.h
    )

# Platform agnostic sources of the iperf3 library (from iperf3 git repo)
set(LIB_IP3_SRCS
    ${IP3_SRC}/cjson.c
    ${IP3_SRC}/cjson.h
    ${IP3_SRC}/iperf_api.c
    ${IP3_SRC}/iperf_api.h
    ${IP3_SRC}/iperf_client_api.c
    ${IP3_SRC}/iperf_error.c
    ${IP3_SRC}/iperf_locale.c
    ${IP3_SRC}/iperf_locale.h
    ${IP3_SRC}/iperf_server_api.c
    ${IP3_SRC}/iperf_tcp.c
    ${IP3_SRC}/iperf_tcp.h
    ${IP3_SRC}/iperf_udp.c
    ${IP3_SRC}/iperf_udp.h
    ${IP3_SRC}/iperf_util.c
    ${IP3_SRC}/iperf_util.h
    ${IP3_SRC}/iperf_util.c
    ${IP3_SRC}/net.c
    ${IP3_SRC}/net.h
    ${IP3_SRC}/portable_endian.h
    ${IP3_SRC}/tcp_info.c
    ${IP3_SRC}/timer.c
    ${IP3_SRC}/timer.h
    ${IP3_SRC}/units.c
    ${IP3_SRC}/units.h
    )

include_directories(${CMAKE_CURRENT_LIST_DIR})

# build target for libiperf3.dll
# add_library(libiperf3 SHARED ${LIB_IP3_SRCS} ${LIB_WIN_SRCS})

# target_compile_definitions(libiperf3 PRIVATE LIBIPERF_EXPORTS STATIC_GETOPT)

# target_link_libraries(libiperf3 ws2_32.lib)

set(IP3_SRCS
    iperf_config.h
    version.h
    ${IP3_SRC}/iperf.h
    ${IP3_SRC}/iperf_api.h
    ${IP3_SRC}/timer.h
    ${IP3_SRC}/main.c
    )

# static iperf3lib.lib library
add_library(iperf3lib STATIC ${LIB_IP3_SRCS} ${LIB_WIN_SRCS})
target_compile_definitions(iperf3lib PRIVATE STATIC_GETOPT)

# build target for iperf3.exe
add_executable(iperf3 ${IP3_SRCS})
target_link_libraries(iperf3 iperf3lib ws2_32.lib)
