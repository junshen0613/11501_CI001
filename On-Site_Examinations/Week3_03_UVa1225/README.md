# Code Review Report: UVa 1225 - Digit Counting

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 1225
- **Problem Title:** Digit Counting
- **Problem Link:** https://onlinejudge.org/external/12/1225.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期僅處理單一數字拆解的未完成草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa1225.cpp](src/UVa1225.cpp)
- **Review Date:** 2026-9-22

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $M$（ $M \le 20$ ），代表測試資料的組數。接下來的 $M$ 行中，每一行都包含一個正整數 $N$（ $1 < N < 10000$ ）。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組整數 $N$，將 $1$ 到 $N$ 的所有連續正整數寫成一個長字串後，統計 `0` 到 `9` 這十個十進位數字各自出現了幾次，並輸出一行以單一空格分隔的 10 個整數（依序對應 `0` 至 `9` 的出現次數）。
- **主要規則與限制條件？（What are the main rules or constraints?）**
  - 測資組數最多 20 組，且 $N < 10000$（最多為四位數）。
  - 每組測資的統計陣列必須獨立計算，不可殘留上一組測資的計數結果。
  - 輸出每行最後一個數字（`9` 的次數）後方**不可有多餘空格**，必須直接換行。
- **核心解決任務？（What is the core task you must solve?）**
  - 針對每組輸入 $N$，逐一拆解 $1$ 到 $N$ 每個整數的十進位各位數字並累加計數，最後依格式輸出 `0` 至 `9` 的統計結果。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 宣告一個長度為 10 的全域整數陣列 `digi[10]` 來記錄 `0` 到 `9` 的出現次數。對於每個輸入 $N$，從 $i = 1$ 迴圈跑到 $N$，利用 `% 10` 與 `/ 10` 逐位取出數字並執行 `digi[temp % 10]++`。
- **一開始注意到的困難、風險或模糊之處？**
  - 需要注意兩個常見陷阱：第一，多組測資共用全域陣列 `digi[10]` 時，若忘記在每組開始前歸零會導致計數累加錯誤；第二，輸出 10 個數字時若全部寫成 `cout << digi[j] << " ";` 會在行尾多出一個空格，容易造成格式錯誤（Presentation Error / Wrong Answer）。
- **為什麼最初的草稿尚未完整？**
  - 僅針對單一數字 $N$ 拆解各位數的草稿尚未包含從 $1$ 遍歷到 $N$ 的外層迴圈、多筆測資 `while (m--)` 控制，以及每次歸零陣列的初始化步驟。

### Final Strategy
- **最終採用什麼方法？**
  - 在 `while (m--)` 迴圈開頭使用 `memset(digi, 0, sizeof(digi))` 將計數陣列徹底清零；接著以 `for (int i = 1; i <= n; i++)` 遍歷所有數字，內層使用 `while (temp > 0)` 拆解 `temp % 10` 並累加對應計數；輸出時先印出 `cout << digi[0];`，再以迴圈印出 `" " << digi[j]`（ $j = 1 \dots 9$ ）。
- **為什麼這個方法有效？**
  - 由於 $N < 10000$，每個數字最多只有 4 位數，直接逐一模擬拆解每位數字總共最多執行約 $4 \times 10000 = 40000$ 次操作，既簡單直觀又絕不會超時；而「先輸出首項、後續項前置空格」的寫法徹底杜絕了行尾多餘空格問題，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 最小輸入邊界（如 $N = 2$，此時 `0` 的出現次數應為 `0`）、最大輸入上限（ $N = 9999$，最大計數為 $4000$，遠小於 `int` 上限），以及連續多組測資之間的計數器隔離。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(N \log_{10} N)$，總計 $M$ 組測資為 $O(M \cdot N \log_{10} N)$。
- **Space Complexity:** $O(1)$，僅使用固定長度為 10 的整數陣列 `digi[10]`。
- **Explanation:** 在 $M \le 20$ 且 $N < 10000$ 的限制下，總運算次數不超過 $20 \times 10000 \times 4 = 8 \times 10^5$ 次基本操作，可在數毫秒內完成。

---

## 4. Pseudocode
```text
START
1. 讀取測資筆數 m
2. WHILE m > 0 (每次執行後 m 減 1):
3.     將陣列 digi[0..9] 全部初始化為 0
4.     讀取正整數 n
5.     FOR i = 1 TO n:
6.         temp = i
7.         WHILE temp > 0:
8.             digi[temp % 10] = digi[temp % 10] + 1
9.             temp = temp / 10
10.        END WHILE
11.    END FOR
12.    輸出 digi[0]
13.    FOR j = 1 TO 9:
14.        輸出 " " + digi[j]
15.    END FOR
16.    輸出換行符號
17. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期僅拆解單一數字的草稿)
```cpp
#include <iostream>
using namespace std;
int digi[10];

// 撰寫過程中的未完成草稿：僅拆解單一輸入數字 n 的位數，尚未加入 1..n 迴圈、多筆測資重置與無尾隨空格輸出
int main() {
    int n;
    cin >> n;
    while (n > 0) {
        digi[n % 10]++;
        n /= 10;
    }
    for (int j = 0; j <= 9; j++)
        cout << digi[j] << " ";
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿僅統計了單一數字 `n` 本身的位數而非 $1$ 到 $n$ 的所有數字，缺少 `while (m--)` 與 `memset` 陣列歸零步驟，且迴圈輸出會在行尾留下多餘的空格。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include <cstring>
using namespace std;
int digi[10];

int main() {
    int m, n;
    cin >> m;
    while (m--) {
        memset(digi, 0, sizeof(digi));
        cin >> n;
        for (int i = 1; i <= n; i++) {
            int temp = i;
            while (temp > 0) {
                digi[temp % 10]++;
                temp /= 10;
            }
        }
        cout << digi[0];
        for (int j = 1; j <= 9; j++)
            cout << " " << digi[j];
        cout << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 每組測資執行前透過 `memset(digi, 0, sizeof(digi))` 確保初始計數全為 `0`；內層使用暫存變數 `temp = i` 進行 `% 10` 與 `/ 10` 拆解，避免破壞外層迴圈變數 `i`；輸出採首項獨立印出搭配後續前置空格，確保格式百分之百精確，首次提交即獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `2` / `13` / `10` | `1 6 2 2 1 1 1 1 1 1` / `1 2 1 1 1 1 1 1 1 1` | `1 6 2 2 1 1 1 1 1 1` / `1 2 1 1 1 1 1 1 1 1` | 驗證官方範例多組測資與計數陣列重置是否正確 |
| **Boundary case** | `2` / `2` / `9999` | `0 1 1 0 0 0 0 0 0 0` / `2889 4000 4000 4000 4000 4000 4000 4000 4000 4000` | `0 1 1 0 0 0 0 0 0 0` / `2889 4000 4000 4000 4000 4000 4000 4000 4000 4000` | 測試最小邊界 $N=2$（無 `0` 出現）與最大上限 $N=9999$ |
| **Edge case** | `2` / `100` / `10` | `11 21 20 20 20 20 20 20 20 20` / `1 2 1 1 1 1 1 1 1 1` | `11 21 20 20 20 20 20 20 20 20` / `1 2 1 1 1 1 1 1 1 1` | 測試由大數值（`100`）切換到小數值（`10`）時無殘留舊資料 |
| **Stress case** | `20` 組 $N = 9999$ 滿載測資 | 皆輸出精確計數且無尾隨空格 | Accepted | 驗證最大測資規模下的執行速度與輸出格式 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 僅拆解單一數字 `n` | 外層遍歷 `1..n` 並以 `temp` 逐位統計所有數字 |
| **Edge Cases** | 未清空多組測資計數且未保護迴圈變數 | 每組開頭 `memset` 歸零並使用 `temp` 保留 `i` |
| **Output Handling** | `cout << digi[j] << " ";` 會產生行尾多餘空格 | 先印 `digi[0]` 再印 `" " << digi[j]` 完美避免尾隨空格 |
| **Complexity** | 未完成 | $O(M \cdot N \log_{10} N)$ |
| **Code Quality** | 缺少多筆測資與範圍迭代控制 | 結構簡潔、格式精確、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在動手前先估算了時間複雜度（ $N < 10000$ 直接暴力拆位完全足夠），並特別注意兩大常見失誤點：在每組測資開始時用 `memset` 歸零全域陣列，以及採用「首項單獨輸出、其餘項前置空格」的技巧避免行尾多餘空白。
- **學到的教訓（Lesson learned）：** 遇到資料範圍小（如 $N \le 10^4$ ）的計數題時，選擇邏輯最簡單、不易出錯的暴力模擬法，往往比硬寫複雜的數學公式推導更快且更穩健地拿到 AC。
- **下一步行動（Next action）：** 延續「先估算運算量選擇最穩健做法、注意多筆測資陣列歸零與行尾無多餘空格」的習慣解後續題目。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 1225 - Digit Counting | Gemini | 協助將一次 AC 的解題邏輯、邊界條件與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
