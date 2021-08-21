CXXFLAGS = -Wall -g

executable:
	c++ -std=c++17 $(CXXFLAGS) -o out src/*.cpp -w -lncurses

clean:
	rm out *.o *.gch *.out
