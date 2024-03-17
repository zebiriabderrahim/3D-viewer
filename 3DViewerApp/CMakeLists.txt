cmake_minimum_required(VERSION 3.10)
project(3DViewerApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(core)
add_subdirectory(app)
# add_subdirectory(gui)
# add_subdirectory(models)

#find_package(spdlog REQUIRED)



#enable_testing()
#add_subdirectory(tests)
