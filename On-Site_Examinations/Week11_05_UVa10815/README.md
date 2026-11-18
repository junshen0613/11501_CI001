# Code Review Report: UVa 10815 - Andy's First Dictionary

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10815
- **Problem Title:** Andy's First Dictionary
- **Problem Link:** https://onlinejudge.org/external/108/10815.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期直接以 `cin >> word` 讀取而未先將非英文字母替換為空白的草稿與最終字串清洗 + `std::set` AC 版本）
- **Source Code (Final/Accepted):** [src/UVa10815.cpp](src/UVa10815.cpp)
- **Review Date:** 2026-11-17

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 一篇包含多行英文文章的測試資料（最多 5,000 行，每行最多 200 個字元），持續讀取直到檔案結尾（EOF）。文中包含大小寫英文字母、數字、空白以及各種標點符號（如 `'` 、 `-` 、 `.` 、 `,` 、 `"` 等）。
- **預期輸出是什麼？（What is the expected output?）**
  - 萃取出文章中出現的所有不重複「單字（Word）」，一律轉換為**全小寫字母**，並依照**字典序（Alphabetical order）**由小到大逐行輸出。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 本題對「單字（Word）」的定義為：**由連續英文字母（ `a` ～ `z` 、 `A` ～ `Z` ）組成的序列**。
  - 任何**非英文字母**（包含標點符號、撇號、連字號與數字）皆視為單字分隔符。例如 `"Andy's"` 必須拆分為 `"andy"` 與 `"s"` 兩個單字，而 `"123"` 則不產生任何單字。
  - 同一個單字無論在文中出現幾次或大小寫如何變化（例如 `"Disneyland"` 與 `"disneyland"` ），在字典中只能輸出一次（全小寫），且不可輸出空行。
- **核心解決任務？（What is the core task you must solve?）**
  - 讀取整份文本至 EOF，將所有非英文字母轉為空白以切分連續小寫英文字母單字，並利用集合容器進行自動去重與字典序排列後輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 題目同時要求「自動去除重複單字」與「按字典序由小到大輸出」，這正是 C++ STL 關聯式容器 `std::set<string>` 的核心功能；而為了讓標點符號、撇號與連字號也能正確切開單字，最乾淨的前處理技巧是先用 `getline(cin, s)` 讀入整行，把所有非英文字母字元全部替換成空白 `' '` 、英文字母全部轉成小寫 `tolower()` ，再交給 `stringstream` 自動依空白切出所有乾淨的小寫單字。
- **一開始注意到的困難、風險或模糊之處？**
  - 若直接用 `while (cin >> word)` 讀取單字再手動去除前後標點符號，會漏掉夾在單字中間的標點符號（例如 `"Andy's"` 或 `"well-known"` ），而且若整行只有標點符號，清洗後變成空字串時若直接插入容器，就會在輸出最前面多印一行空白；改用「非字母全轉空白 + `stringstream` 萃取」後，`ss >> word` 會自動跳過所有連續空白，天然不會產生空字串。
- **為什麼最初的草稿尚未完整？**
  - 直接用 `cin >> word` 讀取 token 的草稿無法拆分內部含有撇號或連字號的複合詞，且在全標點符號的 token 上可能插入空字串。

### Final Strategy
- **最終採用什麼方法？**
  - 宣告 `set<string> st;` 儲存字典單字，透過 `while (getline(cin, s))` 逐行讀取整篇文章直到 EOF；在每行內掃描每個字元 `s[i]` ：
    1. 若 `isalpha(s[i])` 為真，則轉為小寫 `s[i] = tolower(s[i]);` 。
    2. 否則（任何非英文字母），直接替換為空白 `s[i] = ' ';` 。
  - 接著將處理後的字串 `s` 放入 `stringstream ss(s)` ，透過 `while (ss >> word) st.insert(word);` 將每個連續字母序列插入 `set` 中；全部讀完後，以 `for (const auto& i : st) cout << i << "\n";` 依字典序輸出所有不重複單字。
- **為什麼這個方法有效？**
  - 「字元清洗（非字母替換為空白） + `stringstream` 切分」精準實作了「連續英文字母為單字」的定義，並徹底免疫多重連續標點符號與純符號行；`std::set<string>` 底層以紅黑樹維護嚴格弱序（字典序）與元素唯一性，且 `const auto&` 參考走訪避免字串拷貝開銷，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 單字內含撇號或連字號（如 `"Andy's"` 拆成 `"andy"` 與 `"s"` ）、大小寫混合的同一單字（如 `"Apple"` 、 `"APPLE"` 、 `"apple"` 合併為 `"apple"` ）、全標點或純數字行（不插入空字串）、空行，以及單一字母單字（如 `"a"` 、 `"s"` ）。

### Complexity Analysis
- **Time Complexity:** $O(C + W \log U)$ ，其中 $C$ 為整份輸入檔案的總字元數（ $C \le 5000 \times 200 = 10^6$ ）， $W$ 為切分出的總單字數， $U$ 為不重複單字總數（ $U \le 5000$ ）。
- **Space Complexity:** $O(U \cdot L)$ ，其中 $L$ 為單字平均長度，用於在 `set<string> st` 中儲存所有不重複的小寫單字。
- **Explanation:** 在最多 $5000$ 個不重複單字的規模下，每次 `st.insert(word)` 僅需約 $\log_2(5000) \approx 13$ 次字串比較，整體執行時間極短。

---

## 4. Pseudocode
```text
START
1. 宣告字串 s 與有序去重集合 set<string> st
2. WHILE 成功讀取一整行字串 s (直到 EOF):
3.     FOR i = 0 TO s.size() - 1:
4.         IF isalpha(s[i]) 為真 THEN
5.             s[i] = tolower(s[i])
6.         ELSE
7.             s[i] = ' '
8.         END IF
9.     END FOR
10.    將清洗後的 s 放入 stringstream ss
11.    WHILE 成功從 ss 讀取單字 word:
12.        將 word 插入集合 st
13.    END WHILE
14. END WHILE
15. FOR 每個不重複單字 i IN st (已按字典序排列):
16.    輸出 i 並換行
17. END FOR
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期未先將非字母替換為空白的草稿)
```cpp
#include <iostream>
#include <string>
#include <set>
#include <cctype>
using namespace std;

// 撰寫過程中的未完成草稿：直接用 cin >> word 讀取，無法拆分夾在單字中間的標點（如 "Andy's"）且可能產生空字串
int main() {
    string word;
    set<string> st;
    while (cin >> word) {
        string clean = "";
        for (char c : word) {
            if (isalpha(c)) clean += tolower(c);
        }
        if (!clean.empty()) st.insert(clean);
    }
    for (const auto& i : st) cout << i << "\n";
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿直接濾除標點符號而非替換成空白，會把 `"Andy's"` 黏成 `"andys"` 、把 `"mother-in-law"` 黏成 `"motherinlaw"` ，違背題目以非英文字母分隔單字的規則；改為將所有非字母替換成 `' '` 再以 `stringstream` 切分後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include <string>
#include<set>
#include<sstream>
#include<cctype>
using namespace std;
int main()
{
    string s;
    set<string>st;
    while (getline(cin, s)) {
        for (int i = 0; i < s.size(); i++) {
            if (isalpha(s[i]))s[i] = tolower(s[i]);
            else s[i] = ' ';
        }
        stringstream ss(s);
        string word;
        while (ss >> word) {
            st.insert(word);
        }
    }
    for (const auto& i : st) {
        cout << i << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 將整行所有非英文字母原位改寫為空白 `' '` 後，原本相鄰但被標點或數字隔開的字母序列會被 `stringstream` 精準切分為獨立的小寫 token，且完全不產生空字串；再透過 `std::set<string>` 自動完成去重與字典序排序，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `Adventures in Disneyland` / `Two blondes were going to Disneyland when they came to a fork in the` / `road. The sign read: "Disneyland Left."` / `So they went home.` | `a` / `adventures` / `blondes` / `came` / `disneyland` / `fork` / `going` / `home` / `in` / `left` / `read` / `road` / `sign` / `so` / `the` / `they` / `to` / `two` / `went` / `were` | 與預期輸出完全一致 | 驗證官方範例的大小寫合併、去重、標點移除與字典序排列 |
| **Boundary case** | `""` （空行） / `"12345 !@#$%^&*()"` （純符號數字） / `"Z"` | `z` | `z` | 測試空行與純符號行不會插入空字串，以及單一字母轉小寫 |
| **Edge case** | `"Andy's well-known book."` | `andy` / `book` / `known` / `s` / `well` | `andy` / `book` / `known` / `s` / `well` | 驗證單字內部的撇號 `'` 與連字號 `-` 正確將單字切開 |
| **Stress case** | UVa 官方長篇英文文本測資檔 | 全部不重複小寫單字依字典序精確輸出 | Accepted | 驗證字串原位清洗與 `std::set` 在完整文章測資下的穩定性與效能 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 逐 token 讀入並直接刪除標點符號 | 先將整行所有非字母原位改為空白 `' '` ，再用 `stringstream` 切分 |
| **Edge Cases** | 會將 `"Andy's"` 誤合併為 `"andys"` | 精準切開撇號、連字號與數字分隔的單字，且不產生空字串 |
| **Output Handling** | 複合詞分割錯誤 | 嚴格輸出全小寫、無重複、按字典序排列的單字表 |
| **Complexity** | $O(C + W \log U)$ （未完成） | $O(C + W \log U)$ 時間、 $O(U \cdot L)$ 空間 |
| **Code Quality** | 標點處理方式有瑕疵 | 善用字元原位清洗 + `stringstream` + `std::set` 、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 動手前看清楚題目對單字的定義（連續英文字母），因此不直接濾除標點符號，而是「把非英文字母全部轉成空白 `' '` 、英文字母全部轉成小寫 `tolower()` 」，再交給 `stringstream` 自動依空白切分；這樣不僅完美拆分 `"Andy's"` 這類含標點的詞，也徹底杜絕空字串被插入 `set` 的風險。
- **學到的教訓（Lesson learned）：** 在文字探勘與單字萃取題中，「將所有非法分隔符原位替換為空白，再以 `stringstream` 萃取」遠比手動移除前後標點更簡潔且不會遺漏詞中標點；搭配 `std::set<string>` 即可同時解決去重與字典序排序兩大需求。
- **下一步行動（Next action）：** 未來遇到「從非結構化文本中萃取不重複單字或詞彙表」的題目時，固定套用「原位字元清洗（轉小寫／轉空白） + `stringstream` + `std::set` 」的標準三部曲。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10815 - Andy's First Dictionary | Gemini | 協助將一次 AC 的字元原位清洗技巧、 `stringstream` 切分與 `std::set` 複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
