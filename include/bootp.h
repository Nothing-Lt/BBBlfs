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

#ifndef BOOTP_H
#define BOOTP_H

#include "utils.h"
#include "config.h"

typedef u_int8_t ipv4addr[4];

typedef struct bootp {
    u_int8_t opcode; /*!< 1 for BOOTP_REQUEST, 2 for BOOTP_RESPONSE */
    u_int8_t hw; /*!< */
    u_int8_t hwlength; /*!< Length of the MAC */
    u_int8_t hopcount; /*!< Number of routers to pass until discarded */
    u_int32_t xid; /*!< Transaction ID */
    u_int16_t secs; /*!< Seconds since boot */
    u_int16_t flags; /*!<  */
    ipv4addr ciaddr; /*!< IP addr filled by client in REQUEST if known */
    ipv4addr yiaddr; /*!< IP addr of the client filled by server in RESPONSE */
    ipv4addr server_ip; /*!< IP addr of the BOOTP server */
    ipv4addr bootp_gw_ip; /*!< IP addr of the gateway */
    u_int8_t hwaddr[16]; /*!< MAC addr of the client */
    u_int8_t servername[64]; /*!< Name of the server */
    u_int8_t bootfile[128]; /*!< File to be booted */
    u_int8_t vendor[64]; /*!< Vendor extensions(subnet here for this project) */
} bootp_packet;

typedef u_int8_t hwaddr_t[6];

void make_bootp(const char *servername, const char *filename,
                bootp_packet *bpp, u_int32_t xid, unsigned char *hw_Dest);
void debug_bootp(bootp_packet *breq);

#endif
