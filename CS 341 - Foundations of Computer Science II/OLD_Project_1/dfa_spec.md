# DFA Specification for L

Let Σ = Ψ ∪ Π ∪ Φ where Ψ = {a..z}, Π = {'.'}, Φ = {'@'}.
The DFA states are Q = {q1, q2, q3, q4, q5, q6, q7, q8, q9, qT} with start state q1 and trap qT.

Accepting states F = {q8, q9} (only if the input ends in these states).

Intuition:
- Local part is `S1 ( S2 )*` where `S1 = letters+`, `S2 = '.' letters+`.
- Exactly one '@'.
- Domain is `S1 ( S2 )* ('.net' ∪ '.ne')`.

## Transition Summary
- q1 --[letter]--> q2
- q2 --[letter]--> q2 ; q2 --[.]--> q3 ; q2 --[@]--> q4
- q3 --[letter]--> q2
- q4 --[letter]--> q5
- q5 --[letter]--> q5 ; q5 --[.]--> q6
- q6 --[n]--> q7 ; q6 --[letter≠n]--> q5
- q7 --[e]--> q8 ; q7 --[letter≠e]--> q5
- q8 --[t]--> q9 ; q8 --[letter≠t]--> q5 ; q8 --[.]--> q6
- q9 --[any]--> qT

All other unspecified transitions go to qT and remain there.

This DFA recognizes exactly L = L1 ∪ L2 as defined in the project: local/doms of letters and dots, an '@', and a domain ending exactly with `.net` or `.ne`.
