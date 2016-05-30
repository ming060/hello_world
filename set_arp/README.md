# set_arp

Example program to set arp entry into arp table using ioctl.

adding an entry into arp table:
ip address: 1.1.1.1
MAC address: aa:aa:aa:aa:aa:aa

The ioctl cmd lookup the routing table to figure out which interface the arp entry will be bind to.

For example:

sudo ip route add 1.1.1.0/24 dev eth1

Then the arp entry will be add to interface eth1.

Make the program:

cc -g set_arp.c

Checking the result:
ip neigh show to 1.1.1.1
or
ip neigh show dev eth1

Deleting the arp entry:
sudo ip neigh del 1.1.1.1 dev eth1
