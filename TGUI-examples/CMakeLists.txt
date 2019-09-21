
set(CMAKE_CURRENT_BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(ScalableLoginScreen scalable_login_screen/ScalableLoginScreen.cpp )
target_link_libraries( ScalableLoginScreen tgui utilities  sfml-graphics sfml-system sfml-window  sfml-audio  )

add_executable(ManyDifferentWidgets many_different_widgets/ManyDifferentWidgets.cpp )
target_link_libraries( ManyDifferentWidgets tgui utilities  sfml-graphics sfml-system sfml-window  sfml-audio  )
