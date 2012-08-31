CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE($ENV{DEPOT}/config/Tvd.cmake)

find_package( Boost 1.39.0 REQUIRED system filesystem thread )
LIST(APPEND UTIL_LIBRARIES Boost Boost-system Boost-filesystem Boost-thread)
 
LIST(APPEND UTIL_LINK_LIBRARIES pthread)
 
# Test libraries
LIST(APPEND UTIL_TEST_LIBRARIES Boost Boost-system Boost-filesystem Boost-thread)
LIST(APPEND UTIL_TEST_LINK_LIBRARIES pthread)

Add_Lib (
	PROJECT_NAME "util"
	PROJECT_DESCRIPTION "This is a misc. Ginga Util library." 
	PROJECT_VERSION 0.11.1.0
	DEPENDENCIES ${UTIL_LIBRARIES}
	TEST_DEPENDENCIES ${UTIL_TEST_LIBRARIES}
)

