CC=gcc
CFLAGS=-lWarn -pedantic
houseAlarm:	houseAlarm.o libmyifttt.a
	$(CC) houseAlarm.o -L. -lwiringPi -lmyifttt -lcurl -o houseAlarm

tester: tester.o libmyifttt.a
	$(CC) tester.o -L. -lmyifttt -lcurl -o tester


irtester: irtester.o 
	$(CC) irtester.o -lwiringPi -o irtester


blink: blink.o 
	$(CC) blink.o -lwiringPi -o blink


button: button.o 
	$(CC) button.o -lwiringPi -o button


libmyifttt.a:	ifttt.o
	ar -rcs libmyifttt.a ifttt.o


ifttt.o: 	ifttt.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

tester.o:	tester.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

houseAlarm.o:	houseAlarm.c ifttt.h
	$(CC) $(CFLAGS) -c -ansi $<

all:	tester houseAlarm blink button


clean:
	rm tester houseAlarm *.o
