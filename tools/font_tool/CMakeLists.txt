option(FONT_TOOL "Compile font tool" OFF)

if(FONT_TOOL)
    find_package(Freetype)
    find_package(X11)
    find_library(FONTCONFIG_LIBRARY fontconfig)

    if(FREETYPE_FOUND)
        include_directories(${FREETYPE_INCLUDE_DIRS})
        add_executable(font_tool CFontTool.cpp main.cpp)
        target_link_libraries(font_tool ${FREETYPE_LIBRARIES})
        target_link_libraries(font_tool ${X11_Xft_LIB} Xxf86vm)
        target_link_libraries(font_tool ${OPENGL_LIBRARIES})
        target_link_libraries(font_tool ${IRRLICHT_LIBRARIES})
        target_link_libraries(font_tool ${FONTCONFIG_LIBRARY})
    else()
        message(STATUS "Freetype was not found, the font tool won't be built (only useful for developers)")
    endif()
else()
    message(STATUS "Font tool deactivated, the font tool won't be built (only useful for developers)")
endif()
