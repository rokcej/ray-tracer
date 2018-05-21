# Flags
GXX=g++
CPPFLAGS=
LDFLAGS=
LDLIBS=-lSDL2

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

# Clean
.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -f $(OBJS) $(EXEC)
