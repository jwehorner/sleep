##########################################
# Catch Test Installation
##########################################
Include(FetchContent)

set(FETCHCONTENT_QUIET FALSE)

FetchContent_Declare(
	Catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v3.3.2
	GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(Catch2)

enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

##########################################
# Configure Files
##########################################

##########################################
# Catch Test Targets
##########################################
add_executable(sleep_unit_tests			"${CMAKE_CURRENT_SOURCE_DIR}/sleep_unit_tests.cpp")
include_directories(sleep_unit_tests	"${INCLUDES_LIST}" "${TEST_INCLUDES_LIST}")
if(WIN32)
	target_link_libraries(sleep_unit_tests	
		Catch2::Catch2
		Winmm 
	)
else()
	target_link_libraries(sleep_unit_tests	
		Catch2::Catch2
	)
endif()

##########################################
# Regular Test Targets
##########################################