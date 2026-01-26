#Specify minimum version
cmake_minimum_required(VERSION 3.20.0)

#set board
set(BOARD nrf5340dk/nrf5340/cpuapp)

#Locate Zephyr, automatically calls add excecutable(app ..)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})


#Name the project
project(my_app)

#Create Static Library
#add_library(
#    tsl2591
 #   STATIC
#    src/tsl2591.c
#)

#Include directories for the library
#target_include_directories(
    #tsl2591
#    PUBLIC
#    ${CMAKE_CURRENT_SOURCE_DIR}/include
#)

#Linklibraries to the exectiable, PRIVATE means library not exposed to the targets
#target_link_libraries(
#    app
#    PRIVATE
#    tsl2591
#)

target_sources(app PRIVATE src/main.c)

zephyr_include_directories(include)