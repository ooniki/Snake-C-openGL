CC			:= gcc
SRCS 		:= $(shell find . -type f -name '*.c')
OBJ      	:= $(patsubst ./src/%.c, ./obj/%.o, $(SRCS))
ODIR		:= obj
SDIR		:= src
BIN      	:= prog.out
FLAGS		:= -W -Wall -Werror
DEBUG		:= -g -ggdb
GLUT		:= -I/usr/include -L/usr/lib -lGL -lGLU -lglut

all : clean ${BIN}

debug : clean ${OBJ}
	${CC} ${FLAGS} ${DEBUG} -o ${BIN} ${OBJ} ${GLUT}

${BIN} : ${OBJ}
	${CC} ${FLAGS} -o $@ $^ ${GLUT}

${ODIR}/%.o : ${SDIR}/%.c
	mkdir -p $(@D)
	${CC} -c $^ -o $@

clean :
	rm -fr ${ODIR}
	rm -f ${BIN}

use : ${BIN}
	./${BIN}

show :
	@echo ${SRCS}
	@echo ${OBJ}