# vim: set ft=python
env = Environment()

env.ParseConfig("pkg-config jack --libs --cflags")
env.ParseConfig("pkg-config sndfile --libs --cflags")

env.Program("run", Glob("*.cpp"))
