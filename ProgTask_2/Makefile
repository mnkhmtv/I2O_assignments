BUILDDIR = build

TEST_EXEC = $(BUILDDIR)/runTests

all: build

build: install_gtest
	cmake -B$(BUILDDIR) -H.
	$(MAKE) -C $(BUILDDIR)

test: build
	$(TEST_EXEC)

memory: build
	valgrind --leak-check=full $(TEST_EXEC)

format:
	find . -iname "*.h" -o -iname "*.cpp" | xargs clang-format -i --Werror

lint:
	find . -name "*.cpp" -o -name "*.hpp" | grep -v "build/" | xargs cpplint --filter=-legal/copyright,-build/include_subdir

clean:
	$(RM) -r $(BUILDDIR)

install_gtest:
	@if [ ! -d "googletest" ]; then \
		git clone https://github.com/google/googletest.git; \
		cd googletest && mkdir build && cd build && cmake .. && make && sudo make install; \
	fi

.PHONY: all build test memory format lint check clean