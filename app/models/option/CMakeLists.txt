add_library(option STATIC
	option.cpp
)

target_link_libraries(option PUBLIC
	player
)