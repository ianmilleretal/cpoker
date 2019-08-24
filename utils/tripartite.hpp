#ifndef TRIPARTITE
#define TRIPARTITE

template<typename T, typename R, typename S>
class Tripartite
{
public:
    Tripartite() :
        first(),
        second(),
        third() {}
    Tripartite(T _first, R _second, S _third) :
        first(_first),
        second(_second),
        third(_third) {}
        

    T first;
    R second;
    S third;
};


#endif
