MODEL ?= Z10

CFLAGS  = -g -std=gnu11 -Wall -Werror
CFLAGS += -I/opt/redpitaya/include
CFLAGS += -I../include
LDFLAGS = -L/opt/redpitaya/lib
LDLIBS =  -lpthread -lrp -lm

ifeq ($(MODEL),Z20_250_12)
INCLUDE += -I/opt/redpitaya/include/api250-12
LDLIBS += -lrp-gpio -lrp-i2c
endif

# common sources 
COMMON_SRC := build_pulse.c 
#VPATH := ../lib #src1:../src2 
#COMMON_OBJS := $(patsubst %.c, %.o, $(notdir $(COMMON_SRC))) 
COMMON_OBJS :=  $(COMMON_SRC:.c=.o)

#SRCS=$(wildcard *.c)
SRCS=gen_esther_pulse.c gen_esther_pulse2.c
OBJS=$(SRCS:.c=)

.PHONY : all

all: $(OBJS)
	@echo common_objs  $COMMON_OBJS

gen_esther_pulse: $(COMMON_OBJS)
gen_esther_pulse2: $(COMMON_OBJS)

%.o: %.c
	@echo objs  $OBJS
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	$(RM) *.o
	$(RM) $(OBJS)
