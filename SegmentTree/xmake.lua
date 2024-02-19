add_rules("mode.debug")
set_toolchains("@llvm")

-- add_requires("boost")

target("p1") do
    set_kind("binary")
    add_files("./main.cxx")
	set_languages("cxx20")
	set_targetdir("./build")
	if is_mode("debug") then
        add_cxflags("-fsanitize=address")
        add_ldflags("-fsanitize=address")
        -- 如果你的环境中还需要链接其他库，例如在某些系统上可能需要显式链接libasan，可以这样添加：
        -- add_ldflags("-lasan")
    end
end
