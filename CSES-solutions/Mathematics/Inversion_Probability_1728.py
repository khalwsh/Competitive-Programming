/* problem statement text */
/*
CSES - Inversion Probability

Time limit: 1.00 s
Memory limit: 512 MB

An array has nnn integers x1,x2,…,xnx_1,x_2,\dots,x_nx1​,x2​,…,xn​, and each of them has been randomly chosen between 111 and rir_iri​. An inversion is a pair (a,b)(a,b)(a,b) where a<ba<ba<b and xa>xbx_a>x_bxa​>xb​.
What is the expected number of inversions in the array?
Input
The first input line contains an integer nnn: the size of the array.
The second line contains nnn integers r1,r2,…,rnr_1,r_2,\dots,r_nr1​,r2​,…,rn​: the range of possible values for each array position.
Output
Print the expected number of inversions rounded to six decimal places (rounding half to even).
Constraints

1≤n≤1001 \le n \le 1001≤n≤100
1≤ri≤1001 \le r_i \le 1001≤ri​≤100

Example
Input:
3
5 2 7

Output:
1.057143
*/
# expected_inversions.py
import sys
from fractions import Fraction
from decimal import Decimal, getcontext, ROUND_HALF_EVEN
 
def main():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    n = int(next(it))
    r = [int(next(it)) for _ in range(n)]
 
    total = Fraction(0, 1)
 
    for i in range(n):
        for j in range(i+1, n):
            ri = r[i]
            rj = r[j]
            # count of pairs (k,l) with 1<=k<=ri, 1<=l<=rj and k>l
            if ri <= rj:
                cnt = ri * (ri - 1) // 2
            else:
                cnt = rj * (rj - 1) // 2 + (ri - rj) * rj
            total += Fraction(cnt, ri * rj)
 
    # Convert Fraction to Decimal with high precision, then quantize with ROUND_HALF_EVEN
    getcontext().prec = 60  # plenty of precision
    dec = (Decimal(total.numerator) / Decimal(total.denominator))
    rounded = dec.quantize(Decimal('0.000001'), rounding=ROUND_HALF_EVEN)
 
    # Always print exactly 6 decimal places
    print(f"{rounded:.6f}")
 
if __name__ == "__main__":
    main()