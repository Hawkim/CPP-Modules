#include <iostream>

void toUpper(char *str){

    int i =0;

    while (str[i] )
    {
        if (str[i] >= 'a' && str[i]<= 'z')
            str[i]-=32;
        
        i++;
    }    
}


int main(int ac, char **av) {


    if (ac<=1)
    {
        std::cout <<"* LOUD AND UNBEARABLE FEEDBACK NOISE *\n" ;
    }
    else
    {

    for (int i = 1; i < ac; i++) {
    toUpper(av[i]);
        std::cout << av[i] ;
    }
    std::cout << std::endl;
    }
    return 0;
}

