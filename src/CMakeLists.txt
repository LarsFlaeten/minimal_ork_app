set(EXENAME app)

# Sources
include_directories("${PROJECT_SOURCE_DIR}" "${PROJECT_SOURCE_DIR}/libraries" "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB SOURCE_FILES *.cpp)

# Add defines for exe build
find_package(PkgConfig)
PKG_CHECK_MODULES(ORK REQUIRED ork)
add_definitions(${ORK_CFLAGS})

add_executable(${EXENAME} ${SOURCE_FILES})

#Added whole archive due to the "plug-in usage"
target_compile_options(${EXENAME} PUBLIC -std=c++11 -Wall)
set(LIBS ork pthread GL GLU GLEW glut glfw3 rt dl Xrandr Xinerama Xxf86vm Xext Xcursor Xrender Xfixes X11 tiff tinyxml)
target_link_libraries(${EXENAME} ${LIBS})

