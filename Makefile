tsp: tspmain.cpp
	g++ -std=c++11 tspmain.cpp -o tsp

clean:
	rm tsp *.tour
