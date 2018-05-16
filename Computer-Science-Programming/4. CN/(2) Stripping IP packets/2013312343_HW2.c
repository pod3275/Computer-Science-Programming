#include <stdio.h>
#include <time.h>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32")


#define MAGIC 0xa1b2c3d4
#define MAX_P 30
#define MAC_ADDR_LEN 6
#define DF(frag) (frag & 0x40)
#define MF(frag) (frag & 0x20)
#define FRAG_OFFSET(frag) (ntohs(frag) & (~0x6000))


typedef struct p_file_header_{
	int magic;
	unsigned short major_ver;
	unsigned short minor_ver;
	int thiszone;
	unsigned sigfigs;
	unsigned snaplen;
	unsigned linktype;
}p_file_header;

typedef struct timeval_ {
	long timesec;
	long timeusec;
}timeval;

typedef struct p_header_ {
	timeval time;
	unsigned int caplen;
	unsigned int actlen;
}p_header;

typedef struct ethernet_ {
	unsigned char dest_mac[MAC_ADDR_LEN];
	unsigned char src_mac[MAC_ADDR_LEN];
	unsigned short type;
}ethernet;

typedef struct ip_header_{
	unsigned char hlen : 4;
	unsigned char version : 4;
	unsigned char service;
	unsigned short tot_len;
	unsigned short id;
	unsigned short frag;
	unsigned char time_to_live;
	unsigned char protocol;
	unsigned short checksum;
	unsigned int src_addr;
	unsigned int dest_addr;
}ip_header;


int Parsing(FILE *fp);
void PacketParse(FILE *fp);
void ViewPHeader(p_header *ph);
void ViewMac(unsigned char *mac);
unsigned short ntohs_(unsigned short value);
void ViewEthernet(char *buffer);
void ViewIP(char *buffer);


p_header pheaders[MAX_P];
int pcount = 0;


int Parsing(FILE *fp)
{
	p_file_header pfh;
	fread(&pfh, sizeof(pfh), 1, fp);
	PacketParse(fp);
	return 0;
}

void PacketParse(FILE *fp) {
	char buffer[65536];
	p_header *ph = pheaders;
	while (feof(fp) == 0) {
		if (fread(ph, sizeof(p_header), 1, fp) != 1) {
			break;
		}
		if (pcount == MAX_P) break;
		ViewPHeader(ph);
		fread(buffer, 1, ph->caplen, fp);
		ViewEthernet(buffer);
		ph++;
		printf("\n");
	}
}

void ViewPHeader(p_header *ph) {
	pcount++;
	printf("\nFrame %d:  time: %08d:%06d , capture length: %u bytes , actual length: %u bytes\n", pcount, ph->time.timesec, ph->time.timeusec, ph->caplen, ph->actlen);
}

void ViewMac(unsigned char *mac) {
	int i;
	for (i = 0; i < MAC_ADDR_LEN-1; i++) {
		printf("%02x:", mac[i]);
	}
	printf("%02x", mac[i]);
}

unsigned short ntohs_(unsigned short value) {
	return(value << 8) | (value >> 8);
}

void ViewEthernet(char *buffer) {
	ethernet *ph = (ethernet*)buffer;
	printf("Src MAC address: "); ViewMac(ph->src_mac); printf(" -> ");
	printf("Dst MAC address: "); ViewMac(ph->dest_mac);
	if (ntohs_(ph->type) == 0x800)
		ViewIP(buffer + sizeof(ethernet));
}

void ViewIP(char *buffer) {
	IN_ADDR addr;
	ip_header *ip = (ip_header *)buffer;
	addr.s_addr = ip->src_addr;
	printf("\nSrc IP address: %s -> ",inet_ntoa(addr));
	addr.s_addr = ip->dest_addr;
	printf("Dst IP address: %s\n", inet_ntoa(addr));
	
	switch (ip->protocol) {
		case 1: printf("Protocol is ICMP. "); break;
		case 2: printf("Protocol is IGMP. "); break;
		case 6: printf("Protocol is TCP. "); break;
		case 17: printf("Protocol is UDP. "); break;
		case 89: printf("Protocol is OSPF. "); break;
		default: printf("No support protocol. "); break;
	}

	printf("IP header length: %d bytes.\n", ip->hlen * 4);

	printf("id in decimal: %d, ", ntohs_(ip->id));

	printf("Frag-offset: %d, ", FRAG_OFFSET(ip->frag));

	if (DF(ip->frag)) printf("Flag: Don't Fragment.\n");
	else {
		if (MF(ip->frag) == 0) printf("Flag: Last Fragment.\n");
	}
}


int main() {
	char fname[300];
	FILE *fp = 0;
	printf("파일 명을 입력하시오 : ");
	gets_s(fname, sizeof(fname));
	fopen_s(&fp, fname, "rb");
	Parsing(fp);
	fclose(fp);
	return 0;
}