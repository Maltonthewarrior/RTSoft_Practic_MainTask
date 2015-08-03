SRS = /usr/RTSoft_Ivan_Vadim
All: make_it
make_it: ip.o reader.o socket.o main.o
	g++ ip.o reader.o socket.o main.o -o res -lpthread
ip.o: ip.cpp ip.h
	g++ -c ip.cpp
reader.o: reader.cpp reader.h
	g++ -c reader.cpp
socket.o: socket.cpp socket.h
	g++ -c socket.cpp
main.o: main.cpp
	g++-4.8 -c main.cpp -lpthread -std=c++11
clean:
	rm -rf *.o
install: 
	install $(TARGET) $(PREFIX)
uninstall:
	rm -rf $(PREFIX)/$(TARGET)

