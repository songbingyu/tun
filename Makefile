CPPFLAGS = -I include -Wall

src = $(wildcard ./*.c)
obj = $(patsubst /%.c, build/%.o, $(src))
headers = $(wildcard ./*.h)

all: $(obj)
	$(CC) $(obj) -o tun_icmp
clean:
	rm tun_icmp
