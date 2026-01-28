all:
	g++ -o main.exe source/*.cpp -Isources

clean:
	del main.exe