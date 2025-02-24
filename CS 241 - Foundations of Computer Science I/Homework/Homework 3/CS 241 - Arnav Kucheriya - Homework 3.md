Arnav Kucheriya

## Connectives

### 1. Explanation of Theorem 1.1.22 (d), (h), (k)

- **(d) Distributive Law:** $A∩(B∪C)=(A∩B)∪(A∩C)A \cap (B \cup C) = (A \cap B) \cup (A \cap C)$
    
    - This follows because taking the intersection of $AA$ with the union $B∪CB \cup C$ means we consider elements in $AA$ that also belong to either $BB$ or $CC$. This is equivalent to taking the union of the two intersections.
- **(h) De Morgan’s Law:** $¬(A∩B)=¬A∪¬B\neg (A \cap B) = \neg A \cup \neg B$
    
    - The left-hand side represents the complement of the intersection, meaning elements that are missing from at least one of $AA$ or $BB$. This is equivalent to taking the union of the complements.
- **(k) Involution Law:** $¬(¬A)=A\neg (\neg A) = A$
    
    - Applying negation twice restores the original set.

### 2. Conversion of Set Identities to Propositional Logic

- $A∩B→p∧qA \cap B \rightarrow p \land q$
- $A∪B→p∨qA \cup B \rightarrow p \lor q$
- $¬A→¬p\neg A \rightarrow \neg p$
- $U→TU \rightarrow T$
- $∅→F\emptyset \rightarrow F$

Some converted expressions:

- $A∪A=A⇒p∨p=pA \cup A = A \Rightarrow p \lor p = p$
- $A∩A=A⇒p∧p=pA \cap A = A \Rightarrow p \land p = p$
- $¬(¬A)=A⇒¬(¬p)=p\neg(\neg A) = A \Rightarrow \neg(\neg p) = p$

### 3. Applying De Morgan’s Laws to Three Variables

$¬(p1∨p2∨p3)=¬((p1∨p2)∨p3)\neg (p_1 \lor p_2 \lor p_3) = \neg ((p_1 \lor p_2) \lor p_3)$ Applying De Morgan’s Theorem: $=(¬p1∧¬p2)∧¬p3= (\neg p_1 \land \neg p_2) \land \neg p_3$  

Final result: $¬p1∧¬p2∧¬p3\neg p_1 \land \neg p_2 \land \neg p_3$

Similarly, for sets: $¬(A∩B∩C)=¬A∪¬B∪¬C\neg (A \cap B \cap C) = \neg A \cup \neg B \cup \neg C ¬(A∪B∪C)=¬A∩¬B∩¬C\neg (A \cup B \cup C) = \neg A \cap \neg B \cap \neg C$

### 4. Writing Equivalent Expressions Using ${¬,∧}$

- $¬(p∨q)=¬p∧¬q\neg (p \lor q) = \neg p \land \neg q$
- $¬(¬p∨¬q)=p∧q\neg (\neg p \lor \neg q) = p \land q$
- $¬(p∨¬q)=¬p∧q\neg (p \lor \neg q) = \neg p \land q$
- $p∨q=¬(¬p∧¬q)p \lor q = \neg (\neg p \land \neg q)$
- $p∨¬q=¬(¬p∧q)p \lor \neg q = \neg (\neg p \land q)$
- $¬p∨¬q=¬(p∧q)\neg p \lor \neg q = \neg (p \land q)$

### 5. Expressing Logical Connectives Using ${¬,∧,∨}$

- $p→r=¬p∨rp \rightarrow r = \neg p \lor r$
- $¬(p→r)=p∧¬r\neg (p \rightarrow r) = p \land \neg r$
- $p⊕r=(p∧¬r)∨(¬p∧r)p \oplus r = (p \land \neg r) \lor (\neg p \land r)$
- $p⊕(r∧s)=(p∧¬(r∧s))∨(¬p∧(r∧s))p \oplus (r \land s) = (p \land \neg (r \land s)) \lor (\neg p \land (r \land s))$
- $p↔r=(p∧r)∨(¬p∧¬r)p \leftrightarrow r = (p \land r) \lor (\neg p \land \neg r)$

### 6. Proving Functional Completeness Using NOR $(↓)$

- $¬p=p↓p\neg p = p \downarrow p$
- $p∨q=(p↓p)↓(q↓q)p \lor q = (p \downarrow p) \downarrow (q \downarrow q)$
- $p∧q=(p↓q)↓(p↓q)p \land q = (p \downarrow q) \downarrow (p \downarrow q)$

### 7. Proving Functional Completeness of ${¬,∨}$

Using De Morgan’s Laws:

- $¬p=¬p\neg p = \neg p$
- $p∨q=p∨qp \lor q = p \lor q$
- $p∧q=¬(¬p∨¬q)p \land q = \neg (\neg p \lor \neg q)$

### 8. Proving Functional Completeness of ${¬,→}$

Using transformations:

- $¬p=¬p\neg p = \neg p$
- $p∨q=¬(p→¬q)p \lor q = \neg (p \rightarrow \neg q)$
- $p∧q=¬(p→¬q)∨¬(q→¬p)p \land q = \neg (p \rightarrow \neg q) \lor \neg (q \rightarrow \neg p)$

### 9. Functional Completeness of ${¬,⋄}$

Define $p⋄q≡¬(p→q)p \diamond q \equiv \neg (p \rightarrow q):$

- $¬p=p⋄p\neg p = p \diamond p$
- $p∨q=¬(¬p⋄¬q)p \lor q = \neg (\neg p \diamond \neg q)$
- $p∧q=¬((p⋄¬q)⋄(q⋄¬p))p \land q = \neg ((p \diamond \neg q) \diamond (q \diamond \neg p))$

## Normal Forms

### 10. Expressing R3, R4, and Q3 in ${¬,∨,∧}$

- (a) $R3=¬p∧q∧¬rR_3 = \neg p \land q \land \neg r$
- (b) $R4=¬p∧q∧¬rR_4 = \neg p \land q \land \neg r$
- (c) $R4=¬p∧¬q∧¬rR_4 = \neg p \land \neg q \land \neg r$
- (d) $Q3=p∨¬q∨rQ_3 = p \lor \neg q \lor r$
- (e) $Q4=p∨¬q∨¬rQ_4 = p \lor \neg q \lor \neg r$
- (f) $Q8=p∨q∨rQ_8 = p \lor q \lor r$

### 11. Finding the DNF of Logical Expressions

- $p⊕q=(p∧¬q)∨(¬p∧q)p \oplus q = (p \land \neg q) \lor (\neg p \land q)$
- $p↔q=(p∧q)∨(¬p∧¬q)p \leftrightarrow q = (p \land q) \lor (\neg p \land \neg q)$
- $¬(p→q)=p∧¬q\neg (p \rightarrow q) = p \land \neg q$

### 12. Truth Table $R_1$

| p   | q   | r   | R1  | R2  | R3  |
| --- | --- | --- | --- | --- | --- |
| T   | T   | T   | T   | T   | F   |
| T   | T   | F   | F   | T   | T   |
| T   | F   | T   | T   | F   | T   |
| T   | F   | F   | F   | F   | F   |
| F   | T   | T   | T   | T   | T   |
| F   | T   | F   | F   | F   | T   |
| F   | F   | T   | F   | F   | F   |
| F   | F   | F   | F   | T   | F   |

### 13. Finding DNF and CNF of $R_1$

- **DNF**: $R1=(p∧q∧r)∨(p∧¬q∧r)∨(¬p∧q∧r)R_1 = (p \land q \land r) \lor (p \land \neg q \land r) \lor (\neg p \land q \land r)$
- **CNF**: $R1=(p∨q∨r)∧(p∨¬q∨r)∧(¬p∨q∨r)R_1 = (p \lor q \lor r) \land (p \lor \neg q \lor r) \land (\neg p \lor q \lor r)$

### 14. Completing $R_2$ and Finding its CNF

Fill in the values for $R_2$:

- **CNF**: $R2=(p∨q∨r)∧(p∨q∨¬r)∧(¬p∨q∨r)∧(¬p∨¬q∨¬r)R_2 = (p \lor q \lor r) \land (p \lor q \lor \neg r) \land (\neg p \lor q \lor r) \land (\neg p \lor \neg q \lor \neg r)$

### 15. Completing $R_3$ and Finding its DNF

- **DNF**: $R3=(p∧q∧r)∨(p∧q∧¬r)∨(¬p∧q∧r)∨(¬p∧¬q∧¬r)R_3 = (p \land q \land r) \lor (p \land q \land \neg r) \lor (\neg p \land q \land r) \lor (\neg p \land \neg q \land \neg r)$
## Circuit Boolean Expressions

| Circuit | Boolean Expression                                              |
| ------- | --------------------------------------------------------------- |
| D1      | $¬((x1∧x2)∨(x2∧x3))\neg ((x_1 \land x_2) \lor (x_2 \land x_3))$ |
| D2      | $(x2∧x3)∨(x1⊕x2)(x_2 \land x_3) \lor (x_1 \oplus x_2)$          |
| D3      | $¬x1∧¬x2∧¬x3\neg x_1 \land \neg x_2 \land \neg x_3$             |
| D4      | $¬(x3∨(x1⊕x2))\neg (x_3 \lor (x_1 \oplus x_2))$                 |
| D5      | $x1∧x2x_1 \land x_2$                                            |
| D6      | $x1∧(x1∧x2)x_1 \land (x_1 \land x_2)$                           |
| D7      | $x1∧x2x_1 \land x_2$                                            |
| D8      | $x1⊕x2x_1 \oplus x_2$                                           |
| D9      | $x1⊕x2x_1 \oplus x_2$                                           |
| D10     | $(x1⊕x2)∨(x1⊕x2)(x_1 \oplus x_2) \lor (x_1 \oplus x_2)$         |
| D11     | $(x1∧x2)∨(¬x1⊕x2)(x_1 \land x_2) \lor (\neg x_1 \oplus x_2)$    |
| D12     | $(¬x1⊕x2)∨(x1∧x2)(\neg x_1 \oplus x_2) \lor (x_1 \land x_2)$    |
