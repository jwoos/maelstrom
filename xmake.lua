add_rules("mode.debug", "mode.release")

set_warnings("all", "error")

set_languages("c++20")

set_defaultmode("debug")

add_requires("catch2")

set_policy("package.requires_lock", true)

target("maelstrom-lib")
	set_kind("headeronly")
	add_headerfiles("include/**/*.hpp")
	add_includedirs("include", {public = true})

target("main")
	set_kind("binary")
	add_files("src/main.cpp")

target("test")
	set_kind("binary")
	add_files("test/*.cpp")
	add_deps("maelstrom-lib")
	add_tests("default")
	add_packages("catch2")
