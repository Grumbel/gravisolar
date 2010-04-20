env = Environment(LIBS=["GL"], CXXFLAGS=["-O3", "-g"])
env.ParseConfig("sdl-config --cflags --libs")
env.Program("gravisolar",
            Glob("*.cpp") + \
            Glob("math/*.cpp"))

# EOF #
