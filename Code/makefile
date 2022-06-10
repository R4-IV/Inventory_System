#MakeFile software engineering CW

sManagement: product.o report.o employee.o inventory.o main.o dependencies.h product.h employee.h inventory.h report.h
	g++ -std=c++17  report.o  inventory.o employee.o product.o main.o -o sManagement

report.o: report.cpp
	g++ -std=c++17 -c report.cpp

inventory.o: inventory.cpp
	g++ -std=c++17 -c inventory.cpp

employee.o: employee.cpp
	g++ -std=c++17 -c employee.cpp

product.o: product.cpp
	g++ -std=c++17 -c product.cpp

main.o: main.cpp
	g++ -std=c++17 -c main.cpp

	

clean:
	rm *.o sManagement tests
