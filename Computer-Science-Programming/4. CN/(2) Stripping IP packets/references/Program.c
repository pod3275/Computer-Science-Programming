//패킷 분석기 예광탄 - ARP 프로토콜 스택 분석
//언제나 휴일, http://ehclub.co.kr 
//코드 변경없이 사용 및 배포할 수 있습니다.

#include "ehpacket.h"
#include <stdio.h>

#define MAX_PACKET  10
pcap_header headers[MAX_PACKET];//패킷 헤더들을 보관할배열
int pcnt; //패킷 개수
int Parsing(FILE *fp);
int main()
{
    char fname[256];
    FILE *fp = 0;
    printf("파일 명:");
    gets_s(fname, sizeof(fname));
    fopen_s(&fp, fname, "rb");//전달받은 파일을 읽기/바이너리모드로 열기
    Parsing(fp);//분석하기
    fclose(fp);//파일 닫기
    return 0;
}

void ParsingEthernet(FILE *fp);
int Parsing(FILE *fp)
{
    pcap_file_header pfh;
    fread(&pfh, sizeof(pfh), 1, fp);//pcap 파일 헤더 읽기    
    if (pfh.magic != MAGIC) //매직이 다르면
    {
        printf("this file format is not correct \n");
        return -1;
    }
    printf("version:%d.%d\n", pfh.version_major, pfh.version_minor);//pcap 헤더 정보 출력
    
    switch (pfh.linktype)//링크 타입에 따라
    {
    case 1:ParsingEthernet(fp); break; //Ethernet 방식으로 분석
    case 6:printf("Not support Token Ring\n");break;
    case 10:printf("Not support FDDI\n"); break;
    case 0:printf("Not support Loopback\n"); break;
    default:printf("Unknown\n"); break;
    }
    return 0;
}

void ViewPacketHeader(pcap_header *ph);
void ViewEthernet(char *buf);
void ParsingEthernet(FILE *fp)
{
    char buf[65536];
    pcap_header *ph = headers;//ph를 패킷 헤더의 시작 위치로 초기화
    int i = 0;
    while (feof(fp) == 0) //파일의 끝이 아니면 반복
    {
        if (fread(ph, sizeof(pcap_header), 1, fp) != 1)//패킷 헤더 읽기를 실패하면
        {
            break;//루프 탈출
        }
        if (pcnt == MAX_PACKET) //예광탄에서 분석할 수 있게 설정한 패킷 수에 도달
        {
            break;//루프 탈출
        }
        ViewPacketHeader(ph); //패킷 헤더 정보 출력
        fread(buf, 1, ph->caplen, fp); //패킷 읽기
        ViewEthernet(buf); //이더넷 정보 출력
        ph++;//ph를 다음 위치로 이동
    }
}


void ViewPacketHeader(pcap_header *ph)
{
    pcnt++;//패킷 개수를 1 증가
    printf("\nNo:%dtime:%08d:%06d caplen:%u length:%u \n",
        pcnt, ph->ts.tv_sec, ph->ts.tv_usec, ph->caplen, ph->len);
}

void ViewMac(unsigned char *mac);
void ViewIP(char *buf);
void ViewARP(char *buf);
void ViewEthernet(char *buf)
{
    ethernet *ph = (ethernet *)buf; //패킷 버퍼를 ethernet 구조체 포인터로 형 변환
    printf("===========ETHERNET Header==============\n");
    printf("dest mac:0x");
    ViewMac(ph->dest_mac);//MAC 주소 출력
    printf("  src mac:0x");
    ViewMac(ph->src_mac);//MAC 주소 출력
    printf("  type:%#x\n", ntohs(ph->type));    
    //Link 타입을 출력(2바이트 이상데이터는 network byte order -> host byte order 로 변환해야 함
    
    switch (ntohs(ph->type))
	{
    case 0x800:ViewIP(buf + sizeof(ethernet)); /*IP 정보 출력 */ break;
    case 0x806:ViewARP(buf + sizeof(ethernet)); /*ARP 정보 출력*/ break;
    default:printf("Not support Protocol\n"); break;
    }
}

void ViewMac(unsigned char *mac)
{
    int i;
    for (i = 0;i < MAC_ADDR_LEN; ++i)
    {
        printf("%02x ", mac[i]);
    }
}

ushort ip_checksum(ushort *base, int len);
void ViewIP(char *buf)
{
    IN_ADDR addr;
    iphdr *ip = (iphdr *)buf; //패킷 버퍼를 ethernet 구조체 포인터로 형변환
    printf("\n=========== IPv4 Header ==============\n");
    addr.s_addr = ip->src_address;
    
    printf("src:%s, ", inet_ntoa(addr));

    addr.s_addr = ip->dst_address;
    printf("dst:%s\n", inet_ntoa(addr));

    printf("header length:%d bytes, ", ip->hlen * 4);
    printf("version:%d, ", ip->version);
    printf("total length:%d bytes\n", ntohs(ip->tlen));
    printf("id:%d, ", ntohs(ip->id));
    if (DONT_FRAG(ip->frag))
    {
        printf("Don't Fragment\n");
    }
    else
    {
        if (MORE_FRAG(ip->frag) == 0)
        {
            printf("last fragment, ");
        }
        printf("offset:%d ", FRAG_OFFSET(ip->frag));
    }
    if (ip_checksum((ushort *)buf, sizeof(iphdr)) == 0)
    {
        printf("checksum is correct, ");
    }
    else
    {
        printf("checksum is not correct, ");
    }
    printf("TTL:%d\n", ip->ttl);
    switch (ip->protocol)
    {
    case 1: printf("ICMP\n"); break;
    case 2: printf("IGMP\n"); break;
    case 6: printf("TCP\n"); break;
    case 17: printf("UDP\n"); break;
    case 89: printf("OSPF\n"); break;
    default: printf("Not support\n"); break;
    }
}
void ViewARP(char *buf)
{
    arphdr *arphd = (arphdr *)buf;
    printf("\n===========  ARP Header ==============\n");
    printf("h/w type: %u", ntohs(arphd->hwtype));
    if (ntohs(arphd->hwtype) == 1)
    {
        printf("  Ethernet");
    }
    printf("\nprotocol type:%#x", ntohs(arphd->prototype));
    if (ntohs(arphd->prototype) == 0x800)
    {
        IN_ADDR addr;
        printf("  IP\n");
        printf("\n opcode: %d ", ntohs(arphd->opcode));
        
        printf("sender mac:0x");
        ViewMac(arphd->sender_mac);
        addr.s_addr = arphd->sender_address;
        printf("\nsender ip: %s\n", inet_ntoa(addr));
        
        printf("target mac:0x");
        ViewMac(arphd->target_mac);
        addr.s_addr = arphd->target_address;
        printf("\ntarget ip: %s\n", inet_ntoa(addr));
    }
}

ushort ip_checksum(ushort *base, int len)
{
    int nleft = len;
    int sum = 0;
    u_short *w = base;
    u_short answer = 0;
    while (nleft>1)
    {
        sum += *w;
        w++;
        nleft -= 2;
    }

    if (nleft == 1)
    {
        *(ushort *)(&answer) = *(uchar *)w;
        sum += answer;
    }
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    answer = ~sum;
    return (answer);
}