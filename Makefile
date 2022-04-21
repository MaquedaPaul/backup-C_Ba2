all:
	make -C console
	make -C kernel
	make -C cpu
	make -C memory

clean:
	make clean -C console
	make clean -C kernel
	make clean -C cpu
	make clean -C memory

