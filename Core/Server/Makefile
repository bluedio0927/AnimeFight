CPPFLAGS = -std=c++11 -Wall -Werror -O3
LDFLAGS = -lboost_system -lboost_thread-mt

TARGET = Server
OUTDIR = out/
vpath  %.cpp ../Command/
SOURCE = ../Command/Command.cpp \
		 Session.cpp \
		 Room.cpp \
		 Server.cpp \
		 main.cpp

INC = -I. -I../Command
OBJS = $(addprefix $(OUTDIR), $(notdir ${SOURCE:cpp=o}))

All: ${TARGET}

${OUTDIR}:
	mkdir ${OUTDIR}

${TARGET}: ${OUTDIR} ${OBJS}
	g++ ${CPPFLAGS} ${INC}  ${LDFLAGS} ${OBJS} -o $@.out

${OUTDIR}%.o: %.cpp
	g++ ${CPPFLAGS} ${INC}  -c $< -o $@

.PHONY: clean

clean:
	rm -rf ${OUTDIR} ${TARGET}.out

