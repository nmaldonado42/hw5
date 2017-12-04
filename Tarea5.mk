CC=gcc
CFLAGS=-I.
DEPS = RadialVelocities.dat CurvaRotacion.c Plots.py Results_hw5.tex

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hw5: CurvaRotacion.o
	$(CC) -o CurvaRotacion.x CurvaRotacion.o $(CFLAGS)
	./CurvaRotacion.x >PlotData.dat
	python ./Plots.py
	latex Results_hw5.tex
	pdflatex Results_hw5.dvi