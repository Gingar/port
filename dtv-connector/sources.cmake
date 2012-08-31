SET( CONNECTOR_HEADER_FILES
	src/connector.h
	src/remote.h
	src/handler/videoresizehandler.h
	src/handler/exitcommandhandler.h
	src/handler/messagehandler.h
	src/handler/keyeventhandler.h
	src/handler/keyregisterhandler.h
	src/handler/types.h
	src/handler/keepalivehandler.h
	src/handler/editingcommandhandler.h
	src/handler/startcommandhandler.h
	src/handler/canvashandler.h
)

SET( CONNECTOR_SOURCE_FILES
	${CONNECTOR_HEADER_FILES}
	src/connector.cpp
	src/remote.cpp
	src/handler/messagehandler.cpp
	src/handler/keyeventhandler.cpp
	src/handler/keyregisterhandler.cpp
	src/handler/videoresizehandler.cpp
	src/handler/keepalivehandler.cpp
	src/handler/exitcommandhandler.cpp
	src/handler/editingcommandhandler.cpp
	src/handler/startcommandhandler.cpp
	src/handler/canvashandler.cpp
)

