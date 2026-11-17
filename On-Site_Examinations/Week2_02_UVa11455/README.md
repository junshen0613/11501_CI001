# Code Review Report: UVa 11455 - Behold My Quadrangle

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11455
- **Problem Title:** Behold My Quadrangle
- **Problem Link:** https://onlinejudge.org/external/114/11455.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (Initial submission: Compile Error due to wrong language selection)
- **Source Code (Initial/Fail):** [src/UVa11455_fail.cpp](src/UVa11455_fail.cpp)
- **Source Code (Final/Accepted):** [src/UVa11455.cpp](src/UVa11455.cpp)
- **Review Date:** 2026-11-18

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個整數，代表接下來共有幾組測試資料。接下來的每一行包含四個正整數（最大可達 $2^{30}$），分別代表四條線段的長度。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組四條線段，判斷它們能圍成的圖形並輸出一行對應單字：若能圍成正方形輸出 `square`；若非正方形但能圍成長方形輸出 `rectangle`；若皆非但能圍成一般四邊形輸出 `quadrangle`；若四條線段根本無法封閉成四邊形則輸出 `banana`。
- **主要規則與限制條件？（What are the main rules or constraints?）**
  - 輸入的四個邊長**並未保證按照大小順序排列**。
  - 邊長最大值可達 $2^{30}$，因此三條短邊相加（$s_0 + s_1 + s_2$）最大可達 $3 \times 2^{30} \approx 3.22 \times 10^9$，會超過 32 位元有號 `int` 的上限（$2^{31}-1 \approx 2.14 \times 10^9$）。
  - 四條線段能構成四邊形的充要條件為：「最長邊嚴格小於其餘三邊總和」。
- **核心解決任務？（What is the core task you must solve?）**
  - 選用正確的 C++ 編譯環境，對每組四個邊長進行排序、避免三邊相加溢位，並依「正方形 → 長方形 → 一般四邊形 → 無法構成（banana）」的優先順序完成分類。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 直接讀取四個 `int a, b, c, d`，並用 `if / else if / else` 依序判斷四邊相等、兩對邊相等以及三邊和大於第四邊。
- **一開始注意到的困難、風險或模糊之處？**
  - 首次提交時因為 Online Judge 的 **Language 下拉選單選錯語言**（未選到 C++，導致系統用錯誤編譯器編譯 `<iostream>` 與 `using namespace std;`），直接收到 **Compile Error**；此外重新檢視邏輯後也發現，未排序四個邊長會導致亂序長方形（如 `1 2 1 2`）判錯，且 `int` 三邊相加在極值時會溢位。
- **為什麼最初的提交會失敗？**
  - 提交環境選錯語言導致編譯器無法識別 C++ 語法而產生 Compile Error；且未對四邊長排序與使用 64 位元整數會導致邏輯與溢位錯誤。

### Final Strategy
- **最終採用什麼方法？**
  - 在提交介面正確選用 **C++ (C++17)** 編譯器，並使用 `long long s[4]` 儲存四條邊長，先呼叫 `std::sort(s, s + 4)` 由小到大排序（$s_0 \le s_1 \le s_2 \le s_3$），再依階層順序判斷：
    1. `s[0] == s[3]`（四邊全等）$\rightarrow$ `square`
    2. `s[0] == s[1] && s[2] == s[3]`（兩對對邊各自相等）$\rightarrow$ `rectangle`
    3. `s[0] + s[1] + s[2] > s[3]`（三短邊之和大於最長邊）$\rightarrow$ `quadrangle`
    4. 其餘情況 $\rightarrow$ `banana`
- **為什麼這個方法有效？**
  - 選對 C++ 編譯器確保 `<iostream>` 與 `<algorithm>` 正常編譯；排序後消除了輸入順序的任意性，搭配 `long long` 徹底避免大數相加溢位。
- **考慮了哪些邊界條件（Edge cases）？**
  - 邊長輸入順序打亂（如 `1 2 1 2`）、三短邊總和剛好等於最長邊（退化成線段，應輸出 `banana`），以及接近 $2^{30}$ 的大數相加溢位邊界。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$（僅對固定長度 4 的陣列排序與常數次比較），總計 $n$ 組測資為 $O(n)$。
- **Space Complexity:** $O(1)$，僅使用長度為 4 的 `long long` 陣列。
- **Explanation:** 對 4 個元素進行 `std::sort` 與常數次條件判斷，執行時間遠低於限制。

---

## 4. Pseudocode
```text
START
1. 讀取測資筆數 n
2. WHILE n > 0 (每次執行後 n 減 1):
3.     讀取四個 64 位元整數存入陣列 s[0..3]
4.     將 s[0..3] 由小到大排序
5.     IF s[0] == s[3] THEN
6.         輸出 "square"
7.     ELSE IF s[0] == s[1] AND s[2] == s[3] THEN
8.         輸出 "rectangle"
9.     ELSE IF s[0] + s[1] + s[2] > s[3] THEN
10.        輸出 "quadrangle"
11.    ELSE
12.        輸出 "banana"
13.    END IF
14. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code
```cpp
#include<iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    while (n--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        if (a == d) {
            cout << "square" << "\n";
        }
        else if (a == c && a != b) {
            cout << "rectangle" << "\n";
        }
        else if (a+b>c) {
            cout << "quadrangle" << "\n";
        }
        else {
            cout << "banana" << "\n";
        }
    }
    return 0;
}
```

**Why it failed:**
- **直接技術原因：** 提交至 Online Judge 時**選錯編譯語言（Language selection error）**，導致系統以非 C++ 編譯器編譯 `#include<iostream>` 與 `using namespace std;` 而回傳 **Compile Error**；同時程式碼本身尚未對四個邊長排序，且使用 `int` 計算三邊和有溢位風險。
- **會導致錯誤的測資情境：** 任何測資在錯誤語言設定下皆無法編譯；即便編譯通過，輸入 `1 2 1 2`（未排序長方形）也會因 `a != c` 條件不符而誤判。

### Correct Code
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        long long s[4];
        cin >> s[0] >> s[1] >> s[2] >> s[3];
        sort(s, s + 4);
        if (s[0] == s[3]) {
            cout << "square\n";
        } else if (s[0] == s[1] && s[2] == s[3]) {
            cout << "rectangle\n";
        } else if (s[0] + s[1] + s[2] > s[3]) {
            cout << "quadrangle\n";
        } else {
            cout << "banana\n";
        }
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 在提交介面正確指定 **C++ (C++17)** 編譯器，並透過 `sort(s, s + 4)` 建立 $s_0 \le s_1 \le s_2 \le s_3$ 的單調不變量，搭配 `long long` 防止三短邊總和溢位，使四種幾何分類條件完備且互斥。
- **如何解決原本失敗的情境：** 選對 C++ 語言後成功通過編譯；輸入 `1 2 1 2` 排序後變為 `1 1 2 2`，精確命中長方形條件輸出 `rectangle`。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `4` / `1 1 1 1` / `1 2 1 2` / `1 2 3 4` / `1 1 2 5` | `square` / `rectangle` / `quadrangle` / `banana` | `square` / `rectangle` / `quadrangle` / `banana` | 驗證四種幾何圖形分類與亂序輸入處理 |
| **Boundary case** | `1` / `1073741824 1073741824 1073741824 2147483648` | `quadrangle` | `quadrangle` | 測試邊長達 $2^{30}$ 時三邊總和是否發生 32 位元溢位 |
| **Edge case** | `1` / `1 2 3 6` | `banana` | `banana` | 測試三短邊總和剛好等於最長邊（$1+2+3=6$）退化成線段的邊界情況 |
| **Stress case** | $1000$ 組隨機排列正整數邊長 | 皆輸出正確分類 | 皆輸出正確分類 | 驗證排序與多重分支條件的穩定性 |

- **關於先前失敗測資的修正說明：** 將提交語言改回正確的 C++ 選項解決 Compile Error，並補上 `sort(s, s + 4)` 與 `long long` 後，所有測資皆順利通過並取得 Accepted。

---

## 7. Difference and Reflection

### Key Differences
| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **Logic** | 選錯提交語言且未對四邊長排序 | 選對 C++ 編譯器，並以 `sort(s, s + 4)` 排序後判定 |
| **Edge Cases** | 亂序長方形誤判、三邊和溢位 | 支援任意輸入順序與高達 $2^{30}$ 的邊長總和 |
| **Output Handling** | 編譯錯誤無法產出輸出 | 成功編譯並針對每組輸出正確英文分類名稱 |
| **Complexity** | $O(n)$ | $O(n)$ |
| **Code Quality** | 條件不完整且存在 `int` 溢位風險 | 邏輯嚴謹、使用標準演算法庫 `<algorithm>` |

### Reflection
- **根本原因（Root cause）：** 上傳程式碼時未留意 Online Judge 網頁預設的 Language 選項（導致選錯語言而 Compile Error），且初期未先將四條邊排序便直接撰寫條件判斷。
- **學到的教訓（Lesson learned）：** (1) 每次按下 Submit 前務必檢查語言欄位是否為 `C++`；(2) 處理無順序保證的幾何邊長時，先排序再判斷能讓條件最精簡且不遺漏。
- **下一步行動（Next action）：** 提交前養成檢查「語言選項、輸入排序、數值型別上限」三項細節的習慣。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11455 - Behold My Quadrangle | Gemini | 協助釐清 Compile Error 成因、四邊形排序條件與 `long long` 溢位邊界，並整理報告格式 | 親自修正語言設定與程式碼、測試各類幾何邊界測資並通過 UVa Accepted 評測 |

---
