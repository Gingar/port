CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE($ENV{DEPOT}/config/Tvd.cmake)

SetIfEmpty(HAVE_COMPSUPPORT 0)

find_package( XercesC )
LIST(APPEND GINGANCL-PRESENTER_LIBRARIES XERCESC )

find_package( GingaLib 0.11.0 REQUIRED util connector ncl ncl-converter system ic player contextmanager multidevice telemidialinks )
LIST(APPEND GINGANCL-PRESENTER_LIBRARIES GINGALIB-UTIL GINGALIB-CONNECTOR GINGALIB-NCL GINGALIB-NCL-CONVERTER GINGALIB-SYSTEM GINGALIB-IC GINGALIB-PLAYER GINGALIB-CONTEXTMANAGER GINGALIB-MULTIDEVICE GINGALIB-TELEMIDIALINKS )

find_package( Lua51 REQUIRED )
LIST(APPEND GINGANCL-PRESENTER_LIBRARIES LUA )

find_package( DirectFB REQUIRED )
LIST(APPEND GINGANCL-PRESENTER_LIBRARIES DIRECTFB )

OPTIONAL_FIND_PACKAGE( Xine 0.1.0 )
LIST(APPEND GINGANCL-PRESENTER_LIBRARIES XINE )

find_package( Boost 1.39.0 REQUIRED system filesystem thread )
LIST(APPEND GINGANCL-PRESENTER_LIBRARIES Boost Boost-system Boost-filesystem Boost-thread)

find_package( Pthreads REQUIRED )
LIST(APPEND GINGANCL-PRESENTER_LIBRARIES PTHREADS )

Add_Lib (
	PROJECT_NAME "ncl-presenter"
	PROJECT_DESCRIPTION "This is the NCL Presenter Ginga library." 
	PROJECT_VERSION 0.11.1.0
	DEPENDENCIES ${GINGANCL-PRESENTER_LIBRARIES}
)

INSTALL( FILES
  ${PROJECT_SOURCE_DIR}/files/config/formatter/players/ctrldefs.ini
  ${PROJECT_SOURCE_DIR}/files/config/formatter/players/mimedefs.ini
  DESTINATION ${CMAKE_CONFIG_INSTALL_PREFIX}/etc/ginga/cfg/formatter
)

INSTALL( FILES
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/emissora.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/focus_1h.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/programacao_1h.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/selecao_1h.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/epg01.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/focus_2h.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/programacao_2h.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/selecao_2h.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/focus_05h.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/programacao_05h.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/selecao_05h.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/focus_15h.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/programacao_15h.png
  ${PROJECT_SOURCE_DIR}/files/epgFactory/img/selecao_15h.png
  DESTINATION share/ginga/img/epgfactory
)

INSTALL( FILES
  ${PROJECT_SOURCE_DIR}/files/img/b1.png  
  ${PROJECT_SOURCE_DIR}/files/img/b2.png  
  ${PROJECT_SOURCE_DIR}/files/img/b3.png
  ${PROJECT_SOURCE_DIR}/files/img/b4.png  
  ${PROJECT_SOURCE_DIR}/files/img/b5.png
  ${PROJECT_SOURCE_DIR}/files/img/b6.png
  ${PROJECT_SOURCE_DIR}/files/img/b7.png
  ${PROJECT_SOURCE_DIR}/files/img/b8.png
  ${PROJECT_SOURCE_DIR}/files/img/loading.png
  DESTINATION share/ginga/img/roller
)

