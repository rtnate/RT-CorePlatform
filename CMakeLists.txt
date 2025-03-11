cmake_minimum_required(VERSION 3.14)

project(RT-CorePlatform VERSION 0.0.1)

add_library(rtcoreplatform STATIC)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src)

target_sources(rtcoreplatform PRIVATE ${RT_CORE_PLATFORM_SOURCES})

target_include_directories(rtcoreplatform PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)

source_group(TREE "${CMAKE_CURRENT_LIST_DIR}/src" 
    PREFIX "RT-CorePlatform\\src" 
    FILES ${RT_CORE_PLATFORM_SOURCES})