cmake_minimum_required(VERSION 3.20 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(sleep)

#################
###  Options  ###
#################
option(BUILD_SLEEP_TESTS "Optionally compile test cases." OFF)

############################
###  Configured Headers  ###
############################

#####################################
###  Global Compiler Definitions  ###
#####################################

##########################
###  Dependency Setup  ###
##########################

##########################
###  Global Variables  ###
##########################
set(INCLUDES_LIST 			
	"${CMAKE_SOURCE_DIR}/include"
)

#################################
###  Compiler Specific Fixes  ###
#################################


########################
###  Subdirectories  ###
########################
if(BUILD_SLEEP_TESTS) 
	add_subdirectory(test)
endif()