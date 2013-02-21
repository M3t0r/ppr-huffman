#include <stdio.h>
#include "testmain.h"

#if defined __APPLE__ || defined __linux__ || defined __CYGWIN__
#define NORMAL	"\033[0m"
#define GREEN	"\033[0;32m"
#define RED		"\033[0;31m"
#else
#define NORMAL
#define GREEN
#define RED
#endif

int main(void)
{
    int i, errors = 0;
    BOOL testresult;
    for (i = 0; i < nr_of_unittests; i++)
    {
        testresult = testsuit[i].test();
        if (!testresult)
        {
            errors++;
            printf("%sFAILED:%s %s\n", RED, NORMAL, testsuit[i].name);
        }
    }
    
    if (errors == 0)
    {
        printf("%sPASSED:%s %s\n", GREEN, NORMAL, name_of_testsuit);
    }
    
    return errors;
}
