
===========================================================================================
602 以太网 TFTP_Test实验
===========================================================================================
本实验实现通过以太网从PC机传文件到实验箱中。本例程有两种运行方式。
8LED_Test IN RAM         将程序下载到SDRAM中调试。
8LED_Test IN Flash       将程序烧写到Nor Flash中。
===========================================================================================
在程序运行之前, 请用直连网线直接连接试验箱和PC机，用交叉串口线链接PC的串口和实验箱的COM2，将
PC机的IP设定为192.168.2.*。程序运行成功之后，用户点击“开始”->“运行”输入 cmd命令后回车。
再在窗口中键入命令：tftp -i 192.168.2.111 put filename 后回车。但是要确保所要传输的文件在命
令窗口的当前目录下。
超级终端上将显示：


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

以上为用户分别传输了在C盘下的两个文本文件。文件中的内容分别为：0123456789!@#$^&*()_+ 和0123456789abcdefghijklmnopq