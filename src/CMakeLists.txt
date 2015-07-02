# In The Name Of God
# ========================================
# [] File Name : CMakeLists.txt
#
# [] Creation Date : 08-05-2015
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
add_executable (P2P-ChatRoom.out main.c common.c connections.c peer.c)

find_package(PkgConfig)
pkg_check_modules(GLIB REQUIRED glib-2.0>=2.42)
include_directories(${GLIB_INCLUDE_DIRS})
link_directories(${GLIB_LIBRARY_DIRS})
target_link_libraries(P2P-ChatRoom.out ${GLIB_LIBRARIES})