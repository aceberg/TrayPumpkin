run:
	mkdir -p build
	cmake -B build
	cd build && make
	./build/tray-pumpkin -c config.yaml

deb:
	cd build && cpack