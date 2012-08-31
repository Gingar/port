# Build shared file
set(BUILD_SHARED 1)

set(CMAKE_INSTALL_PREFIX /tmp/ginga)
set(CMAKE_CONFIG_INSTALL_PREFIX /tmp/ginga)

LIST(APPEND CMAKE_FIND_ROOT_PATH ${CMAKE_INSTALL_PREFIX} )

# Override build type,  Release, Debug, RelWithDebInfo
# set(CMAKE_BUILD_TYPE "Debug")

set(SILENT 1)
