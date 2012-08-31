
FIND_PATH(DVC_INCLUDE_DIRS dvc.h PATH_SUFFIXES dvc)
LIST(APPEND DVC_NAMES dvc )
FIND_LIBRARY(DVC_LIBRARY NAMES ${DVC_NAMES} )

SET( SYSTEM_HEADER_FILES
	include/io/InputManager.h
	include/io/ILocalDeviceManager.h
	include/io/interface/output/IWindow.h
	include/io/interface/output/ISurface.h
	include/io/interface/output/dfb/DFBSurface.h
	include/io/interface/output/dfb/DFBWindow.h
	include/io/interface/input/CodeMap.h
	include/io/interface/input/IInputEventListener.h
	include/io/interface/input/IEventBuffer.h
	include/io/interface/input/IInputEvent.h
	include/io/interface/input/dfb/DFBGInputEvent.h
	include/io/interface/input/dfb/DFBEventBuffer.h
	include/io/interface/content/text/DFBFontProvider.h
	include/io/interface/content/text/IFontProvider.h
	include/io/interface/content/video/DFBVideoProvider.h
	include/io/interface/content/video/DFBDataBuffer.h
	include/io/interface/content/IProviderListener.h
	include/io/interface/content/IDataBuffer.h
	include/io/interface/content/image/DFBImageProvider.h
	include/io/interface/content/image/IImageProvider.h
	include/io/interface/content/IContinuousMediaProvider.h
	include/io/interface/content/ITimeBaseListener.h
	include/io/interface/content/ITimeBaseProvider.h
	include/io/interface/content/audio/FusionSoundAudioProvider.h
	include/io/interface/content/audio/DFBAudioProvider.h
	include/io/interface/IIOContainer.h
	include/io/interface/device/DeviceAudio.h
	include/io/interface/device/IIODevice.h
	include/io/interface/device/IDeviceAudio.h
	include/io/interface/device/IDeviceCommunication.h
	include/io/interface/device/IDeviceScreen.h
	include/io/interface/device/IODevice.h
	include/io/interface/device/dfb/DFBDeviceScreen.h
	include/io/interface/device/DeviceCommunication.h
	include/io/IInputManager.h
	include/io/IGingaLocatorFactory.h
	include/io/GingaLocatorFactory.h
	include/io/LocalDeviceManager.h
	include/io/IOHandler.h
	include/thread/Thread.h
	include/util/Observable.h
	include/util/functions.h
	include/util/IColor.h
	include/util/mutex/dfbsurfacemutex.h
	include/util/Observer.h
	include/util/Color.h
)

IF(${HAVE_FFMPEG})
	LIST( APPEND SYSTEM_HEADER_FILES
		include/io/interface/content/video/FFmpegVideoProvider.h
		include/io/interface/content/audio/FFmpegAudioProvider.h 
	)
ENDIF(${HAVE_FFMPEG})

IF(${HAVE_XINE})
	LIST( APPEND SYSTEM_HEADER_FILES
		include/io/interface/content/video/XineVideoProvider.h
	)
ENDIF(${HAVE_XINE})

IF(${DVC_INCLUDE_DIRS} MATCHES NOTFOUND OR ${DVC_LIBRARY} MATCHES NOTFOUND)
	INCLUDE_DIRECTORIES( include/util/dvc${DIRECTFB_VERSION_MAJOR}${DIRECTFB_VERSION_MINOR} )
	LIST( APPEND SYSTEM_HEADER_FILES include/util/dvc${DIRECTFB_VERSION_MAJOR}${DIRECTFB_VERSION_MINOR}/dvc/dvc.h )
ENDIF(${DVC_INCLUDE_DIRS} MATCHES NOTFOUND OR ${DVC_LIBRARY} MATCHES NOTFOUND)



SET( SYSTEM_SOURCE_FILES
	${SYSTEM_HEADER_FILES}
	src/io/GingaLocatorFactory.cpp
	src/io/InputManager.cpp
	src/io/interface/output/dfb/DFBSurface.cpp
	src/io/interface/output/dfb/DFBWindow.cpp
	src/io/interface/input/CodeMap.cpp
	src/io/interface/input/dfb/DFBGInputEvent.cpp
	src/io/interface/input/dfb/DFBEventBuffer.cpp
	src/io/interface/content/text/DFBFontProvider.cpp
	src/io/interface/content/video/DFBVideoProvider.cpp
	src/io/interface/content/video/DFBDataBuffer.cpp
	src/io/interface/content/image/DFBImageProvider.cpp
	src/io/interface/content/audio/DFBAudioProvider.cpp
	src/io/interface/content/audio/FusionSoundAudioProvider.cpp
	src/io/interface/device/IODevice.cpp
	src/io/interface/device/DeviceAudio.cpp
	src/io/interface/device/DeviceCommunication.cpp
	src/io/interface/device/dfb/DFBDeviceScreen.cpp
	src/io/LocalDeviceManager.cpp
	src/thread/Thread.cpp
	src/util/Color.cpp
	src/util/mutex/dfbsurfacemutex.cpp
	src/util/functions.cpp
)
IF(${HAVE_FFMPEG})
	LIST( APPEND GINGASYSTEM_SOURCE_FILES 
		src/io/interface/content/video/FFmpegVideoProvider.cpp
		src/io/interface/content/audio/FFmpegAudioProvider.cpp 
	)
ENDIF(${HAVE_FFMPEG})

IF(${HAVE_XINE})
	LIST( APPEND GINGASYSTEM_SOURCE_FILES
		src/io/interface/content/video/XineVideoProvider.cpp
	)
ENDIF(${HAVE_XINE})

IF(${DVC_INCLUDE_DIRS} MATCHES NOTFOUND OR ${DVC_LIBRARY} MATCHES NOTFOUND)
	LIST( APPEND GINGASYSTEM_SOURCE_FILES src/util/dvc${DIRECTFB_VERSION_MAJOR}${DIRECTFB_VERSION_MINOR}/dvc.c )
ELSE(${DVC_INCLUDE_DIRS} MATCHES NOTFOUND OR ${DVC_LIBRARY} MATCHES NOTFOUND)
	LIST(APPEND GINGA_SYSTEM_LIBRARIES DVC )
ENDIF(${DVC_INCLUDE_DIRS} MATCHES NOTFOUND OR ${DVC_LIBRARY} MATCHES NOTFOUND)

