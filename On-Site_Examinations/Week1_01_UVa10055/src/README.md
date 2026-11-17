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
```

---

## 5. Fail Code vs Correct Code

### Fail Code
```cpp
#include <bits/stdc++.h>
using namespace std;

// 未完成／有缺陷的初版：32 位元 int 溢位且未取絕對值
int main() {
    int hashmat, opponent;
    while (cin >> hashmat >> opponent) {
        cout << opponent - hashmat << "\n";
    }
    return 0;
}
```

**Why it failed:**
- **直接技術原因：** 有號 32 位元 `int` 在輸入達到 $2^{31}$ 至 $2^{32}$ 時會發生整數溢位；此外當 `hashmat > opponent` 時，`opponent - hashmat` 會輸出負數。
- **會導致錯誤的測資情境：** 輸入 `0 4294967296`（超過 `INT_MAX` 造成溢位）或輸入 `20 10`（錯誤輸出 `-10` 而非 `10`）。

### Correct Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    long long hashmat, opponent;
    while (cin >> hashmat >> opponent) {
        cout << abs(hashmat - opponent) << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 使用 `long long` 確保高達 $2^{32}$ 的輸入與相減結果絕不溢位，且 `abs()` 保證輸出恆為非負整數。
- **如何解決原本失敗的情境：** 輸入 `0 4294967296` 時，`long long` 能精準儲存並輸出 `4294967296`；輸入 `20 10` 時，`abs(20 - 10)` 正確輸出 `10`。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `10 12` | `2` | `2` | 驗證一般 $a < b$ 的標準輸入流程 |
| **Boundary case** | `0 4294967296` | `4294967296` | `4294967296` | 測試上限極值 $2^{32}$ 是否會發生 32 位元溢位 |
| **Edge case** | `100 100` 與 `200 50` | `0` 與 `150` | `0` 與 `150` | 測試兩數相等以及反序輸入（$a > b$） |
| **Stress case** | $10^5$ 組最大上限測資 | 皆輸出精確差值 | 皆輸出精確差值 | 驗證連續讀取至 EOF 的 I/O 效率 |

- **關於先前失敗測資的修正說明：** 將資料型別從 `int` 改為 `long long` 並加上 `abs()` 後，成功解決了 $2^{32}$ 溢位與反序輸入輸出負數的問題。

---

## 7. Difference and Reflection

### Key Differences
| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **Logic** | 直接相減（`opponent - hashmat`） | 計算絕對差值 `abs(hashmat - opponent)` |
| **Edge Cases** | 在 $a > b$ 與數值 $\ge 2^{31}$ 時失敗 | 正確處理 $a > b$、$a = b$ 與高達 $2^{32}$ 的數值 |
| **Output Handling** | 可能輸出負數或溢位亂碼 | 恆輸出正確的非負差值 |
| **Complexity** | 每組 $O(1)$ | 每組 $O(1)$ |
| **Code Quality** | 整數寬度不足，有溢位風險 | 符合題目數值範圍的安全 64 位元型別 |

### Reflection
- **根本原因（Root cause）：** 讀題時忽略了數值上限可達 $2^{32}$ 的條件，且誤以為第一個數字一定小於第二個數字。
- **學到的教訓（Lesson learned）：** 只要題目給定的數值上限達到 $2^{32}$（或超過 $10^9$ 且涉及加減運算），在 C++ 中應一律優先使用 `long long`。
- **下一步行動（Next action）：** 未來解題前先確認輸入數值的最大範圍與正負號保證，再決定變數型別。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10055 - Hashmat the Brave Warrior | Gemini | 協助釐清 32 位元與 64 位元整數溢位邊界，並整理 Code Review Report 格式 | 親自於本地編譯執行、測試所有邊界測資，並上傳 UVa 確認取得 Accepted |

---

## 9. Final Re-review Checklist
- [x] The problem information, source-code links, and submission result are accurate.
- [x] The problem statement and reflection are written in my own words.
- [x] The strategy, pseudocode, and complexity analysis match the final code.
- [x] The fail-code explanation identifies a reproducible failing case or clearly explains what was incomplete.
- [x] The test table includes actual evidence for normal, boundary, and edge cases.
- [x] The AI usage record is complete and accurate.
