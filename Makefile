CFLAGS = -O3

all: csvanon

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

CsvProcessor.o: CsvProcessor.cpp
	g++ $(CFLAGS) -c CsvProcessor.cpp

csvanon: main.o CsvProcessor.o
	g++ -o csvanon $(CFLAGS) main.o CsvProcessor.o -lcrypto -lboost_program_options

clean:
	rm -rf *.o csvanon








