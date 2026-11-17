# Code Review Report: UVa 10055 - Hashmat the Brave Warrior

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10055
- **Problem Title:** Hashmat the Brave Warrior
- **Problem Link:** https://onlinejudge.org/external/100/10055.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted
- **Source Code (Initial/Fail):** `src/UVa10055_fail.cpp`（使用 32 位元 `int` 的未完成初版）
- **Source Code (Final/Accepted):** `src/UVa10055.cpp`
- **Review Date:** 2026-11-18

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多組測試資料直到檔案結尾（EOF）。每一行包含兩個非負整數，分別代表 Hashmat 軍隊與敵方軍隊的士兵人數。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一對整數，輸出一行單一整數，代表兩軍士兵人數的「絕對差值」。
- **主要規則與限制條件？（What are the main rules or constraints?）**
  - 輸入數值最大可達 $2^{32}$，超過標準有號 32 位元整數（`int`，上限為 $2^{31}-1$）的表示範圍。
  - 題目並未保證第一個數字一定小於第二個數字（Hashmat 的軍隊人數可能比敵軍多，也可能比敵軍少）。
- **核心解決任務？（What is the core task you must solve?）**
  - 持續讀取多組大整數直到 EOF，並在避免整數溢位的前提下正確輸出 $\vert{}a - b\vert{}$。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 直接宣告兩個 `int a, b;` 在 `while` 迴圈中讀取，並輸出 `b - a`。
- **一開始注意到的困難、風險或模糊之處？**
  - 第一，題目明確提示輸入數值不超過 $2^{32}$，這會導致有號 32 位元 `int` 發生溢位；第二，Hashmat 的兵力不一定少於對方，直接相減 `b - a` 可能會得到負數。
- **為什麼最初的想法不夠完整或沒有效率？**
  - 使用 `int` 在數值 $\ge 2^{31}$ 時會溢位導致 Wrong Answer，且未使用絕對值 `abs()` 會在 $a > b$ 時輸出負值。

### Final Strategy
- **最終採用什麼方法？**
  - 將變數型別改為 64 位元有號整數（`long long`），並在 `while (cin >> hashmat >> opponent)` 迴圈內使用 `abs(hashmat - opponent)` 計算差值。
- **為什麼這個方法有效？**
  - 64 位元 `long long` 的最大值可達 $2^{63}-1 \approx 9.22 \times 10^{18}$，能完整容納 $2^{32}$ 以內的數值與差值而不溢位；搭配 `std::abs` 可同時正確處理 $a \le b$ 與 $a > b$ 的情況。
- **考慮了哪些邊界條件（Edge cases）？**
  - 數值上下界極值（$0$ 與 $2^{32}$）、兩軍人數相等（$a = b$），以及前後大小反轉（$a > b$）。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$，總計 $T$ 組測資為 $O(T)$。
- **Space Complexity:** $O(1)$，僅使用兩個 64 位元整數變數。
- **Explanation:** 每筆測資只需執行一次減法與取絕對值運算，能遠低於題目 3.0 秒的時間限制完成。

---

## 4. Pseudocode
```text
START
1. WHILE 成功從標準輸入讀取兩個 64 位元整數 (hashmat, opponent):
2.     計算 diff = abs(hashmat - opponent)
3.     輸出 diff 並換行
4. END WHILE
END
