#ifndef REVLIBC_LINUX_LIKE_H_
#define REVLIBC_LINUX_LIKE_H_

typedef uint16_t sa_family_t;
typedef unsigned speed_t;
typedef unsigned tcflag_t;
typedef int clockid_t;
typedef void *timer_t;
typedef int key_t;
typedef unsigned id_t;

struct in_addr {
  in_addr_t s_addr;
}

struct ip_mreq {
  in_addr imr_multiaddr;
  in_addr imr_interface;
}

struct ip_mreqn {
  in_addr imr_multiaddr;
  in_addr imr_address;
  int imr_ifindex;
}

struct ip_mreq_source {
  in_addr imr_multiaddr;
  in_addr imr_interface;
  in_addr imr_sourceaddr;
}

struct sockaddr {
  sa_family_t sa_family;
  char sa_data[14];
}

struct sockaddr_in {
  sa_family_t sin_family;
  in_port_t sin_port;
  in_addr sin_addr;
  uint8_t sin_zero[8];
}

struct sockaddr_in6 {
  sa_family_t sin6_family;
  in_port_t sin6_port;
  uint32_t sin6_flowinfo;
  in6_addr sin6_addr;
  uint32_t sin6_scope_id;
}

// The order of the `ai_addr` field in this struct is crucial
// for converting between the Rust and C types.
struct addrinfo {
  int ai_flags;
  int ai_family;
  int ai_socktype;
  int ai_protocol;
  socklen_t ai_addrlen;
#if defined(linux) || defined(__EMSCRIPTEN__)
  sockaddr *ai_addr;
#endif
  char *ai_canonname;
#if defined(__ANDROID__)
  sockaddr *ai_addr;
#endif
  addrinfo *ai_next;
}

struct sockaddr_ll {
  unsigned short sll_family;
  unsigned short sll_protocol;
  int sll_ifindex;
  unsigned short sll_hatype;
  unsigned char sll_pkttype;
  unsigned char sll_halen;
  unsigned char sll_addr[8];
}

struct fd_set {
#if sizeof(void *) == 8
  unsigned long fds_bits[FD_SETSIZE / 64];
#elif sizeof(void *) == 4
  unsigned long fds_bits[FD_SETSIZE / 32];
#endif
}

struct tm {
  int tm_sec;
  int tm_min;
  int tm_hour;
  int tm_mday;
  int tm_mon;
  int tm_year;
  int tm_wday;
  int tm_yday;
  int tm_isdst;
  long tm_gmtoff;
  const char *tm_zone;
}

struct sched_param {
  int sched_priority;
// TODO: ohos?
// TODO: musl?
#if defined(musl) || defined(__EMSCRIPTEN__) || defined(ohos)
  int sched_ss_low_priority;
  timespec sched_ss_repl_period;
  timespec sched_ss_init_budget;
  int sched_ss_max_repl;
#endif
}

struct Dl_info {
  const char *dli_fname;
  void *dli_fbase;
  const char *dli_sname;
  void *dli_saddr;
}

struct lconv {
  char *decimal_point;
  char *thousands_sep;
  char *grouping;
  char *int_curr_symbol;
  char *currency_symbol;
  char *mon_decimal_point;
  char *mon_thousands_sep;
  char *mon_grouping;
  char *positive_sign;
  char *negative_sign;
  char int_frac_digits;
  char frac_digits;
  char p_cs_precedes;
  char p_sep_by_space;
  char n_cs_precedes;
  char n_sep_by_space;
  char p_sign_posn;
  char n_sign_posn;
  char int_p_cs_precedes;
  char int_p_sep_by_space;
  char int_n_cs_precedes;
  char int_n_sep_by_space;
  char int_p_sign_posn;
  char int_n_sign_posn;
}

struct in_pktinfo {
  int ipi_ifindex;
  in_addr ipi_spec_dst;
  in_addr ipi_addr;
}

struct ifaddrs {
  ifaddrs *ifa_next;
  char *ifa_name;
  unsigned ifa_flags;
  sockaddr *ifa_addr;
  sockaddr *ifa_netmask;
  // FIXME This should be a union
  sockaddr *ifa_ifu;
  void *ifa_data;
}

struct in6_rtmsg {
  in6_addr rtmsg_dst;
  in6_addr rtmsg_src;
  in6_addr rtmsg_gateway;
  uint32_t rtmsg_type;
  uint16_t rtmsg_dst_len;
  uint16_t rtmsg_src_len;
  uint32_t rtmsg_metric;
  unsigned long rtmsg_info;
  uint32_t rtmsg_flags;
  int rtmsg_ifindex;
}

struct arpreq {
  sockaddr arp_pa;
  sockaddr arp_ha;
  int arp_flags;
  sockaddr arp_netmask;
  char arp_dev[16];
}

struct arpreq_old {
  sockaddr arp_pa;
  sockaddr arp_ha;
  int arp_flags;
  sockaddr arp_netmask;
}

struct arphdr {
  uint16_t ar_hrd;
  uint16_t ar_pro;
  uint8_t ar_hln;
  uint8_t ar_pln;
  uint16_t ar_op;
}

struct mmsghdr {
  msghdr msg_hdr;
  unsigned msg_len;
}

// #[cfg_attr(
//     any(
//         all(
//             target_arch = "x86",
//             not(target_env = "musl"),
//             not(target_os = "android")),
//         target_arch = "x86_64"),
//     repr(packed))]
struct epoll_event {
  uint32_t events;
  uint64_t u64;
}

struct sockaddr_un {
  sa_family_t sun_family;
  char sun_path[108];
}

struct sockaddr_storage {
  sa_family_t ss_family;
#if sizeof(void *) == 4
  uint8_t __ss_pad2[128 - 2 - 4];
#elif sizeof(void *) == 8
  uint8_t __ss_pad2[128 - 2 - 8];
#endif
  size_t __ss_align;
}

struct utsname {
  char sysname[65];
  char nodename[65];
  char release[65];
  char version[65];
  char machine[65];
  char domainname[65];
}

struct sigevent {
  sigval sigev_value;
  int sigev_signo;
  int sigev_notify;
  // Actually a union.  We only expose sigev_notify_thread_id because it's
  // the most useful member
  int sigev_notify_thread_id;
#if sizeof(void *) == 8
  int __unused1[11];
#elif sizeof(void *) == 4
  int __unused1[12];
#endif
}

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define RAND_MAX 2147483647
#define EOF -1
#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2
#define _IOFBF 0
#define _IONBF 2
#define _IOLBF 1

#define F_DUPFD 0
#define F_GETFD 1
#define F_SETFD 2
#define F_GETFL 3
#define F_SETFL 4

// Linux-specific fcntls
#define F_SETLEASE 1024
#define F_GETLEASE 1025
#define F_NOTIFY 1026
#define F_CANCELLK 1029
#define F_DUPFD_CLOEXEC 1030
#define F_SETPIPE_SZ 1031
#define F_GETPIPE_SZ 1032
#define F_ADD_SEALS 1033
#define F_GET_SEALS 1034

#define F_SEAL_SEAL 0x0001
#define F_SEAL_SHRINK 0x0002
#define F_SEAL_GROW 0x0004
#define F_SEAL_WRITE 0x0008

#define SIGTRAP 5

#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_CREATE_DETACHED 1

#define CLOCK_REALTIME (clockid_t)0
#define CLOCK_MONOTONIC (clockid_t)1
#define CLOCK_PROCESS_CPUTIME_ID (clockid_t)2
#define CLOCK_THREAD_CPUTIME_ID (clockid_t)3
#define CLOCK_MONOTONIC_RAW (clockid_t)4
#define CLOCK_REALTIME_COARSE (clockid_t)5
#define CLOCK_MONOTONIC_COARSE (clockid_t)6
#define CLOCK_BOOTTIME (clockid_t)7
#define CLOCK_REALTIME_ALARM (clockid_t)8
#define CLOCK_BOOTTIME_ALARM (clockid_t)9
#define CLOCK_TAI (clockid_t)11
#define TIMER_ABSTIME 1

#define RUSAGE_SELF 0

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2

#define SOCK_CLOEXEC O_CLOEXEC

#define S_IFIFO (mode_t)4096
#define S_IFCHR (mode_t)8192
#define S_IFBLK (mode_t)24576
#define S_IFDIR (mode_t)16384
#define S_IFREG (mode_t)32768
#define S_IFLNK (mode_t)40960
#define S_IFSOCK (mode_t)49152
#define S_IFMT (mode_t)61440
#define S_IRWXU (mode_t)448
#define S_IXUSR (mode_t)64
#define S_IWUSR (mode_t)128
#define S_IRUSR (mode_t)256
#define S_IRWXG (mode_t)56
#define S_IXGRP (mode_t)8
#define S_IWGRP (mode_t)16
#define S_IRGRP (mode_t)32
#define S_IRWXO (mode_t)7
#define S_IXOTH (mode_t)1
#define S_IWOTH (mode_t)2
#define S_IROTH (mode_t)4
#define F_OK 0
#define R_OK 4
#define W_OK 2
#define X_OK 1
#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
#define SIGHUP 1
#define SIGINT 2
#define SIGQUIT 3
#define SIGILL 4
#define SIGABRT 6
#define SIGFPE 8
#define SIGKILL 9
#define SIGSEGV 11
#define SIGPIPE 13
#define SIGALRM 14
#define SIGTERM 15

#define PROT_NONE 0
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4

#define XATTR_CREATE 0x1
#define XATTR_REPLACE 0x2

#ifdef __ANDROID__
#define RLIM64_INFINITY (~0ULL)
#else
#define RLIM64_INFINITY ((rlim64_t)~0)
#endif

#if defined(ohos)
#define LC_CTYPE 0
#define LC_NUMERIC 1
#define LC_TIME 2
#define LC_COLLATE 3
#define LC_MONETARY 4
#define LC_MESSAGES 5
#define LC_PAPER 6
#define LC_NAME 7
#define LC_ADDRESS 8
#define LC_TELEPHONE 9
#define LC_MEASUREMENT 10
#define LC_IDENTIFICATION 11
#define LC_ALL 12
#elif !defined(uclibc)
#define LC_CTYPE 0
#define LC_NUMERIC 1
#define LC_TIME 2
#define LC_COLLATE 3
#define LC_MONETARY 4
#define LC_MESSAGES 5
#define LC_ALL 6
#endif

#define LC_CTYPE_MASK (1 << LC_CTYPE)
#define LC_NUMERIC_MASK (1 << LC_NUMERIC)
#define LC_TIME_MASK (1 << LC_TIME)
#define LC_COLLATE_MASK (1 << LC_COLLATE)
#define LC_MONETARY_MASK (1 << LC_MONETARY)
#define LC_MESSAGES_MASK (1 << LC_MESSAGES)
// LC_ALL_MASK defined per platform

#define MAP_FILE 0x0000
#define MAP_SHARED 0x0001
#define MAP_PRIVATE 0x0002
#define MAP_FIXED 0x0010
#define MAP_FAILED ((void *)~0)

// MS_ flags for msync(2)
#define MS_ASYNC 0x0001
#define MS_INVALIDATE 0x0002
#define MS_SYNC 0x0004

// MS_ flags for mount(2)
#define MS_RDONLY 0x01UL
#define MS_NOSUID 0x02UL
#define MS_NODEV 0x04UL
#define MS_NOEXEC 0x08UL
#define MS_SYNCHRONOUS 0x10UL
#define MS_REMOUNT 0x20UL
#define MS_MANDLOCK 0x40UL
#define MS_DIRSYNC 0x80UL
#define MS_NOATIME 0x0400UL
#define MS_NODIRATIME 0x0800UL
#define MS_BIND 0x1000UL
#define MS_MOVE 0x2000UL
#define MS_REC 0x4000UL
#define MS_SILENT 0x8000UL
#define MS_POSIXACL 0x010000UL
#define MS_UNBINDABLE 0x020000UL
#define MS_PRIVATE 0x040000UL
#define MS_SLAVE 0x080000UL
#define MS_SHARED 0x100000UL
#define MS_RELATIME 0x200000UL
#define MS_KERNMOUNT 0x400000UL
#define MS_I_VERSION 0x800000UL
#define MS_STRICTATIME 0x1000000UL
#define MS_LAZYTIME 0x2000000UL
#define MS_ACTIVE 0x40000000UL
#define MS_MGC_VAL 0xc0ed0000UL
#define MS_MGC_MSK 0xffff0000UL

#define SCM_RIGHTS 0x01
#define SCM_CREDENTIALS 0x02

#define PROT_GROWSDOWN 0x1000000
#define PROT_GROWSUP 0x2000000

#define MAP_TYPE 0x000f

#define MADV_NORMAL 0
#define MADV_RANDOM 1
#define MADV_SEQUENTIAL 2
#define MADV_WILLNEED 3
#define MADV_DONTNEED 4
#define MADV_FREE 8
#define MADV_REMOVE 9
#define MADV_DONTFORK 10
#define MADV_DOFORK 11
#define MADV_MERGEABLE 12
#define MADV_UNMERGEABLE 13
#define MADV_HUGEPAGE 14
#define MADV_NOHUGEPAGE 15
#define MADV_DONTDUMP 16
#define MADV_DODUMP 17
#define MADV_WIPEONFORK 18
#define MADV_KEEPONFORK 19
#define MADV_COLD 20
#define MADV_PAGEOUT 21
#define MADV_HWPOISON 100

#ifndef __EMSCRIPTEN__
#define MADV_POPULATE_READ 22
#define MADV_POPULATE_WRITE 23
#define MADV_DONTNEED_LOCKED 24
#endif

#define IFF_UP 0x1
#define IFF_BROADCAST 0x2
#define IFF_DEBUG 0x4
#define IFF_LOOPBACK 0x8
#define IFF_POINTOPOINT 0x10
#define IFF_NOTRAILERS 0x20
#define IFF_RUNNING 0x40
#define IFF_NOARP 0x80
#define IFF_PROMISC 0x100
#define IFF_ALLMULTI 0x200
#define IFF_MASTER 0x400
#define IFF_SLAVE 0x800
#define IFF_MULTICAST 0x1000
#define IFF_PORTSEL 0x2000
#define IFF_AUTOMEDIA 0x4000
#define IFF_DYNAMIC 0x8000

#define SOL_IP 0
#define SOL_TCP 6
#define SOL_UDP 17
#define SOL_IPV6 41
#define SOL_ICMPV6 58
#define SOL_RAW 255
#define SOL_DECNET 261
#define SOL_X25 262
#define SOL_PACKET 263
#define SOL_ATM 264
#define SOL_AAL 265
#define SOL_IRDA 266
#define SOL_NETBEUI 267
#define SOL_LLC 268
#define SOL_DCCP 269
#define SOL_NETLINK 270
#define SOL_TIPC 271
#define SOL_BLUETOOTH 274
#define SOL_ALG 279

#define AF_UNSPEC 0
#define AF_UNIX 1
#define AF_LOCAL 1
#define AF_INET 2
#define AF_AX25 3
#define AF_IPX 4
#define AF_APPLETALK 5
#define AF_NETROM 6
#define AF_BRIDGE 7
#define AF_ATMPVC 8
#define AF_X25 9
#define AF_INET6 10
#define AF_ROSE 11
#define AF_DECnet 12
#define AF_NETBEUI 13
#define AF_SECURITY 14
#define AF_KEY 15
#define AF_NETLINK 16
#define AF_ROUTE AF_NETLINK
#define AF_PACKET 17
#define AF_ASH 18
#define AF_ECONET 19
#define AF_ATMSVC 20
#define AF_RDS 21
#define AF_SNA 22
#define AF_IRDA 23
#define AF_PPPOX 24
#define AF_WANPIPE 25
#define AF_LLC 26
#define AF_CAN 29
#define AF_TIPC 30
#define AF_BLUETOOTH 31
#define AF_IUCV 32
#define AF_RXRPC 33
#define AF_ISDN 34
#define AF_PHONET 35
#define AF_IEEE802154 36
#define AF_CAIF 37
#define AF_ALG 38

#define PF_UNSPEC AF_UNSPEC
#define PF_UNIX AF_UNIX
#define PF_LOCAL AF_LOCAL
#define PF_INET AF_INET
#define PF_AX25 AF_AX25
#define PF_IPX AF_IPX
#define PF_APPLETALK AF_APPLETALK
#define PF_NETROM AF_NETROM
#define PF_BRIDGE AF_BRIDGE
#define PF_ATMPVC AF_ATMPVC
#define PF_X25 AF_X25
#define PF_INET6 AF_INET6
#define PF_ROSE AF_ROSE
#define PF_DECnet AF_DECnet
#define PF_NETBEUI AF_NETBEUI
#define PF_SECURITY AF_SECURITY
#define PF_KEY AF_KEY
#define PF_NETLINK AF_NETLINK
#define PF_ROUTE AF_ROUTE
#define PF_PACKET AF_PACKET
#define PF_ASH AF_ASH
#define PF_ECONET AF_ECONET
#define PF_ATMSVC AF_ATMSVC
#define PF_RDS AF_RDS
#define PF_SNA AF_SNA
#define PF_IRDA AF_IRDA
#define PF_PPPOX AF_PPPOX
#define PF_WANPIPE AF_WANPIPE
#define PF_LLC AF_LLC
#define PF_CAN AF_CAN
#define PF_TIPC AF_TIPC
#define PF_BLUETOOTH AF_BLUETOOTH
#define PF_IUCV AF_IUCV
#define PF_RXRPC AF_RXRPC
#define PF_ISDN AF_ISDN
#define PF_PHONET AF_PHONET
#define PF_IEEE802154 AF_IEEE802154
#define PF_CAIF AF_CAIF
#define PF_ALG AF_ALG

#define MSG_OOB 1
#define MSG_PEEK 2
#define MSG_DONTROUTE 4
#define MSG_CTRUNC 8
#define MSG_TRUNC 0x20
#define MSG_DONTWAIT 0x40
#define MSG_EOR 0x80
#define MSG_WAITALL 0x100
#define MSG_FIN 0x200
#define MSG_SYN 0x400
#define MSG_CONFIRM 0x800
#define MSG_RST 0x1000
#define MSG_ERRQUEUE 0x2000
#define MSG_NOSIGNAL 0x4000
#define MSG_MORE 0x8000
#define MSG_WAITFORONE 0x10000
#define MSG_FASTOPEN 0x20000000
#define MSG_CMSG_CLOEXEC 0x40000000

#define SCM_TIMESTAMP SO_TIMESTAMP

#define SOCK_RAW 3
#define SOCK_RDM 4
#define IP_TOS 1
#define IP_TTL 2
#define IP_HDRINCL 3
#define IP_OPTIONS 4
#define IP_ROUTER_ALERT 5
#define IP_RECVOPTS 6
#define IP_RETOPTS 7
#define IP_PKTINFO 8
#define IP_PKTOPTIONS 9
#define IP_MTU_DISCOVER 10
#define IP_RECVERR 11
#define IP_RECVTTL 12
#define IP_RECVTOS 13
#define IP_MTU 14
#define IP_FREEBIND 15
#define IP_IPSEC_POLICY 16
#define IP_XFRM_POLICY 17
#define IP_PASSSEC 18
#define IP_TRANSPARENT 19
#define IP_ORIGDSTADDR 20
#define IP_RECVORIGDSTADDR IP_ORIGDSTADDR
#define IP_MINTTL 21
#define IP_NODEFRAG 22
#define IP_CHECKSUM 23
#define IP_BIND_ADDRESS_NO_PORT 24
#define IP_MULTICAST_IF 32
#define IP_MULTICAST_TTL 33
#define IP_MULTICAST_LOOP 34
#define IP_ADD_MEMBERSHIP 35
#define IP_DROP_MEMBERSHIP 36
#define IP_UNBLOCK_SOURCE 37
#define IP_BLOCK_SOURCE 38
#define IP_ADD_SOURCE_MEMBERSHIP 39
#define IP_DROP_SOURCE_MEMBERSHIP 40
#define IP_MSFILTER 41
#define IP_MULTICAST_ALL 49
#define IP_UNICAST_IF 50

#define IP_DEFAULT_MULTICAST_TTL 1
#define IP_DEFAULT_MULTICAST_LOOP 1

#define IP_PMTUDISC_DONT 0
#define IP_PMTUDISC_WANT 1
#define IP_PMTUDISC_DO 2
#define IP_PMTUDISC_PROBE 3
#define IP_PMTUDISintERFACE 4
#define IP_PMTUDISC_OMIT 5

// IPPROTO_IP defined in src/unix/mod.rs
/// Hop-by-hop option header
#define IPPROTO_HOPOPTS 0
// IPPROTO_ICMP defined in src/unix/mod.rs
/// group mgmt protocol
#define IPPROTO_IGMP 2
/// for compatibility
#define IPPROTO_IPIP 4
// IPPROTO_TCP defined in src/unix/mod.rs
/// exterior gateway protocol
#define IPPROTO_EGP 8
/// pup
#define IPPROTO_PUP 12
// IPPROTO_UDP defined in src/unix/mod.rs
/// xns idp
#define IPPROTO_IDP 22
/// tp-4 w/ class negotiation
#define IPPROTO_TP 29
/// DCCP
#define IPPROTO_DCCP 33
// IPPROTO_IPV6 defined in src/unix/mod.rs
/// IP6 routing header
#define IPPROTO_ROUTING 43
/// IP6 fragmentation header
#define IPPROTO_FRAGMENT 44
/// resource reservation
#define IPPROTO_RSVP 46
/// General Routing Encap.
#define IPPROTO_GRE 47
/// IP6 Encap Sec. Payload
#define IPPROTO_ESP 50
/// IP6 Auth Header
#define IPPROTO_AH 51
// IPPROTO_ICMPV6 defined in src/unix/mod.rs
/// IP6 no next header
#define IPPROTO_NONE 59
/// IP6 destination option
#define IPPROTO_DSTOPTS 60
#define IPPROTO_MTP 92
/// encapsulation header
#define IPPROTO_ENCAP 98
/// Protocol indep. multicast
#define IPPROTO_PIM 103
/// IP Payload Comp. Protocol
#define IPPROTO_COMP 108
/// SCTP
#define IPPROTO_SCTP 132
#define IPPROTO_MH 135
#define IPPROTO_UDPLITE 136
/// raw IP packet
#define IPPROTO_RAW 255
#define IPPROTO_BEETPH 94
#define IPPROTO_MPLS 137
/// Multipath TCP
#define IPPROTO_MPTCP 262
/// Ethernet-within-IPv6 encapsulation.
#define IPPROTO_ETHERNET 143

#define MCAST_EXCLUDE 0
#define MCAST_INCLUDE 1
#define MCAST_JOIN_GROUP 42
#define MCAST_BLOCK_SOURCE 43
#define MCAST_UNBLOCK_SOURCE 44
#define MCAST_LEAVE_GROUP 45
#define MCAST_JOIN_SOURCE_GROUP 46
#define MCAST_LEAVE_SOURCE_GROUP 47
#define MCAST_MSFILTER 48

#define IPV6_ADDRFORM 1
#define IPV6_2292PKTINFO 2
#define IPV6_2292HOPOPTS 3
#define IPV6_2292DSTOPTS 4
#define IPV6_2292RTHDR 5
#define IPV6_2292PKTOPTIONS 6
#define IPV6_CHECKSUM 7
#define IPV6_2292HOPLIMIT 8
#define IPV6_NEXTHOP 9
#define IPV6_AUTHHDR 10
#define IPV6_UNICAST_HOPS 16
#define IPV6_MULTICAST_IF 17
#define IPV6_MULTICAST_HOPS 18
#define IPV6_MULTICAST_LOOP 19
#define IPV6_ADD_MEMBERSHIP 20
#define IPV6_DROP_MEMBERSHIP 21
#define IPV6_ROUTER_ALERT 22
#define IPV6_MTU_DISCOVER 23
#define IPV6_MTU 24
#define IPV6_RECVERR 25
#define IPV6_V6ONLY 26
#define IPV6_JOIN_ANYCAST 27
#define IPV6_LEAVE_ANYCAST 28
#define IPV6_IPSEC_POLICY 34
#define IPV6_XFRM_POLICY 35
#define IPV6_HDRINCL 36
#define IPV6_RECVPKTINFO 49
#define IPV6_PKTINFO 50
#define IPV6_RECVHOPLIMIT 51
#define IPV6_HOPLIMIT 52
#define IPV6_RECVHOPOPTS 53
#define IPV6_HOPOPTS 54
#define IPV6_RTHDRDSTOPTS 55
#define IPV6_RECVRTHDR 56
#define IPV6_RTHDR 57
#define IPV6_RECVDSTOPTS 58
#define IPV6_DSTOPTS 59
#define IPV6_RECVPATHMTU 60
#define IPV6_PATHMTU 61
#define IPV6_DONTFRAG 62
#define IPV6_RECVTCLASS 66
#define IPV6_TCLASS 67
#define IPV6_AUTOFLOWLABEL 70
#define IPV6_ADDR_PREFERENCES 72
#define IPV6_MINHOPCOUNT 73
#define IPV6_ORIGDSTADDR 74
#define IPV6_RECVORIGDSTADDR IPV6_ORIGDSTADDR
#define IPV6_TRANSPARENT 75
#define IPV6_UNICAST_IF 76
#define IPV6_PREFER_SRC_TMP 0x0001
#define IPV6_PREFER_SRC_PUBLIC 0x0002
#define IPV6_PREFER_SRC_PUBTMP_DEFAULT 0x0100
#define IPV6_PREFER_SRC_COA 0x0004
#define IPV6_PREFER_SRC_HOME 0x0400
#define IPV6_PREFER_SRC_CGA 0x0008
#define IPV6_PREFER_SRC_NONCGA 0x0800

#define IPV6_PMTUDISC_DONT 0
#define IPV6_PMTUDISC_WANT 1
#define IPV6_PMTUDISC_DO 2
#define IPV6_PMTUDISC_PROBE 3
#define IPV6_PMTUDISintERFACE 4
#define IPV6_PMTUDISC_OMIT 5

#define TCP_NODELAY 1
#define TCP_MAXSEG 2
#define TCP_CORK 3
#define TCP_KEEPIDLE 4
#define TCP_KEEPINTVL 5
#define TCP_KEEPCNT 6
#define TCP_SYNCNT 7
#define TCP_LINGER2 8
#define TCP_DEFER_ACCEPT 9
#define TCP_WINDOW_CLAMP 10
#define TCP_INFO 11
#define TCP_QUICKACK 12
#define TCP_CONGESTION 13
#define TCP_MD5SIG 14
// TODO: GNU?
#if defined(linux) && (defined(GNU) || defined(musl) || defined(ohos))
// WARN: deprecated
#define TCP_COOKIE_TRANSACTIONS 15
#endif
#define TCP_THIN_LINEAR_TIMEOUTS 16
#define TCP_THIN_DUPACK 17
#define TCP_USER_TIMEOUT 18
#define TCP_REPAIR 19
#define TCP_REPAIR_QUEUE 20
#define TCP_QUEUE_SEQ 21
#define TCP_REPAIR_OPTIONS 22
#define TCP_FASTOPEN 23
#define TCP_TIMESTAMP 24
#define TCP_NOTSENT_LOWAT 25
#define TCP_CC_INFO 26
#define TCP_SAVE_SYN 27
#define TCP_SAVED_SYN 28
#if !defined(__EMSCRIPTEN__)
// NOTE: emscripten doesn't support these options yet.
#define TCP_REPAIR_WINDOW 29
#define TCP_FASTOPEN_CONNECT 30
#define TCP_ULP 31
#define TCP_MD5SIG_EXT 32
#define TCP_FASTOPEN_KEY 33
#define TCP_FASTOPEN_NO_COOKIE 34
#define TCP_ZEROCOPY_RECEIVE 35
#define TCP_INQ 36
#define TCP_CM_INQ TCP_INQ
// NOTE: Some CI images doesn't have this option yet.
// #define TCP_TX_DELAY 37
#define TCP_MD5SIG_MAXKEYLEN (size_t)80
#endif

#define SO_DEBUG 1

#define SHUT_RD 0
#define SHUT_WR 1
#define SHUT_RDWR 2

#define LOCK_SH 1
#define LOCK_EX 2
#define LOCK_NB 4
#define LOCK_UN 8

#define SS_ONSTACK 1
#define SS_DISABLE 2

#define PATH_MAX 4096

#define UIO_MAXIOV 1024

#define FD_SETSIZE (size_t)1024

#define EPOLLIN 0x1
#define EPOLLPRI 0x2
#define EPOLLOUT 0x4
#define EPOLLERR 0x8
#define EPOLLHUP 0x10
#define EPOLLRDNORM 0x40
#define EPOLLRDBAND 0x80
#define EPOLLWRNORM 0x100
#define EPOLLWRBAND 0x200
#define EPOLLMSG 0x400
#define EPOLLRDHUP 0x2000
#define EPOLLEXCLUSIVE 0x10000000
#define EPOLLWAKEUP 0x20000000
#define EPOLLONESHOT 0x40000000
#define EPOLLET 0x80000000

#define EPOLL_CTL_ADD 1
#define EPOLL_CTL_MOD 3
#define EPOLL_CTL_DEL 2

#define MNT_FORCE 0x1
#define MNT_DETACH 0x2
#define MNT_EXPIRE 0x4
#define UMOUNT_NOFOLLOW 0x8

#define Q_GETFMT 0x800004
#define Q_GETINFO 0x800005
#define Q_SETINFO 0x800006
#define QIF_BLIMITS (uint32_t)1
#define QIF_SPACE (uint32_t)2
#define QIF_ILIMITS (uint32_t)4
#define QIF_INODES (uint32_t)8
#define QIF_BTIME (uint32_t)16
#define QIF_ITIME (uint32_t)32
#define QIF_LIMITS (uint32_t)5
#define QIF_USAGE (uint32_t)10
#define QIF_TIMES (uint32_t)48
#define QIF_ALL (uint32_t)63

#define Q_SYNC 0x800001
#define Q_QUOTAON 0x800002
#define Q_QUOTAOFF 0x800003
#define Q_GETQUOTA 0x800007
#define Q_SETQUOTA 0x800008

#define TCIOFF 2
#define TCION 3
#define TCOOFF 0
#define TCOON 1
#define TCIFLUSH 0
#define TCOFLUSH 1
#define TCIOFLUSH 2
#define NL0 (tcflag_t)0x00000000
#define NL1 (tcflag_t)0x00000100
#define TAB0 (tcflag_t)0x00000000
#define CR0 (tcflag_t)0x00000000
#define FF0 (tcflag_t)0x00000000
#define BS0 (tcflag_t)0x00000000
#define VT0 (tcflag_t)0x00000000
#define VERASE (size_t)2
#define VKILL (size_t)3
#define VINTR (size_t)0
#define VQUIT (size_t)1
#define VLNEXT (size_t)15
#define IGNBRK (tcflag_t)0x00000001
#define BRKINT (tcflag_t)0x00000002
#define IGNPAR (tcflag_t)0x00000004
#define PARMRK (tcflag_t)0x00000008
#define INPCK (tcflag_t)0x00000010
#define ISTRIP (tcflag_t)0x00000020
#define INLCR (tcflag_t)0x00000040
#define IGNCR (tcflag_t)0x00000080
#define ICRNL (tcflag_t)0x00000100
#define IXANY (tcflag_t)0x00000800
#define IMAXBEL (tcflag_t)0x00002000
#define OPOST (tcflag_t)0x1
#define CS5 (tcflag_t)0x00000000
#define CRTSCTS (tcflag_t)0x80000000
#define ECHO (tcflag_t)0x00000008
#define OCRNL (tcflag_t)0o000010
#define ONOCR (tcflag_t)0o000020
#define ONLRET (tcflag_t)0o000040
#define OFILL (tcflag_t)0o000100
#define OFDEL (tcflag_t)0o000200

#define CLONE_VM 0x100
#define CLONE_FS 0x200
#define CLONE_FILES 0x400
#define CLONE_SIGHAND 0x800
#define CLONE_PTRACE 0x2000
#define CLONE_VFORK 0x4000
#define CLONE_PARENT 0x8000
#define CLONE_THREAD 0x10000
#define CLONE_NEWNS 0x20000
#define CLONE_SYSVSEM 0x40000
#define CLONE_SETTLS 0x80000
#define CLONE_PARENT_SETTID 0x100000
#define CLONE_CHILD_CLEARTID 0x200000
#define CLONE_DETACHED 0x400000
#define CLONE_UNTRACED 0x800000
#define CLONE_CHILD_SETTID 0x01000000
#define CLONE_NEWCGROUP 0x02000000
#define CLONE_NEWUTS 0x04000000
#define CLONE_NEWIPC 0x08000000
#define CLONE_NEWUSER 0x10000000
#define CLONE_NEWPID 0x20000000
#define CLONE_NEWNET 0x40000000
#define CLONE_IO 0x80000000

#define WNOHANG 0x00000001
#define WUNTRACED 0x00000002
#define WSTOPPED WUNTRACED
#define WEXITED 0x00000004
#define WCONTINUED 0x00000008
#define WNOWAIT 0x01000000

// Options for personality(2).
#define ADDR_NO_RANDOMIZE 0x0040000
#define MMAP_PAGE_ZERO 0x0100000
#define ADDR_COMPAT_LAYOUT 0x0200000
#define READ_IMPLIES_EXEC 0x0400000
#define ADDR_LIMIT_32BIT 0x0800000
#define SHORT_INODE 0x1000000
#define WHOLE_SECONDS 0x2000000
#define STICKY_TIMEOUTS 0x4000000
#define ADDR_LIMIT_3GB 0x8000000

// Options set using PTRACE_SETOPTIONS.
#define PTRACE_O_TRACESYSGOOD 0x00000001
#define PTRACE_O_TRACEFORK 0x00000002
#define PTRACE_O_TRACEVFORK 0x00000004
#define PTRACE_O_TRACECLONE 0x00000008
#define PTRACE_O_TRACEEXEC 0x00000010
#define PTRACE_O_TRACEVFORKDONE 0x00000020
#define PTRACE_O_TRACEEXIT 0x00000040
#define PTRACE_O_TRACESECCOMP 0x00000080
#define PTRACE_O_SUSPEND_SECCOMP 0x00200000
#define PTRACE_O_EXITKILL 0x00100000
#define PTRACE_O_MASK 0x003000ff

// Wait extended result codes for the above trace options.
#define PTRACE_EVENT_FORK 1
#define PTRACE_EVENT_VFORK 2
#define PTRACE_EVENT_CLONE 3
#define PTRACE_EVENT_EXEC 4
#define PTRACE_EVENT_VFORK_DONE 5
#define PTRACE_EVENT_EXIT 6
#define PTRACE_EVENT_SECCOMP 7

#define __WNOTHREAD 0x20000000
#define __WALL 0x40000000
#define __WCLONE 0x80000000

#define SPLICE_F_MOVE 0x01U
#define SPLICE_F_NONBLOCK 0x02U
#define SPLICE_F_MORE 0x04U
#define SPLICE_F_GIFT 0x08U

#define RTLD_LOCAL 0
#define RTLD_LAZY 1

#define POSIX_FADV_NORMAL 0
#define POSIX_FADV_RANDOM 1
#define POSIX_FADV_SEQUENTIAL 2
#define POSIX_FADV_WILLNEED 3

#define AT_FDCWD -100
#define AT_SYMLINK_NOFOLLOW 0x100
#define AT_REMOVEDIR 0x200
#define AT_SYMLINK_FOLLOW 0x400
#define AT_NO_AUTOMOUNT 0x800
#define AT_EMPTY_PATH 0x1000
#define AT_RECURSIVE 0x8000

#define LOG_CRON (9 << 3)
#define LOG_AUTHPRIV (10 << 3)
#define LOG_FTP (11 << 3)
#define LOG_PERROR 0x20

#define PIPE_BUF (size_t)4096

#define SI_LOAD_SHIFT 16U

// si_code values for SIGBUS signal
#define BUS_ADRALN 1
#define BUS_ADRERR 2
#define BUS_OBJERR 3
// Linux-specific si_code values for SIGBUS signal
#define BUS_MCEERR_AR 4
#define BUS_MCEERR_AO 5

// si_code values for SIGCHLD signal
#define CLD_EXITED 1
#define CLD_KILLED 2
#define CLD_DUMPED 3
#define CLD_TRAPPED 4
#define CLD_STOPPED 5
#define CLD_CONTINUED 6

#define SIGEV_SIGNAL 0
#define SIGEV_NONE 1
#define SIGEV_THREAD 2

#define P_ALL (idtype_t)0
#define P_PID (idtype_t)1
#define P_PGID (idtype_t)2
#if !defined(__EMSCRIPTEN__)
#define P_PIDFD (idtype_t)3
#endif

#define UTIME_OMIT 1073741822L
#define UTIME_NOW 1073741823L

#define POLLIN (short)0x1
#define POLLPRI (short)0x2
#define POLLOUT (short)0x4
#define POLLERR (short)0x8
#define POLLHUP (short)0x10
#define POLLNVAL (short)0x20
#define POLLRDNORM (short)0x040
#define POLLRDBAND (short)0x080
// TODO: sparc
#if defined(__sparc__) || defined(__sparc64__)
#define POLLRDHUP (short)0x800
#else
#define POLLRDHUP (short)0x2000
#endif

#define IPTOS_LOWDELAY (uint8_t)0x10
#define IPTOS_THROUGHPUT (uint8_t)0x08
#define IPTOS_RELIABILITY (uint8_t)0x04
#define IPTOS_MINCOST (uint8_t)0x02

#define IPTOS_PREC_NETCONTROL (uint8_t)0xe0
#define IPTOS_PREintERNETCONTROL (uint8_t)0xc0
#define IPTOS_PREC_CRITIC_ECP (uint8_t)0xa0
#define IPTOS_PREC_FLASHOVERRIDE (uint8_t)0x80
#define IPTOS_PREC_FLASH (uint8_t)0x60
#define IPTOS_PREC_IMMEDIATE (uint8_t)0x40
#define IPTOS_PREC_PRIORITY (uint8_t)0x20
#define IPTOS_PREC_ROUTINE (uint8_t)0x00

#define IPTOS_ECN_MASK (uint8_t)0x03
#define IPTOS_ECN_ECT1 (uint8_t)0x01
#define IPTOS_ECN_ECT0 (uint8_t)0x02
#define IPTOS_ECN_CE (uint8_t)0x03

#define IPOPT_COPY (uint8_t)0x80
#define IPOPT_CLASS_MASK (uint8_t)0x60
#define IPOPT_NUMBER_MASK (uint8_t)0x1f

#define IPOPT_CONTROL (uint8_t)0x00
#define IPOPT_RESERVED1 (uint8_t)0x20
#define IPOPT_MEASUREMENT (uint8_t)0x40
#define IPOPT_RESERVED2 (uint8_t)0x60
#define IPOPT_END (uint8_t)(0 | IPOPT_CONTROL)
#define IPOPT_NOOP (uint8_t)(1 | IPOPT_CONTROL)
#define IPOPT_SEC (uint8_t)(2 | IPOPT_CONTROL | IPOPT_COPY)
#define IPOPT_LSRR (uint8_t)(3 | IPOPT_CONTROL | IPOPT_COPY)
#define IPOPT_TIMESTAMP (uint8_t)(4 | IPOPT_MEASUREMENT)
#define IPOPT_RR (uint8_t)(7 | IPOPT_CONTROL)
#define IPOPT_SID (uint8_t)(8 | IPOPT_CONTROL | IPOPT_COPY)
#define IPOPT_SSRR (uint8_t)(9 | IPOPT_CONTROL | IPOPT_COPY)
#define IPOPT_RA (uint8_t)(20 | IPOPT_CONTROL | IPOPT_COPY)
#define IPVERSION (uint8_t)4
#define MAXTTL (uint8_t)255
#define IPDEFTTL (uint8_t)64
#define IPOPT_OPTVAL (uint8_t)0
#define IPOPT_OLEN (uint8_t)1
#define IPOPT_OFFSET (uint8_t)2
#define IPOPT_MINOFF (uint8_t)4
#define MAX_IPOPTLEN (uint8_t)40
#define IPOPT_NOP (uint8_t) IPOPT_NOOP
#define IPOPT_EOL (uint8_t) IPOPT_END
#define IPOPT_TS (uint8_t) IPOPT_TIMESTAMP
#define IPOPT_TS_TSONLY (uint8_t)0
#define IPOPT_TS_TSANDADDR (uint8_t)1
#define IPOPT_TS_PRESPEC (uint8_t)3

#define ARPOP_RREQUEST (uint16_t)3
#define ARPOP_RREPLY (uint16_t)4
#define ARPOP_InREQUEST (uint16_t)8
#define ARPOP_InREPLY (uint16_t)9
#define ARPOP_NAK (uint16_t)10

#define ATF_NETMASK 0x20
#define ATF_DONTPUB 0x40

#define ARPHRD_NETROM (uint16_t)0
#define ARPHRD_ETHER (uint16_t)1
#define ARPHRD_EETHER (uint16_t)2
#define ARPHRD_AX25 (uint16_t)3
#define ARPHRD_PRONET (uint16_t)4
#define ARPHRD_CHAOS (uint16_t)5
#define ARPHRD_IEEE802 (uint16_t)6
#define ARPHRD_ARCNET (uint16_t)7
#define ARPHRD_APPLETLK (uint16_t)8
#define ARPHRD_DLCI (uint16_t)15
#define ARPHRD_ATM (uint16_t)19
#define ARPHRD_METRICOM (uint16_t)23
#define ARPHRD_IEEE1394 (uint16_t)24
#define ARPHRD_EUI64 (uint16_t)27
#define ARPHRD_INFINIBAND (uint16_t)32

#define ARPHRD_SLIP (uint16_t)256
#define ARPHRD_CSLIP (uint16_t)257
#define ARPHRD_SLIP6 (uint16_t)258
#define ARPHRD_CSLIP6 (uint16_t)259
#define ARPHRD_RSRVD (uint16_t)260
#define ARPHRD_ADAPT (uint16_t)264
#define ARPHRD_ROSE (uint16_t)270
#define ARPHRD_X25 (uint16_t)271
#define ARPHRD_HWX25 (uint16_t)272
#define ARPHRD_CAN (uint16_t)280
#define ARPHRD_PPP (uint16_t)512
#define ARPHRD_CISCO (uint16_t)513
#define ARPHRD_HDLC (uint16_t) ARPHRD_CISCO
#define ARPHRD_LAPB (uint16_t)516
#define ARPHRD_DDCMP (uint16_t)517
#define ARPHRD_RAWHDLC (uint16_t)518

#define ARPHRD_TUNNEL (uint16_t)768
#define ARPHRD_TUNNEL6 (uint16_t)769
#define ARPHRD_FRAD (uint16_t)770
#define ARPHRD_SKIP (uint16_t)771
#define ARPHRD_LOOPBACK (uint16_t)772
#define ARPHRD_LOCALTLK (uint16_t)773
#define ARPHRD_FDDI (uint16_t)774
#define ARPHRD_BIF (uint16_t)775
#define ARPHRD_SIT (uint16_t)776
#define ARPHRD_IPDDP (uint16_t)777
#define ARPHRD_IPGRE (uint16_t)778
#define ARPHRD_PIMREG (uint16_t)779
#define ARPHRD_HIPPI (uint16_t)780
#define ARPHRD_ASH (uint16_t)781
#define ARPHRD_ECONET (uint16_t)782
#define ARPHRD_IRDA (uint16_t)783
#define ARPHRD_FCPP (uint16_t)784
#define ARPHRD_FCAL (uint16_t)785
#define ARPHRD_FCPL (uint16_t)786
#define ARPHRD_FCFABRIC (uint16_t)787
#define ARPHRD_IEEE802_TR (uint16_t)800
#define ARPHRD_IEEE80211 (uint16_t)801
#define ARPHRD_IEEE80211_PRISM (uint16_t)802
#define ARPHRD_IEEE80211_RADIOTAP (uint16_t)803
#define ARPHRD_IEEE802154 (uint16_t)804

#define ARPHRD_VOID (uint16_t)0xFFFF
#define ARPHRD_NONE (uint16_t)0xFFFE

#if defined(__EMSCRIPTEN__)
// Emscripten does not define any `*_SUPER_MAGIC` constants.
#elif !defined(__s390x__)

#define ADFS_SUPER_MAGIC 0x0000adf5L
#define AFFS_SUPER_MAGIC 0x0000adffL
#define AFS_SUPER_MAGIC 0x5346414fL
#define AUTOFS_SUPER_MAGIC 0x0187L
#define BPF_FS_MAGIC 0xcafe4a11L
#define BTRFS_SUPER_MAGIC 0x9123683eL
#define CGROUP2_SUPER_MAGIC 0x63677270L
#define CGROUP_SUPER_MAGIC 0x27e0ebL
#define CODA_SUPER_MAGIC 0x73757245L
#define CRAMFS_MAGIC 0x28cd3d45L
#define DEBUGFS_MAGIC 0x64626720L
#define DEVPTS_SUPER_MAGIC 0x1cd1L
#define ECRYPTFS_SUPER_MAGIC 0xf15fL
#define EFS_SUPER_MAGIC 0x00414a53L
#define EXT2_SUPER_MAGIC 0x0000ef53L
#define EXT3_SUPER_MAGIC 0x0000ef53L
#define EXT4_SUPER_MAGIC 0x0000ef53L
#define F2FS_SUPER_MAGIC 0xf2f52010L
#define FUSE_SUPER_MAGIC 0x65735546L
#define FUTEXFS_SUPER_MAGIC 0xbad1deaL
#define HOSTFS_SUPER_MAGIC 0x00c0ffeeL
#define HPFS_SUPER_MAGIC 0xf995e849L
#define HUGETLBFS_MAGIC 0x958458f6L
#define ISOFS_SUPER_MAGIC 0x00009660L
#define JFFS2_SUPER_MAGIC 0x000072b6L
#define MINIX2_SUPER_MAGIC2 0x00002478L
#define MINIX2_SUPER_MAGIC 0x00002468L
#define MINIX3_SUPER_MAGIC 0x4d5aL
#define MINIX_SUPER_MAGIC2 0x0000138fL
#define MINIX_SUPER_MAGIC 0x0000137fL
#define MSDOS_SUPER_MAGIC 0x00004d44L
#define NCP_SUPER_MAGIC 0x0000564cL
#define NFS_SUPER_MAGIC 0x00006969L
#define NILFS_SUPER_MAGIC 0x3434L
#define OCFS2_SUPER_MAGIC 0x7461636fL
#define OPENPROM_SUPER_MAGIC 0x00009fa1L
#define OVERLAYFS_SUPER_MAGIC 0x794c7630L
#define PROC_SUPER_MAGIC 0x00009fa0L
#define QNX4_SUPER_MAGIC 0x0000002fL
#define QNX6_SUPER_MAGIC 0x68191122L
#define RDTGROUP_SUPER_MAGIC 0x7655821L
#define REISERFS_SUPER_MAGIC 0x52654973L
#define SECURITYFS_MAGIC 0x73636673L
#define SELINUX_MAGIC 0xf97cff8cL
#define SMACK_MAGIC 0x43415d53L
#define SMB_SUPER_MAGIC 0x0000517bL
#define SYSFS_MAGIC 0x62656572L
#define TMPFS_MAGIC 0x01021994L
#define TRACEFS_MAGIC 0x74726163L
#define UDF_SUPER_MAGIC 0x15013346L
#define USBDEVICE_SUPER_MAGIC 0x00009fa2L
#define XENFS_SUPER_MAGIC 0xabba1974L
#define NSFS_MAGIC 0x6e736673L
#elif defined(__s390x__)
#define ADFS_SUPER_MAGIC 0x0000adf5U
#define AFFS_SUPER_MAGIC 0x0000adffU
#define AFS_SUPER_MAGIC 0x5346414fU
#define AUTOFS_SUPER_MAGIC 0x0187U
#define BPF_FS_MAGIC 0xcafe4a11U
#define BTRFS_SUPER_MAGIC 0x9123683eU
#define CGROUP2_SUPER_MAGIC 0x63677270U
#define CGROUP_SUPER_MAGIC 0x27e0ebU
#define CODA_SUPER_MAGIC 0x73757245U
#define CRAMFS_MAGIC 0x28cd3d45U
#define DEBUGFS_MAGIC 0x64626720U
#define DEVPTS_SUPER_MAGIC 0x1cd1U
#define ECRYPTFS_SUPER_MAGIC 0xf15fU
#define EFS_SUPER_MAGIC 0x00414a53U
#define EXT2_SUPER_MAGIC 0x0000ef53U
#define EXT3_SUPER_MAGIC 0x0000ef53U
#define EXT4_SUPER_MAGIC 0x0000ef53U
#define F2FS_SUPER_MAGIC 0xf2f52010U
#define FUSE_SUPER_MAGIC 0x65735546U
#define FUTEXFS_SUPER_MAGIC 0xbad1deaU
#define HOSTFS_SUPER_MAGIC 0x00c0ffeeU
#define HPFS_SUPER_MAGIC 0xf995e849U
#define HUGETLBFS_MAGIC 0x958458f6U
#define ISOFS_SUPER_MAGIC 0x00009660U
#define JFFS2_SUPER_MAGIC 0x000072b6U
#define MINIX2_SUPER_MAGIC2 0x00002478U
#define MINIX2_SUPER_MAGIC 0x00002468U
#define MINIX3_SUPER_MAGIC 0x4d5aU
#define MINIX_SUPER_MAGIC2 0x0000138fU
#define MINIX_SUPER_MAGIC 0x0000137fU
#define MSDOS_SUPER_MAGIC 0x00004d44U
#define NCP_SUPER_MAGIC 0x0000564cU
#define NFS_SUPER_MAGIC 0x00006969U
#define NILFS_SUPER_MAGIC 0x3434U
#define OCFS2_SUPER_MAGIC 0x7461636fU
#define OPENPROM_SUPER_MAGIC 0x00009fa1U
#define OVERLAYFS_SUPER_MAGIC 0x794c7630U
#define PROC_SUPER_MAGIC 0x00009fa0U
#define QNX4_SUPER_MAGIC 0x0000002fU
#define QNX6_SUPER_MAGIC 0x68191122U
#define RDTGROUP_SUPER_MAGIC 0x7655821U
#define REISERFS_SUPER_MAGIC 0x52654973U
#define SECURITYFS_MAGIC 0x73636673U
#define SELINUX_MAGIC 0xf97cff8cU
#define SMACK_MAGIC 0x43415d53U
#define SMB_SUPER_MAGIC 0x0000517bU
#define SYSFS_MAGIC 0x62656572U
#define TMPFS_MAGIC 0x01021994U
#define TRACEFS_MAGIC 0x74726163U
#define UDF_SUPER_MAGIC 0x15013346U
#define USBDEVICE_SUPER_MAGIC 0x00009fa2U
#define XENFS_SUPER_MAGIC 0xabba1974U
#define NSFS_MAGIC 0x6e736673U
#endif

// {const} fn CMSG_ALIGN(len: usize) -> usize {
//     len + ::mem::size_of::<usize>() - 1 & !(::mem::size_of::<usize>() - 1)
// }

// pub fn CMSG_FIRSTHDR(mhdr: *const msghdr) -> *mut cmsghdr {
//     if (*mhdr).msg_controllen as usize >= ::mem::size_of::<cmsghdr>() {
//         (*mhdr).msg_control as *mut cmsghdr
//     } else {
//         0 as *mut cmsghdr
//     }
// }

// pub fn CMSG_DATA(cmsg: *const cmsghdr) -> *mut ::unsigned char {
//     cmsg.offset(1) as *mut ::unsigned char
// }

// pub {const} fn CMSG_SPACE(length: ::unsigned) -> ::unsigned {
//     (CMSG_ALIGN(length as usize) + CMSG_ALIGN(::mem::size_of::<cmsghdr>()))
//         as ::unsigned
// }

// pub {const} fn CMSG_LEN(length: ::unsigned) -> ::unsigned {
//     CMSG_ALIGN(::mem::size_of::<cmsghdr>()) as ::unsigned + length
// }

// pub fn FD_CLR(fd: ::int, set: *mut fd_set) -> () {
//     let fd = fd as usize;
//     let size = ::mem::size_of_val(&(*set).fds_bits[0]) * 8;
//     (*set).fds_bits[fd / size] &= !(1 << (fd % size));
//     return
// }

// pub fn FD_ISSET(fd: ::int, set: *const fd_set) -> bool {
//     let fd = fd as usize;
//     let size = ::mem::size_of_val(&(*set).fds_bits[0]) * 8;
//     return ((*set).fds_bits[fd / size] & (1 << (fd % size))) != 0
// }

// pub fn FD_SET(fd: ::int, set: *mut fd_set) -> () {
//     let fd = fd as usize;
//     let size = ::mem::size_of_val(&(*set).fds_bits[0]) * 8;
//     (*set).fds_bits[fd / size] |= 1 << (fd % size);
//     return
// }

// pub fn FD_ZERO(set: *mut fd_set) -> () {
//     for slot in (*set).fds_bits.iter_mut() {
//         *slot = 0;
//     }
// }

#define SIGRTMAX __libc_current_sigrtmax
#define SIGRTMIN __libc_current_sigrtmin

// pub {const} fn WIFSTOPPED(status: ::int) -> bool {
//     (status & 0xff) == 0x7f
// }

// pub {const} fn WSTOPSIG(status: ::int) -> ::int {
//     (status >> 8) & 0xff
// }

// pub {const} fn WIFCONTINUED(status: ::int) -> bool {
//     status == 0xffff
// }

// pub {const} fn WIFSIGNALED(status: ::int) -> bool {
//     ((status & 0x7f) + 1) as i8 >= 2
// }

// pub {const} fn WTERMSIG(status: ::int) -> ::int {
//     status & 0x7f
// }

// pub {const} fn WIFEXITED(status: ::int) -> bool {
//     (status & 0x7f) == 0
// }

// pub {const} fn WEXITSTATUS(status: ::int) -> ::int {
//     (status >> 8) & 0xff
// }

// pub {const} fn WCOREDUMP(status: ::int) -> bool {
//     (status & 0x80) != 0
// }

// pub {const} fn W_EXITCODE(ret: ::int, sig: ::int) -> ::int {
//     (ret << 8) | sig
// }

// pub {const} fn W_STOPCODE(sig: ::int) -> ::int {
//     (sig << 8) | 0x7f
// }

// pub {const} fn QCMD(cmd: ::int, type_: ::int) -> ::int {
//     (cmd << 8) | (type_ & 0x00ff)
// }

// pub {const} fn IPOPT_COPIED(o: u8) -> u8 {
//     o & IPOPT_COPY
// }

// pub {const} fn IPOPT_CLASS(o: u8) -> u8 {
//     o & IPOPT_CLASS_MASK
// }

// pub {const} fn IPOPT_NUMBER(o: u8) -> u8 {
//     o & IPOPT_NUMBER_MASK
// }

// pub {const} fn IPTOS_ECN(x: u8) -> u8 {
//     x & ::IPTOS_ECN_MASK
// }

// #[allow(ellipsis_inclusive_range_patterns)]
// pub {const} fn KERNEL_VERSION(a: u32, b: u32, c: u32) -> u32 {
//     ((a << 16) + (b << 8)) + match c {
//         0 ... 255 => c,
//         _ => 255,
//     }
// }

#ifdef __cplusplus
extern "C" {
#endif
  int __libc_current_sigrtmax(void);
  int __libc_current_sigrtmin(void);

  // pub fn sem_destroy(sem: *mut sem_t) -> ::int;
  // pub fn sem_init(sem: *mut sem_t, pshared: ::int, value: ::unsigned) ->
  // ::int; pub fn fdatasync(fd: ::int) -> ::int; pub fn mincore(addr: void*,
  // len: size_t, vec: *mut ::unsigned char) -> ::int;

  // pub fn clock_getres(clk_id: ::clockid_t, tp: *mut ::timespec) -> ::int;
  // pub fn clock_gettime(clk_id: ::clockid_t, tp: *mut ::timespec) -> ::int;
  // pub fn clock_settime(clk_id: ::clockid_t, tp: *const ::timespec) -> ::int;
  // pub fn clock_getcpuclockid(pid: ::pid_t, clk_id: *mut ::clockid_t) ->
  // ::int;

  // pub fn dirfd(dirp: *mut ::DIR) -> ::int;

  // pub fn pthread_getattr_np(native: ::pthread_t, attr: *mut ::pthread_attr_t)
  // -> ::int; pub fn pthread_attr_getstack(
  //     attr: *const ::pthread_attr_t,
  //     stackaddr: *mut void*,
  //     stacksize: *mut size_t,
  // ) -> ::int;
  // pub fn memalign(align: size_t, size: size_t) -> void*;
  // pub fn setgroups(ngroups: size_t, ptr: *const ::gid_t) -> ::int;
  // pub fn pipe2(fds: *mut ::int, flags: ::int) -> ::int;
  // pub fn statfs(path: const char*, buf: *mut statfs) -> ::int;
  // pub fn fstatfs(fd: ::int, buf: *mut statfs) -> ::int;
  // pub fn memrchr(cx: *const ::c_void, c: ::int, n: size_t) -> void*;
  // pub fn posix_fadvise(fd: ::int, offset: ::off_t, len: ::off_t, advise:
  // ::int)
  // -> ::int; pub fn futimens(fd: ::int, times: *const ::timespec) -> ::int;
  // pub fn utimensat(
  //     dirfd: ::int,
  //     path: const char*,
  //     times: *const ::timespec,
  //     flag: ::int,
  // ) -> ::int;
  // pub fn duplocale(base: ::locale_t) -> ::locale_t;
  // pub fn freelocale(loc: ::locale_t);
  // pub fn newlocale(mask: ::int, locale: const char*, base: ::locale_t) ->
  // ::locale_t; pub fn uselocale(loc: ::locale_t) -> ::locale_t; pub fn
  // mknodat(
  //     dirfd: ::int,
  //     pathname: const char*,
  //     mode: ::mode_t,
  //     dev: dev_t,
  // ) -> ::int;
  // pub fn pthread_condattr_getclock(
  //     attr: *const pthread_condattr_t,
  //     clock_id: *mut clockid_t,
  // ) -> ::int;
  // pub fn pthread_condattr_setclock(
  //     attr: *mut pthread_condattr_t,
  //     clock_id: ::clockid_t,
  // ) -> ::int;
  // pub fn pthread_condattr_setpshared(attr: *mut pthread_condattr_t, pshared:
  // ::int) -> ::int; pub fn pthread_mutexattr_setpshared(
  //     attr: *mut pthread_mutexattr_t,
  //     pshared: ::int,
  // ) -> ::int;
  // pub fn pthread_rwlockattr_getpshared(
  //     attr: *const pthread_rwlockattr_t,
  //     val: *mut ::int,
  // ) -> ::int;
  // pub fn pthread_rwlockattr_setpshared(attr: *mut pthread_rwlockattr_t, val:
  // ::int) -> ::int; pub fn ptsname_r(fd: ::int, buf: *mut char, buflen:
  // size_t)
  // -> ::int; pub fn clearenv() -> ::int; pub fn waitid(idtype: idtype_t, id:
  // id_t, infop: *mut ::siginfo_t, options: ::int)
  //     -> ::int;
  // pub fn getresuid(ruid: *mut ::uid_t, euid: *mut ::uid_t, suid: *mut
  // ::uid_t)
  // -> ::int; pub fn getresgid(rgid: *mut ::gid_t, egid: *mut ::gid_t, sgid:
  // *mut
  // ::gid_t) -> ::int; pub fn acct(filename: const char*) -> ::int; pub fn
  // brk(addr: void*) -> ::int; pub fn sbrk(increment: ::intptr_t) -> void*;
  // #[deprecated(
  //     since = "0.2.66",
  //     note = "causes memory corruption, see rust-lang/libc#1596"
  // )]
  pid_t vfork(void);
  int setresgid(gid_t rgid, gid_t egid, gid_t sgid);
// pub fn setresuid(ruid: ::uid_t, euid: ::uid_t, suid: ::uid_t) -> ::int;
// pub fn wait4(
//     pid: ::pid_t,
//     status: *mut ::int,
//     options: ::int,
//     rusage: *mut ::rusage,
// ) -> ::pid_t;
// pub fn login_tty(fd: ::int) -> ::int;
// pub fn execvpe( file: const char*, argv: *const const char*, envp: *const
// const char*,) -> ::int; pub fn fexecve( fd: ::int, argv: *const const char*,
// envp: *const const char*,) -> ::int; pub fn getifaddrs(ifap: *mut *mut
// ::ifaddrs) -> ::int; pub fn freeifaddrs(ifa: *mut ::ifaddrs); pub fn
// bind(socket: ::int, address: *const ::sockaddr, address_len: ::socklen_t) ->
// ::int;

// pub fn writev(fd: ::int, iov: *const ::iovec, iovcnt: ::int) -> ::ssize_t;
// pub fn readv(fd: ::int, iov: *const ::iovec, iovcnt: ::int) -> ::ssize_t;

// pub fn sendmsg(fd: ::int, msg: *const ::msghdr, flags: ::int) -> ::ssize_t;
// pub fn recvmsg(fd: ::int, msg: *mut ::msghdr, flags: ::int) -> ::ssize_t;
// pub fn uname(buf: *mut ::utsname) -> ::int;

// pub fn strchrnul(s: const char*, c: ::int) -> *mut char;
#ifdef __cplusplus
}
#endif

// LFS64 extensions
//
// * musl and Emscripten has 64-bit versions only so aliases the LFS64 symbols
// to the standard ones
// * ulibc doesn't have preadv64/pwritev64
#if !defined(musl) && !defined(__EMSCRIPTEN__)
#ifdef __cplusplus
extern "C" {
#endif
// pub fn fstatfs64(fd: ::int, buf: *mut statfs64) -> ::int;
// pub fn statvfs64(path: const char*, buf: *mut statvfs64) -> ::int;
// pub fn fstatvfs64(fd: ::int, buf: *mut statvfs64) -> ::int;
// pub fn statfs64(path: const char*, buf: *mut statfs64) -> ::int;
// pub fn creat64(path: *const char, mode: mode_t) -> ::int;
// pub fn fstat64(fildes: ::int, buf: *mut stat64) -> ::int;
// pub fn fstatat64( dirfd: ::int, pathname: *const char, buf: *mut stat64,
// flags: ::int,) -> ::int; pub fn ftruncate64(fd: ::int, length: off64_t) ->
// ::int; pub fn lseek64(fd: ::int, offset: off64_t, whence: ::int) -> off64_t;
// pub fn lstat64(path: *const char, buf: *mut stat64) -> ::int;
// pub fn mmap64( addr: void*, len: size_t, prot: ::int, flags: ::int, fd:
// ::int, offset: off64_t,) -> void*; pub fn open64(path: *const char, oflag:
// ::int, ...) -> ::int; pub fn openat64(fd: ::int, path: *const char, oflag:
// ::int, ...) -> ::int; pub fn posix_fadvise64( fd: ::int, offset: ::off64_t,
// len: ::off64_t, advise: ::int,) -> ::int; pub fn pread64( fd: ::int, buf:
// void*, count: size_t, offset: off64_t) -> ::ssize_t; pub fn pwrite64( fd:
// ::int, buf: *const ::c_void, count: size_t, offset: off64_t,) -> ::ssize_t;
// pub fn readdir64(dirp: *mut ::DIR) -> *mut ::dirent64;
// pub fn readdir64_r( dirp: *mut ::DIR, entry: *mut ::dirent64, result: *mut
// *mut ::dirent64,) -> ::int; pub fn stat64(path: *const char, buf: *mut
// stat64) -> ::int; pub fn truncate64(path: *const char, length: off64_t) ->
// ::int;
#ifdef __cplusplus
}
#endif
#endif

// if #[cfg(not(any(target_env = "uclibc", target_env = "musl", target_os =
// "emscripten")))] {
//     extern "C" {
//         pub fn preadv64( fd: ::int, iov: *const ::iovec, iovcnt: ::int,
//         offset: ::off64_t,) -> ::ssize_t; pub fn pwritev64( fd: ::int, iov:
//         *const ::iovec, iovcnt: ::int, offset: ::off64_t,) -> ::ssize_t;
//     }
// }

// if #[cfg(not(target_env = "uclibc"))] {
//     extern "C" {
//         // uclibc has separate non-const version of this function
//         pub fn forkpty( amaster: *mut ::int, name: *mut char, termp: *const
//         termios, winp: *const ::winsize,) -> ::pid_t;
//         // uclibc has separate non-const version of this function
//         pub fn openpty( amaster: *mut ::int, aslave: *mut ::int, name: *mut
//         char, termp: *const termios, winp: *const ::winsize,) -> ::int;
//     }
// }

// TODO: l4re?
#if defined(__EMSCRIPTEN__)
#include "emsc/ripten/impl.h"
#elif defined(linux) || defined(l4re)
#include "linux/impl.h"
#elif defined(__ANDROID__)
#include "android/impl.h"
#endif

#endif // REVLIBC_LINUX_LIKE_H_
