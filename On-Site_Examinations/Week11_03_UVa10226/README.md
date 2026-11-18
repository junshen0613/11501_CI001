# Code Review Report: UVa 10226 - Hardwood Species

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10226
- **Problem Title:** Hardwood Species
- **Problem Link:** https://onlinejudge.org/external/102/10226.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期未清除 `t` 後空行且在最後一組測資多印空行的未完成草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa10226.cpp](src/UVa10226.cpp)
- **Review Date:** 2026-11-17

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $T$ ，代表測試資料的組數，緊接著**有一個空行（Blank line）**。之後的 $T$ 組測試資料中，每一組包含若干行樹木品種名稱（每行一棵樹，樹名由大小寫英文字母與空白組成，長度不超過 30 字元；每組最多 10,000 種不同樹種、總數不超過 1,000,000 棵），不同組測資之間以**一個空行**分隔。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組測資，依照樹種名稱的**字典序（Alphabetical / ASCII order）**由小到大排列，逐行輸出 `樹種名稱 百分比` ，其中百分比為該樹種佔該組總樹木數量的比例（四捨五入至**小數點後 4 位**）。不同組測資的輸出之間必須以**一個空行**隔開，但最後一組測資輸出完畢後不可多印空行。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 樹木名稱可能包含空白字元（例如 `"Red Alder"` 、 `"Sugar Maple"` ），因此必須使用 `getline(cin, s)` 整行讀入，不可使用會被空白截斷的 `cin >> s` 。
  - 第一組測資開始前有兩個換行（ `t` 後方的 `\n` 加上一列空行），必須先消耗掉這兩行才能進入第一組測資的讀取。
  - 輸出組與組之間需隔一個空行（ `if (t) cout << "\n";` ），最後一組後面不能有額外空行（否則可能導致 Presentation Error 或 Wrong Answer）。
- **核心解決任務？（What is the core task you must solve?）**
  - 分組讀取包含空白的整行樹種名稱 until 空行或 EOF，使用有序映射表統計各樹種數量與總數，依字典序輸出精確至小數點後 4 位的百分比，並正確控制組間空行。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 題目要求「統計每個不重複樹種的出現次數」並「按樹種名稱的字典序輸出」，這完全契合 C++ STL 的 `map<string, int>` 特性——每次執行 `mp[s]++` 既能累計次數，底層紅黑樹也會自動依照 `string` 的字典序維持有序狀態，走訪時直接依序輸出即可。
- **一開始注意到的困難、風險或模糊之處？**
  - 本題有三個經典的輸入／輸出格式陷阱必須一次防範：
    1. **首行後的空白過濾：** `cin >> t;` 讀完組數後，緩衝區內還有 `t` 後面的換行符以及題目規定的一整行空行，因此必須連續呼叫兩次 `getline(cin, s)` 將其消耗掉，才能讓 `while (t--)` 精準從第一組的第一棵樹開始讀取。
    2. **整行樹名與組間空行偵測：** 樹名含有空白，故用 `while (getline(cin, s) && s != "")` 讀取；當遇到組間分隔空行（ `s == ""` ）或最後一組遇到檔案結尾 EOF（ `getline` 回傳 `false` ）時，迴圈都會自然終止。
    3. **組間空行控制：** 在 `while (t--)` 內輸出完一組所有樹種後，必須用 `if (t) cout << "\n";` 判斷是否還有下一組測資，確保最後一組後方不會多印空行。
- **為什麼最初的草稿尚未完整？**
  - 若少呼叫一次 `getline(cin, s)` 吃掉初始空行，第一組測資會直接讀到空字串（ `sum == 0` ）造成除以零錯誤；若無條件輸出 `cout << "\n";` 則會在最後一組測資結尾多出一個空行。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `if (!(cin >> t)) return 0;` 讀取測資組數後，緊接著執行兩次 `getline(cin, s);` 清掉換行與首個空行；進入 `while (t--)` 後，每組局部宣告 `map<string, int> mp;` 與 `int sum = 0;` ，透過 `while (getline(cin, s) && s != "")` 累加 `mp[s]++` 與 `sum++` ；接著使用 `for (const auto& i : mp)` 搭配 `fixed << setprecision(4)` 輸出 `i.first` 與 `(double)i.second / sum * 100` ，最後以 `if (t) cout << "\n";` 輸出組間分隔空行。
- **為什麼這個方法有效？**
  - 兩次 `getline` 精準對齊第一組測資起點；`while (getline(cin, s) && s != "")` 同時兼容「遇到空行換下一組」與「最後一組遇到 EOF 結束」兩種終止情形；`std::map` 自動維護字典序，且使用 `const auto&` 參考遍歷避免無謂的字串拷貝，首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 僅有單一組測資（ $T = 1$ ，`if (t)` 為假，結尾不印多餘空行）、包含多重空格的長樹名（如 `"Red Alder"` ）、該組所有樹木皆為同一品種（輸出 `100.0000` ），以及最後一組測資結尾無空行直接接 EOF 的情況。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(N \log K)$ ，其中 $N$ 為該組樹木總數（ $N \le 10^6$ ）， $K$ 為不同樹種數量（ $K \le 10^4$ ）。
- **Space Complexity:** $O(K \cdot L)$ ，其中 $L \le 30$ 為單一樹種名稱最大長度，用於在 `map<string, int>` 中儲存所有不重複樹種。
- **Explanation:** 在 $K \le 10^4$ 的限制下，每次 `mp[s]++` 的紅黑樹搜尋僅需最多 $\log_2(10000) \approx 14$ 次字串比較，在 $10^6$ 筆資料下依然能在時限內穩定完成。

---

## 4. Pseudocode
```text
START
1. 讀取測資筆數 t (若失敗則結束)
2. 連續呼叫兩次 getline 消耗 t 後方的換行字元與首個空行
3. WHILE t > 0 (每次執行後 t 減 1):
4.     宣告有序映射表 map<string, int> mp 與總數 sum = 0
5.     WHILE 成功讀取一整行字串 s 且 s != "":
6.         mp[s] = mp[s] + 1
7.         sum = sum + 1
8.     END WHILE
9.     FOR 每個鍵值對 (name, count) IN mp (已按字典序排列):
10.        percentage = (double)count / sum * 100
11.        輸出 name + " " + 格式化至小數點後4位(percentage) 並換行
12.    END FOR
13.    IF t > 0 THEN
14.        輸出一個空行
15.    END IF
16. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期少消耗一次初始空行且結尾無條件印空行的草稿)
```cpp
#include <iostream>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

// 撰寫過程中的未完成草稿：cin >> t 後僅呼叫一次 getline，第一輪會讀到空行導致 sum == 0 除以零，且最後一組多印空行
int main() {
    int t;
    cin >> t;
    string s;
    getline(cin, s); // 僅吃掉 t 後的換行，遺漏第一組前的空白行
    while (t--) {
        map<string, int> mp;
        int sum = 0;
        while (getline(cin, s) && s != "") {
            mp[s]++;
            sum++;
        }
        for (const auto& i : mp) {
            cout << i.first << " " << fixed << setprecision(4) << (double)i.second / sum * 100 << "\n";
        }
        cout << "\n"; // 最後一組測資結束時會多輸出一個空行
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿在 `cin >> t` 後只用了一次 `getline`，會將第一組測資前的空行當成第一組測資（造成 `sum = 0` 與後續測資全數錯位），且無條件在每組末尾輸出 `"\n"` 會在最後一組產生多餘空行；補上第二次 `getline` 與 `if (t) cout << "\n";` 後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include <string>
#include<map>
#include<sstream>
#include<iomanip>
using namespace std;
int main()
{
    int t;
    if (!(cin >> t))return 0;
    string s;
    getline(cin, s);
    getline(cin, s);
    while (t--) {
        map<string, int>mp;
        int sum = 0;
        while (getline(cin, s)&&s!="") {
            mp[s]++;
            sum++;
        }
        for (const auto& i : mp) {
            cout << i.first << " " << fixed << setprecision(4) << (double)i.second / sum * 100 << "\n";
        }
        if (t)cout << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 透過兩次 `getline` 精準跳過首行換行與第一組前的空白行；利用 `while (getline(cin, s) && s != "")` 完整讀取含空白的樹名直到組間空行或 EOF；藉由 `std::map` 自動維持字典序並搭配 `fixed << setprecision(4)` 與 `if (t)` 組間空行控制，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `1` / （空行） / `Red Alder` / `Ash` / `Aspen` / `Basswood` / `Ash` / `Beech` / ...（官方 29 筆範例） | `Ash 13.7931` / `Aspen 3.4483` / ... / `Yellow Birch 3.4483` （結尾無多餘空行） | 與預期輸出完全一致 | 驗證官方範例含空白樹名、字典序排列、四位小數百分比與單組結尾無空行 |
| **Boundary case** | `2` / （空行） / `Oak` / （空行） / `Pine` / `Pine` | `Oak 100.0000` / （空行） / `Pine 100.0000` | 與預期輸出完全一致 | 測試單一樹種 `100.0000%` 輸出以及多組測資間精準隔一個空行 |
| **Edge case** | `2` / （空行） / `A B` / `A` / （空行） / `a` / `Z` | `A 50.0000` / `A B 50.0000` / （空行） / `Z 50.0000` / `a 50.0000` | 與預期輸出完全一致 | 驗證 ASCII 字典序（大寫 `'Z'` 排在小寫 `'a'` 前面，短字串 `'A'` 排在 `'A B'` 前面） |
| **Stress case** | UVa 官方高達 $1,000,000$ 筆樹木資料之完整測資檔 | 全部輸出精確無誤且不超時 | Accepted | 驗證 `std::map` 與 `const auto&` 遍歷在百萬級資料規模下的執行效能 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 僅呼叫一次 `getline` ，未消耗第一組前的空白行 | 連續呼叫兩次 `getline` 精準對齊第一組測資起點 |
| **Edge Cases** | 首組讀入空行造成 `sum == 0` 且後續測資全數錯位 | 同時支援空行換組與最後一組遇到 EOF 正常結束 |
| **Output Handling** | 最後一組測資結尾多印一個空行 | 使用 `if (t) cout << "\n";` 嚴格只在組間輸出空行 |
| **Complexity** | 邏輯錯誤（未完成） | $O(N \log K)$ 時間、 $O(K \cdot L)$ 空間 |
| **Code Quality** | 輸入緩衝與結尾空行處理不完整 | 善用 `std::map` 自動排序、 `const auto&` 參考與 `setprecision(4)` 、一次過關 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 動手前仔細看清楚題目輸入格式中「 $T$ 後面還有一行空行」以及「輸出組與組之間隔空行、但結尾不印空行」兩大細節，因此一開始就寫下兩次 `getline(cin, s)` 與 `if (t) cout << "\n";` ；同時選用 `map<string, int>` 一次包辦計數與字典序排列，並用 `const auto&` 避免遍歷時的字串複製開銷。
- **學到的教訓（Lesson learned）：** 在多筆空行分隔型（Blank-line separated）UVa 題目中，標準起手式是「讀取 `t` 後用兩次 `getline` 跳過換行與首個空行，內層用 `while (getline(cin, s) && s != "")` 讀到空行或 EOF 為止，組尾用 `if (t) cout << "\n";` 控制組間空行」。
- **下一步行動（Next action）：** 未來遇到所有空行分隔的多筆字串統計題時，直接套用此標準控制框架與 `std::map` 頻率計數模板。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10226 - Hardwood Species | Gemini | 協助將一次 AC 的雙次 `getline` 緩衝清理、 `std::map` 頻率統計與組間空行控制整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
