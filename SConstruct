env = Environment(LIBS=["GL"],
                  CXXFLAGS = [ "-O3", "-g3",
                               "-ansi",
                               "-pedantic",
                               "-Wall",
                               "-Wextra",
                               "-Wnon-virtual-dtor",
                               "-Weffc++",
                               "-Wconversion",
                               "-Wold-style-cast",
                               # "-Werror",
                               "-Wshadow",
                               "-Wcast-qual",
                               "-Winit-self", # only works with >= -O1
                               "-Wno-unused-parameter",
                               ])
env.ParseConfig("sdl-config --cflags --libs")
env.Program("gravisolar",
            Glob("*.cpp") + \
            Glob("math/*.cpp"))

# EOF #
