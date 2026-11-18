# Code Review Report: UVa 10931 - Parity

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10931
- **Problem Title:** Parity
- **Problem Link:** https://onlinejudge.org/external/109/10931.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期尚未反轉二進位字串順序的未完成草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa10931.cpp](src/UVa10931.cpp)
- **Review Date:** 2026-10-13

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，每一行包含一個正整數 $I$ （ $1 \le I \le 2147483647$ ）。當讀到 `0` 時代表輸入結束，不需要處理或輸出該行結果。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一個正整數 $I$ ，將其轉換為無前導零的二進位表示法 $B$ ，並計算二進位表示中 `1` 的總個數（即題目定義的 Parity 總和 $P$ ），依嚴格格式輸出：
    `The parity of B is P (mod 2).`
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 輸入皆為嚴格正整數（ $I \ge 1$ ），以 `0` 作為終止訊號（Sentinel value）。
  - 輸出字串的英文單字、空格位置以及句尾句點 `.` 必須完全精確（例如 `The parity of 1 is 1 (mod 2).` ）。
  - 二進位字串 $B$ 必須由最高有效位元（MSB）排列至最低有效位元（LSB），不可包含前導零。
- **核心解決任務？（What is the core task you must solve?）**
  - 讀取多筆正整數直到 `0` 為止，將每個整數轉為正確順序的二進位字串並統計位元 `1` 的個數，最後依照指定句型格式化輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 使用標準的「除以 2 取餘數（Repeated division by 2）」將整數 $n$ 轉為二進位：每次取出 `rem = n % 2` ，將 `rem + '0'` 附加至字串 `bin` 尾端；同時若 `rem == 1` 就將計數器 `cnt` 加 1 ，在單一迴圈內同步完成二進位建構與 `1` 的計數。
- **一開始注意到的困難、風險或模糊之處？**
  - 需要注意兩個細節：第一，短除法產生的餘數順序是由最低位（LSB）到最高位（MSB），輸出前必須呼叫 `std::reverse` 反轉字串；第二，輸出格式 `The parity of ... is ... (mod 2).` 包含多個固定單字與括號、句點，必須逐字核對避免漏掉空格或句點。
- **為什麼最初的草稿尚未完整？**
  - 僅有短除法迴圈而未呼叫 `reverse(bin.begin(), bin.end())` 的草稿會輸出反序二進位（例如 `2` 會誤印成 `01` 而非 `10` ），且需補上完整輸出句型與 `n != 0` 終止條件。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `long long n` 搭配 `while (cin >> n && n != 0)` 讀取測資；每組測資初始化 `string bin = "";` 與 `int cnt = 0;` ，進入 `while (n > 0)` 迴圈提取 `rem = n % 2` ，將 `rem + '0'` 接至 `bin` 並在 `rem == 1` 時遞增 `cnt` ，接著將 `n /= 2` ；迴圈結束後呼叫 `reverse(bin.begin(), bin.end())` 還原正確位元順序，最後輸出 `"The parity of " << bin << " is " << cnt << " (mod 2).\n"` 。
- **為什麼這個方法有效？**
  - 由於題目限定輸入為正整數 $I \ge 1$ ，`while (n > 0)` 必定至少執行一次且最後一位餘數必為 `1` ，因此反轉後的字串天然沒有前導零；在同一個迴圈中同步累加 `cnt` 省去二次掃描字串的步驟，且 `long long` 足以安全承載 $2^{31} - 1$ 上限，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 終止輸入 `0` （不輸出任何結果）、最小正整數 `1` （二進位 `1` ，個數 `1` ）、2 的冪次（如 `2` 轉為 `10` ，只有 1 個 `1` ）、全 `1` 數字（如 `7` 轉為 `111` ，共 3 個 `1` ），以及 32 位元整數上限 $2147483647$ （ $2^{31} - 1$ ，共 31 個 `1` ）。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(\log_2 I)$ ，總計 $T$ 組測資為 $O(T \log_2 I)$ 。
- **Space Complexity:** $O(\log_2 I)$ ，用於儲存長度為 $\lfloor \log_2 I \rfloor + 1$ 的二進位字串 `bin` 。
- **Explanation:** 對於上限 $I \le 2^{31} - 1$ ，`while (n > 0)` 最多執行 31 次整數除法與取餘數運算，字串反轉亦僅需 31 次字元交換，執行時間為常數級別。

---

## 4. Pseudocode
```text
START
1. WHILE 成功讀取整數 n 且 n != 0:
2.     初始化空字串 bin = "" 與計數器 cnt = 0
3.     WHILE n > 0:
4.         rem = n % 2
5.         將 (rem + '0') 附加至 bin 尾端
6.         IF rem == 1 THEN
7.             cnt = cnt + 1
8.         END IF
9.         n = n / 2
10.    END WHILE
11.    反轉字串 bin
12.    輸出 "The parity of " + bin + " is " + cnt + " (mod 2)." 並換行
13. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期尚未加入字串反轉與完整句型的草稿)
```cpp
#include <iostream>
#include <string>
using namespace std;

// 撰寫過程中的未完成草稿：短除法收集的位元是由低位到高位，尚未呼叫 reverse 反轉且缺少完整輸出句型
int main() {
    long long n;
    while (cin >> n && n != 0) {
        string bin = "";
        int cnt = 0;
        while (n > 0) {
            int rem = n % 2;
            bin += (rem + '0');
            if (rem == 1) cnt++;
            n /= 2;
        }
        cout << bin << " " << cnt << "\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿建構的 `bin` 為反序二進位（例如輸入 `10` 會得到 `"0101"` 而非 `"1010"` ），且尚未套用題目規定的 `The parity of B is P (mod 2).` 輸出格式；補上 `reverse(bin.begin(), bin.end())` 與精確格式字串後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<string>
#include<algorithm>
using namespace std;
int main()
{
    long long n;
    while (cin >> n && n != 0) {
        string bin = "";
        int cnt = 0;
        while (n > 0) {
            int rem = n % 2;
            bin += (rem + '0');
            if (rem == 1) {
                cnt++;
            }
            n /= 2;
        }
        reverse(bin.begin(), bin.end());
        cout << "The parity of " << bin << " is " << cnt << " (mod 2).\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 在 `while (n > 0)` 迴圈中同步記錄餘數位元與 `1` 的累計次數，利用正整數 $I \ge 1$ 保證最高位必為 `'1'` （自動無前導零），反轉後搭配精確格式字串輸出，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `1` / `2` / `10` / `21` / `0` | `The parity of 1 is 1 (mod 2).` / `The parity of 10 is 1 (mod 2).` / `The parity of 1010 is 2 (mod 2).` / `The parity of 10101 is 3 (mod 2).` | 與預期輸出完全一致 | 驗證官方範例的二進位轉換、 `1` 的個數統計與 `0` 終止條件 |
| **Boundary case** | `1` / `2147483647` / `0` | `The parity of 1 is 1 (mod 2).` / `The parity of 1111111111111111111111111111111 is 31 (mod 2).` | 與預期輸出完全一致 | 測試最小正整數 $I = 1$ 與題目上限 $2^{31} - 1$ （31 個連續 `1` ） |
| **Edge case** | `8` / `15` / `16` / `0` | `The parity of 1000 is 1 (mod 2).` / `The parity of 1111 is 4 (mod 2).` / `The parity of 10000 is 1 (mod 2).` | 與預期輸出完全一致 | 測試 2 的冪次與 $2^k - 1$ 位數進位邊界無前導零誤差 |
| **Stress case** | UVa 官方多筆連續測資 | 全部通過 | Accepted | 驗證程式在官方評測環境下的正確性與執行效率 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 短除法收集反序位元並統計 `1` | 補上 `reverse(bin.begin(), bin.end())` 還原正確二進位順序 |
| **Edge Cases** | 二進位高低位顛倒 | 完整涵蓋 $I = 1$ 、 $2^{31} - 1$ 上限與 `0` 終止條件 |
| **Output Handling** | 僅輸出原始數字與計數 | 嚴格符合 `The parity of B is P (mod 2).` 句型與句尾句點 |
| **Complexity** | $O(\log_2 I)$ （未完成） | $O(\log_2 I)$ per case |
| **Code Quality** | 缺少字串反轉與輸出格式 | 單迴圈同步計數與轉進位、結構簡潔、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在短除法提取 `rem = n % 2` 時直接同步更新 `cnt` ，避免轉換完字串後還需要再寫一個迴圈去數 `'1'` 的個數；同時仔細核對了輸出句型中的空格位置與最後的 `(mod 2).` 句點，使程式一次提交即過關。
- **學到的教訓（Lesson learned）：** 短除法由低位向高位產生數字，反轉（ `reverse` ）是將餘數序列轉為人類閱讀順序的標準步驟；此外，題目指定長句子輸出時，直接複製題目範例字串再替換變數位置，能有效防止拼字或標點符號筆誤。
- **下一步行動（Next action）：** 未來處理進位制轉換與格式化長句輸出題時，維持「單迴圈同步統計 + `reverse` 反轉 + 逐字核對輸出樣板」的開發流程。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10931 - Parity | Gemini | 協助將一次 AC 的短除法同步計數邏輯、邊界案例與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
