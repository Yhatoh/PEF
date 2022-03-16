FILE = /
run:
	./build.sh
	./testpef

test:
	./build_dijkstra.sh
	./testpef < $(FILE)