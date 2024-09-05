# Poly Sum

If
$P(k)=p_rk^r+p_{r-1}k^{r-1}+\dots+p_1k+p_0$
is a polynomial in $k$ of degree $r$ with rational coefficients $p_0,\dots,p_r$, the sum
$Q(n)=P(0)+P(1)+\dots+P(n)=\sum_{k=0}^nP(k)$
is a polynomial in $n$ of degree $r+1$ with rational coefficients $q_0,\dots,q_{r+1}$, i.e.
$Q(n)=q_{r+1}n^{r+1}+q_rn^r+\dots+q_1n+q_0.$

If given the rational numbers $r,p_0,\dots,p_r$, this program outputs the rational numbers $r+1,q_0,\dots,q_{r+1}$.

## Usage
Requirements:
- A UNIX build environment with a C compiler and Make installed
- [GNU Multiple Precision Arithmetic Library](https://gmplib.org/). `apt install libgmp-dev` on Debian-based systems

Build with `make`.

### Example
If we want to evaluate the sum
$Q(n)=1+2+\dots+n,$
we give the program the input (on `/dev/stdin`)
```
1
0
1
```
since $P(k)=k=1\cdot k^1+0\cdot k^0$ and it will output (on `/dev/stdout`)
```
2
0
1/2
1/2
```
since $1+2+\dots+n=\frac{n(n+1)}2=\frac12n^2+\frac12n$.

