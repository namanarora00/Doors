unsigned char in_byte_from_port(unsigned short port);
void out_byte_from_port(unsigned char data, unsigned short port);
unsigned short in_word_from_port(unsigned short port);
void out_word_from_port(unsigned short data, unsigned short port);
void memset(void *start, char target, int len);