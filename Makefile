CXXFLAGS = -Wall -g

executable:
	c++ $(CXXFLAGS) -o out *.cpp 

clean:
	rm out *.o *.gch *.out