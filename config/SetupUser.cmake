# Build shared file
set(BUILD_SHARED 1)

set(CMAKE_INSTALL_PREFIX $ENV{DEPOT}/DEPLOY/usr)
set(CMAKE_CONFIG_INSTALL_PREFIX $ENV{DEPOT}/DEPLOY/usr)

LIST(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_INSTALL_PREFIX} )

# Override build type,  Release, Debug, RelWithDebInfo
# set(CMAKE_BUILD_TYPE "Debug")

set(SILENT 1)
