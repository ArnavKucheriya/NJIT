# p1_25f_001_akucheriya.py
# Name: Arnav Kucheriya
# UCID: ak2945
# Section: 005
# Semester: Fall 2025
# Instructor: Marvin Nakayama
#
# NOTE: All function/class names end with the suffix "956".
# This program implements a DFA for the language L described in Project 1:
# Alphabet Σ = {a..z} ∪ {'.', '@'}
# Local part: S1 (letters) optionally followed by repetitions of ('.' + letters)
# exactly one '@'
# Domain: S1 (letters) followed by repetitions of ('.' + letters) and finally
# a top-level domain of either ".net" or ".ne".
#
# The DFA states (q1..q9 plus qT trap) are:
# q1: start (expect first local letter)
# q2: in local letters
# q3: in local after dot (must see a letter)
# q4: after '@' (expect first domain letter)
# q5: in a domain label's letters
# q6: domain after dot
# q7: domain after ".n"
# q8: domain after ".ne"  (ACCEPT if input ends here; otherwise may continue as label)
# q9: domain after ".net" (ACCEPT if input ends here; any more input -> trap)
# qT: trap

from typing import Dict, Tuple, List
import sys

letters = [chr(c) for c in range(ord('a'), ord('z')+1)]
DOT = "."
AT = "@"

state_names = {
    1: "q1",
    2: "q2",
    3: "q3",
    4: "q4",
    5: "q5",
    6: "q6",
    7: "q7",
    8: "q8",
    9: "q9",
    10: "qT",
}

accepting_states = {8, 9}

def build_transitions_956() -> Dict[Tuple[int, str], int]:
    delta: Dict[Tuple[int, str], int] = {}
    alphabet = letters + [DOT, AT]

    # init all to trap
    for s in state_names.keys():
        for ch in alphabet:
            delta[(s, ch)] = 10  # trap

    # q1: start -> letter -> q2
    for a in letters:
        delta[(1, a)] = 2

    # q2: local letters
    for a in letters:
        delta[(2, a)] = 2
    delta[(2, DOT)] = 3
    delta[(2, AT)] = 4

    # q3: local after dot (need letter)
    for a in letters:
        delta[(3, a)] = 2

    # q4: after '@' -> domain first letter
    for a in letters:
        delta[(4, a)] = 5

    # q5: domain label letters
    for a in letters:
        delta[(5, a)] = 5
    delta[(5, DOT)] = 6

    # q6: after domain dot
    for a in letters:
        if a == 'n':
            delta[(6, a)] = 7
        else:
            delta[(6, a)] = 5

    # q7: saw ".n"
    for a in letters:
        if a == 'e':
            delta[(7, a)] = 8
        else:
            delta[(7, a)] = 5
    delta[(7, DOT)] = 10
    delta[(7, AT)] = 10

    # q8: saw ".ne"
    for a in letters:
        if a == 't':
            delta[(8, a)] = 9  # ".net"
        else:
            delta[(8, a)] = 5  # treat ".neX" as just a label, not TLD
    delta[(8, DOT)] = 6
    delta[(8, AT)] = 10

    # q9: saw ".net" (must end)
    for a in letters:
        delta[(9, a)] = 10
    delta[(9, DOT)] = 10
    delta[(9, AT)] = 10

    # qT: remains trap (already set)
    return delta

DELTA = build_transitions_956()

def run_dfa_956(s: str) -> Tuple[bool, List[Tuple[str, str, str]]]:
    curr = 1
    steps: List[Tuple[str, str, str]] = []
    for ch in s:
        to_state = DELTA.get((curr, ch), 10)
        steps.append((state_names[curr], ch, state_names[to_state]))
        curr = to_state
    is_accepted = curr in accepting_states
    return is_accepted, steps

def print_header_956() -> str:
    return "\\n".join([
        "Project 1 for CS 341",
        "Section number: 001",
        "Semester: Fall 2025",
        "Written by: Arnav Kucheriya, akucheri",
        "Instructor: Marvin Nakayama, marvin@njit.edu",
        ""
    ])

def interactive_main_956():
    print(print_header_956())
    try:
        m = int(input("Enter the number of input strings to process (m >= 0): ").strip())
    except Exception:
        print("Invalid integer. Exiting.")
        return
    print(m)
    if m == 0:
        return
    for i in range(1, m+1):
        prompt = f"Enter string {i} of {m}: "
        s = input(prompt)
        print(s)
        accepted, steps = run_dfa_956(s)
        for (frm, sym, to) in steps:
            print(f"{frm} --[{sym}]--> {to}")
        print("ACCEPTED" if accepted else "REJECTED")

def batch_run_testcases_956(input_path: str, output_path: str):
    with open(input_path, "r", encoding="utf-8") as f:
        testcases = [line.strip() for line in f if line.strip() != ""]
    out_lines = []
    out_lines.append(print_header_956())
    out_lines.append(str(len(testcases)))
    for idx, s in enumerate(testcases, start=1):
        out_lines.append(f"Enter string {idx} of {len(testcases)}")
        out_lines.append(s)
        accepted, steps = run_dfa_956(s)
        for (frm, sym, to) in steps:
            out_lines.append(f"{frm} --[{sym}]--> {to}")
        out_lines.append("ACCEPTED" if accepted else "REJECTED")
        out_lines.append("")
    with open(output_path, "w", encoding="utf-8") as f:
        f.write("\\n".join(out_lines))

if __name__ == "__main__":
    if len(sys.argv) >= 2 and sys.argv[1] == "--batch":
        if len(sys.argv) != 4:
            print("Usage: python p1_25f_001_akucheriya.py --batch <Testcases.txt> <output.txt>")
            sys.exit(1)
        batch_run_testcases_956(sys.argv[2], sys.argv[3])
    else:
        interactive_main_956()
