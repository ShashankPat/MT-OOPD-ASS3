all: debug optimize

debug: quart_debug

quart_debug: quart.cpp
	g++ -g -o quart_debug quart.cpp
	./quart_debug

optimize: quart_optimize

quart_optimize: quart.cpp
	g++ -O3 -o quart_optimize quart.cpp
	./quart_optimize

clean:
	rm -f quart_debug quart_optimize