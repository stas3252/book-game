add_library(game STATIC
	game.cpp
)

target_link_libraries(game PUBLIC
	console_editor
	menu
	dice
	json
	decoder
	player
	level
	point
	actions
	option
	items
)
