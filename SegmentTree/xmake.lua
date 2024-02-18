add_rules("mode.debug")
set_toolchains("@llvm")

-- add_requires("boost")

target("p1") do
    set_kind("binary")
    add_files("./main.cxx")
	set_languages("cxx20")
	set_targetdir("./build")
end
