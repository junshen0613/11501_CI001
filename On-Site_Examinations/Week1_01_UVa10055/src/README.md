# Code Review Report: UVa 10055 - Hashmat the Brave Warrior

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10055
- **Problem Title:** Hashmat the Brave Warrior
- **Problem Link:** https://onlinejudge.org/external/100/10055.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted
- **Source Code (Initial/Fail):** N/A（第一週因大二以上加退選時程尚未加選，未參加現場上機考，此為課後補寫之初版草稿）
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
  - 補寫時最初的草稿想法是宣告兩個 `int a, b;` 在 `while` 迴圈中讀取，並輸出 `b - a`。
- **一開始注意到的困難、風險或模糊之處？**
  - 檢視題目限制後發現輸入數值上限為 $2^{32}$，使用有號 32 位元 `int` 會發生溢位；且 Hashmat 的兵力不一定少於敵方，直接相減 `b - a` 會產生負數。
- **為什麼最初的想法不夠完整或沒有效率？**
  - `int` 型別無法容納 $2^{31}$ 至 $2^{32}$ 的數值，且未取絕對值無法處理 $a > b$ 的輸入順序。

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
// 第一週因加退選尚未入班而缺考；此為課後補寫時最初的未完成草稿（存在 int 溢位與未取絕對值問題）

```

**Why it failed:**
- **未完成／缺陷原因：** 第一週開學時因大二以上加退選時程尚未完成加選，未參加當週現場上機考。
- **會導致錯誤的測資情境：** 。

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

- **關於補寫與測試的說明：** 補寫完成後已於本地端測試上述四類測資，並正式提交至 UVa Online Judge 確認取得 Accepted。

---

## 7. Difference and Reflection

### Key Differences
| Item | Fail Code (Initial Draft) | Correct Code |
| :--- | :--- | :--- |
| **Logic** | 直接相減（`opponent - hashmat`） | 計算絕對差值 `abs(hashmat - opponent)` |
| **Edge Cases** | 在 $a > b$ 與數值 $\ge 2^{31}$ 時失敗 | 正確處理 $a > b$、$a = b$ 與高達 $2^{32}$ 的數值 |
| **Output Handling** | 可能輸出負數或溢位亂碼 | 恆輸出正確的非負差值 |
| **Complexity** | 每組 $O(1)$ | 每組 $O(1)$ |
| **Code Quality** | 整數寬度不足，有溢位風險 | 符合題目數值範圍的安全 64 位元型別 |

### Reflection
- **根本原因（Root cause）：** 第一週因加退選尚未入班而錯過現場練習。
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
