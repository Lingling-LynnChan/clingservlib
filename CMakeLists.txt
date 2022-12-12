# 反正我可以用
cmake_minimum_required(VERSION 3.24)
project(clingservlib C)

set(CMAKE_C_STANDARD 99)

add_executable(clingservlib main.c clingservlib/lib/bool.h clingservlib/lib/struct.h clingservlib/src/safe/safe_ptr.c clingservlib/lib/safe/safe_ptr.h clingservlib/src/map/obj_map.c clingservlib/lib/map/obj_map.h clingservlib/src/list/obj_list.c clingservlib/lib/list/obj_list.h clingservlib/src/object/int.c clingservlib/lib/object/int.h clingservlib/src/object/flt.c clingservlib/lib/object/flt.h clingservlib/src/object/str.c clingservlib/lib/object/str.h clingservlib/lib/object/obj.h clingservlib/src/locker/mutexlock.c clingservlib/lib/locker/mutexlock.h clingservlib/src/map/obj_set.c clingservlib/lib/map/obj_set.h clingservlib/lib/object.h clingservlib/lib/def_struct.h clingservlib/src/proxy/lalloc.c clingservlib/lib/proxy/lalloc.h clingservlib/clinglib.h clingservlib/lib/safe.h clingservlib/lib/io.h clingservlib/src/locker/rwlock.c clingservlib/lib/locker/rwlock.h clingservlib/src/proxy/output.c clingservlib/lib/proxy/output.h clingservlib/ccmanager.h)

# 链接pthread
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)
target_link_libraries(clingserv ${CMAKE_THREAD_LIBS_INIT})
