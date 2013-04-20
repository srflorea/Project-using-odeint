FLAGS 	= -Wall -o
CC	= g++
LIBS	= -I ./odeint/ ./boost/
RM	= rm
OBJFLAG = -c

simple_ode	: simple_ode.o
		$(CC) $(FLAGS) $@ $^ 

simple_ode.o	: simple_ode.cpp
		$(CC) $(LIBS) $(OBJFLAG) $^

clean		: simple_ode simple_ode.o
		$(RM) $^
