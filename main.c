#include <stdio.h>
#include "tun.h"

int main(int argc, char *argv[]) {
    int tun, ret;
    char tun_name[IFNAMSIZ];
    unsigned char buf[4096];

    tun_name[0] = '\0';
    tun = tun_alloc(tun_name);
    if (tun < 0) {
            perror("tun_create");
            return 1;
    }
    printf("TUN name is %s\n", tun_name);

    while (1) {
        unsigned char ip[4];

        ret = read(tun, buf, sizeof(buf));
        if (ret < 0)
                break;
        memcpy(ip, &buf[12], 4);
        memcpy(&buf[12], &buf[16], 4);
        memcpy(&buf[16], ip, 4);
        buf[20] = 0;
        *((unsigned short*)&buf[22]) += 8;
        printf("read %d bytes\n", ret);
        ret = write(tun, buf, ret);
        printf("write %d bytes\n", ret);
    }
    return 0;
}

