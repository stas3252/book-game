add_library(actions STATIC
	action.cpp
	add_strength.cpp
)

target_link_libraries(actions PUBLIC
	player
)