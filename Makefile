build:
	g++ comenzi.cpp piese.cpp -o engine

run: build
	xboard -fcp ./engine

clean:
	rm -rf engine
