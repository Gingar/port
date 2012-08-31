CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE($ENV{DEPOT}/config/Tvd.cmake)

# Connector keep alive interval
SetIfEmpty(CONNECTOR_KEEP_ALIVE_INTERVAL 500)

# Connector keep alive max retry
SetIfEmpty(CONNECTOR_KEEP_ALIVE_MAX_RETRY 5)

# Connector connect timeout
SetIfEmpty(CONNECTOR_CONNECT_TIMEOUT 10000)

# Connector connect retry timeout
SetIfEmpty(CONNECTOR_CONNECT_TIMEOUT_RETRY 1000)

# Connector connect max retry timeout
SetIfEmpty(CONNECTOR_CONNECT_TIMEOUT_MAX_RETRY 10)

find_package( Boost 1.39.0 REQUIRED system filesystem thread )
LIST(APPEND CONNECTOR_LIBRARIES Boost Boost-system Boost-filesystem Boost-thread)
 
find_package( GingaLib 0.11.0 REQUIRED util )
LIST(APPEND CONNECTOR_LIBRARIES GINGALIB-UTIL )
 
LIST(APPEND CONNECTOR_LINK_LIBRARIES z pthread)
 
# Test libraries
LIST(APPEND CONNECTOR_TEST_LIBRARIES Boost Boost-system Boost-filesystem Boost-thread GINGALIB-UTIL)
LIST(APPEND CONNECTOR_TEST_LINK_LIBRARIES z pthread)

Add_Lib (
	PROJECT_NAME "connector"
	PROJECT_DESCRIPTION "This library connect zapper with ginga." 
	PROJECT_VERSION 0.0.1.0
	DEPENDENCIES ${CONNECTOR_LIBRARIES}
	TEST_DEPENDENCIES ${CONNECTOR_TEST_LIBRARIES}
)


