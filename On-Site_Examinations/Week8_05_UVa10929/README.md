# Code Review Report: UVa 10929 - You can say 11

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10929
- **Problem Title:** You can say 11
- **Problem Link:** https://onlinejudge.org/external/109/10929.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期試圖使用 `long long` 進行一般取餘數運算的未完成草稿與最終字串奇偶位差 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa10929.cpp](src/UVa10929.cpp)
- **Review Date:** 2026-10-27

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，每一行包含一個正整數 $N$ ，其位數最多可達 $1000$ 位數（即 $N < 10^{1000}$ ）。當輸入為單獨一個 `"0"` 時代表測試資料結束，不需要處理或輸出該行結果。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組非 `"0"` 的整數，判斷該數是否為 $11$ 的倍數，並依格式輸出：
    - 若是 $11$ 的倍數：`N is a multiple of 11.`
    - 若不是 $11$ 的倍數：`N is not a multiple of 11.`
    其中 `N` 必須與輸入的原始數字字串完全一致。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 輸入數值高達 $1000$ 位數，遠超過 64 位元整數 `long long` （上限約 $9 \times 10^{18}$ ，僅 19 位數）的儲存範圍，必須以字串（ `string` ）處理。
  - 部分測資可能包含前導零（例如 `0011` 或 `0121` ），輸出時必須原封不動印出輸入時的原始字串 `s` ，不可自行刪除前導零；同時終止條件僅限於字串嚴格等於 `"0"` 。
- **核心解決任務？（What is the core task you must solve?）**
  - 以字串讀取大整數直到遇到 `"0"` 為止，計算奇數位與偶數位的數字總和之差是否能被 $11$ 整除，並依指定句型輸出結果。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 一般判斷整數是否為 $11$ 的倍數只需寫 `n % 11 == 0` ，但本題數字高達 $1000$ 位數，無法用內建整數型別讀入；因此改用 `string s` 讀入每個數字字元，並套用數論中的「 $11$ 的倍數判別法」：因為 $10 \equiv -1 \pmod{11}$ ，故 $10^k \equiv (-1)^k \pmod{11}$ ，一個大數能被 $11$ 整除，若且唯若「奇數位數字和」與「偶數位數字和」的差值為 $11$ 的倍數。
- **一開始注意到的困難、風險或模糊之處？**
  - 需要注意三個關鍵細節：第一，字串的字元 `'0'` ～ `'9'` 必須減去 `'0'` 轉為數值（ `s[i] - '0'` ）才能累加，否則會加到 ASCII 碼；第二，部分測資帶有前導零（例如 `00011` ），使用 `cin >> s` 讀入並直接輸出原字串 `s` 既能保留前導零，也能防止誤觸發 `s != "0"` 的終止條件；第三，單獨的 `"0"` 必須作為終止訊號跳出迴圈，不可當成 $0$ 是 $11$ 的倍數而輸出。
- **為什麼最初的草稿尚未完整？**
  - 使用 `long long n` 直接執行 `n % 11 == 0` 的草稿在超過 19 位數的測資會立刻溢位並導致讀取失敗（Wrong Answer）。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `string s` 搭配 `while (cin >> s && s != "0")` 讀取測資；每組初始化 `int odd = 0, even = 0;` ，遍歷字串索引 `i = 0` 到 `s.length() - 1` ，依 `i % 2 == 0` 與 `else` 分別將 `s[i] - '0'` 累加至 `odd` 與 `even` ；最後判斷 `if (abs(odd - even) % 11 == 0)` 輸出 `s << " is a multiple of 11.\n"` ，否則輸出 `s << " is not a multiple of 11.\n"` 。
- **為什麼這個方法有效？**
  - 根據同餘性質 $\sum_{i=0}^{L-1} d_i \cdot 10^{L-1-i} \equiv \pm \sum_{i=0}^{L-1} (-1)^i d_i \pmod{11}$ ，奇偶索引數字和之差 `abs(odd - even)` 與原大數模 $11$ 同餘（或互為相反數），故 `abs(odd - even) % 11 == 0` 為 $11$ 倍數的充要條件；即使 $1000$ 位全為 `'9'` ，總和上限也僅為 $9000$ ，在 `int` 範圍內絕對安全，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 終止條件 `"0"` （不輸出任何結果）、帶有前導零的合法數字（如 `00` 、 `011` 、 `000121` ，均為 $11$ 的倍數且原樣輸出前導零）、奇偶位總和相等（差值為 `0` ， `0 % 11 == 0` 成立，例如 `11` 或 `1221` ），以及接近 $1000$ 位數的超大整數。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(L)$ （ $L$ 為數字位數， $L \le 1000$ ），總計 $T$ 組測資為 $O(T \cdot L)$ 。
- **Space Complexity:** $O(L)$ ，僅使用長度為 $L$ 的 `string s` 與常數個計數變數。
- **Explanation:** 每筆測資僅需單趟線性掃描字串並累加奇偶位數字，對於最多 $1000$ 位數的輸入在微秒級時間內即可完成。

---

## 4. Pseudocode
```text
START
1. WHILE 成功讀取字串 s 且 s != "0":
2.     初始化 odd = 0, even = 0
3.     FOR i = 0 TO s.length() - 1:
4.         IF i % 2 == 0 THEN
5.             odd = odd + (s[i] - '0')
6.         ELSE
7.             even = even + (s[i] - '0')
8.         END IF
9.     END FOR
10.    IF abs(odd - even) % 11 == 0 THEN
11.        輸出 s + " is a multiple of 11." 並換行
12.    ELSE
13.        輸出 s + " is not a multiple of 11." 並換行
14.    END IF
15. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期試圖用整數型別直接取模的未完成草稿)
```cpp
#include <iostream>
using namespace std;

// 撰寫過程中的未完成草稿：使用 long long 讀入並直接執行 n % 11，遇到超過 19 位數（題目上限 1000 位）會嚴重溢位
int main() {
    long long n;
    while (cin >> n && n != 0) {
        if (n % 11 == 0) cout << n << " is a multiple of 11.\n";
        else cout << n << " is not a multiple of 11.\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿受限於 `long long` 最多只能容納約 $9.22 \times 10^{18}$ （19 位數），面對題目高達 $1000$ 位數的大整數會發生整數溢位（Input stream failure），且會自動吃掉測資中的前導零；改用 `string s` 搭配奇偶位數字和差值取模後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s;
    while (cin >> s&&s!="0") {
        int odd = 0, even = 0;
        for (int i = 0; i < s.length(); i++) {
            if (i % 2 == 0) {
                odd+=s[i]-'0';
            }
            else {
                even+=s[i]-'0';
            }
        }
        if (abs(odd - even) % 11==0) {
            cout << s << " is a multiple of 11.\n";
        }
        else {
            cout << s << " is not a multiple of 11.\n";
        }
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 透過 `string s` 完整保留大數的每一位數字與前導零，並利用 $10^k \equiv (-1)^k \pmod{11}$ 的同餘性質將大數整除問題化簡為奇偶索引數字和之差的絕對值對 $11$ 取模，徹底避開大數溢位問題，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `112233` / `30800` / `2937` / `323455693` / `5038297` / `112234` / `0` | 前五組輸出 `... is a multiple of 11.` 、最後一組輸出 `... is not a multiple of 11.` | 與預期輸出完全一致 | 驗證官方範例多組大整數的 $11$ 倍數判斷與 `"0"` 終止條件 |
| **Boundary case** | `1` / `11` / `00` / `0` | `1 is not a multiple of 11.` / `11 is a multiple of 11.` / `00 is a multiple of 11.` | 與預期輸出完全一致 | 測試最小單位數、最小正倍數 `11` 以及 `"00"` 不誤觸發 `"0"` 終止 |
| **Edge case** | `000121` / `918273645546372819` / `0` | `000121 is a multiple of 11.` / `918273645546372819 is a multiple of 11.` | 與預期輸出完全一致 | 測試帶前導零的輸入原樣輸出以及超過 `long long` 範圍的大數 |
| **Stress case** | 包含 $1000$ 位數的超大整數測資 | 皆在毫秒內精確判斷並原樣輸出千位數字 | Accepted | 驗證 $1000$ 位數上限下的線性掃描效能與零溢位安全性 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 使用 `long long` 直接執行 `n % 11` | 使用 `string` 讀入並計算奇偶位數字和之差模 $11$ |
| **Edge Cases** | 超過 19 位數即溢位，且遺失前導零 | 完整支援 $1000$ 位大數、前導零原樣保留與 `"0"` 終止 |
| **Output Handling** | 無法原樣輸出帶前導零的測資 | 精確輸出原字串 `s` 搭配 `is (not) a multiple of 11.` |
| **Complexity** | 無法處理大數（未完成） | $O(T \cdot L)$ 時間、 $O(L)$ 空間 |
| **Code Quality** | 受限於原生整數型別位寬 | 善用數論同餘性質與字串處理、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在看題目限制時第一時間注意到「最多 $1000$ 位數」，立刻排除 `int` 與 `long long` ，改用 `string` 讀入並套用奇偶位差值的 $11$ 倍數判別法；同時將終止條件寫為字串比對 `s != "0"` ，使得像 `"00"` 這類含前導零的測資既能正確判斷也能原封不動輸出。
- **學到的教訓（Lesson learned）：** 當題目數字位數上限超過 $18$ ～ $19$ 位（如 $100$ 位或 $1000$ 位）時，必須改用 `string` 儲存，並結合進位同餘性質（例如模 $3$ 、模 $9$ 看各位數字和，模 $11$ 看奇偶位數字和之差）來取代直接除法取模。
- **下一步行動（Next action）：** 未來解大數整除性或字元數字統計題時，維持「以 `string` 讀入、減去 `'0'` 轉數值、保留原字串輸出」的標準處理流程。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10929 - You can say 11 | Gemini | 協助將一次 AC 的大數同餘判別法、前導零邊界與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
