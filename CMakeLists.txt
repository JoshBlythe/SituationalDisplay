cmake_minimum_required(VERSION 2.6)
project(SituationalDisplay)

include_directories(
    ${PROJECT_SOURCE_DIR}/src
)

if(WIN32)
  add_definitions(-DSDL_MAIN_HANDLED -DGLEW_STATIC)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

add_library(inc
  src/inc/util.cpp
  src/inc/util.h
  src/inc/stent.h
)
if(WIN32)
  target_link_libraries(inc glew32 opengl32 winmm imm32 version setupapi)
else()
  target_link_libraries(inc GLEW GL m)
endif()

add_executable(client
  src/client/main.cpp
  src/client/TcpSocket.cpp
  src/client/TcpSocket.h
  src/client/PlaneManager.cpp
  src/client/PlaneManager.h
  src/client/Display.cpp
  src/client/Display.h
  src/client/Exception.cpp
  src/client/Exception.h
  src/client/SpriteRender.cpp
  src/client/SpriteRender.h
  src/client/Enviroment.cpp
  src/client/Enviroment.h
  src/client/SendData.cpp
  src/client/SendData.h
  src/client/PlaneData.h

)

if(WIN32)
  target_link_libraries(client inc SDL2 SDL2_image jsoncpp ws2_32)
else()
  target_link_libraries(client inc SDL2 SDL2_image jsoncpp)
endif()

add_executable(TestEnviroment
  src/TestEnviroment/main.cpp
  src/TestEnviroment/TcpSocket.cpp
  src/TestEnviroment/TcpSocket.h
  src/TestEnviroment/PlaneManager.cpp
  src/TestEnviroment/PlaneManager.h
  src/TestEnviroment/Display.cpp
  src/TestEnviroment/Display.h
  src/TestEnviroment/Exception.cpp
  src/TestEnviroment/Exception.h
  src/TestEnviroment/SpriteRender.cpp
  src/TestEnviroment/SpriteRender.h
  src/TestEnviroment/Enviroment.cpp
  src/TestEnviroment/Enviroment.h
  src/TestEnviroment/SendData.cpp
  src/TestEnviroment/SendData.h
  src/TestEnviroment/ServerMessageEm.cpp
  src/TestEnviroment/ServerMessageEm.h


)

if(WIN32)
  target_link_libraries(TestEnviroment inc SDL2 SDL2_image jsoncpp ws2_32)
else()
  target_link_libraries(TestEnviroment inc SDL2 SDL2_image jsoncpp)
endif()




