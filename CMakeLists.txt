cmake_minimum_required(VERSION 3.1)
project(book_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories(
  ${PROJECT_SOURCE_DIR}
)

add_subdirectory(app)
add_subdirectory(library)
add_subdirectory(sources)


add_executable(book_game
  main.cpp
)

target_link_libraries(book_game PUBLIC
	game
	application
)
