if (ENABLE_COVERAGE)
  message(INFO "Coverage analysis enabled")
  set(CMAKE_CXX_FLAGS "-coverage ${CMAKE_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "-coverage ${CMAKE_EXE_LINKER_FLAGS}")
endif ()
