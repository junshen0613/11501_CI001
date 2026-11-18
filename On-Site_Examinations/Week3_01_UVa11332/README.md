# Code Review Report: UVa 11332 - Summing Digits

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11332
- **Problem Title:** Summing Digits
- **Problem Link:** https://onlinejudge.org/external/113/11332.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期僅執行單次位數拆解的草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa11332.cpp](src/UVa11332.cpp)
- **Review Date:** 2026-9-22

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，每一行包含一個正整數 $n$（ $n \le 2,000,000,000$ ）。當讀取到 `0` 時代表輸入結束，該行不需要處理或輸出。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一個非零正整數 $n$ ，持續將其十進位各位數字相加，直到結果只剩下一位數（即 $< 10$ ），並輸出一行該最終個位數 $g(n)$。
- **主要規則與限制條件？（What are the main rules or constraints?）**
  - 輸入上限達 $2 \times 10^9$（最多 10 位數），以 `0` 作為終止訊號（Sentinel value）。
  - 過程必須反覆執行直到數值嚴格小於 $10$（例如 $47 \rightarrow 4 + 7 = 11 \rightarrow 1 + 1 = 2$）。
- **核心解決任務？（What is the core task you must solve?）**
  - 讀取多筆正整數直到遇到 `0` 為止，並將每個數字反覆進行各位數加總收斂至單一位數後輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 直覺做法是寫兩層迴圈：外層迴圈檢查 `n >= 10`，內層迴圈用 `sum += temp % 10; temp /= 10;` 把所有位數一次加完後再指派回 `n`。
- **一開始注意到的困難、風險或模糊之處？**
  - 進一步觀察發現，其實不需要額外的 `sum` 變數與內層迴圈：每次將個位數 `n % 10` 剝離並直接加到剩餘的高位數 `n / 10` 上，數字的各位數總和保持不變且數值會嚴格遞減，最終一樣會收斂到相同的單一位數。
- **為什麼最初的草稿尚未完整？**
  - 僅執行單次 `(n / 10) + (n % 10)` 的草稿無法處理「相加後仍 $\ge 10$」的多位數（例如 `1234567892` 需多次縮減），且需加上 `n == 0` 終止條件。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `long long n` 讀取輸入，遇到 `if (n == 0) break;` 立即結束程式；接著透過單層迴圈 `while (n >= 10) { n = (n / 10) + (n % 10); }` 反覆將最低位數字加回高位部分，直到 `n < 10` 後輸出結果。
- **為什麼這個方法有效？**
  - 對於任意整數 $n \ge 10$，設 $n = 10q + r$（其中 $q = \lfloor n/10 \rfloor \ge 1$ ， $0 \le r \le 9$ ），則新數值 $n' = q + r$ 嚴格小於原數值 $10q + r$（因為 $9q > 0$），保證迴圈必然有限步終止；同時 $n' \equiv q + r \equiv 10q + r = n \pmod 9$，數位根（Digital Root）完全不變，因此首次提交即直接取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 終止輸入 `0`（不應輸出任何結果）、本身已是個位數的輸入（如 `2`，不進入 `while (n >= 10)` 直接原樣輸出）、相加後恰好等於 `10` 的進位邊界（如 `19` $\rightarrow 1+9=10 \rightarrow 1+0=1$ ），以及最大值 $2,000,000,000$。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(\log_{10} n)$，總計 $T$ 組測資為 $O(T \log_{10} n)$。
- **Space Complexity:** $O(1)$，僅使用單一 `long long` 變數 `n`。
- **Explanation:** 每次迴圈迭代至少將原數字縮減為原本的約十分之一，對於上限 $2 \times 10^9$（10 位數）最多僅需約 10 次整數除法與取餘數運算即可收斂至個位數。

---

## 4. Pseudocode
```text
START
1. WHILE 讀取整數 n 成功:
2.     IF n == 0 THEN
3.         BREAK (結束程式)
4.     END IF
5.     WHILE n >= 10:
6.         n = (n / 10) + (n % 10)
7.     END WHILE
8.     輸出 n 並換行
9. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期僅執行單次縮減的草稿)
```cpp
#include <iostream>
using namespace std;

// 撰寫過程中的未完成草稿：僅執行一次位數拆解相加，尚未包入 while (n >= 10) 與處理輸入 0 終止條件
int main() {
    long long n;
    cin >> n;
    n = (n / 10) + (n % 10);
    cout << n << endl;
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿僅進行單次 `(n / 10) + (n % 10)` 運算，對於三位數以上或相加後仍 $\ge 10$ 的數字無法收斂至個位數，且缺少多筆讀取迴圈與 `n == 0` 終止判斷。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
using namespace std;

int main()
{
    long long n;
    while (cin >> n)
    {
        if (n == 0)
            break;
        while (n >= 10)
        {
            n = (n / 10) + (n % 10);
        }
        cout << n << endl;
    }

    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 每次執行 `n = (n / 10) + (n % 10)` 均保持 $n \pmod 9$ 同餘不變量，且每步使 $n$ 嚴格遞減；搭配 `while (n >= 10)` 與 `if (n == 0) break;`，確保所有測試資料皆精確收斂至數位根並正確終止，首次提交即獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `2` / `11` / `47` / `1234567892` / `0` | `2` / `2` / `2` / `2` | `2` / `2` / `2` / `2` | 驗證官方範例多組數據與 `0` 終止條件 |
| **Boundary case** | `1` / `9` / `10` / `1999999999` / `2000000000` / `0` | `1` / `9` / `1` / `1` / `2` | `1` / `9` / `1` / `1` / `2` | 測試單一位數邊界、進位臨界值 `10` 與題目上限 $2 \times 10^9$ |
| **Edge case** | `19` / `99` / `1000000000` / `0` | `1` / `9` / `1` | `1` / `9` / `1` | 測試多次進位（如 `99 -> 18 -> 9`）與大量尾隨零的情況 |
| **Stress case** | $10^5$ 組接近 $2 \times 10^9$ 的大數測資 | 皆在毫秒內輸出正確個位數 | Accepted | 驗證單層 `while (n >= 10)` 收斂速度與 I/O 效率 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 僅執行單次 `(n / 10) + (n % 10)` | 使用 `while (n >= 10)` 反覆收斂至個位數 |
| **Edge Cases** | 無法處理多位數、個位數原樣輸出與 `0` 終止 | 完整處理 `n == 0` 結束、單一位數與進位邊界 |
| **Output Handling** | 僅處理單筆輸入 | 連續處理多行輸入並在讀到 `0` 時安靜結束 |
| **Complexity** | $O(1)$（未完成） | $O(\log_{10} n)$ per case |
| **Code Quality** | 缺少迴圈與終止條件 | 結構極簡、不需額外變數、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 利用「每次把個位數剝離加進剩餘高位數」的等價轉換，省去額外的內層迴圈與暫存變數，讓程式碼結構既短又不易寫錯；同時使用 `long long` 確保大數讀入安全無虞。
- **學到的教訓（Lesson learned）：** 在實作數位根或位數加總問題時，掌握數學不變量（保持模 9 同餘且嚴格遞減）可以大幅簡化程式結構。
- **下一步行動（Next action）：** 面對數位處理或迴圈收斂題時，持續先確認終止條件（如 Sentinel value `0`）與邊界極值再動手實作。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11332 - Summing Digits | Gemini | 協助將一次 AC 的解題邏輯與時間複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
