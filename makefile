all: fb testMyADT

fb: FriendsBook.o MyADT.o Profile.o
	g++ -Wall -o fb FriendsBook.o MyADT.o Profile.o

FriendsBook.o: FriendsBook.cpp MyADT.h Profile.h
	g++ -Wall -c FriendsBook.cpp

MyADT.o: MyADT.h MyADT.cpp
	g++ -Wall -c MyADT.cpp

Profile.o: Profile.h Profile.cpp
	g++ -Wall -c Profile.cpp

MyADT_test_driver.o: MyADT_test_driver.cpp MyADT.h Profile.h
	g++ -Wall -c MyADT_test_driver.cpp

testMyADT: MyADT_test_driver.o MyADT.o Profile.o
	g++ -Wall -o testMyADT MyADT_test_driver.o MyADT.o Profile.o

clean:
	rm -f fb *.o