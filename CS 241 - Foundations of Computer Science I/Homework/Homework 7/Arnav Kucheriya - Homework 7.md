# Section 2.4 Mathematical Induction

## Group a

### 2.
Using induction, verify:
$$
\sum_{k=1}^{n} k(k+1) = \frac{n(n+1)(n+2)}{3}
$$

#### Basis Step:
For $n = 1$,
$$
1(1+1) = \frac{1(1+1)(1+2)}{3} = 2
$$
which holds true.

#### Inductive Step:
Assume for $n$,
$$
\sum_{k=1}^{n} k(k+1) = \frac{n(n+1)(n+2)}{3}
$$
For $n+1$,
$$
\sum_{k=1}^{n+1} k(k+1) = \frac{n(n+1)(n+2)}{3} + (n+1)(n+2)
$$

Rewriting:
$$
\frac{n(n+1)(n+2)}{3} + \frac{3(n+1)(n+2)}{3} = \frac{(n+1)(n+2)(n+3)}{3}
$$
which completes the proof.

### 3.
Using induction, prove:
$$
\sum_{k=1}^{n} k(k!) = (n+1)! - 1
$$

#### Basis Step:
For $n = 1$,
$$
1(1!) = (1+1)! - 1 = 2 - 1 = 1
$$
which is true.

#### Inductive Step:
Assume for $n$,
$$
\sum_{k=1}^{n} k(k!) = (n+1)! - 1
$$

For $n+1$,
$$
\sum_{k=1}^{n+1} k(k!) = (n+1)! - 1 + (n+1)(n+1)!
$$

$$
= (n+1)! - 1 + (n+1)(n+1)!
$$

$$
= (n+2)! - 1
$$

which proves the statement.

---

## Group b

### 5.
Prove using induction:
$$
1^2 - 2^2 + 3^2 - ... + (-1)^{n+1}n^2 = \frac{(-1)^{n+1} n(n+1)}{2}
$$

#### Basis Step:
For $n = 1$,
$$
1^2 = \frac{(-1)^{1+1} 1(1+1)}{2} = \frac{2}{2} = 1
$$
which holds.

#### Inductive Step:
Assume for $n$,
$$
\sum_{k=1}^{n} (-1)^{k+1} k^2 = \frac{(-1)^{n+1} n(n+1)}{2}
$$

For $n+1$,
$$
\sum_{k=1}^{n+1} (-1)^{k+1} k^2 = \frac{(-1)^{n+1} n(n+1)}{2} + (-1)^{(n+1)+1}(n+1)^2
$$

Rearranging,
$$
= \frac{(-1)^{n+2} (n+1)(n+2)}{2}
$$

which matches the formula for $n+1$, completing the proof.

### 6.
Using induction:
$$
1^3 + 2^3 + \dots + n^3 = \left(\frac{n(n+1)}{2}\right)^2
$$

#### Basis Step:
For $n = 1$,
$$
1^3 = \left(\frac{1(1+1)}{2}\right)^2 = 1
$$
which holds.

#### Inductive Step:
Assume for $n$,
$$
\sum_{k=1}^{n} k^3 = \left(\frac{n(n+1)}{2}\right)^2
$$

For $n+1$,
$$
\sum_{k=1}^{n+1} k^3 = \left(\frac{n(n+1)}{2}\right)^2 + (n+1)^3
$$

Using algebraic manipulation, we get:
$$
= \left(\frac{(n+1)(n+2)}{2}\right)^2
$$

which matches the formula for $n+1$, completing the proof.

---

## Group c

### 22.
Prove by induction that:
$$
2n + 1 \leq 2^n, \quad n \geq 3
$$

#### Basis Step:
For $n = 3$,
$$
2(3) + 1 = 7 \leq 2^3 = 8
$$
which holds.

#### Inductive Step:
Assume for $n$,
$$
2n + 1 \leq 2^n
$$

For $n+1$,
$$
2(n+1) + 1 = 2n + 3
$$

Using the assumption,
$$
2n + 3 \leq 2^n + 2 \leq 2^{n+1}
$$

which proves the statement.

---


## Group d

### 23.
Prove by induction:
$$
1 + 4 + 9 + \dots + n^2 = \frac{n(n+1)(2n+1)}{6}
$$

#### Basis Step:
For $n = 1$,
$$
1^2 = \frac{1(1+1)(2(1)+1)}{6} = \frac{1(2)(3)}{6} = 1
$$
which holds.

#### Inductive Step:
Assume for $n$,
$$
\sum_{k=1}^{n} k^2 = \frac{n(n+1)(2n+1)}{6}
$$

For $ n+1 $,
$$
\sum_{k=1}^{n+1} k^2 = \frac{n(n+1)(2n+1)}{6} + (n+1)^2
$$

Expanding and simplifying:
$$
\frac{n(n+1)(2n+1) + 6(n+1)^2}{6}
$$

$$
= \frac{(n+1)[n(2n+1) + 6(n+1)]}{6}
$$

$$
= \frac{(n+1)(n+2)(2n+3)}{6}
$$

which matches the formula for $ n+1 $, completing the proof.

---

### 24.
Prove:
$$
1^3 + 2^3 + \dots + n^3 = \left(\frac{n(n+1)}{2}\right)^2
$$

#### Basis Step:
For $ n = 1 $,
$$
1^3 = \left(\frac{1(1+1)}{2}\right)^2 = 1
$$
which holds.

#### Inductive Step:
Assume for $ n $,
$$
\sum_{k=1}^{n} k^3 = \left(\frac{n(n+1)}{2}\right)^2
$$

For $ n+1 $,
$$
\sum_{k=1}^{n+1} k^3 = \left(\frac{n(n+1)}{2}\right)^2 + (n+1)^3
$$

Using algebraic manipulation, we get:
$$
= \left(\frac{(n+1)(n+2)}{2}\right)^2
$$

which completes the proof.

---

### 25.
Prove:
$$
1 + 3 + 5 + \dots + (2n-1) = n^2
$$

#### Basis Step:
For $ n = 1 $,
$$
1 = 1^2
$$
which holds.

#### Inductive Step:
Assume for $ n $,
$$
\sum_{k=1}^{n} (2k-1) = n^2
$$

For $ n+1 $,
$$
\sum_{k=1}^{n+1} (2k-1) = n^2 + (2(n+1)-1)
$$

$$
= n^2 + (2n+1)
$$

$$
= (n+1)^2
$$

which matches the formula, completing the proof.

---

## Group e

### 26a.
Prove:
$$
\sum_{k=1}^{n} k! = 1! + 2! + ... + n! = (n+1)! - 1
$$

#### Basis Step:
For $ n = 1 $,
$$
1! = (1+1)! - 1 = 2 - 1 = 1
$$
which holds.

#### Inductive Step:
Assume for $ n $,
$$
\sum_{k=1}^{n} k! = (n+1)! - 1
$$

For $ n+1 $,
$$
\sum_{k=1}^{n+1} k! = (n+1)! - 1 + (n+1)!
$$

$$
= (n+1)! - 1 + (n+1)!
$$

$$
= (n+2)! - 1
$$

which completes the proof.

---

### 26b.
Prove:
$$
1 \cdot 1! + 2 \cdot 2! + ... + n \cdot n! = (n+1)! - 1
$$

#### Basis Step:
For $ n = 1 $,
$$
1 \cdot 1! = 2! - 2 = 1
$$
which holds.

#### Inductive Step:
Assume for $ n $,
$$
\sum_{k=1}^{n} k \cdot k! = (n+1)! - (n+1)
$$

For $ n+1 $,
$$
\sum_{k=1}^{n+1} k \cdot k! = (n+1)! - (n+1) + (n+1)(n+1)!
$$

$$
= (n+1)! + (n+1)(n+1)! - (n+1)
$$

$$
= (n+2)! - (n+2)
$$

which completes the proof.

---

### 27.
Prove:
$$
\sum_{k=1}^{n} \frac{1}{k(k+1)} = \frac{n}{n+1}
$$

#### Basis Step:
For $ n = 1 $,
$$
\frac{1}{1(1+1)} = \frac{1}{2}
$$
which holds.

#### Inductive Step:
Assume for $ n $,
$$
\sum_{k=1}^{n} \frac{1}{k(k+1)} = \frac{n}{n+1}
$$

For $ n+1 $,
$$
\sum_{k=1}^{n+1} \frac{1}{k(k+1)} = \frac{n}{n+1} + \frac{1}{(n+1)(n+2)}
$$

$$
= \frac{n(n+2) + 1}{(n+1)(n+2)}
$$

$$
= \frac{(n+1)}{(n+2)}
$$

which proves the formula.

---

## Group f

### 28.
Prove:
$$
F_n < 2^n \quad \text{for all } n \geq 1
$$
where $ F_n $ is the Fibonacci sequence.

#### Basis Step:
For $ n = 1, 2 $:
$$
F_1 = 1 < 2^1 = 2
$$
$$
F_2 = 1 < 2^2 = 4
$$
which holds.

#### Inductive Step:
Assume for $ n $:
$$
F_n < 2^n, \quad F_{n-1} < 2^{n-1}
$$

For $ n+1 $:
$$
F_{n+1} = F_n + F_{n-1}
$$

Using the induction hypothesis:
$$
F_n + F_{n-1} < 2^n + 2^{n-1}
$$

$$
< 2^n + 2^n = 2^{n+1}
$$

which proves the inequality.

---

Arnav Kucheriya - CS 241 - Homework 7
