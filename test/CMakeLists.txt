#######################################
# Configure Files					###
#######################################
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/DirectoryConfig.hpp.in" "${CMAKE_CURRENT_SOURCE_DIR}/DirectoryConfig.hpp")

#######################################
# Test Variables					###
#######################################
set(TEST_INCLUDES_LIST
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

############################
###  Target Definitions  ###
############################

########################
###  Subdirectories  ###
########################
add_subdirectory(unit_tests)
