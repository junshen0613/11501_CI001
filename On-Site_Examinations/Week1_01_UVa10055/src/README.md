# Code Review Report: UVa 10055 - Hashmat the Brave Warrior

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10055
- **Problem Title:** Hashmat the Brave Warrior
- **Problem Link:** https://onlinejudge.org/external/100/10055.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted
- **Source Code (Initial/Fail):** `src/UVa10055_fail.cpp` (Incomplete initial draft using 32-bit `int`)
- **Source Code (Final/Accepted):** `src/UVa10055.cpp`
- **Review Date:** 2026-11-18

---

## 2. Problem Statement in My Own Words
- **What is the input?**
  - Multiple test cases until End-of-File (EOF). Each line contains two non-negative integers representing the number of soldiers in Hashmat's army and his opponent's army.
- **What is the expected output?**
  - For each pair of integers, print a single integer on a new line representing the absolute difference between the two army sizes.
- **What are the main rules or constraints?**
  - Input integers can be up to $2^{32}$, which exceeds the range of a standard signed 32-bit integer (`int`, max $2^{31}-1$).
  - The input order is not guaranteed to have the smaller number first; Hashmat's army can be larger or smaller than the opponent's.
- **What is the core task you must solve?**
  - Read pairs of large integers continuously until EOF and output $\vert{}a - b\vert{}$ without integer overflow.

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **What was your first idea?**
  - Use `int a, b;` to read two numbers in a `while` loop and print `b - a`.
- **What difficulty, risk, or ambiguity did you notice at the beginning?**
  - First, the problem explicitly states that input numbers are not greater than $2^{32}$, which overflows signed 32-bit `int`. Second, Hashmat's army is not always smaller than the opponent's, so `b - a` can yield a negative value.
- **Why was the initial idea insufficient or inefficient?**
  - Using `int` causes integer overflow (Wrong Answer) on values $\ge 2^{31}$, and omitting `abs()` produces negative results when $a > b$.

### Final Strategy
- **What method did you finally use?**
  - Declared both variables as 64-bit signed integers (`long long`) and used `abs(hashmat - opponent)` inside a `while (cin >> hashmat >> opponent)` loop.
- **Why does this method work?**
  - A signed 64-bit `long long` holds values up to $2^{63}-1 \approx 9.22 \times 10^{18}$, easily accommodating differences up to $2^{32}$ without overflow. `std::abs` handles both $a \le b$ and $a > b$ cases cleanly.
- **What edge cases did you consider?**
  - Maximum boundary values ($0$ and $2^{32}$), equal army sizes ($a = b$), and reversed order ($a > b$).

### Complexity Analysis
- **Time Complexity:** $O(1)$ per test case, $O(T)$ overall for $T$ test cases.
- **Space Complexity:** $O(1)$, using only two 64-bit integer variables.
- **Explanation:** Each line requires a single subtraction and absolute value operation, easily completing well within the 3.0-second time limit.

---

## 4. Pseudocode
```text
START
1. WHILE reading two 64-bit integers (hashmat, opponent) from standard input succeeds:
2.     Compute diff = abs(hashmat - opponent)
3.     Print diff followed by a newline
4. END WHILE
END
