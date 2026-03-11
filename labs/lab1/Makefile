CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
SOURCES = recursive_sequence.cpp type_info.cpp
TARGETS = $(SOURCES:%.cpp=%)
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGETS)

%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -vf $(TARGETS) *.o

run: $(TARGETS)
	@echo ""
	@for t in $(TARGETS); do \
		echo "./$$t"; \
		./$$t; \
	done
	python3 generate_graphs.py
