# Set install, and config install PREFIX
set(CMAKE_INSTALL_PREFIX $ENV{DEPOT})
set(CMAKE_CONFIG_INSTALL_PREFIX $ENV{DEPOT})

# Set default platform PC
SetIfEmpty(PLATFORM PC)

# Set build type Release, Debug, RelWithDebInfo
set(CMAKE_BUILD_TYPE Release)

# Set warning level 
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

# Set debug flags
set(CMAKE_CXX_FLAGS_DEBUG "-rdynamic")

# Set compile tests in true
set(COMPILE_TESTS 1)
# Set run tests in false
set(RUN_TESTS 0)

# Set lib prefix to tvd
set(LIB_PREFIX dtv)
