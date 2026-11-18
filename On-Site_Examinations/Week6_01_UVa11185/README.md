# Code Review Report: UVa 11185 - Ternary

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11185
- **Problem Title:** Ternary
- **Problem Link:** https://onlinejudge.org/external/111/11185.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期未特判 `n == 0` 邊界情況的未完成草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa11185.cpp](src/UVa11185.cpp)
- **Review Date:** 2026-10-13

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，每一行包含一個十進位整數 $N$ （測資最多 100 行）。當讀到任何負整數（ $N < 0$ ）時代表輸入結束，不需要處理或輸出該行結果。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一個非負十進位整數 $N$ （ $N \ge 0$ ），將其轉換為三進位（Base-3）表示法（僅由字元 `0` 、 `1` 、 `2` 組成），並輸出一行該三進位字串（不可有多餘的前導零，但 `0` 本身應輸出 `"0"` ）。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 終止條件為「任意負數（ `n < 0` ）」，而不僅限於 `-1` ，因此外層條件必須寫成 `n >= 0` 。
  - 輸入數值為非負整數，使用 64 位元 `long long` 可確保大數讀入與除法運算完全不會溢位。
  - 當輸入為 `0` 時，必須明確輸出 `"0"` ，不能輸出空行。
- **核心解決任務？（What is the core task you must solve?）**
  - 持續讀取非負十進位整數直到遇到負數為止，透過重複除以 3 取餘數的方式將其轉換為三進位字串並輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 採用標準的進位制轉換「短除法（Repeated division by 3）」：當 $n > 0$ 時，反覆計算 `n % 3` 得到由低位到高位的三進位數字，轉換成字元 `(n % 3) + '0'` 接在字串尾端，再將 `n /= 3` ，最後將整個字串反轉（ `reverse` ）即可。
- **一開始注意到的困難、風險或模糊之處？**
  - 有兩個常見的邊界陷阱必須事先防範：第一，若輸入為 `0` ，直接進入 `while (n > 0)` 會完全不執行任何迭代，導致 `ternary` 維持空字串 `""` 而輸出空行；第二，題目規定「遇到任何負數即結束」，因此迴圈判斷條件應寫為 `n >= 0` 而非 `n != -1` 。
- **為什麼最初的草稿尚未完整？**
  - 僅有 `while (n > 0)` 短除法主體的草稿在輸入 `0` 時會輸出空行，導致格式錯誤（Wrong Answer）。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `long long n` 搭配 `while (cin >> n && n >= 0)` 讀取測資；一進入迴圈先以 `if (n == 0) { cout << "0\n"; continue; }` 獨立處理零值情況；對於正整數則透過 `while (n > 0)` 將 `n % 3 + '0'` 依序加入 `string ternary` ，最後呼叫 `std::reverse(ternary.begin(), ternary.end())` 反轉字串並輸出。
- **為什麼這個方法有效？**
  - 根據進位制展開定理，任何正整數 $N = \sum_{k=0}^{m} d_k \cdot 3^k$ （ $d_k \in \{0, 1, 2\}$ ），每次對 $N$ 取模 3 必得最低位係數 $d_0$ ，整除 3 則使係數右移一位；搭配 `n == 0` 特判與字串反轉，所有非負整數皆能得到無前導零的唯一三進位表示，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 輸入為 `0` （獨立特判輸出 `"0"` ）、單一位數三進位（ `1` 與 `2` ）、進位臨界值（ `3` 輸出 `"10"` 、 `8` 輸出 `"22"` 、 `9` 輸出 `"100"` ），以及以 `-1` 或任意負數（如 `-5` ）作為輸入結尾。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(\log_3 N)$ ，總計 $T$ 組測資為 $O(T \log_3 N)$ 。
- **Space Complexity:** $O(\log_3 N)$ ，用於儲存轉換後長度為 $\lfloor \log_3 N \rfloor + 1$ 的三進位字串 `ternary` 。
- **Explanation:** 每次迴圈迭代將 $N$ 除以 3 ，即使對於 64 位元整數上限（約 $9 \times 10^{18}$ ），最多也僅需執行約 40 次除法與字元附加，反轉字串亦為線性時間，執行速度極快。

---

## 4. Pseudocode
```text
START
1. WHILE 成功讀取整數 n 且 n >= 0:
2.     IF n == 0 THEN
3.         輸出 "0" 並換行
4.         CONTINUE (處理下一筆測資)
5.     END IF
6.     初始化空字串 ternary = ""
7.     WHILE n > 0:
8.         將 (n % 3 + '0') 附加至 ternary 尾端
9.         n = n / 3
10.    END WHILE
11.    反轉字串 ternary
12.    輸出 ternary 並換行
13. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期未特判 `n == 0` 的未完成草稿)
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 撰寫過程中的未完成草稿：缺少 n == 0 的特判，當輸入為 0 時會跳過 while (n > 0) 而輸出空行
int main() {
    long long n;
    while (cin >> n && n >= 0) {
        string ternary = "";
        while (n > 0) {
            ternary += (n % 3 + '0');
            n /= 3;
        }
        reverse(ternary.begin(), ternary.end());
        cout << ternary << "\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿未對 `n == 0` 做前置特判，遇到輸入 `0` 時 `while (n > 0)` 條件為假，會直接印出空字串而非 `"0"` ；補上 `if (n == 0) { cout << "0\n"; continue; }` 後首次提交即直接通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
    long long n;
    while (cin >> n && n >= 0) {
        if (n == 0) {
            cout << "0\n";
            continue;
        }
        string ternary = "";
        while (n > 0) {
            ternary += (n%3 + '0');
            n /= 3;
        }
        reverse(ternary.begin(), ternary.end());
        cout << ternary << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 透過 `n >= 0` 精確攔截所有負數終止條件，以 `if (n == 0)` 確保零值輸出正確，並利用短除法與 `reverse` 由低位至高位建構三進位字串，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `10` / `100` / `1000` / `-1` | `101` / `10201` / `1101001` | `101` / `10201` / `1101001` | 驗證官方範例的十進位轉三進位結果與 `-1` 終止條件 |
| **Boundary case** | `0` / `1` / `2` / `3` / `-1` | `0` / `1` / `2` / `10` | `0` / `1` / `2` / `10` | 測試零值特判、單一位數上限與首次進位臨界值 `3` |
| **Edge case** | `8` / `9` / `27` / `-99` | `22` / `100` / `1000` | `22` / `100` / `1000` | 測試多位連續進位（ $3^k - 1 \rightarrow 3^k$ ）與非 `-1` 的負數終止 |
| **Stress case** | `100` 組包含 $10^{12}$ 等級大數之測資 | 皆在毫秒內輸出正確三進位字串 | Accepted | 驗證 `long long` 與 $O(\log_3 N)$ 字串建構的效能與正確性 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 直接進入 `while (n > 0)` 短除法 | 加入 `if (n == 0)` 特判後執行短除法與 `reverse` |
| **Edge Cases** | 輸入 `0` 時會輸出空行 | 完整涵蓋 `n == 0` 、三的冪次進位與任意負數終止 |
| **Output Handling** | 對 `0` 無法輸出字元 `'0'` | 精確輸出無前導零的三進位字串 |
| **Complexity** | $O(\log_3 N)$ （未完成） | $O(\log_3 N)$ per case |
| **Code Quality** | 缺少零值邊界檢查 | 型別安全（ `long long` ）、邊界完備、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在動手寫進位制轉換時，第一時間就記得「 `0` 在 `while (n > 0)` 短除法中是特殊邊界，必須單獨特判輸出 `"0"` 」，同時將終止條件寫成 `n >= 0` 而非寫死 `n != -1` ，並選用 `long long` 預防大數溢位。
- **學到的教訓（Lesson learned）：** 所有利用 `while (n > 0)` 逐位拆解數字（不論十進位、二進位、三進位或十六進位）的題目，只要輸入允許 `0` ，都必須在迴圈前額外處理 `n == 0` 的特例。
- **下一步行動（Next action）：** 未來遇到任何進位制轉換或位數拆解題時，固定檢查三件事：「 `n == 0` 特判、負數／EOF 終止條件、數值上限是否需用 `long long` 」。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11185 - Ternary | Gemini | 協助將一次 AC 的進位制轉換原理、零值邊界分析與複雜度整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
