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

If you wanted to evaluate
$Q(n)=\sum_{k=0}^n(k²-\frac32k+\frac13)$ for some reason, you would enter
```
2
1/3
-3/2
1
```
and get
```
3
1/3
-1/4
-1/4
1/3
```
i.e.
$Q(n)=\frac13k^3-\frac14k^2-\frac14k+\frac13$.
You can verify this result using [WolframAlpha](https://www.wolframalpha.com/input?i2d=true&i=Sum%5BPower%5Bk%2C2%5D-Divide%5B3%2C2%5Dk%2BDivide%5B1%2C3%5D%2C%7Bk%2C0%2Cn%7D%5D) (which renders my program obsolete).
