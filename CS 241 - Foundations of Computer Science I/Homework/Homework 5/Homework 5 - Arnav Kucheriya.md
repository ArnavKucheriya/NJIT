 Section 1.4:

 **Exercise 5**
$$
(p \lor r) \rightarrow q
$$
$$
\neg q
$$
$$
\therefore \neg p \land \neg r
$$

 **Exercise 11**
$$
p \rightarrow (r \lor q)
$$
$$
r \rightarrow \neg q
$$
$$
\therefore p \rightarrow r
$$

 **Exercise 14**
$$
p \rightarrow r
$$
$$
r \rightarrow q
$$
$$
p
$$
$$
\therefore q
$$

 **Exercise 15**
$$
(p \lor q) \rightarrow (r \lor s)
$$
$$
p
$$
$$
\neg r
$$
$$
\therefore s
$$

 **Exercise 22**
$$
p \land \neg p
$$
$$
\therefore q
$$

 **Exercise 30**
1. **Hypothesis**:
   - If there is gas in the car, then I will go to the store.
   - If I go to the store, then I will get a soda.
   - There is gas in the car.

2. **Applying hypothetical syllogism**:
   $$
   g \rightarrow s
   $$
   $$
   s \rightarrow d
   $$
   $$
   g
   $$
   $$
   \therefore d
   $$

 **Exercise 33 (Modus Tollens)**
$$
p \rightarrow q
$$
$$
\neg q
$$
$$
\therefore \neg p
$$

 **Exercise 34 (Addition)**
$$
p
$$
$$
\therefore p \lor q
$$

 **Exercise 35 (Simplification)**
$$
p \land q
$$
$$
\therefore p
$$

---

## **Quantifiers Problem Set**

 **Problem 1**

 (a)
The given statement:
$$
\forall x \ (x \in A \rightarrow x \in B)
$$
This defines the subset relation:
$$
A \subseteq B
$$

 (b)
The given statement:
$$
[\forall x \ (x \in A \rightarrow x \in B)] \land [\forall x \ (x \in B \rightarrow x \in A)]
$$
This defines the set equality:
$$
A = B
$$

---

 **Problem 3 (Proofs in Integer and Rational Numbers)**

 (a) **False**:
$$
\forall x, y \in \mathbb{Z}, \quad x - y = 7
$$
This is not true for all integers \( x, y \), e.g.,
$$
1 - 2 = -1 \neq 7
$$

 (b) **True**:
$$
\exists x, y \in \mathbb{Z}, \quad x - y = 7
$$
Example:
$$
x = 10, y = 3 \Rightarrow 10 - 3 = 7
$$

 (c) **True**:
For any \( x \), we can choose:
$$
y = x - 7
$$
such that:
$$
x - y = 7
$$

 (d) **False**:
If:
$$
\exists x \forall y, \quad x - y = 7
$$
then some \( x \) must work for all \( y \), which is impossible.

 (e) **False**:
For all \( x \in \mathbb{Z} \), \( x = 0 \) does not satisfy:
$$
x \cdot y = 7
$$
for any integer \( y \).

 (f) **False**:
In rationals:
$$
\forall x \in \mathbb{Q}, \exists y \in \mathbb{Q}, \quad x \cdot y = 7
$$
\( x = 0 \) does not work.

 (g) **True**:
If \( x \neq 0 \), then:
$$
y = \frac{7}{x}
$$
works.

 (h) **True**:
In \( \mathbb{Q} - \{0\} \), the equation:
$$
x \cdot y = 7
$$
is always solvable for some \( y \).

 (i) **True**:
For any integer \( y \), we can find:
$$
x = y + 1
$$
such that:
$$
x > y
$$

 (j) **False**:
There is no single integer \( y \) such that all integers \( x \) are greater than \( y \).
