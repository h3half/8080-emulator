src_dir = src
build_dir = build

all: clear emulator.out

clear:
	clear

$(build_dir)/disassembler.o: $(src_dir)/disassembler.c
	gcc -c -g -o $@ $<

$(build_dir)/utilities.o: $(src_dir)/utilities.c
	gcc -c -g -o $@ $<

$(build_dir)/opcodes.o: $(src_dir)/opcodes.c
	gcc -c -g -o $@ $<

emulator.out: $(src_dir)/emulator.c $(build_dir)/disassembler.o $(build_dir)/utilities.o $(build_dir)/opcodes.o
	gcc -g -o $@ $^
	./$@ | tee output.txt

clean:
	rm build/*
	rm *.out
	rm *.txt
