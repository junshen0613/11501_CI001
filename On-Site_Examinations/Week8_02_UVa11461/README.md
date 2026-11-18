# Code Review Report: UVa 11461 - Square Numbers

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11461
- **Problem Title:** Square Numbers
- **Problem Link:** https://onlinejudge.org/external/114/11461.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (Initial submission: Wrong Answer due to insufficient loop upper bound `i < 100`)
- **Source Code (Initial/Fail):** [src/UVa11461_fail.cpp](src/UVa11461_fail.cpp)
- **Source Code (Final/Accepted):** [src/UVa11461.cpp](src/UVa11461.cpp)
- **Review Date:** 2026-10-27

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，每一行包含兩個正整數 $a$ 與 $b$ （ $0 < a \le b \le 100000$ ）。當輸入為 `0 0` 時代表測試資料結束，不需要輸出該行結果。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組閉區間 $[a, b]$ ，輸出一行單一整數，代表在 $a \le x \le b$ 範圍內（包含 $a$ 與 $b$ 本身）總共有幾個「完全平方數」（即能表示為正整數平方 $i^2$ 的數）。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 區間最大上限為 $b = 100000$ ，由於 $316^2 = 99856 \le 100000 < 317^2 = 100489$ ，合法的平方根底數 $i$ 範圍最高可達 $316$ 。
  - 區間端點 $a$ 與 $b$ 皆包含在內，終止訊號為 `0 0` 。
- **核心解決任務？（What is the core task you must solve?）**
  - 統計滿足 $a \le i^2 \le b$ 的正整數 $i$ 個數，並持續處理每組區間直到讀到 `0 0` 為止。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 為了完全避免浮點數開根號（ `sqrt` ）可能產生的精度誤差，改用純整數枚舉：從 $i = 1$ 開始遞增，直接計算平方值 `i * i` 並判斷是否同時滿足 `i * i >= a` 且 `i * i <= b` ，符合就將計數器 `count` 加 1 。
- **一開始注意到的困難、風險或模糊之處？**
  - 撰寫 `for` 迴圈終止條件時，隨手設定了 `i < 100` ，誤以為平方根底數到 $99$ （ $99^2 = 9801$ ）就足夠；但題目上限是 $b \le 100000$ ，實際上需要檢查到 $\lfloor \sqrt{100000} \rfloor = 316$ ，導致所有大於 $9801$ 的完全平方數全部漏算，首次提交因此收到 **Wrong Answer**。
- **為什麼最初的提交會失敗？**
  - 迴圈上界 `i < 100` 過小，只能涵蓋 $1$ 到 $9801$ 之間的 $99$ 個平方數，當輸入區間包含 $10000$ 至 $100000$ 時會嚴重低估答案。

### Final Strategy
- **最終採用什麼方法？**
  - 將枚舉迴圈的上界放寬至 `i < 1000` （涵蓋平方數範圍最高至 $999^2 = 998001$ ，遠超過題目上限 $100000$ ），在 `while (cin >> a >> b && (a != 0 && b != 0))` 內重置 `int count = 0;` ，依序檢查 `if (i * i >= a && i * i <= b) count++;` 並輸出結果。
- **為什麼這個方法有效？**
  - 在 $1 \le i < 1000$ 範圍內，所有 $i^2$ 均為精確的 32 位元整數（無浮點誤差也無溢位風險），且完整覆蓋題目上限 $100000$ 內全部 $316$ 個完全平方數；每組測資僅執行 $999$ 次整數乘法與比較，因此修正迴圈上界後即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 題目上限 `[1, 100000]` （必須包含 $100^2 = 10000$ 至 $316^2 = 99856$ 共 $316$ 個平方數）、端點本身為平方數（如 `[1, 4]` 輸出 `2` 、 `[99856, 100000]` 輸出 `1` ）、區間內無任何平方數（如 `[2, 3]` 輸出 `0` ），以及終止條件 `0 0` 。

### Complexity Analysis
- **Time Complexity:** 每組測資固定執行 $999$ 次迴圈，即 $O(\sqrt{B_{\max}})$ （常數級別 $O(1)$ ），總計 $T$ 組測資為 $O(T \cdot \sqrt{B_{\max}})$ 。
- **Space Complexity:** $O(1)$ ，僅使用四個整數變數 `a, b, count, i` 。
- **Explanation:** 每組測資僅需固定 $999$ 次整數運算，即使多組測資連續輸入也能在數毫秒內完成。

---

## 4. Pseudocode
```text
START
1. WHILE 成功讀取兩個整數 a, b 且 (a != 0 AND b != 0):
2.     初始化計數器 count = 0
3.     FOR i = 1 TO 999:
4.         IF i * i >= a THEN
5.             IF i * i <= b THEN
6.                 count = count + 1
7.             END IF
8.         END IF
9.     END FOR
10.    輸出 count 並換行
11. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code (Wrong Answer due to Insufficient Loop Upper Bound `i < 100`)
```cpp
#include <iostream>

using namespace std;
int main()
{
    int a, b;
    while (cin >> a >> b && (a != 0 && b != 0)) {
        int count = 0;
        for (int i = 1; i < 100; i++) {
            if (i * i >= a) {
                if (i * i <= b) {
                    count++;
                }
            }
        }
        cout << count << "\n";
    }
    return 0;
}
```

**Why it failed:**
- **直接技術原因：** 第 9 行的迴圈上界設定為 `i < 100` ，僅枚舉到 $99^2 = 9801$ ；然而題目輸入上限為 $b \le 100000$ （對應 $\sqrt{100000} \approx 316.22$ ），導致所有落於 $[10000, 100000]$ 區間內的 $217$ 個完全平方數全部被遺漏，造成 **Wrong Answer**。
- **會導致錯誤的測資情境：** 輸入 `1 100000` 時，程式錯誤輸出 `99` ，而正確答案應為 `316` ；輸入 `10000 10000` 時錯誤輸出 `0` 而非 `1` 。

### Correct Code (Accepted)
```cpp
#include <iostream>

using namespace std;
int main()
{
    int a, b;
    while (cin >> a >> b && (a != 0 && b != 0)) {
        int count = 0;
        for (int i = 1; i < 1000; i++) {
            if (i * i >= a) {
                if (i * i <= b) {
                    count++;
                }
            }
        }
        cout << count << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 將枚舉上界放寬至 `i < 1000` （覆蓋至 $999^2 = 998001 > 100000$ ），確保題目值域內所有可能的完全平方數皆被完整檢查，且純整數乘法完全不存在浮點誤差，修正後即通過 UVa 官方評測獲得 Accepted。
- **如何解決原本失敗的情境：** 輸入 `1 100000` 時，迴圈能完整檢查 $i = 1$ 至 $i = 316$ ，正確統計並輸出 `316` 。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `1 4` / `1 10` / `0 0` | `2` / `3` | `2` / `3` | 驗證官方範例與小範圍區間計算 |
| **Boundary case** | `1 100000` / `10000 10000` / `99856 100000` / `0 0` | `316` / `1` / `1` | `316` / `1` / `1` | 驗證修正 `i < 1000` 後涵蓋 $100^2$ 至 $316^2$ 上限極值（原失敗測資） |
| **Edge case** | `2 3` / `9802 9999` / `0 0` | `0` / `0` | `0` / `0` | 測試區間內完全不含平方數的情況 |
| **Stress case** | `201` 組 `[1, 100000]` 滿載測資 | 皆在毫秒內輸出 `316` | Accepted | 驗證固定 $999$ 次迭代在最大測資組數下的執行效率 |

- **關於先前失敗測資的修正說明：** 首次提交因 `i < 100` 上界不足，導致大於 $9801$ 的平方數全部漏算而拿到 Wrong Answer；將迴圈上界改為 `i < 1000` 後，包含 `[1, 100000]` 在內的所有測資皆正確通過並獲得 Accepted。

---

## 7. Difference and Reflection

### Key Differences
| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **Logic** | `for (int i = 1; i < 100; i++)` （枚舉上限僅到 $99^2 = 9801$ ） | `for (int i = 1; i < 1000; i++)` （枚舉上限達 $999^2 = 998001$ ） |
| **Edge Cases** | 所有包含 $\ge 10000$ 的區間均漏計平方數 | 完整覆蓋 $1$ 至 $100000$ 內全部 $316$ 個平方數 |
| **Output Handling** | 大範圍區間輸出偏小（Wrong Answer） | 所有合法區間輸出完全精確 |
| **Complexity** | $O(T \cdot 100)$ （範圍不足） | $O(T \cdot 1000)$ |
| **Code Quality** | 未依題目最大上限計算對應平方根上界 | 純整數運算零誤差、上界預留充足緩衝、成功 AC |

### Reflection
- **根本原因（Root cause）：** 寫迴圈上界時沒有根據題目給定的最大值 $b \le 100000$ 反推對應的 $\sqrt{b} \approx 316.22$ ，憑直覺寫了 `i < 100` ，導致平方值在 $9801$ 就提早停止檢查。
- **學到的教訓（Lesson learned）：** 使用枚舉法解題時，**必須先計算題目最大測資上限對應的循環次數**（如 $\sqrt{100000} \approx 317$ ），並將迴圈上界設在略大於該值的安全緩衝數（如 `1000` ），同時保持在時間限制與整數不溢位範圍內。
- **下一步行動（Next action）：** 每次撰寫固定次數的枚舉迴圈前，先動筆算出題目最大輸入限制對應的最小必要迴圈上界，並用題目極限值（如 `1 100000` ）作為必測邊界測資。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11461 - Square Numbers | Gemini | 協助分析迴圈上界 `i < 100` 漏算平方數的原因，並整理成標準報告格式 | 親自撰寫原始 C++ 程式碼、修正枚舉上界為 `i < 1000` 並通過 UVa Accepted 評測 |

---
