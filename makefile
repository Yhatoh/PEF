run:
	./build.sh
	./testpef

test:
	./build_dijkstra.sh
	./testpef < /data/bitvectors/ii/gov2/url/gov2_ii_nofreq_url_dif.txt.dat.100000