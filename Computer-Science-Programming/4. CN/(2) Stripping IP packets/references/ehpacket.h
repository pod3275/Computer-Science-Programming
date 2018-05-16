#pragma once
#pragma warning(disable:4996)
#include <WinSock2.h>
#pragma comment(lib,"ws2_32")
#pragma pack(1)
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned int uint;

//                          pcap fileheader
//  __________________________________________________________________________
//  |             4               |    2       |      2     |             4                 | 
//  __________________________________________________________________________
//  |  magic(0xa1b2c3d4)  | maj.ver   |  min.ver  | gmt to localcorrection | 
//  _________________________________________________________________________
//  |             4               |              4            |             4               | 
//   _________________________________________________________________________
//  |      캡쳐한 시각         |   snap의 최대 길이  |     datalink type        | 
//  _________________________________________________________________________

typedef struct _pcap_file_header
{
#define MAGIC   0xa1b2c3d4 //pcap magic
    int magic;
    unsigned short version_major;
    unsigned short version_minor;
    int thiszone; /* gmt to localcorrection */
    unsigned sigfigs; /* accuracy oftimestamps */
    unsigned snaplen;            /* maxlength savedportion of each pkt */
    unsigned linktype;            /* datalink type (LINKTYPE_*) */
}pcap_file_header;

typedef struct _timeval
{
    long    tv_sec;         /* seconds*/
    long    tv_usec;        /*andmicroseconds */
}timeval;

//                                         pcapheader
//  _______________________________________________________________________________
//  |            8                                 |          4            |        4             |
//   ______________________________________________________________________________
//  | seconds(4)       | micro seconds(4) |    캡쳐한 길이    |       패킷 길이    |
//  _______________________________________________________________________________ 

typedef struct _pcap_header
{
    timeval ts;    /*time stamp */
    unsigned caplen; /* length of portionpresent */
    unsigned len;     /*length thispacket (off wire) */
}pcap_header;


//                 ethernet protocol stack
//   ____________________________________________________________________________
//  |                   6                  |                 6                 |       2       |
//  ____________________________________________________________________________
//  |         dest mac address       |       src mac address        |     type     |
//  ____________________________________________________________________________ 

#define MAC_ADDR_LEN    6
typedef struct _ethernet
{
    unsigned char dest_mac[MAC_ADDR_LEN];
    unsigned char src_mac[MAC_ADDR_LEN];
    unsigned short type;
}ethernet;

//                             IPv4 protocol stack
//   _____________________________________________________________________________________
//  |      4      |      4       |          8            |                       16                       |
//   _____________________________________________________________________________________
//  |   version |  HLEN      |    service type    |                total length                  |
//   _____________________________________________________________________________________
//  |                           16                       |     3   |                13                   |
//   _____________________________________________________________________________________
//  |                 identification                   |  Flags |          Fragment offset        |
//   _____________________________________________________________________________________
//  |             8              |           8           |                       16                       |
//   _____________________________________________________________________________________
//  |    Time To Live        |      Protocol       |             Header Checksum            |
//   ____________________________________________________________________________________
//  |                                                    32                                               |
//   ____________________________________________________________________________________
//  |                                        Source IPv4 Address                                   |
//   ____________________________________________________________________________________
//  |                                                   32                                                |
//   ____________________________________________________________________________________
//  |                                    Destination IPv4 Address                                  |
//   ____________________________________________________________________________________
//  |                                       0~320(40 바이트)                                        |
//   ____________________________________________________________________________________
//  |                                       Options and Padding                                   |
//   ____________________________________________________________________________________


typedef struct _iphdr
{
    uchar  hlen : 4; //header length , 1 per 4bytes
    uchar  version : 4; //version , 4
    uchar  service;
    ushort tlen; //total length
    ushort    id; //identification    
    ushort    frag;
#define DONT_FRAG(frag)   (frag & 0x40)
#define MORE_FRAG(frag)   (frag & 0x20)
#define FRAG_OFFSET(frag) (ntohs(frag) & (~0x6000))
    uchar ttl;//time to live
    uchar protocol;
    ushort checksum;
    uint src_address;
    uint dst_address;
}iphdr;


//                                         ARP
//   ____________________________________________________________________________
//  |    Hardware Type (16)               |        Protocol Type (16)                  |
//   ____________________________________________________________________________
//  |    H/W length(8)  | Pro length(8)  |           OP code (16)                      |
//   ____________________________________________________________________________
//  |         Sender H/W Address (가변 , Ethernet 48bits, 6Bytes)                   |
//   ____________________________________________________________________________
//  |          Sender Protocol Address (가변 , IP 32bits, 4Bytes)                     |
//   ____________________________________________________________________________
//  |          Target H/W Address (가변 , Ethernet 48bits, 6Bytes)                   |
//   ____________________________________________________________________________
//  |            Target Protocol Address (가변 , IP 32bits, 4Bytes)                    |
//   ____________________________________________________________________________

typedef struct _arphdr
{
    ushort hwtype; //hardware type
    ushort prototype;//protocol type
    uchar hlen;//h/w length
    uchar plen;//protocol length
    ushort opcode; //operation code
    uchar sender_mac[MAC_ADDR_LEN];
    uint sender_address;
    uchar target_mac[MAC_ADDR_LEN];
    uint target_address;
}arphdr;
