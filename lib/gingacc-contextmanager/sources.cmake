
SET( CONTEXTMANAGER_HEADER_FILES
	include/ContextManager.h
	include/system/ISystemInfo.h
	include/system/SystemInfo.h
	include/user/GingaUser.h
	include/user/IGingaUser.h
	include/IContextManager.h
)


SET( CONTEXTMANAGER_SOURCE_FILES
	${CONTEXTMANAGER_HEADER_FILES}
	sources.cmake
	src/system/SystemInfo.cpp
	src/ContextManager.cpp
	src/user/GingaUser.cpp
)

