# Code Review Report: UVa 10282 - Babelfish

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10282
- **Problem Title:** Babelfish
- **Problem Link:** https://onlinejudge.org/external/102/10282.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期直接使用 `cin >> a >> b` 無法偵測空行分隔符的未完成草稿與最終 `getline` + `map` AC 版本）
- **Source Code (Final/Accepted):** [src/UVa10282.cpp](src/UVa10282.cpp)
- **Review Date:** 2026-11-17

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 輸入分為兩個部分，中間以**一個空行（Blank line）**隔開：
    1. **字典區塊（Dictionary）：** 最多 $100,000$ 行，每行包含兩個由小寫英文字母組成的單字（以單一空格分隔），第一個單字為**英文單字**，第二個單字為對應的**外語單字**（所有外語單字皆不重複）。
    2. **查詢區塊（Message）：** 空行之後為最多 $100,000$ 行的待翻譯文件，每行包含一個外語單字，持續讀取直到檔案結尾（EOF）。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對查詢區塊中的每一個外語單字，輸出一行其對應的英文翻譯；若該外語單字未出現在字典中，則輸出一行 `eh` 。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 字典與查詢之間沒有給定行數 $N$ ，唯一的分界訊號是**空行**，因此建立字典時必須逐行讀取並偵測空字串 `s.empty()` 才能停止建表。
  - 查詢鍵值（Key）為每行字典的第二個單字（外語），目標輸出值（Value）為第一個單字（英文），方向不可顛倒。
  - 字典與查詢規模皆高達 $100,000$ 筆，必須使用對數時間 $O(\log N)$ 或雜湊平均 $O(1)$ 的關聯式容器（如 `std::map` ）儲存字典，不可使用線性搜尋。
- **核心解決任務？（What is the core task you must solve?）**
  - 讀取字典行直到空行為止，將 `外語 -> 英文` 存入 `map<string, string>` ，接著逐一讀取查詢單字直至 EOF 並輸出對應英文或 `eh` 。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 字典查詢規模高達 $100,000$ 筆，最適合使用 C++ STL 的 `map<string, string> mp` 來儲存鍵值對；由於題目要求「輸入外語、輸出英文」，建表時應將外語單字 `b` 作為 Key、英文單字 `a` 作為 Value（即 `mp[b] = a` ）。
- **一開始注意到的困難、風險或模糊之處？**
  - 最大的輸入陷阱在於如何區分「字典結束」與「查詢開始」：若直接用 `while (cin >> a >> b)` 讀字典，`cin >>` 會自動跳過中間的空行，把查詢區塊的單字當成字典繼續讀入，導致整個程式邏輯錯亂；必須改用 `while (getline(cin, s))` 讀取整行，檢查 `if (s.empty()) break;` 來精準偵測空行邊界，再用 `stringstream` 拆出 `a` 與 `b` 。
- **為什麼最初的草稿尚未完整？**
  - 使用 `cin >> a >> b` 讀字典的草稿無法偵測空行分界點，會吞掉查詢單字並使字典建表與查詢階段混在一起。

### Final Strategy
- **最終採用什麼方法？**
  - 第一階段（建立字典）：使用 `while (getline(cin, s))` 逐行讀入，若 `s.empty()` 為真則立刻 `break` 結束字典讀取；否則透過 `stringstream ss(s); ss >> a >> b;` 萃取出英文 `a` 與外語 `b` ，並存入 `mp[b] = a;` 。
  - 第二階段（處理查詢）：空行跳出後，使用 `while (cin >> b)` 逐一讀取查詢的外語單字直至 EOF，透過 `if (mp.count(b))` 檢查鍵值是否存在，存在則輸出 `mp[b] << "\n"` ，否則輸出 `"eh\n"` 。
- **為什麼這個方法有效？**
  - `getline` 搭配 `s.empty()` 精準捕捉唯一作為分隔的空行；`std::map` 底層為紅黑樹（Red-Black Tree），每次插入與 `mp.count(b)` 查詢皆為 $O(\log D)$ 時間，總計 $10^5$ 筆資料僅需約 $1.7 \times 10^6$ 次字串比較，完全在時間限制內；且使用 `mp.count(b)` 檢查存在性，不會因為查詢不存在的單字而意外在 `map` 中插入空字串鍵值，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 字典為空（輸入第一行就是空行，所有查詢皆輸出 `eh` ）、查詢區塊為空（空行後直接到達 EOF，無任何輸出）、查詢不存在的單字（輸出 `eh` ），以及字典與查詢皆達到 $100,000$ 筆上限的效能表現。

### Complexity Analysis
- **Time Complexity:** 建立字典為 $O(D \log D)$ ，處理 $Q$ 筆查詢為 $O(Q \log D)$ ，總時間複雜度為 $O((D + Q) \log D)$ （其中 $D, Q \le 100,000$ ）。
- **Space Complexity:** $O(D)$ ，用於在 `map<string, string> mp` 中儲存最多 $D$ 組單字映射。
- **Explanation:** 在 $D, Q \le 10^5$ 的限制下，對數時間查詢確保程式不會發生 Time Limit Exceeded（TLE），執行效率穩定。

---

## 4. Pseudocode
```text
START
1. 宣告字串 s, a, b 與映射表 map<string, string> mp
2. WHILE 成功讀取一整行字串 s:
3.     IF s 為空字串 THEN
4.         BREAK (字典區塊結束)
5.     END IF
6.     使用 stringstream 從 s 中依序讀取英文單字 a 與外語單字 b
7.     mp[b] = a
8. END WHILE
9. WHILE 成功讀取查詢單字 b (直到 EOF):
10.    IF mp 中包含鍵值 b THEN
11.        輸出 mp[b] 並換行
12.    ELSE
13.        輸出 "eh" 並換行
14.    END IF
15. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期使用 `cin >> a >> b` 無法偵測空行邊界的草稿)
```cpp
#include <iostream>
#include <string>
#include <map>
using namespace std;

// 撰寫過程中的未完成草稿：使用 cin >> a >> b 會忽略空白與空行，無法在空行處停止建立字典並切換至查詢階段
int main() {
    string a, b;
    map<string, string> mp;
    while (cin >> a >> b) {
        mp[b] = a;
    }
    while (cin >> b) {
        if (mp.count(b)) cout << mp[b] << "\n";
        else cout << "eh\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿的第一個 `while (cin >> a >> b)` 會一路把空行之後的查詢單字也兩兩配對讀進字典直到 EOF，導致第二個查詢迴圈完全沒有資料可讀；改用 `while (getline(cin, s))` 偵測 `s.empty()` 並以 `stringstream` 解析後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include <string>
#include<map>
#include<sstream>
using namespace std;
int main()
{
    string s,a,b;
    map<string, string>mp;
    while (getline(cin, s)) {
        if (s.empty())break;
        stringstream ss(s);
        ss >> a >> b;
        mp[b] = a;
    }
    while (cin >> b) {
        if (mp.count(b)) {
            cout << mp[b] << "\n";
        }
        else {
            cout << "eh\n";
        }
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 第一階段透過 `getline` 與 `s.empty()` 精準隔離字典與查詢兩大區塊，並建立反向映射 `mp[b] = a` ；第二階段利用 `mp.count(b)` 在 $O(\log D)$ 時間內安全判斷外語單字是否已收錄並輸出對應結果，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `dog ogday` / `cat atcay` / `pig igpay` / `froot ootfray` / `loops oopslay` / （空行） / `atcay` / `ittenkay` / `oopslay` | `cat` / `eh` / `loops` | `cat` / `eh` / `loops` | 驗證官方範例的空行分界、字典反向查詢與未收錄單字輸出 `eh` |
| **Boundary case** | （第一行即為空行） / `hello` / `world` | `eh` / `eh` | `eh` / `eh` | 測試字典為空時的邊界表現（ `s.empty()` 立即跳出建表） |
| **Edge case** | `apple elppa` / （空行） / （直接 EOF，無任何查詢） | （無任何輸出） | （無任何輸出） | 測試查詢區塊為空時的程式正常結束行為 |
| **Stress case** | $100,000$ 筆字典條目與 $100,000$ 筆查詢之滿載測資 | 皆在時間限制內輸出精確翻譯 | Accepted | 驗證 `std::map` 的 $O((D + Q) \log D)$ 效能與記憶體表現 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 直接用 `cin >> a >> b` 讀取字典（無法區分空行） | 使用 `getline` + `s.empty()` 偵測空行分隔符並以 `stringstream` 切分 |
| **Edge Cases** | 查詢區塊被誤當成字典讀入 | 精準隔離字典與查詢階段、安全處理空字典與空查詢 |
| **Output Handling** | 查詢階段無輸出 | 存在則輸出 `mp[b]` ，不存在則輸出 `eh` |
| **Complexity** | 邏輯錯誤（未完成） | $O((D + Q) \log D)$ 時間、 $O(D)$ 空間 |
| **Code Quality** | 混用流讀取未處理空行 | 結構清晰、善用 `map.count()` 避免無效鍵值插入、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 一開始就注意到字典與查詢之間是靠「空行」分隔，因此果斷用 `while (getline(cin, s))` 搭配 `if (s.empty()) break;` 來切開兩個輸入階段，再用 `stringstream` 拆出兩個單字並反向存入 `mp[b] = a` ；查詢時也使用 `mp.count(b)` 而非直接存取 `mp[b]` ，避免查詢失敗時無謂擴充 `map` 的大小。
- **學到的教訓（Lesson learned）：** 當題目輸入由「空行」分成前後兩個不同格式的區塊時，第一區塊必須使用 `getline` 配合 `s.empty()` 偵測分界；此外，在 C++ `std::map` 中檢查鍵值是否存在時，優先使用 `count()` 或 `find()` 是兼顧效能與防止記憶體膨脹的好習慣。
- **下一步行動（Next action）：** 未來遇到字典查詢、字串映射或雙區塊（空行分隔）輸入題時，固定套用 `getline + s.empty() + stringstream + map` 的標準架構。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10282 - Babelfish | Gemini | 協助將一次 AC 的空行分段讀取技巧、 `std::map` 反向映射與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
