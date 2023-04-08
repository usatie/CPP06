NAME = convert

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic

SRCDIR	= src
SRCS	= $(wildcard $(SRCDIR)/*.cpp)
INCLUDES	= $(wildcard $(SRCDIR)/*.hpp)
OBJDIR	= obj
OBJS	= $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME) : $(OBJS)
	$(CXX) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $^ $(CXXFLAGS) -c -o $@

clean:
	$(RM) *.o
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

debug: CXXFLAGS += -D DEBUG
debug: re

run: $(NAME)
	# Tests from example
	./$(NAME) 0
	./$(NAME) nan
	./$(NAME) 42.0f
	# char
	./$(NAME) 'c'
	./$(NAME) 'a'
	# int
	./$(NAME) 0
	./$(NAME) 42
	./$(NAME) -42
	# float
	./$(NAME) 0.0f
	./$(NAME) 4.2f
	./$(NAME) -4.2f
	./$(NAME) -inff
	./$(NAME) +inff
	./$(NAME) nanf
	# double
	./$(NAME) 0.0
	./$(NAME) 4.2
	./$(NAME) -4.2
	./$(NAME) -inf
	./$(NAME) +inf
	./$(NAME) nan
	# overflow while converting from int to char
	./$(NAME) 128
	./$(NAME) -129
	./$(NAME) 2147483647
	./$(NAME) -2147483648
	# overflow while converting from float to int
	./$(NAME) 2147483648.0f
	./$(NAME) -2147483649.0f
	# overflow while converting from string to char
	./$(NAME) 2147483648
	./$(NAME) -2147483649
	# overflow while converting from double to float
	./$(NAME) 340282346638528859811704183484516925440.0 # FLT_MAX
	./$(NAME) 3402823466385288598117041834845169254400.0 # FLT_MAX * 10
	./$(NAME) 1000000000000000000000000000000000000000000000000000000000000.0
	# tests non printable chararacter
	# ./$(NAME) '\177'

leakcheck: $(NAME)
	leaks --atExit -q -- ./$(NAME)

format:
	clang-format -style=google $(SRCS) $(INCLUDES) -i
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem . -I .

.PHONY: all clean fclean re run format debug leakcheck
