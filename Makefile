run:
	mkdir -p build
	cmake -B build
	cd build && make
	./build/tray-pumpkin -c example-config.ini

