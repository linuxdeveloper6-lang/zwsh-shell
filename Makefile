CC = gcc
CCFLAGS = -O2 -s -fno-stack-protector -fomit-frame-pointer -fno-unwind-tables -std=c99 -fdata-sections -ffunction-sections -flto -fno-math-errno -fmerge-all-constants -lreadline
LDFLAGS = -Wl,--gc-sections -Wl,--strip-all -Wl,--no-undefined
CFILES = src/main.c
OUTPUT = zwsh

$(OUTPUT):
	$(CC) $(CFILES) $(CCFLAGS) $(LDFLAGS) -o $(OUTPUT)
clean:
	rm -rf $(OUTPUT)
install:
	cp $(OUTPUT) /bin/
remove:
	rm /bin/$(OUTPUT)
