# Code Review Report: UVa 11388 - GCD LCM

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11388
- **Problem Title:** GCD LCM
- **Problem Link:** https://onlinejudge.org/external/113/11388.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (Initial submission: Wrong Answer due to inverted divisibility condition)
- **Source Code (Initial/Fail):** [src/UVa11388_fail.cpp](src/UVa11388_fail.cpp)
- **Source Code (Final/Accepted):** [src/UVa11388.cpp](src/UVa11388.cpp)
- **Review Date:** 2026-10-6

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $T$（$T \le 100$），代表測試資料的組數。接下來的 $T$ 行中，每一行都包含兩個正整數 $G$ 與 $L$（$1 \le G, L < 2^{31}$）。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組 $(G, L)$，尋找兩個正整數 $a$ 與 $b$（$a \le b$），使得 $\gcd(a, b) = G$ 且 $\text{lcm}(a, b) = L$。若存在多組解，輸出「$a$ 最小」的那一組（以單一空格分隔 `a b`）；若不存在任何滿足條件的正整數對，則輸出 `-1`。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - $G$ 與 $L$ 的上限為 $2^{31}-1$，在 32 位元有號 `int` 範圍內。
  - 若要使數對 $(a, b)$ 存在，因為 $G$ 是 $a, b$ 的因數而 $L$ 是 $a, b$ 的倍數，必然滿足 **$G$ 整除 $L$**（即 $L \bmod G == 0$）。
  - 當 $L \bmod G == 0$ 成立時，直接取 $a = G$、$b = L$ 必為合法解，且因為 $a$ 必須是 $G$ 的正整數倍數（$a \ge G$），$a = G$ 同時也是所有合法解中 $a$ 最小的一組。
- **核心解決任務？（What is the core task you must solve?）**
  - 判斷 $L$ 是否能被 $G$ 整除：若不能整除（`l % g != 0`）則無解輸出 `-1`；若能整除則直接輸出 `g` 與 `l`。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 利用數論性質直接判斷：$G$ 必須是 $L$ 的因數（`l % g == 0`），否則不存在任何正整數對；而當條件成立時，$(G, L)$ 本身就是 $a$ 最小的最佳解（$\gcd(G, L) = G$ 且 $\text{lcm}(G, L) = L$），完全不需要暴力枚舉因數。
- **一開始注意到的困難、風險或模糊之處？**
  - 在撰寫 `if` 條件分支時一時筆誤，把「不能整除才輸出 `-1`（`l % g != 0`）」反寫成「能整除就輸出 `-1`（`l % g == 0`）」，導致所有合法測資與無解測資的輸出結果完全顛倒，首次提交因此收到 **Wrong Answer**。
- **為什麼最初的提交會失敗？**
  - 條件運算子 `==` 與 `!=` 寫反，使得整除時輸出 `-1`、不整除時反而輸出 `g l`，邏輯與題意完全相反。

### Final Strategy
- **最終採用什麼方法？**
  - 將 `void gcd(int a)` 函式內的判斷條件修正為 `if (l % g != 0) cout << -1 << "\n"; else cout << g << " " << l << "\n";`，並於 `main()` 中透過 `if (cin >> t)` 與 `while (t--)` 呼叫函式處理所有測資。
- **為什麼這個方法有效？**
  - 根據最大公因數與最小公倍數的定義，$G \mid a$ 且 $a \mid L \implies G \mid L$。因此 `l % g != 0` 為無解的充要條件；反之若 `l % g == 0`，設 $L = kG$（$k \ge 1$），則 $\gcd(G, kG) = G$ 且 $\text{lcm}(G, kG) = kG = L$，且因 $G \mid a$ 保證任何合法解必有 $a \ge G$，故 `(g, l)` 必為唯一最佳解，修正運算子後即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - $G = L$ 的情況（例如 `3 3`，`3 % 3 == 0` 成立，輸出 `3 3`）、$G = 1$ 的情況（例如 `1 10`，`10 % 1 == 0` 成立，輸出 `1 10`）、$G > L$ 的無解情況（例如 `10 5`，`5 % 10 == 5 != 0`，輸出 `-1`），以及最大上限 $2^{31}-1$。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$，總計 $T$ 組測資為 $O(T)$。
- **Space Complexity:** $O(1)$，僅使用常數個整數變數 `t, g, l`。
- **Explanation:** 每筆測資只需執行一次取餘數運算 `%` 與條件輸出，不需任何循環或質因數分解，在常數時間內即可完成。

---

## 4. Pseudocode
```text
START
1. 讀取測資筆數 t
2. WHILE t > 0 (每次執行後 t 減 1):
3.     讀取兩個正整數 g 與 l
4.     IF l % g != 0 THEN
5.         輸出 -1 並換行
6.     ELSE
7.         輸出 g + " " + l 並換行
8.     END IF
9. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code (Wrong Answer due to Inverted `==` / `!=` Operator)
```cpp
#include <iostream>

using namespace std;
void gcd(int a) {
    int g, l;
    cin >> g >> l;
    if (l % g == 0) {
     cout<<-1<<"\n";
    }
    else {
        cout << g << " " << l << "\n";
    }
}
int main()
{
    int t;
    if (cin >> t) {
        while (t--) {
            gcd(t);
        }
    }
    return 0;
}
```

**Why it failed:**
- **直接技術原因：** 第 7 行的無解判定條件誤寫為 `if (l % g == 0)`，將「整除」與「不整除」的分支完全寫反，導致存在合法解時輸出 `-1`，而無解時反而錯誤輸出 `g l`，造成 **Wrong Answer**。
- **會導致錯誤的測資情境：** 輸入官方範例 `2` / `1 2` / `3 4` 時，程式錯誤輸出 `-1` 與 `3 4`，而正確輸出應為 `1 2` 與 `-1`。

### Correct Code (Accepted)
```cpp
#include <iostream>

using namespace std;
void gcd(int a) {
    int g, l;
    cin >> g >> l;
    if (l % g != 0) {
     cout<<-1<<"\n";
    }
    else {
        cout << g << " " << l << "\n";
    }
}
int main()
{
    int t;
    if (cin >> t) {
        while (t--) {
            gcd(t);
        }
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 透過 `l % g != 0` 精確過濾所有 $G \nmid L$ 的無解測資；當 $G \mid L$ 成立時，直接利用最小合法解性質輸出 $a = G, b = L$，不需任何額外乘除法（也完全避開 $G \times L$ 溢位風險），修正後即通過 UVa 官方評測獲得 Accepted。
- **如何解決原本失敗的情境：** 輸入 `1 2` 時 `2 % 1 == 0` 進入 `else` 正確輸出 `1 2`；輸入 `3 4` 時 `4 % 3 == 1 != 0` 命中 `if` 正確輸出 `-1`。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `2` / `1 2` / `3 4` | `1 2` / `-1` | `1 2` / `-1` | 驗證官方範例的合法解與無解輸出（修正原版完全相反的錯誤） |
| **Boundary case** | `2` / `5 5` / `2147483647 2147483647` | `5 5` / `2147483647 2147483647` | `5 5` / `2147483647 2147483647` | 測試 $G = L$ 相等邊界與 32 位元 `int` 上限 $2^{31}-1$ |
| **Edge case** | `2` / `10 5` / `6 9` | `-1` / `-1` | `-1` / `-1` | 測試 $G > L$ 以及兩數有公因數但互不整除的無解情況 |
| **Stress case** | `100` 組最大測資 | 皆在毫秒內輸出精確結果 | Accepted | 驗證 $T \le 100$ 上限下的執行速度與穩定性 |

- **關於先前失敗測資的修正說明：** 首次提交因 `l % g == 0` 條件寫反導致所有測資輸出完全顛倒而拿到 Wrong Answer；將運算子改為 `l % g != 0` 後，所有測資皆正確通過並獲得 Accepted。

---

## 7. Difference and Reflection

### Key Differences
| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **Logic** | `if (l % g == 0)`（將無解條件寫反） | `if (l % g != 0)`（正確判定 $G$ 無法整除 $L$ 時無解） |
| **Edge Cases** | 所有合法與無解測資輸出完全顛倒 | 正確處理 $G = L$、$G > L$ 與 $2^{31}-1$ 極值 |
| **Output Handling** | 合法時輸出 `-1`、無解時輸出 `g l` | 無解時輸出 `-1`、合法時輸出 `g l` |
| **Complexity** | $O(T)$ | $O(T)$ |
| **Code Quality** | 條件運算子筆誤 | 數學推導精簡、無乘法溢位風險、成功 AC |

### Reflection
- **根本原因（Root cause）：** 在寫 `if` 判斷「無解輸出 `-1`」時，心裡想著整除條件 `l % g == 0` 就順手打了 `==`，沒有再次核對該分支對應的動作是輸出 `-1` 還是輸出 `g l`。
- **學到的教訓（Lesson learned）：** 每當寫出 `if (cond) cout << -1;` 這類「異常／無解提早處理」的分支時，務必在腦中代一組最簡單的具體數字（例如 `1 2` 與 `3 4`）順一遍真假值方向，能百分之百避免條件寫反的低級失誤。
- **下一步行動（Next action）：** 提交程式碼前一定先跑過題目提供的 Sample Input，確認輸出與 Sample Output 完全一致再送出評測。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11388 - GCD LCM | Gemini | 協助分析 `l % g == 0` 與 `!=` 條件反轉導致 Wrong Answer 的原因，並整理報告格式 | 親自撰寫原始 C++ 程式碼、修正條件運算子並通過 UVa Accepted 評測 |

---
