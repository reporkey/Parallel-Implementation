all: P_FW P_FWT S_FW S_FWT nodegen

P_FW: P_FW.c
	gcc -Wall -fopenmp -std=c99 -O3 -o P_FW P_FW.c

P_FWT: P_FWT.c
	gcc -Wall -fopenmp -std=c99 -O3 -o P_FWT P_FWT.c

S_FWT: S_FWT.c
	gcc -Wall -fopenmp -std=c99 -O3 -o S_FWT S_FWT.c

S_FW: S_FW.cpp
	g++ -Wall -fopenmp -O3 -o S_FW S_FW.cpp

nodegen: nodegen.cpp
	g++ -Wall -O3 -o nodegen nodegen.cpp

clean:
	rm P_FW P_FWT S_FW S_FWT nodegen
