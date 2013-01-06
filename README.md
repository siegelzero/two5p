These programs are designed to search for numbers that can be represented as a
sum of two powers in two different ways. The simplest interesting numbers of
this form are the famous Taxicab numbers, 1729 = 10^3 + 9^3 = 12^3 + 1^3 being
the best known example.

It is known that 635318657 = 133^4 + 134^4 = 59^4 + 158^4, and this is the
smallest integer expressible as a sum of two fourth powers in two different
ways. It is currently unknown what the smallest integer expressible as a sum of
two fifth powers in two different ways, or if any of these even exist.

Our algorithm is based on work published by D. Bernstein for enumerating
solutions to diophantine equations.  Bernstein's work gives an algorithm using
min heaps to enumerate solutions of p(a) + q(b) = r(c) + s(d), where p, q, r, s
are polynomials with integer coefficients.

We have parallelized the algorithm by splitting congruences classes into
separate cases.  For example, we have that x^5 = x (mod 30), so that x^5 + y^5
= x + y (mod 30).  Thus, we can check each congruence class separately,
according to x + y (mod 30).  Each power requires its own choice of modulus.

Usage:

two5p M
    This searches for x > y > 0 such that k = x^5 + y^5 two representations as
    a sum of two fifth powers. The algorithm uses 128 bit integers internally,
    so speed is slightly sacrificed in order to expand the search space.  We
    can search up to x = 44275338 before any overlapping.
