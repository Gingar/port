CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE($ENV{DEPOT}/config/Tvd.cmake)

SetIfEmpty(HAVE_COMPSUPPORT 0)

find_package( GingaLib 0.11.0 REQUIRED util )
LIST(APPEND GINGAMULTIDEVICE_LIBRARIES GINGALIB-UTIL GINGA-SYSTEM )

find_package( Pthreads REQUIRED )
LIST(APPEND GINGAMULTIDEVICE_LIBRARIES PTHREADS )

Add_Lib (
	PROJECT_NAME "multidevice"
	PROJECT_DESCRIPTION "This is the Ginga Multi Device library project."
	PROJECT_VERSION 0.0.1.0
	DEPENDENCIES ${GINGAMULTIDEVICE_LIBRARIES}
)

