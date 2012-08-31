SET( IC_HEADER_FILES
	include/curlic/CurlInteractiveChannel.h
	include/InteractiveChannelManager.h
	include/IInteractiveChannelManager.h
	include/IInteractiveChannelListener.h
	include/IInteractiveChannel.h
)

SET( IC_SOURCE_FILES
	${IC_HEADER_FILES}
	src/curlic/CurlInteractiveChannel.cpp
	src/InteractiveChannelManager.cpp
)


