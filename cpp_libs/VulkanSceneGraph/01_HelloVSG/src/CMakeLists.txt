set(TARGET_NAME ${PROJECT_NAME})

################################################################################

set(SOURCES
    main.cpp
)

################################################################################

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(${TARGET_NAME}
    vsg::vsg
    vsgXchange::vsgXchange
    ${Vulkan_LIBRARIES}

)

################################################################################

install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})