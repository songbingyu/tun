#include <net/if.h>
#include <linux/if_tun.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
  
int tun_alloc(char *dev) {
    struct ifreq ifr;
    int fd, err;

    if( (fd = open("/dev/net/tun", O_RDWR)) < 0 )
       return fd;

    memset(&ifr, 0, sizeof(ifr));

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers) 
     *        IFF_TAP   - TAP device  
     *
     *        IFF_NO_PI - Do not provide packet information  
     */ 
    ifr.ifr_flags = IFF_TUN|IFF_NO_PI; 
    if (*dev != '\0') {
       strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }
    err = ioctl(fd, TUNSETIFF, (void *) &ifr);
    if (err < 0 ) {
       close(fd);
       return err;
    }
    strcpy(dev, ifr.ifr_name);
    return fd;
}              
