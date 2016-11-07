CPPFLAGS = -std=c++11 -Wall -Werror -O3
LDFLAGS = -lboost_system -lboost_thread-mt

TARGET = Client
OUTDIR = out/
SOURCE = ../Command/Command.cpp Client.cpp main.cpp

vpath %.cpp ../Command

OBJS = $(addprefix $(OUTDIR), $(notdir ${SOURCE:cpp=o}))
INC = -I. -I../Command/

All: ${TARGET}

${TARGET}: ${OUTDIR} ${OBJS}
	g++ ${CPPFLAGS} ${INC} ${LDFLAGS} ${OBJS} -o $@.out

${OUTDIR}:
	mkdir $@

${OUTDIR}%.o: %.cpp
	g++ ${CPPFLAGS} ${INC} -c $< -o $@

.PHONY: clean
clean:
	rm -rf ${OUTDIR} ${TARGET}.out

