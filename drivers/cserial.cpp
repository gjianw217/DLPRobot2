#include "cserial.h"

CSerial::CSerial()
{

}
CSerial::~CSerial()
{

}
int CSerial::Open(const char *com)
{
#ifdef DLP_ARM_LINUX
    m_fd=open(com,  O_RDWR );
    if(m_fd<0)
    {
        printf("m_fd=open(com,  O_RDWR )%s\n",com);
        perror("CSerial::Open ");
    }
#endif // DLP_ARM_LINUX
    return m_fd;
}
void CSerial::Config(const uint8_t &baudrate,const uint8_t &databit,const uint8_t &parity,const uint8_t &stopbit)
{
#ifdef DLP_ARM_LINUX
    if(m_fd<0) return;

    struct termios old;
    tcgetattr(m_fd, &old);
    //tcgetattr(m_fd, &m_uart2);

    memset(&m_uart2, 0, sizeof(struct termios));
    SetBaudRate(baudrate );
    SetDataBits(databit );
    SetParity(parity);
    SetStopBits(stopbit);
    SetFlowControl(0);


	/* C_CFLAG      Control m_uart2
       CLOCAL       Local line - do not change "owner" of port
       CREAD        Enable receiver
    */
	m_uart2.c_cflag |= (CLOCAL | CREAD);

	  /* C_LFLAG      Line m_uart2

       ISIG Enable SIGINTR, SIGSUSP, SIGDSUSP, and SIGQUIT signals
       ICANON       Enable canonical input (else raw)
       XCASE        Map uppercase \lowercase (obsolete)
       ECHO Enable echoing of input characters
       ECHOE        Echo erase character as BS-SP-BS
       ECHOK        Echo NL after kill character
       ECHONL       Echo NL
       NOFLSH       Disable flushing of input buffers after
       interrupt or quit characters
       IEXTEN       Enable extended functions
       ECHOCTL      Echo control characters as ^char and delete as ~?
       ECHOPRT      Echo erased character as character erased
       ECHOKE       BS-SP-BS entire line on line kill
       FLUSHO       Output being flushed
       PENDIN       Retype pending input at next read or input char
       TOSTOP       Send SIGTTOU for background output

       Canonical input is line-oriented. Input characters are put
       into a buffer which can be edited interactively by the user
       until a CR (carriage return) or LF (line feed) character is
       received.

       Raw input is unprocessed. Input characters are passed
       through exactly as they are received, when they are
       received. Generally you'll deselect the ICANON, ECHO,
       ECHOE, and ISIG m_uart2 when using raw input
    */

    /* Raw input *//*set local flag*/
	m_uart2.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	 /* C_IFLAG      Input m_uart2

       Constant     Description
       INPCK        Enable parity check
       IGNPAR       Ignore parity errors
       PARMRK       Mark parity errors
       ISTRIP       Strip parity bits
       IXON Enable software flow control (outgoing)
       IXOFF        Enable software flow control (incoming)
       IXANY        Allow any character to start flow again
       IGNBRK       Ignore break condition
       BRKINT       Send a SIGINT when a break condition is detected
       INLCR        Map NL to CR
       IGNCR        Ignore CR
       ICRNL        Map CR to NL
       IUCLC        Map uppercase to lowercase
       IMAXBEL      Echo BEL on input line too long
    */
    /* set input mode flag*/
    //m_uart2.c_iflag &= ~(ICRNL | INLCR);
     /* Software flow control is disabled */
	m_uart2.c_iflag &= ~(IXON | IXOFF | IXANY);
	/* C_OFLAG      Output m_uart2
       OPOST        Postprocess output (not set = raw output)
       ONLCR        Map NL to CR-NL

       ONCLR ant others needs OPOST to be enabled
    */
    /*set output mode flag*/
    /* Raw ouput */
	m_uart2.c_oflag &= ~OPOST;
	//m_uart2.c_oflag &= ~(ONLCR | OCRNL);

	/*set control charactor*/
	 /* Unused because we use open with the NDELAY option */
	  /* C_CC         Control characters
       VMIN         Minimum number of characters to read
       VTIME        Time to wait for data (tenths of seconds)

      */
	m_uart2.c_cc[VTIME] = 10;
	m_uart2.c_cc[VMIN]   = 10;  //more than 0;

	/*flush the input/output buffer*/
	tcflush(m_fd, TCIOFLUSH);

	/*save the configure*/
	if(tcsetattr(m_fd, TCSANOW, &m_uart2) != 0)/* Update the m_uart2 and do it NOW */
	{
		perror("serial configure save error\n");
		return ;
	}


    if(fcntl(m_fd,F_SETFL,0) < 0){   //阻塞
        printf("fcntl failed\n");
    }
#endif // DLP_ARM_LINUX
}

int CSerial::Read(uint8_t *data,const uint8_t &len)
{
#ifdef DLP_ARM_LINUX
    if(m_fd<0)
    {
        return -2;
    }
    else
    {
        return read(m_fd,data,len);
    }
#else
    return 0;
#endif // DLP_ARM_LINUX
}

int CSerial::Write(const uint8_t *data,const uint8_t &len)
{
#ifdef DLP_ARM_LINUX
    if(m_fd<0)
    {
        return -2;
    }
    else
    {
        return write(m_fd,data,len);
    }
#else
    return 0;
#endif // DLP_ARM_LINUX
}


void CSerial::SetBaudRate(const uint8_t &rate )
{
#ifdef DLP_ARM_LINUX
    int speed;
    switch(rate)
    {
        case BR2400:speed=B2400;break;
        case BR4800:speed=B4800;break;
        case BR9600:speed=B9600;break;
        case BR19200:speed=B19200;break;
        case BR38400:speed=B38400;break;
        case BR57600:speed=B57600;break;
        case BR115200:
        default:speed=B115200;break;
    }
    if(cfsetispeed(&m_uart2, speed)<0||cfsetospeed(&m_uart2, speed)<0)
    {
        printf("unable to set baudrate\n");
    }
    else
    {
        printf("serial speed %d ==%d\n",rate,speed);
    }

#endif // DLP_ARM_LINUX
}

void CSerial::SetDataBits(const uint8_t &databits )
{
#ifdef DLP_ARM_LINUX
    m_uart2.c_cflag &= ~CSIZE;
	switch (databits) /*设置数据位数*/
	{
	case 7:
		m_uart2.c_cflag |= CS7;
		break;
	case 8:
		m_uart2.c_cflag |= CS8;/*set data bit 8 bit*/
		break;
	default:
		fprintf(stderr,"Unsupported data size\n");
	}
#endif // DLP_ARM_LINUX
}

void CSerial::SetParity(const uint8_t &parity)
{
#ifdef DLP_ARM_LINUX
    switch (parity)
    {
        case 'n':
        case 'N':
        case 0:
            m_uart2.c_cflag &= ~PARENB;   /* Clear parity enable */
            m_uart2.c_iflag &= ~INPCK;     /* Enable parity checking */
            break;
        case 'o':
        case 'O':
        case 1:
            m_uart2.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
            m_uart2.c_iflag |= INPCK;             /* Disnable parity checking */
            break;
        case 'e':
        case 'E':
        case 2:
            m_uart2.c_cflag |= PARENB;     /* Enable parity */
            m_uart2.c_cflag &= ~PARODD;   /* 转换为偶效验*/
            m_uart2.c_iflag |= INPCK;       /* Disnable parity checking */
            break;
        case 'S':
        case 's':  /*as no parity*/
        case 3:
            m_uart2.c_cflag &= ~PARENB;
            m_uart2.c_cflag &= ~CSTOPB;break;
        default:
            fprintf(stderr,"Unsupported parity\n");
    }
#endif // DLP_ARM_LINUX
}

void CSerial::SetStopBits(const uint8_t &stopbits)
{
#ifdef DLP_ARM_LINUX
    switch (stopbits)
    {
        case 1:m_uart2.c_cflag &= ~CSTOPB; break;  /*set stop bit 1 bit*/
        case 2:m_uart2.c_cflag |= CSTOPB ; break;
        default:fprintf(stderr,"Unsupported stop bits\n");

    }
#endif // DLP_ARM_LINUX
}

void CSerial::SetFlowControl(const uint8_t &flow)
{

}










