#ifndef XORSHIFT128P
#define XORSHIFT128P

static unsigned long long xorshift128p_state0=56924581;
static unsigned long long xorshift128p_state1=(12561346ull<<31);

void sxorshift128p(unsigned long long seed_)
{
    if (seed_<((1ull<<32)-1))
        seed_=(seed_|(xorshift128p_state0<<31));
    unsigned long seed=(seed_&((1ull<<31)-1));
    seed^=seed<<13;
    seed^=seed>>17;
    seed^=seed<<15;
    xorshift128p_state1=seed;
    seed=((seed_>>31)&((1ull<<31)-1));
    seed^=seed<<13;
    seed^=seed>>17;
    seed^=seed<<15;
    xorshift128p_state0=((unsigned long long)seed)<<30;
}

unsigned long long xorshift128p()
{
    unsigned long long s1=xorshift128p_state0;
    unsigned long long s0=xorshift128p_state1;
    xorshift128p_state0=s0;
    s1^=s1<<23;
    s1^=s1>>17;
    s1^=s0;
    s1^=s0>>26;
    xorshift128p_state1=s1;
    return xorshift128p_state0+xorshift128p_state1;
}
#endif // XORSHIFT128P
