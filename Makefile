CXXFLAGS = -Wall -g

executable:
	c++ $(CXXFLAGS) -o out src/*.cpp -w -lncurses

clean:
	rm out *.o *.gch *.out
