# Code Review Report: UVa 11727 - Cost Cutting

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11727
- **Problem Title:** Cost Cutting
- **Problem Link:** https://onlinejudge.org/external/117/11727.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (Initial submission: Wrong Answer due to missing space in output format)
- **Source Code (Initial/Fail):** [src/UVa11727_fail.cpp](src/UVa11727_fail.cpp)
- **Source Code (Final/Accepted):** [src/UVa11727.cpp](src/UVa11727.cpp)
- **Review Date:** 2026-9-15

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $T$（ $T < 20$ ），代表測試資料的組數。接下來的 $T$ 行中，每一行都包含三個介於 $1000$ 到 $10000$ 之間且互不相同的正整數，代表三位員工的薪水。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對第 $i$ 組測資（從 $1$ 開始編號），輸出一行 `Case i: X`，其中 `X` 為三位員工中「薪水居於中間值（既不是最高也不是最低）」的那位員工薪水。
- **主要規則與限制條件？（What are the main rules or constraints?）**
  - 題目保證每組的三個薪水數字彼此互不相等（distinct），因此一定存在唯一的中間值。
  - 輸出格式必須嚴格遵守 `Case i: ans`，冒號 `:` 與答案數字之間**必須有一個半形空格**。
- **核心解決任務？（What is the core task you must solve?）**
  - 針對每組測資找出三個相異整數的中位數，並以精確的 `Case i: ans` 格式輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 因為只有三個數字 $a, b, c$ 且題目保證三數互不相等，三個數字的大小排列總共只有 $3! = 6$ 種可能，因此直接透過六個 `if / else if` 分支窮舉所有排列組合，分別指派中間值給 `ans`。
- **一開始注意到的困難、風險或模糊之處？**
  - 在撰寫輸出語句時，寫成了 `cout << "Case " << i << ":" << ans << "\n";`，忘記在冒號 `:` 後面加上一個空格，導致輸出變成 `Case 1:2000` 而非題目規定的 `Case 1: 2000`，首次提交因此收到 **Wrong Answer**。
- **為什麼最初的提交會失敗？**
  - Online Judge 採用嚴格的字元逐字比對，輸出字串中缺少一個半形空格即會導致整份提交被判為 Wrong Answer。

### Final Strategy
- **最終採用什麼方法？**
  - 保留六種排列組合的條件分支邏輯找出三數之中位數 `ans`，並修正輸出語句為 `cout << "Case " << i << ":" << " " << ans << "\n";`，確保冒號後方包含精確的單一空格。
- **為什麼這個方法有效？**
  - 由於題目保證三個薪水數值互不相同（無重複值），嚴格不等式（`<` 與 `>`）的六種排列組合完美涵蓋了所有可能的輸入情況；修正空格格式後輸出字串與標準答案完全一致，順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 三個數字分別位於第一個（ $b < a < c$ 或 $c < a < b$ ）、第二個（ $a < b < c$ 或 $c < b < a$ ）與第三個位置（ $a < c < b$ 或 $b < c < a$ ）的所有 6 種排列，以及最低薪資 $1000$ 與最高薪資 $10000$ 的數值範圍。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$（最多執行 6 個常數次條件判斷），總計 $n$ 組測資為 $O(n)$。
- **Space Complexity:** $O(1)$，僅使用五個整數變數 `n, ans, i, a, b, c`。
- **Explanation:** 在 $T < 20$ 的限制下，每組僅需常數次比較即可完成，時間與空間皆為 $O(1)$。

---

## 4. Pseudocode
```text
START
1. 讀取測資筆數 n
2. FOR i = 1 TO n:
3.     讀取三個相異整數 a, b, c
4.     IF (b < a < c) OR (c < a < b) THEN
5.         ans = a
6.     ELSE IF (a < c < b) OR (b < c < a) THEN
7.         ans = c
8.     ELSE IF (a < b < c) OR (c < b < a) THEN
9.         ans = b
10.    END IF
11.    輸出 "Case " + i + ": " + ans 並換行
12. END FOR
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code (Wrong Answer due to Missing Space after Colon)
```cpp
#include<iostream>
using namespace std;
int main() {
    int n;
    int ans;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a > b && a < c && b < c) {
            ans = a;
        }else if (a < b && a > c && b > c) {
            ans = a;
        }
        else if (a > b && a > c && b < c) {
            ans = c;
        }
        else if (a < b && a < c && b > c) {
            ans = c;
        }
        else if (a < b && a < c && b < c) {
            ans = b;
        }
        else if (a > b && a > c && b > c) {
            ans = b;
        }
        cout << "Case " << i << ":" << ans << "\n";
    }
    return 0;
}
```

**Why it failed:**
- **直接技術原因：** 第 27 行的輸出格式寫成 `cout << "Case " << i << ":" << ans << "\n";`，冒號 `:` 與變數 `ans` 之間**缺少一個半形空格**，導致輸出格式與題目規範不符而判定為 **Wrong Answer**。
- **會導致錯誤的測資情境：** 輸入範例 `1` 與 `1000 2000 3000` 時，程式錯誤輸出 `Case 1:2000`，而預期正確輸出應為 `Case 1: 2000`。

### Correct Code (Accepted)
```cpp
#include<iostream>
using namespace std;
int main() {
    int n;
    int ans;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a > b && a < c && b < c) {
            ans = a;
        }else if (a < b && a > c && b > c) {
            ans = a;
        }
        else if (a > b && a > c && b < c) {
            ans = c;
        }
        else if (a < b && a < c && b > c) {
            ans = c;
        }
        else if (a < b && a < c && b < c) {
            ans = b;
        }
        else if (a > b && a > c && b > c) {
            ans = b;
        }
        cout << "Case " << i << ":" <<" " << ans << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 6 個條件分支完整覆蓋三個相異數字的所有 $3! = 6$ 種大小排列，確保 `ans` 必為三者之中位數；補上 `" "` 後嚴格符合 `Case i: ans` 的輸出格式要求。
- **如何解決原本失敗的情境：** 輸入 `1` 與 `1000 2000 3000` 時，`a < b && a < c && b < c` 成立使 `ans = 2000`，並精確輸出 `Case 1: 2000`。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `3` / `1000 2000 3000` / `3000 2500 1500` / `1500 1200 1800` | `Case 1: 2000` / `Case 2: 2500` / `Case 3: 1500` | `Case 1: 2000` / `Case 2: 2500` / `Case 3: 1500` | 驗證官方範例三組測資與輸出空格格式 |
| **Boundary case** | `2` / `1000 5000 10000` / `10000 1000 5000` | `Case 1: 5000` / `Case 2: 5000` | `Case 1: 5000` / `Case 2: 5000` | 測試薪資上下界（$1000$ 與 $10000$）極值 |
| **Edge case** | `3` / `2000 1000 3000` / `2000 3000 1000` / `3000 1000 2000` | `Case 1: 2000` / `Case 2: 2000` / `Case 3: 2000` | `Case 1: 2000` / `Case 2: 2000` / `Case 3: 2000` | 驗證其餘排列組合皆能正確選出中位數 |
| **Stress case** | `19` 組最大筆數測資 | `Case 1` 至 `Case 19` 皆正確輸出 | Accepted | 驗證在 $T < 20$ 上限下編號 `i` 與格式完全正確 |

- **關於先前失敗測資的修正說明：** 原本所有測資皆因缺少冒號後的空格（輸出 `Case 1:2000`）而導致 Wrong Answer；在輸出語句補上 `" "` 後，所有測資皆通過並取得 Accepted。

---

## 7. Difference and Reflection

### Key Differences
| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **Logic** | 6 種排列窮舉邏輯正確 | 保留相同的 6 種排列中位數判定邏輯 |
| **Edge Cases** | 完整涵蓋 6 種相異數排列 | 完整涵蓋 6 種相異數排列 |
| **Output Handling** | `":" << ans`（漏掉冒號後的空格） | `":" << " " << ans`（精確符合 `Case i: ans`） |
| **Complexity** | $O(n)$ | $O(n)$ |
| **Code Quality** | 輸出字串格式疏失 | 輸出格式精確，可進一步用陣列排序精簡條件式 |

### Reflection
- **根本原因（Root cause）：** 撰寫輸出字串時過於大意，沒注意到 `Case i:` 後面還有一個半形空格，在 UVa 嚴格字元比對下直接造成 Wrong Answer。此外，雖然 6 個 `if-else` 窮舉在三個相異數字下完全正確，但條件式較長（例如 `a > b && a < c && b < c` 中的 `b < c` 其實可由前兩者推導得出），未來也可以透過長度 3 的陣列搭配 `std::sort` 直接取 `arr[1]` 來讓程式碼更簡潔。
- **學到的教訓（Lesson learned）：** 凡是遇到輸出格式包含 `Case #i:` 或特定標點符號的題目，必須逐字核對範例輸出的空格位置與大小寫。
- **下一步行動（Next action）：** 提交前將程式實際輸出與題目 Sample Output 做逐字比對，確認無多餘或遺漏的空白字元。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11727 - Cost Cutting | Gemini | 協助釐清輸出格式空格缺失導致 Wrong Answer 的原因，並整理報告格式 | 親自撰寫原始 C++ 程式碼、補上輸出空格並通過 UVa Accepted 評測 |

---
