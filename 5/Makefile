CC = g++
CFLAGS = -w -Wall -O2
SRCS = canny_edge_detection_test.c

PROG = test

OPENCV = `pkg-config --cflags --libs opencv`
LIBS = $(OPENCV)

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)
	$(./PROG)
