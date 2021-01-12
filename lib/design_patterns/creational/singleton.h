#ifndef CPPREPO_SINGLETON_H
#define CPPREPO_SINGLETON_H


class Singleton {
public:
    static Singleton &get_instance();

    int foo() {
        return 5;
    }

private:
    Singleton() {}

    Singleton(Singleton const &);

    void operator=(Singleton const &);
};


#endif //CPPREPO_SINGLETON_H
