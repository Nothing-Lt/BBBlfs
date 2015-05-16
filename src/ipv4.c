/*
 * Copyright (C) 2013-2015 Vlad Ungureanu
 * Contact: Vlad Ungureanu <vvu@vdev.ro>
 *
 * This source is subject to the license found in the file 'LICENSE' which must
 * be be distributed together with this source. All other rights reserved.
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
 * EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "ipv4.h"

#include "udp.h"
#include "bootp.h"

uint16_t ip_checksum(const void *buf, size_t hdr_len);

void make_ipv4(struct iphdr *ip, char *src_addr, char *dst_addr,
                uint8_t proto, uint16_t id, ssize_t total_len) {
	ip->version = 4;
	ip->ihl = 5;
	ip->ttl = 64;
	ip->id = htons(id);
	ip->tot_len = htons(total_len);
	ip->protocol = proto;

    if(inet_aton(src_addr, (struct in_addr *)&ip->saddr) == 0) {
		printf("Cannot add IPv4 src address!\n");
	}

	if(inet_aton(dst_addr, (struct in_addr *)&ip->daddr) == 0) {
		printf("Cannot add IPv4 dst address!\n");
	}

    ip->check = ip_checksum(ip, sizeof(struct iphdr));
}

uint16_t ip_checksum(const void *buf, size_t hdr_len) {
	unsigned long sum = 0;
	const uint16_t *ip1;
	ip1 = buf;

	while(hdr_len > 1) {
		sum += *ip1++;
		if (sum & 0x80000000)
			sum = (sum & 0xFFFF) + (sum >> 16);
		hdr_len -= 2;
	}

	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	return(~sum);
}

void debug_ipv4(struct iphdr *ip) {
	syslog(LOG_DEBUG, "STARTING IPV4 LOG");
	syslog(LOG_DEBUG, "IP Version: %d", ip->version);
	syslog(LOG_DEBUG, "IP Header Length: %d", ip->ihl);
	syslog(LOG_DEBUG, "IP ID: %d", ip->id);
	syslog(LOG_DEBUG, "IP Total Length: %d", ntohs(ip->tot_len));
	syslog(LOG_DEBUG, "IP Protocol: %d", ip->protocol);
	syslog(LOG_DEBUG, "IP TTL: %d", ip->ttl);
	syslog(LOG_DEBUG, "IP SrcAddr: %s", inet_ntoa(*(struct in_addr*)&ip->saddr));
	syslog(LOG_DEBUG, "IP DstAddr: %s", inet_ntoa(*(struct in_addr*)&ip->daddr));
	syslog(LOG_DEBUG, "IP CheckSum: %dd", ip->check);
	syslog(LOG_DEBUG, "END OF IPV4 LOG");
}
