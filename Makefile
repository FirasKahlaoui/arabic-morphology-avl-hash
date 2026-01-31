CXX = g++
CXXFLAGS = -std=c++17 -Iinclude -Wall -Wextra

SRCDIR = src
INCDIR = include
BUILDDIR = build
TESTDIR = tests
TARGET = $(BUILDDIR)/ArabicMorphology
TEST_AVL = $(BUILDDIR)/test_avl

SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES))

LIB_SOURCES = $(filter-out $(SRCDIR)/main.cpp, $(SOURCES))
LIB_OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(LIB_SOURCES))

$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(OBJECTS) -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TEST_AVL): $(TESTDIR)/test_avl.cpp $(LIB_OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

test-avl: $(TEST_AVL)
	./$(TEST_AVL)

clean:
	rm -rf $(BUILDDIR)/*

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run test-avl
