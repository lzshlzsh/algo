.PHONY: all clean

src := $(wildcard *.cpp)
obj := $(patsubst %.cpp,%.o,${src})
target := $(patsubst %.cpp,%,${src})

all: ${target}

${target}: %: %.o

clean:
	${RM} ${target} ${obj}
