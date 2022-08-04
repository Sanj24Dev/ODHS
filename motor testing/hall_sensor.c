#include<stdio.h>
int main()
{
int h1, h2, h3;

switch(h1)
{
    case 0:
        switch(h2)
        {
            case 0:
                switch(h3)
                {
                    case 0:
                        // no output
                    case 1:
                        // -i 0 i
                }
            case 1:
                switch(h3)
                {
                    case 0:
                        // 0 i -i 
                    case 1:
                        // -i i 0
                }
        }
    case 1:
        switch(h2)
        {
            case 0:
                switch(h3)
                {
                    case 0:
                        // i -i 0
                    case 1:
                        // 0 -i i
                }
            case 1:
                switch(h3)
                {
                    case 0:
                        // i 0 -i 
                    case 1:
                        // no ouput 
                }
        }

}
}