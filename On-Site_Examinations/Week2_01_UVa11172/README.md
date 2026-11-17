# Code Review Report: UVa 11172 - Relational Operator

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11172
- **Problem Title:** Relational Operator
- **Problem Link:** https://onlinejudge.org/external/111/11172.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；以下第 5 節對照撰寫過程中的「未完成單筆草稿」與「最終 AC 版本」）
- **Source Code (Final/Accepted):** `src/UVa11172.cpp`
- **Review Date:** 2026-11-18

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $t$（$t < 15$），代表接下來總共有幾組測試資料。接下來的 $t$ 行中，每一行都包含兩個整數 $a$ 與 $b$（$\vert{}a\vert{}, \vert{}b\vert{} < 1000000001$）。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一對整數 $(a, b)$，各自輸出一行對應的關係運算子：若 $a < b$ 輸出 `<`；若 $a > b$ 輸出 `>`；若兩者相等則輸出 `=`。
- **主要規則與限制條件？（What are the main rules or constraints?）**
  - 輸入採用「先給測資筆數 $n$」的格式（而非讀到 EOF 為止）。
  - 數值範圍在 $[-10^9, 10^9]$ 之間，包含負整數與零。
- **核心解決任務？（What is the core task you must solve?）**
  - 依照指定的測資筆數 $n$ 依序讀取每對整數，並透過條件分支判斷兩數大小關係後輸出對應符號。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 先寫出單組整數 $a, b$ 的 `if / else if / else` 大小比較邏輯，確認三個分支的符號輸出正確。
- **一開始注意到的困難、風險或模糊之處？**
  - 需確認兩點：第一，測資數量是由第一行的整數 $n$ 控制，必須先讀取 $n$ 並用迴圈包住單組判斷邏輯；第二，確認 $\vert{}a\vert{}, \vert{}b\vert{} \le 10^9$ 在 32 位元 `int`（上限約 $2.14 \times 10^9$）的安全範圍內。
- **為什麼最初的草稿不夠完整？**
  - 僅有單組 `cin >> a >> b` 的草稿缺少外層的測資計數迴圈，無法處理多筆輸入。

### Final Strategy
- **最終採用什麼方法？**
  - 先讀取測資筆數 `cin >> n;`，接著以 `while (n--)` 執行 $n$ 次迴圈；每次迴圈讀取 `int a, b;`，並使用 `if (a < b)`、`else if (a > b)`、`else` 直接比較兩數大小並輸出對應字元與換行符號 `"\n"`。
- **為什麼這個方法有效？**
  - 有號 32 位元 `int` 足以完整涵蓋 $\pm 10^9$ 範圍，且直接使用 `<` 與 `>` 關係運算子比較兩數大小，不涉及算術加減，完全不會發生整數溢位，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 負數與正數比較、兩個負數比較、兩數相等（包含 `0 0`），以及題目最大上限極值（`-1000000000` 與 `1000000000`）。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$，總計 $n$ 組測資為 $O(n)$。
- **Space Complexity:** $O(1)$，僅使用三個整數變數 $n, a, b$。
- **Explanation:** 每次迭代僅執行兩次整數讀取與最多兩次條件比較，在 $t < 15$ 的限制下瞬間即可完成。

---

## 4. Pseudocode
```text
START
1. 讀取測資筆數 n
2. WHILE n > 0 (每次執行後 n 減 1):
3.     讀取兩個整數 a 與 b
4.     IF a < b THEN
5.         輸出 "<" 並換行
6.     ELSE IF a > b THEN
7.         輸出 ">" 並換行
8.     ELSE
9.         輸出 "=" 並換行
10.    END IF
11. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為補上外層迴圈前的未完成草稿)
```cpp
#include <iostream>
using namespace std;

// 撰寫過程中的未完成初版：僅完成單組比較邏輯，尚未加上讀取測資筆數 n 的 while 迴圈
int main() {
    int a, b;
    cin >> a >> b;
    if (a < b) {
        cout << "<" << "\n";
    }
    else if (a > b) {
        cout << ">" << "\n";
    }
    else{
        cout << "=" << "\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿僅實作了單組 $(a, b)$ 的條件判斷，尚未加入讀取第一行測資筆數 `n` 與重複執行 $n$ 次的控制結構，若直接執行會把第一行的 `n` 誤當成第一組的 `a` 且只輸出一行便結束。

### Correct Code (First Submission Accepted)
```cpp
#include<iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    while (n--) {
        int a, b;
        cin >> a >> b;
        if (a < b) {
            cout << "<" << "\n";
        }
        else if (a > b) {
            cout << ">" << "\n";
        }
        else{
            cout << "=" << "\n";
        }
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 先以 `cin >> n` 讀取測資總數，再透過 `while (n--)` 精準控制迴圈執行 $n$ 次；每次直接使用關係運算子 `<` 與 `>` 比較，確保正負數與極值皆能精確判斷，首次提交即通過所有隱藏測資。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `3` / `10 20` / `20 10` / `10 10` | `<` / `>` / `=` | `<` / `>` / `=` | 驗證官方範例的三種基本大小關係 |
| **Boundary case** | `2` / `-1000000000 1000000000` / `1000000000 -1000000000` | `<` / `>` | `<` / `>` | 測試題目規範的 $\pm 10^9$ 上下界極值 |
| **Edge case** | `3` / `-5 -2` / `0 0` / `-100 0` | `<` / `=` / `<` | `<` / `=` / `<` | 測試負數與負數比較、零值相等的情況 |
| **Stress case** | `14` 組最大上限交錯測資 | 皆輸出正確符號 | 皆輸出正確符號 | 驗證在 $t < 15$ 上限下迴圈次數與輸出完全一致 |

- **關於評測結果的說明：** 本題在完成多筆測資迴圈後首次提交即獲得 Accepted，無需額外修正。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (AC) |
| :--- | :--- | :--- |
| **Logic** | 僅有單組大小比較邏輯 | 加上 `cin >> n` 與 `while (n--)` 完整多筆處理 |
| **Edge Cases** | 無法處理多筆輸入 | 支援正負數、零與 $\pm 10^9$ 邊界值 |
| **Output Handling** | 僅輸出一行結果即結束 | 嚴格對應 $n$ 組輸入逐行輸出 |
| **Complexity** | $O(1)$（未完成） | $O(n)$ |
| **Code Quality** | 缺少外層控制結構 | 結構清晰、一次通過評測 |

### Reflection
- **實作回顧（Root cause / Design choice）：** 撰寫時先確認單筆條件分支正確，再補上外層 `while (n--)` 控制多筆輸入，並確認數值範圍（$\pm 10^9$）未超過 `int` 上限，因此一次就順利 AC。
- **學到的教訓（Lesson learned）：** 先把單筆核心邏輯寫對，再包上符合題目格式的輸入控制迴圈（`while (n--)` 或 `while (cin >> ...)`），是減少低級錯誤的好習慣。
- **下一步行動（Next action）：** 延續「先確認輸入格式與數值範圍、再寫核心邏輯」的步驟解後續題目。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11172 - Relational Operator | Gemini | 協助將一次 AC 的解題邏輯與思考過程整理成符合規範的 Code Review Report 格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
