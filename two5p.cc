#include <iostream>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <stdint.h>
#include <omp.h>

using namespace std;

typedef __uint128_t uint128_t;

uint128_t pow(uint32_t a, uint32_t k);

// Each entry in the heap is a triple.
struct triple {
    uint128_t sum;
    uint32_t a;
    uint32_t b;
};

// Comparison function for our min heap of triples.
class compare_triples
{
    public:
        bool operator()(struct triple x, struct triple y)
        {
            if(x.sum > y.sum)
                return true;
            return false;
        }
};

int main(int argc, char *argv[])
{

    uint32_t x, n, a, b, p, M, i, mod;
    uint128_t y, pp;

    p = 5;
    mod = 30;

    // Input the power p and the bound M.
    if (argc == 2) {
        M = atol(argv[1]);
    }

    if (argc != 2) {
        cout << "usage: two5_parallel M\n";
        return 0;
    }


    priority_queue<struct triple, vector<struct triple>, compare_triples> H;
    triple heap_entry, last, current, next;

    # pragma omp parallel for schedule(dynamic) private(H, heap_entry, last, current, next, i, x, y, n, a, b)
    for (i = 0; i <= mod; i++) {
        # pragma omp critical
        {
            cout << "thread " << i << endl;
        }
        for (x = 1; x < M; x++) {
            if ((x + 1) % mod == i) {
                heap_entry.sum = 1 + pow(x, p);
                heap_entry.a = 1;
                heap_entry.b = x;
                H.push(heap_entry);
            }
        }

        for (a = 2; a <= mod; a++) {
            for (x = a; x < M; x++) {
                if ((x + a) % mod == i) {
                    heap_entry.sum = pow(a, p) + pow(x, p);
                    heap_entry.a = a;
                    heap_entry.b = x;
                    H.push(heap_entry);
                }
            }
        }

        last.sum = (uint128_t)0;
        last.a = (uint32_t)0;
        last.b = (uint32_t)0;

        while (!H.empty()) {
            current = H.top();
            H.pop();

            if (current.sum == last.sum) {
                # pragma omp critical
                {
                    cout << current.a << " " << current.b << " ";
                    cout << last.a << " " << last.b << endl;
                }
            }

            last = current;
            y = current.sum;
            n = current.a;
            b = current.b;

            if (n + mod < b) {
                next.sum = pow(n + mod, p) - pow(n, p) + y;
                next.a = n + mod;
                next.b = b;
                H.push(next);
            }
        }
        # pragma omp critical
        {
            cout << "thread " << i << " complete" << endl;
        }
    }

    return 1;
}

uint128_t pow(uint32_t a, uint32_t p)
{
    uint128_t t, e, k;

    e = (uint128_t) a;
    k = (uint128_t) p;
    t = (uint128_t) 1;

    while (k) {
        if (k % 2 == 1)
            t *= e;
        k >>= 1;
        e *= e;
    }

    return t;
}
