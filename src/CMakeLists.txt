project(cpp-snippets)

file(GLOB source_files "*.cpp")
foreach(file ${source_files})
	get_filename_component(filename ${file} NAME_WE)
	message(STATUS "snippet: ${filename}")
	add_executable(${filename} ${file})
endforeach()
