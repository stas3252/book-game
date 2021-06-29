add_library(actions STATIC
	action.cpp
	add_strength.cpp
	add_flask.cpp
	add_extra_info.cpp
	spend_flask.cpp
	spend_strength.cpp
	get_item.cpp
	get_gold.cpp
	check_luck.cpp
)

target_link_libraries(actions PUBLIC
	player
	items
	json
)