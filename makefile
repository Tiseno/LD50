FLAGS = `pkg-config --static --libs glew`
FLAGS += `pkg-config --static --libs glfw3`

FLAGS += `pkg-config --cflags glew`
FLAGS += `pkg-config --cflags glfw3`

default:
	clear
	g++ -std=c++2a ./main.cpp $(FLAGS)
	./a.out


