SET(PROJECT_DIR ${CMAKE_SOURCE_DIR}/projects)

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB CHILDREN_FILES ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${CHILDREN_FILES})
    IF(IS_DIRECTORY ${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

SUBDIRLIST(SUBDIRS ${PROJECT_DIR})
foreach(subdir ${SUBDIRS})
  file(GLOB_RECURSE PROJECT_FILES ${subdir}/*)
  string( REPLACE ${PROJECT_DIR} "" project_name ${subdir})
  string( REPLACE "/" "" project_name ${project_name})
  add_executable(${project_name} ${PROJECT_FILES})
  target_link_libraries(${project_name} PUBLIC Alloy_Core Alloy_Common Alloy_Modules )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Oi /Ox /fp:fast /FAs /arch:AVX2")
  set_target_properties (${project_name} PROPERTIES FOLDER Projects)
endforeach()