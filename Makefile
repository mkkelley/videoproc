
all:
	mkdir -p build
	cd build; \
	 cmake .. -DCMAKE_BUILD_TYPE=Release
	make -j8 -C build

debug:
	mkdir -p debug
	cd debug; \
	 cmake .. -DCMAKE_BUILD_TYPE=Debug
	make -j8 -C debug

doc:
	doxygen Doxyfile

clean:
	rm -rf build
	rm -rf debug
	rm -rf html
