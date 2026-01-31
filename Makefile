CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra

SRCDIR = src
INCDIR = include
BUILDDIR = build
TARGET = $(BUILDDIR)/ArabicMorphology

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(OBJECTS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)/*

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
