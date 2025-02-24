
## Section 1.5:

### Exercise 7, 10, 12, 14: "n Divides 77" - True or False
1. **P(11)**  
   - True (11 divides 77)

2. **∀n P(n)**  
   - False (Not every number divides 77)

3. **∀n ¬P(n)**  
   - False (Some numbers do divide 77, such as 1, 7, 11, and 77)

4. **¬(∀n P(n))**  
   - True (Since not all numbers divide 77, the negation of the universal quantifier is true)

---

### Exercise 20, 22, 24: "x² ≥ x" - True or False
5. **∃x P(x)**  
   - True (At least one value, such as x = 2, satisfies x² ≥ x)

6. **¬(∃x P(x))**  
   - False (Since at least one x satisfies x² ≥ x, the negation of existential quantifier is false)

7. **∃x ¬P(x)**  
   - True (There exists an x, such as x = 1/2, where x² < x)

---

### Exercise 25, 29: Rewrite Using Only Negation, Disjunction, and Conjunction
8. **∀x P(x) → ¬∃x ¬P(x)**  
   - Equivalent to **¬∃x ¬P(x)**  

9. **∃x ¬P(x)**  
   - Equivalent to **¬∀x P(x)**  

---

### Exercise 53, 55, 59: Truth Values
10. **∀x(x² > x)**  
   - False  
   - Counterexample: x = 1 violates the statement since 1² = 1 is not greater than 1.

11. **∀x(x > 1 → x² > x)**  
   - True  
   - For any x > 1, squaring x always results in a larger value.

12. **Negation of 53 and 55**  
   - Negation of **53**: **∃x(x² ≤ x)**  
   - Negation of **55**: **∃x(x > 1 ∧ x² ≤ x)**



## Section 1.6 Exercises

### Exercise 34-38: Negation in Words and Symbols
13. Someone loves everybody.  
   **Negation**: No one loves everybody.  
   **Symbolic**: ¬∃x ∀y L(x, y) ⇔ ∀x ∃y ¬L(x, y)

14. Everybody loves everybody.  
   **Negation**: There is someone who does not love everybody.  
   **Symbolic**: ¬∀x ∀y L(x, y) ⇔ ∃x ∃y ¬L(x, y)

15. Somebody loves somebody.  
   **Negation**: Nobody loves anybody.  
   **Symbolic**: ¬∃x ∃y L(x, y) ⇔ ∀x ∀y ¬L(x, y)

16. Everybody loves somebody.  
   **Negation**: There exists someone who loves nobody.  
   **Symbolic**: ¬∀x ∃y L(x, y) ⇔ ∃x ∀y ¬L(x, y)

### Exercise 48-51: Truth Values
17. **∀x∀y (x² < y + 1)**  
   - **True**  
   - Justification: For any real number x, we can always find y such that x² is smaller than y + 1.

18. **∀x∃y (x² < y + 1)**  
   - **True**  
   - Justification: For each x, we can always find a y such that x² < y + 1 (for example, y = x²).

19. **∃x∀y (x² < y + 1)**  
   - **False**  
   - Counterexample: If we assume x = 0, for every y, it must satisfy 0² < y + 1, which holds, but choosing x very large does not guarantee this holds for all y.

20. **∃x∃y (x² < y + 1)**  
   - **True**  
   - Justification: We can find at least one pair (e.g., x = 0, y = 1) where this statement holds.

### Exercise 54-57: Truth Values
21. **∀x∀y (x² + y² = 9)**  
   - **False**  
   - Counterexample: Choosing x = 0, y = 0 leads to 0² + 0² ≠ 9.

22. **∃x∃y (x² + y² = 9)**  
   - **True**  
   - Justification: (3,0) or (0,3) satisfies this equation.

23. **∃x∀y (x² + y² = 9)**  
   - **False**  
   - Counterexample: If x = 0, the equation y² = 9 must hold for all y, which is not true.

24. **∃x∃y (x² + y² = 9)**  
   - **True**  
   - Justification: Same reasoning as problem 55.

### Exercise 62: Logical Proposition
25. **∀x∀y ((x < y) → (x² < y²))**  
   - **False**  
   - Counterexample: Consider x = -2 and y = -1. We have -2 < -1, but (-2)² = 4 is not less than (-1)² = 1.


---

## Problem 3: Truth Values and Negations

 (a) **∀x∀y (x - y = 7) in ℤ**
- **In words**: "For all integers x and y, x - y is always 7."
- **Truth value**: **False** (This is not always true for all x and y.)
- **Negation**: **∃x∃y (x - y ≠ 7)**  
  ("There exist some integers x and y such that x - y is not 7.")

 (b) **∃x∃y (x - y = 7) in ℤ**
- **In words**: "There exist integers x and y such that x - y = 7."
- **Truth value**: **True** (For example, x = 10 and y = 3 satisfy this equation.)

(c) **∀x∃y (x - y = 7) in ℤ**
- **In words**: "For every integer x, there exists an integer y such that x - y = 7."
- **Truth value**: **True** (For every x, choosing y = x - 7 makes the equation hold.)

 (d) **∃x∀y (x - y = 7) in ℤ**
- **In words**: "There exists an integer x such that for all y, x - y = 7."
- **Truth value**: **False** (If x were fixed, x - y = 7 must hold for all y, which is impossible.)
- **Negation**: **∀x∃y (x - y ≠ 7)**  
  ("For every integer x, there exists an integer y such that x - y is not 7.")

 (e) **∀x∃y (xy = 7) in ℚ**
- **In words**: "For every rational number x, there exists a rational number y such that xy = 7."
- **Truth value**: **False** (For x = 0, there is no y such that 0·y = 7.)
- **Negation**: **∃x∀y (xy ≠ 7)**  
  ("There exists some x such that for all y, xy is not 7.")

 (f) **∀x∃y ((x ≠ 0) → xy = 7) in ℚ**
- **In words**: "For every rational number x, if x ≠ 0, then there exists a rational number y such that xy = 7."
- **Truth value**: **True** (For any x ≠ 0, choosing y = 7/x ensures xy = 7.)

 (g) **∀x∃y (xy = 7) in ℚ - {0}**
- **In words**: "For every nonzero rational number x, there exists a rational number y such that xy = 7."
- **Truth value**: **True** (For any x ≠ 0, choosing y = 7/x satisfies the equation.)

 (h) **∀x∃y (x > y) in ℤ**
- **In words**: "For every integer x, there exists an integer y such that x > y."
- **Truth value**: **True** (For any integer x, choosing y = x - 1 satisfies x > y.)

 (i) **∃y∀x (x ≤ y) in ℤ**
- **In words**: "There exists an integer y such that for all integers x, x ≤ y."
- **Truth value**: **False** (There is no maximum integer.)
- **Negation**: **∀y∃x (x > y)**  
  ("For every integer y, there exists an integer x such that x > y.")


---

Arnav Kucheriya - Spring 2025 - CS 241