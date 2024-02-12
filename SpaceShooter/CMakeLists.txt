PROJECT(SpaceShooter)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

#set(glm_DIR /usr/lib/cmake/glm/)
#find_package(glm REQUIRED)
add_subdirectory(glm)

SET(HDRS ) # module headers go here (*.h)
SET(SRCS SpaceShooter.cpp Game.cpp Entity.cpp Ship.cpp Actor.cpp EnemyManager.cpp Projectile.cpp ProjectileManager.cpp) # module implementations go here (*.cpp)
ADD_EXECUTABLE(SpaceShooter ${HDRS} ${SRCS}) # compile and link main executable
target_link_libraries(SpaceShooter ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_include_directories(SpaceShooter PRIVATE glm)
