#include "debug.h"

char num_table[16] = "0123456789abcdef";

void uart_send(char ch);
void print_num(unsigned long num, int base);

void print_deci(int data);
void print_oct(unsigned int data);
void print_hex(unsigned int data);
void print_char(char data);
void print_addr(unsigned long data);
void print_str(char * data);

void log_trace(char * fmt, ...)
{
	int cnt = 0;
	/* Parameter table pointer */
	va_list_t va_ptr;
	/* Initialize so that the pointer points to the first parameter */
	va_start(va_ptr, fmt);

	/* Loop prints all format strings */
	while ('\0' != fmt[cnt])
	{
		/* Normal characters print normally */
		if ('%' != fmt[cnt])
		{
			uart_send(fmt[cnt]);
			cnt++;
			continue;
		}
		/* Special handling of format characters */
		switch (fmt[++cnt])			/* Extract the format */
		{
			case 'd': print_deci(va_arg(va_ptr,int));
			  		  break;
			case 'o': print_oct(va_arg(va_ptr,unsigned int));
			  		  break;
			case 'x': print_hex(va_arg(va_ptr,unsigned int));
			  		  break;
			case 'c': print_char(va_arg(va_ptr,int));
			  		  break;
			case 'p': print_addr(va_arg(va_ptr,unsigned long));
			  		  break;
			case 'f': print_float(va_arg(va_ptr,double));
			  		  break;
			case 's': print_str(va_arg(va_ptr,char *));
					  break;
			default : break;
		}
		cnt++;
	}
	uart_send('\r');
	uart_send('\n');
    va_end(va_ptr);
}

void print_num(unsigned long num, int base)
{
	if (num == 0)
    {
        return;
    }

	print_num(num/base, base);

	uart_send(num_table[num%base]);
}

void print_deci(int data)
{
	if(data < 0)
	{
		uart_send('-');
		data = -data;
	}
	if (data == 0)
    {
        uart_send('0');
    }
	else
	{
		print_num(data, 10);
	}
}

void print_oct(unsigned int data)
{
	if (data == 0)
    {
        uart_send('0');
    }
	else
	{
		print_num(data, 8);
	}
}

void print_hex(unsigned int data)
{
	if (data == 0)
    {
        uart_send('0');
    }
	else
	{
		print_num(data, 16);
	}
}

void print_char(char data)
{
	uart_send(data);
}

void print_addr(unsigned long data)
{
	uart_send('0');
    uart_send('x');
	print_num(data, 16);
}

void print_float(double data)
{
	int tmp = 0;

	/* Print the integer part first */
    tmp = (int)data;
    if(0 == tmp)
    {
        uart_send('0');
    }
    else
    {
        print_num(tmp, 10);
    }

    uart_send('.');

	/* Print decimal */
    data -= tmp;
    if (data == 0)
    {
		/* Floating-point data must have at least six digits of precision */
		for (tmp = 0; tmp < 6; tmp++)
		{
		    uart_send('0');
		}
		return;
    }
    else
    {
        tmp = (int)(data * 1000000);
        print_num(tmp,10);
    }
}

void print_str(char * data)
{
	int cnt = 0;
    while ('\0' != data[cnt])
    {
        uart_send(data[cnt++]);
    }
}

void uart_send(char ch)
{
    putchar(ch);
}
