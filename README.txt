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

Each of the following programs uses 128 bit integers internally. This increases
the search space available to us at the cost of speed.

Usage:

two3p M

    This searches for 0 < y < x <= M such that k = x^3 + y^3 has two
    representations as a sum of two fifth powers. We can search up to x =
    5541191377756 before any overlapping occurs. This program can utilize up
    to 6 threads at once.

    For example, ./two3p 30 prints to the terminal

    2 16 9 15
    9 10 1 12

    since 2^3 + 16^3 = 9^3 + 15^3 = 4104 and 9^3 + 10^3 = 1^3 + 12^3 = 1729.
    Note that these are printed out of order due to the parallelization.

two5p M

    This searches for 0 < y < x <= M such that k = x^5 + y^5 has two
    representations as a sum of two fifth powers. We can search up to x =
    44275338 before any overlapping occurs. This program can utilize up to 30
    threads at once.

    The output is the same as two3p.

two_pows p M

    This searches for 0 < y < x <= M such that k = x^p + y^p has two
    representations as a sum of two pth powers. Take into consideration that
    the search space is smaller for larger values of p. For each p, this
    program finds the best choice of modulus for parallelization purposes.

    For example, ./two_pows 4 250 prints to the terminal

    Checking remainders modulo 2
    133 134 59 158
    7 239 157 227
    
    since 133^4 + 134^4 = 59^4 + 158^4 = 635318657 and 7^4 + 239^4 = 157^4 +
    227^4 = 3262811042.
