add_library(menu STATIC
	menu.cpp
)

target_link_libraries(menu PUBLIC
	console_editor
	point
)