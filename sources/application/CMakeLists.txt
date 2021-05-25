add_library(application STATIC
	application.cpp
)

target_link_libraries(application PUBLIC
	httplib
	game
	game_handler
)
