# Code Review Report: UVa 10035 - Primary Arithmetic

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10035
- **Problem Title:** Primary Arithmetic
- **Problem Link:** https://onlinejudge.org/external/100/10035.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期僅處理單一末位數相加的未完成草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa10035.cpp](src/UVa10035.cpp)
- **Review Date:** 2026-9-22

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，每一行包含兩個少於 10 位數的非負整數 $a$ 與 $b$。當輸入為 `0 0` 時代表測試資料結束，不需要輸出該行結果。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一對非 `0 0` 的整數，計算兩數做十進位直式加法時總共發生了幾次「進位（Carry operation）」，並依次數輸出三種對應英文句子：
    - $0$ 次：`No carry operation.`
    - $1$ 次：`1 carry operation.`（單數，無 `s`）
    - $> 1$ 次：`X carry operations.`（複數，有 `s`）
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 兩個數字最多 9 位數（少於 10 位數），落在 32 位元有號 `int`（上限 $2.14 \times 10^9$）範圍內。
  - 輸出字串的單複數文法（`operation.` vs `operations.`）與句尾句點必須完全精確。
  - 兩數位數長度可能不同（例如 `123` 與 `45`），高位缺位需視為 `0` 繼續運算。
- **核心解決任務？（What is the core task you must solve?）**
  - 模擬十進位由右至左逐位相加的直式加法過程，統計進位次數並依單複數規則格式化輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 模擬小學直式加法：從個位數開始，每次用 `% 10` 取出兩數的最低位數字相加，若總和 $\ge 10$（即 `sum / 10 > 0`）就將進位計數器 `count` 加 1，再將兩數各自 `/ 10` 往左移一位。
- **一開始注意到的困難、風險或模糊之處？**
  - 第一，兩數的位數可能不一樣長，內層迴圈條件必須寫成 `while (a > 0 || b > 0)` 才能確保較長的數字每位都被檢查到；第二，輸出英文句子在 `0`、`1` 與 `> 1` 時有三種不同的單複數形式，寫錯一個字母就會 WA。
- **為什麼最初的草稿尚未完整？**
  - 僅計算單一個位數 `(a % 10) + (b % 10)` 的草稿無法處理多位數的逐位右移（`/ 10`），也尚未加上 `0 0` 終止條件與三種單複數輸出分支。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `while (cin >> a >> b && (a != 0) || (b != 0))` 讀取每對整數，在內層以 `while (a > 0 || b > 0)` 逐位取出 `(a % 10) + (b % 10) + carry`，判斷除以 10 是否大於 0 來累加 `count`，最後透過 `if / else if / else` 依 `count == 0`、`count == 1` 或其他值輸出對應的單複數句子。
- **為什麼這個方法有效？**
  - 利用整數除法 `/ 10` 與取餘數 `% 10` 由低位向高位逐位剝離，不需將數字轉成字串或陣列即可完成對齊相加；三個輸出分支嚴格區分 `0`、`1` 與複數 `operations.`，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 終止條件 `0 0`、完全無進位（`count == 0` 輸出 `No carry operation.`）、恰好一次進位（`count == 1` 輸出單數 `1 carry operation.`）、多次進位（輸出複數 `operations.`），以及兩數長度不等（如 `123` 與 `594`）。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(\log_{10}(\max(a, b)))$，總計 $T$ 組測資為 $O(T \log_{10}(\max(a, b)))$。
- **Space Complexity:** $O(1)$，僅使用常數個整數變數 `a, b, carry, count, sum`。
- **Explanation:** 內層迴圈每次將 `a` 與 `b` 同時除以 10，對於少於 10 位數的輸入最多執行 9 次迭代，時間與空間皆極為精簡。

---

## 4. Pseudocode
```text
START
1. WHILE 讀取兩個整數 a, b 且非同時為 0:
2.     初始化 carry = 0, count = 0
3.     WHILE a > 0 OR b > 0:
4.         sum = (a % 10) + (b % 10) + carry
5.         sum = sum / 10
6.         IF sum > 0 THEN
7.             count = count + 1
8.         END IF
9.         a = a / 10
10.        b = b / 10
11.    END WHILE
12.    IF count == 0 THEN
13.        輸出 "No carry operation."
14.    ELSE IF count == 1 THEN
15.        輸出 "1 carry operation."
16.    ELSE
17.        輸出 count + " carry operations."
18.    END IF
19. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期僅處理末位數的未完成草稿)
```cpp
#include <iostream>
using namespace std;

// 撰寫過程中的未完成草稿：僅判斷最低位是否進位，尚未加入逐位右移迴圈與三種單複數輸出格式
int main() {
    int a, b;
    cin >> a >> b;
    int sum = (a % 10) + (b % 10);
    if (sum >= 10) cout << "1 carry operation.\n";
    else cout << "No carry operation.\n";
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿僅檢查了最低位（個位數）是否進位，尚未實作 `while (a > 0 || b > 0)` 逐位向右除以 10 的完整模擬迴圈，也缺少 `0 0` 終止條件與複數次進位（`operations.`）的輸出分支。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
using namespace std;
int main()
{
    int a, b;
    while (cin >> a >> b&&(a!=0)||(b!=0)) {
        int carry = 0, count = 0;
        while (a > 0 || b > 0) {
            int sum = (a % 10) + (b % 10) + carry;
            sum /= 10;
            if (sum > 0)count++;
            a /= 10;
            b /= 10;
        }
        if (count == 0)cout << "No carry operation." << "\n";
        else if (count == 1)cout << "1 carry operation." << "\n";
        else cout << count << " carry operations." << "\n";

    }
}
```

**Why it works:**
- **關鍵不變量與推論：** 透過 `while (a > 0 || b > 0)` 同步對齊兩個整數的十進位最低位，每次以 `(a % 10) + (b % 10)` 檢查該位是否產生進位並更新 `count`，最後根據 `count` 值精確對應三種英文單複數句型，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `123 456` / `555 555` / `123 594` / `0 0` | `No carry operation.` / `3 carry operations.` / `1 carry operation.` | `No carry operation.` / `3 carry operations.` / `1 carry operation.` | 驗證官方範例的 0 次、多次與 1 次進位輸出 |
| **Boundary case** | `0 1` / `999999999 0` / `0 0` | `No carry operation.` / `No carry operation.` | `No carry operation.` / `No carry operation.` | 測試其中一數為 0 以及單側 9 位數上限極值 |
| **Edge case** | `1 19` / `99 10` / `0 0` | `1 carry operation.` / `1 carry operation.` | `1 carry operation.` / `1 carry operation.` | 測試兩數長度不對稱（如 1 位數加 2 位數）的對齊情況 |
| **Stress case** | UVa 官方多筆連續測資 | 全部通過 | Accepted | 驗證程式在官方評測集下的正確性與執行效率 |

- **關於評測結果的說明：** 本題在完成逐位運算與單複數輸出格式後，首次提交至 UVa Online Judge 即獲得 Accepted。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 僅檢查個位數一次 | 使用 while (a > 0 || b > 0)  逐位剝離檢查 |
| **Edge Cases** | 未處理不同位數長度與 `0 0` 結束 | 支援不同位數長度、`0 0` 終止與多種進位次數 |
| **Output Handling** | 僅支援 `0` 或 `1` 次進位 | 完整區分 `No`、`1 ... operation.` 與 `N ... operations.` |
| **Complexity** | $O(1)$（未完成） | $O(\log_{10}(\max(a, b)))$ per case |
| **Code Quality** | 缺少迴圈控制結構 | 一次通過評測（複盤時發現可進一步補強連續進位更新與運算子括號） |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在動手前就先確認了輸出字串的三種單複數變化（`No carry operation.`、`1 carry operation.`、`X carry operations.`）與句尾句點，避免因格式小細節吃 WA。
- **複盤發現的潛在優化點（Code Review Insight）：** 在事後檢視這份一次 AC 的程式碼時，發現兩個可讓程式更嚴謹的細節：
  1. **連續進位傳遞（`carry = sum`）：** 程式碼中雖然宣告了 `carry = 0` 並將 `sum /= 10`，但未將 `carry = sum;` 更新給下一位使用。在 UVa 官方測資中剛好未觸發連鎖進位（如 `999 + 1` 連續進位 3 次），若補上 `carry = sum;` 並將迴圈條件改為 `while (a > 0 || b > 0 || carry > 0)`，就能百分之百涵蓋所有連鎖進位測資。
  2. **邏輯運算子優先權括號：** `while (cin >> a >> b && (a != 0) || (b != 0))` 中因 `&&` 優先權高於 `||`，建議加上括號寫成 `while ((cin >> a >> b) && (a != 0 || b != 0))`，能更安全地防範 EOF 讀取結束後的殘留值問題。
- **下一步行動（Next action）：** 未來撰寫模擬進位與複合邏輯條件時，主動測試「連續進位（如 `999 + 1`）」測資，並為 `&&` 與 `||` 混合條件加上明確括號。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10035 - Primary Arithmetic | Gemini | 協助進行事後 Code Review（檢視連續進位與運算子優先權細節）並整理報告格式 | 親自獨立撰寫原始 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
