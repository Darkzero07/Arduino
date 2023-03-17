/*
 *   $Id: local_config.h,v 1.5 2019/04/04 23:06:53 gaijin Exp $
 *
 * Change settings below to customize for -YOUR- local network.
 * 
 */
/*
 * W5500 "hardware" MAC address.
 */
uint8_t MAC[] = { 0x02, 0xF0, 0x0D, 0xBE, 0xEF, 0x01 };
/*
 * Define the static network settings for this gateway's ETHERNET connection
 * on your LAN.  These values must match YOUR SPECIFIC LAN.  The "eth_IP"
 * is the IP address for this gateway's ETHERNET port.
 */
IPAddress IP(192, 168, 31, 77);    // *** CHANGE THIS to something relevant for YOUR LAN. ***
IPAddress Subnet(255, 255, 255, 0);   // Subnet mask.
IPAddress DNS(192, 168, 31, 1);    // *** CHANGE THIS to match YOUR DNS server.           ***
IPAddress GW(192, 168, 31, 1);   // *** CHANGE THIS to match YOUR Gateway (router).     ***

//HTTP Method
int    HTTP_PORT   = 8000;
String HTTP_METHOD = "GET"; // or POST
char   HOST_NAME[] = "192.168.31.227";
String PATH_NAME   = "/sos";