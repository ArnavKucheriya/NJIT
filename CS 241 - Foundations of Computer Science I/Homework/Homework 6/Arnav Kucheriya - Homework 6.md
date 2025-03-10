
# Question 1:

## Section 2.1 Solutions

### Problem 9
Prove that for all integers \( m \) and \( n \), if \( m \) and \( n \) are even, then \( mn \) is even.

**Proof:**  
Since \( m \) and \( n \) are even, we can write:

$m = 2a, \quad n = 2b$

for some integers \( $a, b$ \). Then,

$mn = (2a)(2b) = 4ab = 2(2ab)$

which is clearly even.

### Problem 10
Prove that for all integers \( m \) and \( n \), if \( m \) and \( n \) are odd, then \( mn \) is odd.

**Proof:**  
Since \( m \) and \( n \) are odd, we can write:

$m = 2a + 1, \quad n = 2b + 1$

for some integers \( a, b \). Then,

$mn = (2a+1)(2b+1) = 4ab + 2a + 2b + 1 = 2(2ab + a + b) + 1$

which is of the form \( $2k + 1$ \), meaning \( $mn$ \) is odd.

### Problem 16
Prove that the product of two integers, one of the form \( 3k_1 + 1 \) and the other of the form \( 3k_2 + 2 \), is of the form \( 3k_3 + 2 \) for some integer \( k_3 \).

**Proof:**  
Let \( $m = 3k_1 + 1$ \) and \( $n = 3k_2 + 2$ \). Then:

$mn = (3k_1 + 1)(3k_2 + 2) = 9k_1k_2 + 6k_1 + 3k_2 + 2$ 

**$= 3(3k_1k_2 + 2k_1 + k_2) + 2$**

which is of the form \( $3k_3 + 2$ \) where \($ k_3 = 3k_1k_2 + 2k_1 + k_2$ \).

### Problem 17
Prove that the product of two integers, one of the form \( $3k_1 + 2$ \) and the other of the form \( $3k_2 + 2$ \), is of the form \( $3k_3 + 1$ \) for some integer \( $k_3$ \).

**Proof:**  
Let \( $m = 3k_1 + 2$ \) and \( $n = 3k_2 + 2$ \). Then:

$mn = (3k_1 + 2)(3k_2 + 2) = 9k_1k_2 + 6k_1 + 6k_2 + 4$
$= 3(3k_1k_2 + 2k_1 + 2k_2 + 1) + 1$

which is of the form \( $3k_3 + 1$ \) where \( $k_3 = 3k_1k_2 + 2k_1 + 2k_2 + 1$ \).

### Problem 21
Prove that \($X \cap Y \subseteq X$\) for all sets \( $X$ \) and \( $Y$ \).

Let \( $x \in X \cap Y$ \). 
By definition of intersection, \( $x \in X$ \) and \( $x \in Y$ \). Since \( $x \in X$ \), 
it follows that \( $X \cap Y \subseteq X$ \).

### Problem 22
Prove that \( $X \subseteq X \cup Y$ \) for all sets \( $X$ \) and \( $Y$ \).

**Proof:**  
Let \( $x \in X$ \). By definition of union, \( $x \in X \cup Y$ \), 
since elements of \( $X$ \) are always in \( $X \cup Y$ \). 
Thus, \( $X \subseteq X \cup Y$ \).

### Problem 24
Prove that if \( $X \subseteq Y$ \), then \( $X \cap Z \subseteq Y \cap Z$ \) for all sets \( $X, Y$ \) and \( $Z$ \).

**Proof:**  
Let \( $x \in X \cap Z$ \). Then \( $x \in X$ \) and \( $x \in Z$ \). 
Since \( $X \subseteq Y$ \), we also have \( $x \in Y$ \). 
Thus, \( $x \in Y \cap Z$ \), so \( $X \cap Z \subseteq Y \cap Z$ \).

### Problem 25
Prove that if \( $X \subseteq Y$ \), then \( $Z - Y \subseteq Z - X$ \) for all sets \( $X, Y$ \) and \($Z$\).

**Proof (by contrapositive):**  
We prove that if \( $x \notin Z - X$ \), then \( $x \notin Z - Y$ \).

If \( $x \notin Z - X$ \), then either \( $x \notin Z$ \) or \( $x \in X$ \). 
Since \( $X \subseteq Y$ \), we have \( $x \in Y$ \), which means \( $x \notin Z - Y$ \). 
Thus, \( $Z - Y \subseteq Z - X$ \).


### Problem 29
Prove that \( $\mathcal{P}(X \cup Y) = \mathcal{P}(X) \cup \mathcal{P}(Y)$ \) for all sets \( $X$ \) and \( $Y$ \).

**Proof (Counterexample):**  
Let \( $X = \{a\}$ \) and \( $Y = \{b\}$ \). Then:

$\mathcal{P}(X) = \{\emptyset, \{a\}\}, \quad \mathcal{P}(Y) = \{\emptyset, \{b\}\}$

$\mathcal{P}(X) \cup \mathcal{P}(Y) = \{\emptyset, \{a\}, \{b\}\}$

$\mathcal{P}(X \cup Y) = \mathcal{P}(\{a, b\}) = \{\emptyset, \{a\}, \{b\}, \{a, b\}\}$

Since \( $\mathcal{P}(X \cup Y) \neq \mathcal{P}(X) \cup \mathcal{P}(Y)$ \), the statement is false.


### Problem 30
Prove that \( $\mathcal{P}(X \cap Y$) $\subseteq \mathcal{P}(X) \cap \mathcal{P}(Y)$ \) for all sets \( $X$ \) and \( $Y$ \).

**Proof:**  
Let \( $A \in \mathcal{P}(X \cap Y)$ \). Then \( $A \subseteq X \cap Y$ \), meaning \( $A \subseteq X$ \) and \( $A \subseteq Y$ \). Since \( A \) is a subset of both \( $X$ \) and \( $Y$ \), it belongs to both \( $\mathcal{P}(X)$ \) and \( $\mathcal{P}(Y)$ \). Therefore, \( $A \in \mathcal{P}(X) \cap \mathcal{P}(Y)$ \), so:

$\mathcal{P}(X \cap Y) \subseteq \mathcal{P}(X) \cap \mathcal{P}(Y).$

---

## Section 2.2:

### Problem 4
Prove by contradiction that for every \( $n \in \mathbb{Z}$ \), if \( $n^2$ \) is odd, then \( $n$ \) is odd.

**Proof (Contradiction):**  
Assume that \( $n^2$ \) is odd, but \( $n$ \) is even.  
Since \( $n$ \) is even, we can write \( $n = 2k$ \) for some integer \( $k$ \). Then,

$n^2 = (2k)^2 = 4k^2 = 2(2k^2)$

which is even, contradicting our assumption that \( $n^2$ \) is odd.  
Thus, our assumption is false, and \( $n$ \) must be odd.

---

### Problem 5
Prove by contradiction that for all real numbers \( $x, y$ \) and \( $z$ \), if \( $x + y + z \geq 3$ \), then either 
\( $x \geq 1$ \) or \( $y \geq 1$ \) or \( $z \geq 1$ \).

**Proof (Contradiction):**  
Assume that \( $x + y + z \geq 3$ \) and that \( $x < 1$ \), \( $y < 1$ \), and \( $z < 1$ \).  
Then,

$x + y + z < 1 + 1 + 1 = 3$

which contradicts our assumption that \( $x + y + z \geq 3$ \).  
Thus, at least one of \( $x, y$ \) or \( $z$ \) must be \( $\geq 1$ \).

---

### Problem 22
Prove by contradiction that if 100 balls are placed in 9 boxes, some box contains at least 12 or more balls.

**Proof (Contradiction):**  
Assume that no box contains 12 or more balls. Then, each box has at most 11 balls.  
The total number of balls would be at most:

$9 \times 11 = 99$

which contradicts the assumption that there are 100 balls.  
Thus, at least one box must contain 12 or more balls.

---

### Problem 23
Prove by contradiction that if 40 coins are distributed among nine bags so that each bag contains at least one coin, at least two bags contain the same number of coins.

**Proof (Contradiction):**  
Each bag contains at least one coin, so the number of coins per bag must be between 1 and 32 (since \( $1 + 2 + \dots + 9 = 45$ \) exceeds 40).  
If each bag had a unique number of coins, they would contain \( $1, 2, \dots, 9$ \), summing to:

$\frac{9(10)}{2} = 45$

which is more than $40$.  
Thus, at least two bags must contain the same number of coins.

---

### Problem 27
Prove by contradiction that there exists \( $i$ \) such that \( $s_i \leq A$ \).

**Proof (Contradiction):**  
Assume that for all \( $i$ \), \( $s_i > A$ \).  
Then, the minimum value of \( $s_i$ \) is greater than \( $A$ \), contradicting the definition of \( $A$ \) as an average.  
Thus, there must exist some \( $i$ \) such that \( $s_i \leq A$ \).

---

### Problem 29
Prove by contradiction that there exists \( $i$ \) such that \( $s_i > A$ \).

**Proof (Contradiction):**  
Assume that for all \( $i$ \), \( $s_i \leq A$ \).  
Then, the maximum value of \( $s_i$ \) is less than or equal to \( $A$ \), contradicting the definition of \( $A$ \) as an average.  
Thus, there must exist some \( $i$ \) such that \( $s_i > A$ \).

---

### Problem 32
Prove by contradiction that \( $2m + 5n = 2$ \) has no solution in positive integers.

**Proof (Contradiction):**  
Assume there exist positive integers \( $m, n$ \) such that:

$2m + 5n = 2$

Since \( $2m$ \) is always even and \( $5n$ \) is always odd for positive integers, their sum is odd.  
However, 2 is even, which contradicts this equation.  
Thus, no positive integer solutions exist.

---

### Problem 33
Prove by contradiction that \( $m^3 + 2n^2 = 36$ \) has no solution in positive integers.

**Proof (Contradiction):**  
Assume there exist positive integers \( $m, n$ \) such that:

$m^3 + 2n^2 = 36$

Since \( $m^3$ \) is odd when \( $m$ \) is odd and even when \( $m$ \) is even, and \( $2n^2$ \) is always even, their sum must be even.  
However, $36$ is even, so \( $m^3$ \) must also be even, implying \( $m$ \) is even.  

Let \( $m = 2k$ \), then:

$(2k)^3 + 2n^2 = 36 \Rightarrow 8k^3 + 2n^2 = 36$

Dividing by 2:

$4k^3 + n^2 = 18$

Since \( $4k^3$ \) is always even, \( $n^2$ \) must be even. Thus, \( $n$ \) must be even.  
Let \( $n = 2p$ \), then:

$4k^3 + 4p^2 = 18$

Dividing by 2:

$2k^3 + 2p^2 = 9$

which is a contradiction, as the left side is even, while 9 is odd.  
Thus, no positive integer solutions exist.

---

## Section 5.1 Solutions

### Problem 27
Let \( $m, n, d$ \), and \( $b$ \) be integers. Show that if \( $d \mid m$ \) and \( $d \mid n$ \), then \( $d \mid (m - n)$ \).

**Proof:**  
Since \( $d \mid m$ \), there exists an integer \( $k$ \) such that \( $m = dk$ \).  
Since \( $d \mid n$ \), there exists an integer \( $l$ \) such that \( $n = dl$ \).  
Thus,  

$m - n = dk - dl = d(k - l).$

Since \( $k - l$ \) is an integer, it follows that \( $d \mid (m - n)$ \).

### Problem 28
Let \( $m, n$ \) and \( $b$ \) be integers. Show that if \( $d \mid m$ \), then \( $d \mid bm$ \).

**Proof:**  
Since \( $d \mid m$ \), there exists an integer \( $k$ \) such that \( $m = dk$ \).  
Multiplying both sides by \( $b$ \), we obtain:  

$bm = b(dk) = d(bk).$

Since \( $bk$ \) is an integer, it follows that \( $d \mid bm$ \).

### Problem 29
Let \( $m, n, d_1,$ \) and \( $d_2$ \) be integers. Show that if \( $d_1 \mid m$ \) and \( $d_2 \mid n$ \), then \( $d_1 d_2 \mid mn$ \).

**Proof:**  
Since \( $d_1 \mid m$ \), there exists an integer \( $k$ \) such that \( $m = d_1 k$ \).  
Since \( $d_2 \mid n$ \), there exists an integer \( $l$ \) such that \( $n = d_2 l$ \).  
Thus,  

$mn = (d_1 k)(d_2 l) = d_1 d_2 (kl).$

Since \( $kl$ \) is an integer, it follows that \( $d_1 d_2 \mid mn$ \).


### Problem 30
Let \( $n, c,$ \) and \( $d$ \) be integers. Show that if \( $dc \mid nc$ \), then \( $d \mid n$ \).

**Proof:**  
Since \( $dc \mid nc$ \), there exists an integer \( $k$ \) such that  

$nc = (dc)k.$

Dividing both sides by \( $c$ \) (assuming \( $c \neq 0$ \)), we get:  

$n = dk.$

Since \( $k$ \) is an integer, it follows that \( $d \mid n$ \).


### Problem 31
Let \( $a, b,$ \) and \( $c$ \) be integers. Show that if \( $a \mid b$ \) and \( $b \mid c$ \), then \( $a \mid c$ \).

**Proof:**  
Since \( $a \mid b$ \), there exists an integer \( $k$ \) such that \( $b = ak$ \).  
Since \( $b \mid c$ \), there exists an integer \( $l$ \) such that \( $c = bl$ \).  
Substituting \( $b = ak$ \) into \( $c = bl$ \), we get:  

$c = (ak)l = a(kl).$

Since \( $kl$ \) is an integer, it follows that \( $a \mid c$ \).

---

# Question 2-5:

## Problem 2
Prove that for all sets  $A, B$ :  
$$
A \cap B = \emptyset \iff B \subseteq A^c
$$
**Proof:**  
- ($\Rightarrow$) Assume $A \cap B = \emptyset$. This means no element of  $B$ is in $A$, so every element of $B$ must be in $A^c$. Thus, $B \subseteq A^c$.
- ($\Leftarrow$) Assume $B \subseteq A^c$. Then every element of $B$ is not in $A$, so $A \cap B = \emptyset$.

---

## Problem 3
Prove that for all $n \in \mathbb{N} \cup \{0\}$:  
$$
n^2 \not\equiv 3 \pmod{5}
$$
**Proof:**  
The possible remainders of $n$ modulo 5 are $0, 1, 2, 3, 4$. Squaring each:
$$
0^2 \equiv 0, \quad 1^2 \equiv 1, \quad 2^2 \equiv 4, \quad 3^2 \equiv 9 \equiv 4, \quad 4^2 \equiv 16 \equiv 1 \pmod{5}
$$
Since 3 does not appear among these values, $n^2 \not\equiv 3 \pmod{5}$.

---

## Problem 4
Prove that for all $x, y \in \mathbb{R}$:
$$
\min(x, y) + \max(x, y) = x + y
$$
**Proof:**  
By definition:
$$
\max(x, y) =
\begin{cases} 
b & \text{if } a \leq b \\
a & \text{if } a > b
\end{cases}
$$
$$
\min(x, y) =
\begin{cases} 
a & \text{if } a \leq b \\
b & \text{if } a > b
\end{cases}
$$
In both cases, $\min(x, y) + \max(x, y) = a + b$, proving the statement.

---

## Problem 5: Proving the Irrationality of $\sqrt{3}$

### Definition:
A number $ s $ is **rational** if there exist integers $a, b$ such that  
$$
s = \frac{a}{b}, \quad \text{where } b \neq 0.
$$

### Definition (Lowest Terms):
A rational number $s = \frac{a}{b}$ is in **lowest terms** if $\gcd(a, b) = 1$.

---

Author: Arnav Kucheriya 
CS 241 - March 9, 2025.