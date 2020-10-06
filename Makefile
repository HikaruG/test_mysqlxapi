MYSQL_CONCPP_DIR= /usr/local/mysql/connector-c++-8.0
CPPFLAGS = -I $(MYSQL_CONCPP_DIR)/include -L $(MYSQL_CONCPP_DIR)/lib64
LDLIBS = -lmysqlcppconn8
CXXFLAGS = -std=c++11

app : app.cc

test: test.o
		g++ $(CXXFLAGS) -o test test.o

test.o: test.cpp test.h
		g++ $(CXXFLAGS) -o test.o test.cpp $(CPPFLAGS)
