#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <string.h>
#include <syslog.h>

#include "udp.h"

void make_udp(udp_t *udp_packet, uint16_t udp_len, uint16_t srcPort, uint16_t dstPort) {
	memset(&udp_packet->chkSum, 0, sizeof(udp_packet->chkSum));
	memset(&udp_packet->udpLen, 0, sizeof(udp_packet->udpLen));

	udp_packet->udpSrc = srcPort;
	udp_packet->udpDst = dstPort; 

	udp_packet->udpLen += 8;
	udp_packet->udpLen += udp_len;
}

void debug_udp(udp_t *udp_packet, uint16_t udp_len) {
	syslog(LOG_DEBUG, "Starting UDP Log");
	syslog(LOG_DEBUG, "Src Port: %d",udp_packet->udpSrc);
	syslog(LOG_DEBUG, "Dst Port: %d",udp_packet->udpDst);
	syslog(LOG_DEBUG, "Length: %d", udp_packet->udpLen);
	syslog(LOG_DEBUG, "CheckSum: %d", udp_packet->chkSum);
	syslog(LOG_DEBUG, "End of UDP Log");
}