add_library(game_handler STATIC
	game.cpp
)

target_link_libraries(game_handler PUBLIC
	game
	json
	items
)
