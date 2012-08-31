CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE($ENV{DEPOT}/config/Tvd.cmake)

find_package( Boost 1.39.0 REQUIRED system filesystem thread )
LIST(APPEND LAYER_LIBRARIES Boost Boost-system Boost-filesystem Boost-thread)

LIST(APPEND LAYER_LINK_LIBRARIES pthread)

Add_Lib (
	PROJECT_NAME "layer"
	PROJECT_DESCRIPTION "This is a misc. library."
	PROJECT_VERSION 0.1.1.0
	DEPENDENCIES ${LAYER_LIBRARIES}
)

