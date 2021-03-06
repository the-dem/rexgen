project(${prj} C)
set(rexgen_exename rexgen)

set(rexgen_sources rexgen.c)
set(rexgen_manpages rexgen.1)

# set compiler flags
if(MSVC)
  ADD_DEFINITIONS("-DUNICODE -D_UNICODE")
else()
  ADD_DEFINITIONS("--std=c89 -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Winline")
endif(MSVC)

if(CMAKE_BUILD_TYPE MATCHES FUZZER)
	add_compile_definitions("USE_LIBFUZZER=1")
	ADD_COMPILE_OPTIONS("-fsanitize=fuzzer,address")
	ADD_COMPILE_OPTIONS("-g")
	ADD_COMPILE_OPTIONS("-O0")
	ADD_LINK_OPTIONS("-fsanitize=fuzzer,address")
	ADD_LINK_OPTIONS("-g")
endif(CMAKE_BUILD_TYPE MATCHES FUZZER)

add_executable(${rexgen_exename} ${rexgen_sources})
target_link_libraries(${rexgen_exename} ${librexgen})

install(TARGETS ${rexgen_exename} RUNTIME DESTINATION bin)

# install manpage
if(MSVC)
else()
	add_custom_command(
		OUTPUT rexgen.1.gz
		COMMAND gzip "${CMAKE_CURRENT_SOURCE_DIR}/rexgen.1" -c >rexgen.1.gz)
	add_custom_target(man ALL DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/rexgen.1.gz")
	install(FILES "${CMAKE_CURRENT_BINARY_DIR}/rexgen.1.gz" DESTINATION "man/man1")
endif(MSVC)
