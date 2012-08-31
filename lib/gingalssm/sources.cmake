SET( LSSM_HEADER_FILES
	include/CommonCoreManager.h
	include/PresentationEngineManager.h
	include/ICommonCoreManager.h
	include/IPresentationEngineManager.h
	include/DataWrapperListener.h
)

SET( LSSM_SOURCE_FILES
	${LSSM_HEADER_FILES}
	src/PresentationEngineManager.cpp
	src/CommonCoreManager.cpp
)
