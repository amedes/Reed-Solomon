all: rstest

rstest: rstest.o poly.o rs.o gf.o
	$(CC) -o rstest rstest.o rs.o poly.o gf.o

rstest.o: rstest.c gf.h poly.h rs.h

gf.o: gf.c gf.h

poly.o: poly.c poly.h gf.h

rs.o: rs.c rs.h gf.h poly.h

clean:
	rm *.o rstest
