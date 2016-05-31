/* Hello World program */

#include<stdio.h>
#include<string.h>
#include <errno.h>
#include <linux/rtnetlink.h>
#include <sys/socket.h>

/* Socket interface to kernel */
struct nlsock
{
  int sock;
  int seq;
  struct sockaddr_nl snl;
  const char *name;
} netlink      = { -1, 0, {0}, "netlink-listen"},     /* kernel messages */
  netlink_cmd  = { -1, 0, {0}, "netlink-cmd"};        /* command channel */

int
addattr_l (struct nlmsghdr *n, int maxlen, int type, void *data, int alen)
{
  int len;
  struct rtattr *rta;

  len = RTA_LENGTH (alen);

  if (NLMSG_ALIGN (n->nlmsg_len) + len > maxlen)
    return -1;

  rta = (struct rtattr *) (((char *) n) + NLMSG_ALIGN (n->nlmsg_len));
  rta->rta_type = type;
  rta->rta_len = len;
  memcpy (RTA_DATA (rta), data, alen);
  n->nlmsg_len = NLMSG_ALIGN (n->nlmsg_len) + len;

  return 0;
}

// convert mac address string to lladdr
static int ll_addr_a2n(char *lladdr, int len, char *arg)
{
    int i;

    for (i = 0; i < len; i++) {
        int temp;
        char *cp = strchr(arg, ':');
        if (cp) {
            *cp = 0;
            cp++;
        }
        if (sscanf(arg, "%x", &temp) != 1) {
            fprintf(stderr, "\"%s\" is invalid lladdr.\n", arg);
            return -1;
        }
        if (temp < 0 || temp > 255) {
            fprintf(stderr, "\"%s\" is invalid lladdr.\n", arg);
            return -1;
        }
        lladdr[i] = temp;
        if (!cp)
            break;
        arg = cp;
    }
    return i + 1;
}

// Convert ip address string to unsigned
// Return 1 if success
static int ip_str_to_int(char * ip_str, unsigned int * ip)
{
    return inet_pton(AF_INET, ip_str, ip);
}

main()
{
    unsigned int lla_length;
    unsigned int addr;
    char lla[6];
    unsigned int ifindex = 3;

    struct {
        struct nlmsghdr n;
        struct ndmsg ndm;
        char buf[256];
    } req;

    struct sockaddr_nl snl;
    struct nlmsghdr *n;

    int ret = 0;
    bzero(&req, sizeof(req));

    sscanf("aa:aa:aa:aa:aa:aa", "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
        lla, lla+1, lla+2,
        lla+3, lla+4, lla+5);

    lla_length = ll_addr_a2n(lla, sizeof(lla), strdup("aa:aa:aa:aa:aa:aa"));

    ip_str_to_int(strdup("1.1.1.1"), &addr);

    req.n.nlmsg_len = NLMSG_LENGTH(sizeof(struct ndmsg));
    req.n.nlmsg_flags = NLM_F_REQUEST | NLM_F_CREATE | NLM_F_REPLACE;
    req.n.nlmsg_type = RTM_NEWNEIGH;
    req.ndm.ndm_family = AF_INET;
    req.ndm.ndm_state = NUD_PERMANENT;
    req.ndm.ndm_ifindex = ifindex;

    addattr_l(&req.n, sizeof(req), NDA_DST, &addr, 4);
    addattr_l(&req.n, sizeof(req), NDA_LLADDR, lla, lla_length);

    int sock, seq;
    sock = socket (AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);

    seq = 0;

    req.n.nlmsg_flags |= NLM_F_ACK;

    n = &req.n;
    n->nlmsg_seq = ++seq;

    struct iovec iov = { (void *) n, n->nlmsg_len };
    struct msghdr msg = { (void *) &snl, sizeof snl, &iov, 1, NULL, 0, 0 };
    int save_errno;

    bzero (&snl, sizeof snl);

    snl.nl_family = AF_NETLINK;

    /* Send message to netlink interface. */
    ret = sendmsg (sock, &msg, 0);
    save_errno = errno;

    if (ret < 0)
    {
        perror("netlink");
        return -1;
    }

    /*
    * Get reply from netlink socket.
    * The reply should either be an acknowlegement or an error.
    */
    //return netlink_parse_info (netlink_talk_filter, nl);
    return ret;
}
