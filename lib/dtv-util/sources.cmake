SET( UTIL_HEADER_FILES
	src/functions.h
	src/string.h
	src/singleton.h
	src/debugging_aids.h
	src/buffer.h
	src/any.h
	src/types.h
	src/mcr.h
	src/fs.h
	src/resourcepool.h
	src/keydefs.h
	src/taskqueue.h
)

SET( UTIL_SOURCE_FILES
	${UTIL_HEADER_FILES}
	src/keydefs.cpp
	src/functions.cpp
	src/resourcepool.cpp
	src/buffer.cpp
	src/fs.cpp
	src/string.cpp
	src/taskqueue.cpp
)



