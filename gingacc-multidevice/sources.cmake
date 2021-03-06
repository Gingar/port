SET( MULTIDEVICE_HEADER_FILES
	include/RemoteDevice.h
	include/IRemoteDevice.h
	include/IRemoteDeviceListener.h
	include/RemoteDeviceManager.h
	include/services/RemoteEventService.h
	include/services/BaseDeviceDomain.h
	include/services/PassiveDeviceDomain.h
	include/services/IDeviceDomain.h
	include/services/ActiveDeviceDomain.h
	include/services/DeviceDomain.h
	include/services/network/TcpSocketService.h
	include/services/network/TcpClientConnection.h
	include/services/network/NetworkUtil.h
	include/services/network/ISocketService.h
	include/services/network/MulticastSocketService.h
	include/services/network/BroadcastSocketService.h
	include/services/device/IDeviceService.h
	include/services/device/DeviceService.h
	include/services/device/PassiveDeviceService.h
	include/services/device/BaseDeviceService.h
	include/services/device/ActiveDeviceService.h
	include/IRemoteDeviceManager.h
)

SET( MULTIDEVICE_SOURCE_FILES
	${MULTIDEVICE_HEADER_FILES}
	src/RemoteDevice.cpp
	src/RemoteDeviceManager.cpp
	src/services/ActiveDeviceDomain.cpp
	src/services/DeviceDomain.cpp
	src/services/PassiveDeviceDomain.cpp
	src/services/network/TcpSocketService.cpp
	src/services/network/NetworkUtil.cpp
	src/services/network/MulticastSocketService.cpp
	src/services/network/TcpClientConnection.cpp
	src/services/network/BroadcastSocketService.cpp
	src/services/device/BaseDeviceService.cpp
	src/services/device/ActiveDeviceService.cpp
	src/services/device/DeviceService.cpp
	src/services/device/PassiveDeviceService.cpp
	src/services/BaseDeviceDomain.cpp
	src/services/RemoteEventService.cpp
)
