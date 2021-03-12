add_library(level STATIC
	level.cpp
)

target_link_libraries(level PUBLIC
	actions
)