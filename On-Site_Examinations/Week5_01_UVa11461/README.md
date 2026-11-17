# Code Review Report: UVa 11461 - Square Numbers

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11461
- **Problem Title:** Square Numbers
- **Problem Link:** https://onlinejudge.org/external/114/11461.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期以迴圈逐一檢查平方數的草稿與最終 $O(1)$ 公式 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa11461.cpp](src/UVa11461.cpp)
- **Review Date:** 2026-10-6

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，每一行包含兩個正整數 $a$ 與 $b$（$0 < a \le b \le 100000$）。當輸入為 `0 0` 時代表測試資料結束，不需要輸出該行結果。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組區間 $[a, b]$，輸出一行單一整數，代表在閉區間 $[a, b]$ 內（包含 $a$ 與 $b$ 本身）總共有幾個「完全平方數」（即可以寫成某個整數平方 $k^2$ 的數）。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 區間端點 $a$ 與 $b$ **皆包含在計算範圍內**（若 $a$ 或 $b$ 本身是完全平方數，必須計入）。
  - 測資組數最多可達 201 組，終止訊號為 `0 0`。
- **核心解決任務？（What is the core task you must solve?）**
  - 計算滿足 $a \le k^2 \le b$ 的正整數 $k$ 的總個數，並持續處理每組區間直到讀到 `0 0`。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 直覺上可以從 $i = a$ 迴圈跑到 $b$，對每個 $i$ 檢查 `sqrt(i)` 是否為整數；或是從 $k = 1$ 開始枚舉 $k^2$ 直到超過 $b$。
- **一開始注意到的困難、風險或模糊之處？**
  - 如果直接用數學不等式推導：$a \le k^2 \le b$ 等價於 $\sqrt{a} \le k \le \sqrt{b}$。因為 $k$ 必須是整數，所以 $k$ 的最小值為 $\lceil \sqrt{a} \rceil$（無條件進位），最大值為 $\lfloor \sqrt{b} \rfloor$（無條件捨去）。這能直接把迴圈化簡為一行 $O(1)$ 公式，但必須確認邊界端點（例如 $a$ 本身剛好是完全平方數，如 $a = 1$ 或 $a = 4$）在 `ceil(sqrt(a))` 下不會多減 1。
- **為什麼最初的草稿尚未完整？**
  - 迴圈逐一判斷每個數字的做法雖然可行但效率較低（每組 $O(b - a)$），且尚未加上 `a == 0 && b == 0` 終止條件。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `while (cin >> a >> b)` 讀取每組區間並檢查 `if (a == 0 && b == 0) break;`；接著利用數學閉式解計算區間內的整數平方根數量：
    $$\text{ans} = \lfloor \sqrt{b} \rfloor - \lceil \sqrt{a} \rceil + 1$$
    在 C++ 中寫成 `int ans = sqrt(b) - ceil(sqrt(a)) + 1;`（利用 `double` 轉 `int` 自動向零截斷相當於 $\lfloor \sqrt{b} \rfloor$）。
- **為什麼這個方法有效？**
  - 滿足 $k^2 \le b$ 的最大正整數為 $\lfloor \sqrt{b} \rfloor$，而滿足 $k^2 \ge a$ 的最小正整數為 $\lceil \sqrt{a} \rceil$。閉區間 $[\lceil \sqrt{a} \rceil, \lfloor \sqrt{b} \rfloor]$ 內的整數總數恰好為「上界 $-$ 下界 $+ 1$」。由於 $b \le 100000$，雙精度浮點數 `double` 的 53 位元尾數精度足以精確表示所有整數平方根而無誤差，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 兩端點皆為完全平方數（如 `[1, 4]`：$\lfloor\sqrt{4}\rfloor - \lceil\sqrt{1}\rceil + 1 = 2 - 1 + 1 = 2$，包含 $1$ 與 $4$）、區間內完全沒有平方數（如 `[2, 3]`：$\lfloor\sqrt{3}\rfloor - \lceil\sqrt{2}\rceil + 1 = 1 - 2 + 1 = 0$）、單點區間（如 `[9, 9]` 輸出 `1`、`[8, 8]` 輸出 `0`），以及題目上限 `[1, 100000]`。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$，總計 $T$ 組測資為 $O(T)$。
- **Space Complexity:** $O(1)$，僅使用三個整數變數 `a, b, ans`。
- **Explanation:** 透過數學公式直接計算區間內整數個數，不需任何迴圈枚舉，每筆測資僅執行一次開根號與加減法即可完成。

---

## 4. Pseudocode
```text
START
1. WHILE 成功讀取兩個整數 a, b:
2.     IF a == 0 AND b == 0 THEN
3.         BREAK (結束程式)
4.     END IF
5.     ans = floor(sqrt(b)) - ceil(sqrt(a)) + 1
6.     輸出 ans 並換行
7. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期以線性迴圈枚舉的未完成草稿)
```cpp
#include <iostream>
#include <cmath>
using namespace std;

// 撰寫過程中的未完成草稿：使用 O(b - a) 迴圈逐一檢查平方數，尚未最佳化為 O(1) 數學公式且缺少 0 0 終止判斷
int main() {
    int a, b;
    cin >> a >> b;
    int count = 0;
    for (int i = a; i <= b; i++) {
        int r = sqrt(i);
        if (r * r == i) count++;
    }
    cout << count << "\n";
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿僅能處理單組測資、缺少 `0 0` 終止條件，且每次都需要從 `a` 跑到 `b` 逐一計算 `sqrt(i)`，效率遠不如直接套用 $\lfloor\sqrt{b}\rfloor - \lceil\sqrt{a}\rceil + 1$ 的 $O(1)$ 閉式解。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<cmath>
using namespace std;
int main()
{
    int a, b;
    while (cin >> a >> b) {
        if (a == 0 && b == 0) {
            break;
        }
        int ans = sqrt(b) - ceil(sqrt(a)) + 1;
        cout << ans << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 將區間計數問題等價轉換為整數區間 $[\lceil\sqrt{a}\rceil, \lfloor\sqrt{b}\rfloor]$ 的長度計算，利用 `sqrt(b)` 轉 `int` 自動向下取整與 `ceil(sqrt(a))` 向上取整，精確包含左右端點平方數並於無平方數時自然得出 `0`，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `1 4` / `1 10` / `0 0` | `2` / `3` | `2` / `3` | 驗證官方範例與端點為平方數時的包含性 |
| **Boundary case** | `1 1` / `1 100000` / `0 0` | `1` / `316` | `1` / `316` | 測試最小值 $a=1$ 與題目最大上限 $b=100000$（$316^2 = 99856$） |
| **Edge case** | `2 3` / `8 8` / `9 9` / `0 0` | `0` / `0` / `1` | `0` / `0` / `1` | 測試區間內完全無平方數（公式得 `0`）以及單點區間情況 |
| **Stress case** | `201` 組 `[1, 100000]` 滿載測資 | 皆在毫秒內輸出 `316` | Accepted | 驗證 $O(1)$ 公式在最大測資組數下的瞬時執行速度 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 逐一檢查 $[a, b]$ 內每個數字是否為平方數 | 直接套用數學公式 $\lfloor\sqrt{b}\rfloor - \lceil\sqrt{a}\rceil + 1$ |
| **Edge Cases** | 缺少多筆迴圈與 `0 0` 結束條件 | 精確處理端點平方數、零個平方數區間與 `0 0` 終止 |
| **Output Handling** | 僅輸出單筆結果 | 持續處理多行輸入直至 `0 0` |
| **Complexity** | $O(b - a)$ per case | $O(1)$ per case |
| **Code Quality** | 暴力迴圈版本 | 數學推導精煉、常數時間複雜度、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 利用不等式轉換將區間內平方數個數化簡為 $\lfloor\sqrt{b}\rfloor - \lceil\sqrt{a}\rceil + 1$，同時特別驗證了「區間內沒有平方數（如 `[2, 3]`）」與「兩端點剛好是平方數（如 `[1, 4]`）」這兩種最容易差一（Off-by-one）的邊界案例，確保公式完全正確。
- **學到的教訓（Lesson learned）：** 遇到詢問「區間 $[a, b]$ 內滿足某單調性質的整數個數」時，先嘗試用上下界取整（`floor` 與 `ceil`）推導閉式解，通常能將時間複雜度從 $O(N)$ 降至 $O(1)$；不過若題目數值上限達到 $10^{18}$ 等級時，則需留意 `double` 浮點數精度限制並改用整數二分搜尋。
- **下一步行動（Next action）：** 未來解數學區間計數題時，優先推導 $\text{upper} - \text{lower} + 1$ 公式，並先以「單點區間」與「空區間」驗證是否會發生 Off-by-one 誤差。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11461 - Square Numbers | Gemini | 協助將一次 AC 的閉式解推導、邊界案例與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
