file(GLOB_RECURSE BEBONE_NET_SRC_FILES "*.cpp")

add_library(bebone_net STATIC ${BEBONE_NET_SRC_FILES})