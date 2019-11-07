#include "debug.h"

int main()
{
    int d = -1115555;
    char c = 'a';
    int *p = &d;
    char s[15] = "hello  0";
    log_info("hahahaha");
    log_info("%d%d%d%d%d%d", d,1,1,1,1,1);
    log_warning("%o", 15);
    log_fatal("%x", 17);
    log_debug("%c", c);
    log_error("%p", p);
    log_error("%s", s);
    log_error("%f", 0.5555);
    log_error("%f", 1235.5555);
    system("pause");
    return 0;
}
