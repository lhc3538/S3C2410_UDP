
===========================================================================================
602 ��̫�� TFTP_Testʵ��
===========================================================================================
��ʵ��ʵ��ͨ����̫����PC�����ļ���ʵ�����С����������������з�ʽ��
8LED_Test IN RAM         ���������ص�SDRAM�е��ԡ�
8LED_Test IN Flash       ��������д��Nor Flash�С�
===========================================================================================
�ڳ�������֮ǰ, ����ֱ������ֱ�������������PC�����ý��洮��������PC�Ĵ��ں�ʵ�����COM2����
PC����IP�趨Ϊ192.168.2.*���������гɹ�֮���û��������ʼ��->�����С����� cmd�����س���
���ڴ����м������tftp -i 192.168.2.111 put filename ��س�������Ҫȷ����Ҫ������ļ�����
��ڵĵ�ǰĿ¼�¡�
�����ն��Ͻ���ʾ��


 boot success...

FS2410XP TFTP Test,please Enter 'ESC' to exit
Mini TFTP Server 1.0 (IP : 192.168.2.111 PORT: 69)
Type tftp -i 192.168.2.111 put filename at the host PC
detected DM9000...

dwEthernetIOBase =  20000000

dwEthernetDataPort =  20100000

id_val =  90000a46

INFO: Probe: DM9000 is detected.

INFO:CHIP Revision is:25
DM9000: MAC Address: 0:0:50:18:51:18

dm9000_hash_table

link stauts = 40

INFO: Init: DM9000_Init OK.

Starting the TFTP download...
Copy data!
Copy data end!

download 0x16 bytes to 0x30008000

0123456789!@#$^&*()_+
Press any key to continue...
FS2410XP TFTP Test,please Enter 'ESC' to exit
Mini TFTP Server 1.0 (IP : 192.168.2.111 PORT: 69)
Type tftp -i 192.168.2.111 put filename at the host PC
detected DM9000...

dwEthernetIOBase =  20000000

dwEthernetDataPort =  20100000

id_val =  90000a46

INFO: Probe: DM9000 is detected.

INFO:CHIP Revision is:25
DM9000: MAC Address: 0:0:50:18:51:18

dm9000_hash_table

link stauts = 40

INFO: Init: DM9000_Init OK.

Starting the TFTP download...
Copy data!
Copy data end!

download 0x1b bytes to 0x30008000

0123456789abcdefghijklmnopq
Press any key to continue...

����Ϊ�û��ֱ�������C���µ������ı��ļ����ļ��е����ݷֱ�Ϊ��0123456789!@#$^&*()_+ ��0123456789abcdefghijklmnopq