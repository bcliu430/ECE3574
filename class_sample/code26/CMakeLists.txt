cmake_minimum_required(VERSION 3.2)
project(basic_type CXX)

add_executable(singleton_ex singleton_ex.cpp)
set_property(TARGET singleton_ex PROPERTY CXX_STANDARD 11)

set(ActorSRC actor_base.h actor_id.h actors.h controller.cpp controller.h controller_impl.cpp controller_impl.h message_queue.h simple_actor_ex.cpp)

add_executable(simple_actor_ex ${ActorSRC} )
set_property(TARGET simple_actor_ex PROPERTY CXX_STANDARD 11)

enable_testing()
add_test(simple_actor_ex simple_actor_ex)

