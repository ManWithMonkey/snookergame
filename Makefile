CXXFLAGS = -Wall -g

executable:
	c++ $(CXXFLAGS) -o out src/*.cpp -lncurses

clean:
	rm out *.o *.gch *.out
