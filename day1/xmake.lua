add_rules("mode.debug")
set_toolchains("@llvm")

-- add_requires("boost")

-- target("p1") do
--     set_kind("binary")
--     add_files("./p1.cxx")
-- 	set_languages("cxx23")
-- 	set_targetdir("./build")
-- end

-- target("p2") do
--     set_kind("binary")
--     add_files("./p2.cxx")
-- 	set_languages("cxx23")
-- 	set_targetdir("./build")
-- end

-- target("p3") do
--     set_kind("binary")
--     add_files("./p3.cxx")
-- 	set_languages("cxx23")
-- 	set_targetdir("./build")
-- end

-- target("p4") do
--     set_kind("binary")
--     add_files("./p4.cxx")
-- 	set_languages("cxx23")
-- 	set_targetdir("./build")
-- end

-- target("p5") do
--     set_kind("binary")
--     add_files("./p5.cxx")
-- 	set_languages("cxx23")
-- 	set_targetdir("./build")
-- end

target("p6") do
    set_kind("binary")
    add_files("./p6.cxx")
	set_languages("cxx23")
	set_targetdir("./build")
end