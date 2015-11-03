CXX = g++
CXXFLAGS = -Wall -O2
LDFLAGS = -flto -fwhole-program
#CXXFLAGS = -Wall -O0 -g3
#LDFLAGS = -g3

SOURCES =\
TicketSolverCLI.cpp \
../TicketSolver/TicketSolver.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXECUTABLE = ticketsolver

All: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@-rm $(OBJECTS)
	@-rm $(EXECUTABLE)