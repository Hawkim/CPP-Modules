
cc= c++ 

CFLAGS=-Wall -Wextra -Werror  -std=c++98

TARGET= zombie

SRCS= Zombie.cpp newZombie.cpp randomChump.cpp main.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS) 
	$(cc) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(cc) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)

fclean :clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
