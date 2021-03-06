/**
 * sixlowpan/ip.h   - 6LoWPAN constants, data structs, and prototypes
 *                    for network layer
 *
 * Copyright (C) 2013  INRIA.
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 *
 * @ingroup sixlowpan
 * @{
 * @file
 * @brief   6LoWPAN network layer header
 * @author  Stephan Zeisberg <zeisberg@mi.fu-berlin.de>
 * @author  Martin Lenders <mlenders@inf.fu-berlin.de>
 * @author  Eric Engel <eric.engel@fu-berlin.de>
 * @author  Oliver Gesch <oliver.gesch@googlemail.com>
 */

#ifndef SIXLOWPAN_IP_H
#define SIXLOWPAN_IP_H

#include <stdint.h>

#include "sixlowpan/types.h"

/**
 * @brief   IPv6 maximum transmission unit.
 */
#define IPV6_MTU                (256)

/**
 * @brief   Maximum length of a IPv6 address represented as string.
 */
#define IPV6_MAX_ADDR_STR_LEN   (40)

/**
 * @brief   L4 protocol number for TCP.
 */
#define IPV6_PROTO_NUM_TCP          (6)

/**
 * @brief   L4 protocol number for UDP.
 */
#define IPV6_PROTO_NUM_UDP          (17)

/**
 * @brief   L4 protocol number for ICMPv6.
 */
#define IPV6_PROTO_NUM_ICMPV6       (58)

/**
 * @brief   L4 protocol number for no L4 protocol in IPv6.
 */
#define IPV6_PROTO_NUM_NONE         (59)

/**
 * @brief   L4 protocol number for IPv6 destination options.
 */
#define IPV6_PROTO_NUM_IPV6_OPTS    (60)

/**
 * @brief   Get IPv6 send/receive buffer.
 *
 * @return  Pointer to IPv6 header in send/receive bouffer.
 * @note    To be deleted in later releases. Here only because it is
 *          used by the rpl module.
 */
ipv6_hdr_t *ipv6_get_buf(void);

/**
 * @brief   Send IPv6 packet to dest.
 *
 * @param[in] dest              Destination of this packet.
 * @param[in] next_header       Next header ID of payload.
 * @param[in] payload           Payload of the packet.
 * @param[in] payload_length    Length of payload.
 */
void ipv6_sendto(const ipv6_addr_t *dest, uint8_t next_header,
                 const uint8_t *payload, uint16_t payload_length);

/**
 * @brief   Determines if node is a router.
 *
 * @return  1 if node is router, 0 otherwise.
 */
uint8_t ipv6_is_router(void);

/**
 * @brief   Registers a handler thread for incoming IP packets.
 *
 * @param[in] pid   PID of handler thread.
 *
 * @return  0 on success, ENOMEN if maximum number of registrable
 *          threads is exceeded.
 */
uint8_t ipv6_register_packet_handler(int pid);

/**
 * @brief   Registers a handler thread for L4 protocol.
 *
 * @param[in] next_header   Next header ID of the L4 protocol.
 * @param[in] pid           PID of the handler thread
 */
void ipv6_register_next_header_handler(uint8_t next_header, int pid);

/**
 * @brief   Registers a handler thread for RPL options
 *
 * @param[in] pid   PID of the handler thread.
 */
void ipv6_register_rpl_handler(int pid);

/**
 * @brief   Sets the first 64 bit of *ipv6_addr* to link local prefix.
 *
 * @param[in,out] ipv6_addr The address to set.
 */
void ipv6_addr_set_link_local_prefix(ipv6_addr_t *ipv6_addr);

/**
 * @brief   Sets IPv6 address *out* according to the remaining
 *          parameters.
 *
 * @param[out]  out     The resulting address.
 * @param[in]   addr0   The first 16 bit of the new address.
 * @param[in]   addr1   The second 16 bit of the new address.
 * @param[in]   addr2   The third 16 bit of the new address.
 * @param[in]   addr3   The fourth 16 bit of the new address.
 * @param[in]   addr4   The fifth 16 bit of the new address.
 * @param[in]   addr5   The sixth 16 bit of the new address.
 * @param[in]   addr6   The seventh 16 bit of the new address.
 * @param[in]   addr7   The eighth 16 bit of the new address.
 */
void ipv6_addr_init(ipv6_addr_t *out, uint16_t addr0, uint16_t addr1,
                    uint16_t addr2, uint16_t addr3, uint16_t addr4,
                    uint16_t addr5, uint16_t addr6, uint16_t addr7);

/**
 * @brief   Sets IPv6 address *out* using the given *prefix* and this
 *          nodes EUI-64 (i. e. interface must be initialized).
 *
 * @param[out]  out     Address to be set.
 * @param[in]   prefix  64-bit network prefix to be used for *out*
 *                      (only the first 64 bit of the ipv6_addr_t type
 *                      are copied to *out*)
 */
void ipv6_addr_set_by_eui64(ipv6_addr_t *out,
                            const ipv6_addr_t *prefix);

/**
 * @brief   Sets IPv6 address *out* with the first *bits* bit taken
 *          from *prefix* and the remaining bits to 0.
 *
 * @param[out]  out     Prefix to be set.
 * @param[in]   prefix  Address to take prefix from.
 * @param[in]   bits    Bits to be copied from *prefix* to *out*
 *                      (set to 128 when greater than 128).
 */
void ipv6_addr_init_prefix(ipv6_addr_t *out, const ipv6_addr_t *prefix,
                           uint8_t bits);

/**
 * @brief   Set *ipv6_addr* to the loopback address.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4291">
 *          RFC 4291
 *      </a>
 *
 * @param[out] ipv6_addr    Is set to the loopback address.
 */
void ipv6_addr_set_loopback_addr(ipv6_addr_t *ipv6_addr);

/**
 * @brief   Set *ipv6_addr* to a link-local all routers multicast
 *          address (ff02::/16 prefix).
 *
 * @see <a href="http://tools.ietf.org/html/rfc4291">
 *          RFC 4291
 *      </a>
 *
 * @param[out] ipv6_addr    Is set to a link-local all routers multicast
 *                          address.
 */
void ipv6_addr_set_all_routers_addr(ipv6_addr_t *ipv6_addr);

/**
 * @brief   Set *ipv6_addr* to a link-local all nodes multicast address
 *          (ff02::/16 prefix).
 *
 * @see <a href="http://tools.ietf.org/html/rfc4291">
 *          RFC 4291
 *      </a>
 *
 * @param[out] ipv6_addr    Is set to a link-local all nodes multicast
 *                          address.
 */
void ipv6_addr_set_all_nodes_addr(ipv6_addr_t *ipv6_addr);

/**
 * @brief   Set *ipv6_addr_out* to the solicited-node multicast address
 *          computed from *ipv6_addr_in*.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4291">
 *          RFC 4291
 *      </a>
 *
 * @param[out]  ipv6_addr_out   Is set to solicited-node address of
 *                              this node.
 * @param[in]   ipv6_addr_in    The IPv6 address the solicited-node
 *                              address.
 */
void ipv6_addr_set_solicited_node_addr(ipv6_addr_t *ipv6_addr_out,
                                       const ipv6_addr_t *ipv6_addr_in);

/**
 * @brief   Converts IPv6 address into string (unabbrivated notation).
 *          Note that addr_str must allocate at least
 *          IPV6_MAX_ADDR_STR_LEN byte (40 byte).
 *
 * @param[out]  addr_str    The IPv6 address as string. Must allocate
 *                          at least IPV6_MAX_ADDR_STR_LEN byte (40
 *                          byte).
 * @param[in]   ipv6_addr   IPv6 address to be converted.
 *
 * @return  Pointer to addr_str.
 */
char *ipv6_addr_to_str(char *addr_str, const ipv6_addr_t *ipv6_addr);

/**
 * @brief   Checks if two IPv6 addresses are equal.
 *
 * @param[in] a     An IPv6 address.
 * @param[in] b     Another IPv6 address.
 *
 * @return  1 if *a* and *b* are equal, 0 otherwise.
 */
int ipv6_addr_is_equal(const ipv6_addr_t *a, const ipv6_addr_t *b);

/**
 * @brief   Checks if *ipv6_addr* is unspecified (all zero).
 *
 * @see <a href="http://tools.ietf.org/html/rfc4291">
 *          RFC 4291
 *      </a>
 *
 * @param[in] ipv6_addr An IPv6 address.
 *
 * @return  1 if *ipv6_addr* is unspecified address, 0 otherwise.
 */
int ipv6_addr_is_unspecified(const ipv6_addr_t *ipv6_addr);

/**
 * @brief   Check if *ipv6_addr* is a link-local address.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4291">
 *          RFC 4291
 *      </a>
 *
 * @param[in] ipv6_addr     An IPv6 address.
 *
 * @return  1 if *ipv6_addr* is link-local address, 0 otherwise.
 */
int ipv6_addr_is_link_local(const ipv6_addr_t *ipv6_addr);

/**
 * @brief   Check if *ipv6_addr* is unique local unicast address.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4193">
 *          RFC 4193
 *      </a>
 *
 * @param[in] ipv6_addr     An IPv6 address.
 *
 * @return  1 if *ipv6_addr* is unique local unicast address,
 *          0 otherwise.
 */
int ipv6_addr_is_unique_local_unicast(const ipv6_addr_t *addr);

/**
 * @brief   Check if *ipv6_addr* is a multicast address.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4291">
 *          RFC 4291
 *      </a>
 *
 * @param[in] ipv6_addr     An IPv6 address.
 *
 * @return  1 if *ipv6_addr* is multicast address, 0 otherwise.
 */
int ipv6_addr_is_multicast(const ipv6_addr_t *ipv6_addr);

/**
 * @brief   Check if *ipv6_addr* is solicited-node multicast address.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4291">
 *          RFC 4291
 *      </a>
 *
 * @param[in] ipv6_addr     An IPv6 address.
 *
 * @return  1 if *ipv6_addr* is solicited-node multicast address,
 *          0 otherwise.
 */
int ipv6_addr_is_solicited_node(const ipv6_addr_t *ipv6_addr);

/*
 * TODO to wrap sixlowpan initialisations
 * int ipv6_iface_init(transceiver_type_t trans, ..);
 */

/**
 * @brief   Add an IPv6 address to this nodes interface.
 *
 * @see <a href="http://tools.ietf.org/html/rfc4862">
 *          RFC 4862
 *      </a>
 *
 * @param[in] addr          Address to be added to the interface.
 * @param[in] type          Type of this address.
 * @param[in] state         Initial state of the address.
 * @param[in] val_ltime     Valid lifetime of this address in seconds.
 * @param[in] pref_ltime    Preferred lifetime of this address in
 *                          seconds.
 */
void ipv6_iface_add_addr(const ipv6_addr_t *addr, ipv6_addr_type_t type,
                         ndp_addr_state_t state, uint32_t val_ltime,
                         uint32_t pref_ltime);

/**
 * @brief   Tries to determine best suitable source address attached to
 *          the interface of this node based on the given destination
 *          address. The use-case for this function is to find a
 *          suitable address for the source address field of an IPv6
 *          address upon sending. *src* may be empty (all zero) if there
 *          is no suitable address attached to the interface.
 *
 * @param[out]  src     The best source address for this node (may be
 *                      all zero if ther is none).
 * @param[in]   dest    The destination address for a packet we search
 *                      the source address for.
 */
void ipv6_iface_get_best_src_addr(ipv6_addr_t *src,
                                  const ipv6_addr_t *dest);

/**
 * @brief   Print all addresses attached to the interface to stdout.
 */
void ipv6_iface_print_addrs(void);

/**
 * @brief   Registers a function that decides how to route incomming
 *          IP packets with a destination that is not this interface.
 *          The default behaviour is to try forwarding such packets to
 *          the neighborhood.
 *          Register a function to change the default behaviour.
 *          Such function shall return the next hop to reach the destination
 *          of the IP packet, or NULL if no such next hop is known.
 *          In this case, the packet will be discarded.
 *
 * @param   next_hop    function that returns the next hop to reach dest
 */
void ipv6_iface_set_routing_provider(ipv6_addr_t *(*next_hop)(ipv6_addr_t* dest));

/**
 * @brief Calculates the IPv6 upper-layer checksum.
 *
 * @see <a href="http://tools.ietf.org/html/rfc2460#section-8.1">
 *          RFC 2460, section 8.1
 *      </a>
 * @param[in] ipv6_header   Pointer to the IPv6 header of the packet.
 * @param[in] buf           Pointer to the upper-layer payload of the IP datagram.
 * @param[in] len           The length of the upper-layer header and data.
 * @param[in] proto         Upper-layer protocol number according to RFC1700.
 *
 * @return The IPv6 upper-layer checksum.
 */
uint16_t ipv6_csum(ipv6_hdr_t *ipv6_header, uint8_t *buf, uint16_t len, uint8_t proto);
/**
 * @}
 */
#endif /* SIXLOWPAN_IP_H */
