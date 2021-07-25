CXXFLAGS = -Wall -g

executable:
	c++ $(CXXFLAGS) -o out *.cpp -lncurses

clean:
	rm out *.o *.gch *.out