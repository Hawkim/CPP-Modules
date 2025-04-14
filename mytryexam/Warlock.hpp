#ifndef WARLOCK_HPP
#define WARLOCK_HPP

#include <iostream>

class Warlock{

    private:
        std::string name;
        std::string title;
        Warlock ();
        Warlock (Warlock const &other);
        Warlock &operator=(Warlock const &other);

    public:
        void getName();
        void getTitle();

        void setTitle();

        ~Warlock (); 

        void introduce() const;
        
    }       

#endif