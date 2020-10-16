lab4.zip: makefile *.c *.h lab4readme
	zip lab4.zip makefile *.c *.h lab4readme
	rm -rf install
	mkdir install
	unzip lab4.zip -d install
	make -C install lab4
	
lab4: lab4.o linkedlist.o PSW.o
	gcc lab4.o linkedlist.o PSW.o -o lab4
	
lab4.o: lab4.c PSW.c linkedlist.c constants.h ballstructs.h
	gcc -ansi -pedantic -g -c lab4.c
	
linkedlist.o: linkedlist.c linkedlist.h
	gcc -ansi -pedantic -g -c linkedlist.c
	
PSW.o: PSW.c PSW.h
	gcc -ansi -pedantic -g -c PSW.c
	
Test0: Test0.c
	gcc -ansi -pedantic -g -o Test0 Test0.c
	
Test1: Test1.c
	gcc -ansi -pedantic -g -o Test1 Test1.c
	
Test2: Test2.c linkedlist.c ballstructs.h
	gcc -ansi -pedantic -g -o Test2 Test2.c linkedlist.o
	
Test3: Test3.c linkedlist.o ballstructs.h
	gcc -ansi -pedantic -g -o Test3 Test3.c linkedlist.o
	
clean:
	rm -rf *.o lab4
	
	
