FILE = /
run:
	./build.sh
	./testpef

test:
	./build_dijkstra.sh
	./testpef < $(FILE)

test_compression:
	g++ -std=c++17 -O3 -DNDEBUG -I ~/include -L ~/lib testpef_compression.cpp -o testpef_compression -lsdsl;
