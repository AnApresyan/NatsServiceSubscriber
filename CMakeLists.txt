cmake_minimum_required(VERSION 3.10)
project(NatsSubscriberProject)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}/src)

find_package(PkgConfig REQUIRED)

pkg_check_modules(PQXX REQUIRED libpqxx)
include_directories(${PQXX_INCLUDE_DIRS})
link_directories(${PQXX_LIBRARY_DIRS})

pkg_check_modules(NATS REQUIRED nats)
include_directories(${NATS_INCLUDE_DIRS})
link_directories(${NATS_LIBRARY_DIRS})


set(MAIN_SOURCE "${CMAKE_SOURCE_DIR}/main.cpp")
file(GLOB_RECURSE SRC_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

list(FILTER SRC_SOURCES EXCLUDE REGEX ".*/CMakeFiles/.*")
set(SOURCES ${MAIN_SOURCE} ${SRC_SOURCES})

add_executable(nats_subscriber ${SOURCES})

target_link_libraries(nats_subscriber ${PQXX_LIBRARIES} ${NATS_LIBRARIES} pthread)

set_target_properties(nats_subscriber PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "/usr/local/lib"
)
