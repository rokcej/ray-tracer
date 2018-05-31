# Flags
GXX=g++
CPPFLAGS=-std=c++11
LDFLAGS=
LDLIBS=-lSDL2 -lm

# Parameters
EXECUTABLE=main
SOURCEDIR=src
BUILDDIR=build

# Files
EXEC=$(BUILDDIR)/$(EXECUTABLE)
SRCS=$(wildcard $(SOURCEDIR)/*.cpp)
OBJS=$(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

.PHONY: all
all: $(BUILDDIR) $(EXEC)

# Create builddir
$(BUILDDIR):
	@mkdir -p $@

# Link
$(EXEC): $(OBJS)
	@echo "Linking..."
	@$(CXX) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# Compile
$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	@echo "Compiling $^"
	@$(CXX) $(CPPFLAGS) -c $< -o $@

# Run
.PHONY: run
run:
	@echo "Running..."
	@$(BUILDDIR)/$(EXECUTABLE)

# Clean
.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXEC)

# Clean, compile, run
.PHONY: dev
dev: clean all run