add_library(console_editor STATIC
	console_editor.cpp
)


target_link_libraries(console_editor PUBLIC
	point
)