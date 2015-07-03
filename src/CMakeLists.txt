# In The Name Of God
# ========================================
# [] File Name : CMakeLists.txt
#
# [] Creation Date : 08-05-2015
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
add_executable (P2P-ChatRoom.out main.c common.c connections.c peer.c command.c)

find_package (Threads)
target_link_libraries (P2P-ChatRoom.out ${CMAKE_THREAD_LIBS_INIT})
