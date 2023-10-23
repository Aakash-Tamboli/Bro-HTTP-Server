cmake_minimum_required (VERSION 3.22 FATAL_ERROR)
project (bro)
include_directories ("../include")
add_library(bro bro.cpp bro_utilities.cpp bro_gmt_date_time.cpp)
