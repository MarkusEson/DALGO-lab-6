#ifndef RK_H
#define RK_H


struct RK{
    RK(int r, int k) : _r(r), _k(k) {}
    RK() : _r(0), _k(0) {}
    int _r;
    int _k;
};
inline bool operator==(const RK& rk1, const RK& rk2){ return rk1._r==rk2._r && rk1._k==rk2._k; }
inline bool operator!=(const RK& rk1, const RK& rk2){ return !(rk1 == rk2); }
#endif // RK_H
