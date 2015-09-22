# Modify this file to change the last-modified date when you add/remove a file. 
# This will then trigger a new cmake run automatically.
file(GLOB_RECURSE STORMRIDER_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.h")
file(GLOB_RECURSE STORMRIDER_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "src/*.cpp")