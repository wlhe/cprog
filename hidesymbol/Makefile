all:
	g++ -o libsym.so -shared -I../ symbol.cpp -Wl,--version-script=sym.map
	g++ -o lib2sym.so -shared -I../ symbol.cpp -fvisibility=hidden
	# g++ main.cpp -lsym -L./