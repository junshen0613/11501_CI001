# Code Review Report: UVa 10008 - What's Cryptanalysis?

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10008
- **Problem Title:** What's Cryptanalysis?
- **Problem Link:** https://onlinejudge.org/external/100/10008.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期未清除 `cin >> n` 殘留換行符且僅統計字母次數未排序的草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa10008.cpp](src/UVa10008.cpp)
- **Review Date:** 2026-11-03

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $n$ ，代表接下來加密文章的行數。緊接著有 $n$ 行文字，每行由大小寫英文字母、數字、空白與標點符號組成。
- **預期輸出是什麼？（What is the expected output?）**
  - 統計所有 $n$ 行文字中 26 個英文字母各自出現的總次數（**不分大小寫**，一律轉為大寫字母 `A` ～ `Z` 合併計算），並依以下雙重排序規則逐行輸出 `大寫字母 次數` ：
    1. 出現次數**較多者優先**（次數由大到小遞減排列）。
    2. 若兩個字母的出現次數相同，則按**英文字母順序優先**（即 `'A'` 在 `'B'` 前面）。
    3. **從未出現過（次數為 `0` ）的英文字母不可輸出**。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 大小寫字母視為相同（例如 `'a'` 與 `'A'` 皆計入 `'A'` ），非英文字母（空白、數字、標點）一律忽略不計。
  - 讀完第一行整數 $n$ 後必須先清除緩衝區中的換行符號，才能用 `getline` 正確讀取接下來的 $n$ 行文字。
- **核心解決任務？（What is the core task you must solve?）**
  - 讀取 $n$ 行文字並統計大寫字母 `A` ～ `Z` 的出現頻率，再依照「頻率遞減、同頻率則字母遞增」的順序輸出所有出現次數 $\ge 1$ 的字母與次數。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 一般的做法是定義一個 `struct` 或 `pair<int, char>` 儲存 `(次數, 字母)` 後呼叫 `std::sort` 並撰寫自訂比較函式；但觀察到英文字母總共只有 26 個，先掃描找出最大出現次數 `max` ，再用外層迴圈 `times` 從 `max` 遞減到 `1` 、內層迴圈 `ch` 從 `'A'` 遞增到 `'Z'` ，只要 `count[ch] == times` 就直接輸出，不需任何排序結構就能天然達成雙重排序！
- **一開始注意到的困難、風險或模糊之處？**
  - 需要注意三個細節：第一，在 `cin >> n;` 之後必須呼叫 `cin.ignore();` 吃掉第一行後方的 `\n` ，否則第一個 `getline` 會讀到空字串並漏讀最後一行文字；第二，計數陣列開 `int count[128] = { 0 };` 直接以 ASCII 字元 `'A'` ～ `'Z'` 作為索引，比 `count[c - 'A']` 更不易發生負數索引越界；第三，外層迴圈下界必須停在 `times >= 1` ，確保次數為 `0` 的字母不會被輸出。
- **為什麼最初的草稿尚未完整？**
  - 未在 `cin >> n` 後加上 `cin.ignore()` 的草稿會漏讀最後一行測資，且僅由 `'A'` 印到 `'Z'` 的草稿尚未依出現次數由高到低排序。

### Final Strategy
- **最終採用什麼方法？**
  - 讀取 `cin >> n;` 後立刻執行 `cin.ignore();` ；宣告 `int count[128] = { 0 };` ，在 `while (n--)` 迴圈內以 `getline(cin, line)` 逐行讀入並走訪每個字元 `c` ，若 `isalpha(c)` 為真則執行 `count[toupper(c)]++` ；統計完畢後，先找出 `'A'` ～ `'Z'` 中的最大出現次數 `max` ，最後透過雙層迴圈 `for (int times = max; times >= 1; times--)` 與 `for (char ch = 'A'; ch <= 'Z'; ch++)` 依序輸出滿足 `count[ch] == times` 的結果。
- **為什麼這個方法有效？**
  - 外層 `times` 由 `max` 嚴格遞減至 `1` 保證了頻率高者先輸出且排除零次字母；在相同 `times` 的同一輪內，內層 `ch` 由 `'A'` 嚴格遞增至 `'Z'` 則保證了字典序較小者先輸出；整個過程完全無需額外結構體與排序比較器，程式碼簡潔直觀，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - `cin >> n` 後的換行符號處理、大小寫混合統計（如 `'c'` 與 `'C'` 合併）、完全不含英文字母的文字行（如 `"12345 !@#$"` ，`max` 為 `0` 時外層迴圈 `times >= 1` 不執行，安全無輸出）、出現次數相同的字母字典序排列，以及 `0` 次字母的過濾。

### Complexity Analysis
- **Time Complexity:** 統計階段為 $O(\sum L)$ （ $\sum L$ 為所有 $n$ 行文字的總字元數）；輸出階段為 $O(26 \cdot M)$ （ $M$ 為最高單字元出現次數，且 $M \le \sum L$ ），總時間複雜度為 $O(\sum L)$ 。
- **Space Complexity:** $O(1)$ ，僅使用固定長度為 128 的整數陣列 `count[128]` 與單行字串緩衝 `line` 。
- **Explanation:** 在一般文本規模下，桶排序（Bucket-style scan）掃描時間極短，且省去 `std::sort` 的額外結構配置。

---

## 4. Pseudocode
```text
START
1. 讀取行數 n (若失敗則結束)
2. 呼叫 cin.ignore() 清除第一行數字後的換行字元
3. 初始化計數陣列 count[0..127] 全為 0
4. WHILE n > 0 (每次執行後 n 減 1):
5.     讀取一整行字串 line
6.     FOR 每個字元 c IN line:
7.         IF isalpha(c) 為真 THEN
8.             count[toupper(c)] = count[toupper(c)] + 1
9.         END IF
10.    END FOR
11. END WHILE
12. 找出 ch = 'A'..'Z' 中 count[ch] 的最大值 max
13. FOR times = max DOWN TO 1:
14.     FOR ch = 'A' TO 'Z':
15.         IF count[ch] == times THEN
16.             輸出 ch + " " + times 並換行
17.         END IF
18.     END FOR
19. END FOR
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期未清除緩衝區換行符且未依頻率排序的草稿)
```cpp
#include <iostream>
#include <cctype>
#include <string>
using namespace std;

// 撰寫過程中的未完成草稿：cin >> n 後缺少 cin.ignore() 導致首輪 getline 讀到空行，且輸出僅按 A-Z 順序未依頻率由高到低排列
int main() {
    int n;
    cin >> n;
    int count[128] = { 0 };
    string line;
    while (n--) {
        getline(cin, line);
        for (char c : line) {
            if (isalpha(c)) count[toupper(c)]++;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (count[ch] > 0) cout << ch << " " << count[ch] << "\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿在 `cin >> n;` 後未消耗換行字元，會使最後一行輸入被漏讀；同時輸出僅按字母表 `'A'` ～ `'Z'` 排列，未滿足「出現次數高者優先」的主要排序條件；補上 `cin.ignore()` 與 `times = max` 遞減雙層掃描後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<cctype>
#include<string>
using namespace std;

int main()
{
    int n;
    if (!(cin >> n))return 0;
    cin.ignore();
    int count[128] = { 0 };
    string line;
    while (n--) {
        getline(cin, line);
        for (char c: line) {
            if (isalpha(c)) {
                count[toupper(c)]++;
            }
        }
    }
    int max = 0;
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (count[ch] > max) {
            max = count[ch];
        }
    }
    for (int times = max; times >= 1; times--) {
        for (char ch = 'A'; ch <= 'Z'; ch++) {
            if (count[ch] == times) {
                cout << ch << " " << times << "\n";
            }
        }
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 透過 `cin.ignore()` 精準對齊後續 $n$ 行輸入，利用 `count[128]` 直接以大寫 ASCII 碼統計字母頻率；輸出階段外層以 `times` 由 `max` 遞減至 `1` 、內層以 `ch` 由 `'A'` 遞增至 `'Z'` ，自然同時滿足雙重排序與過濾零次字母的要求，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `3` / `This is a test.` / `Count me 1 2 3 4 5.` / `Wow!!!! Is this question easy?` | `S 7` / `T 6` / `I 5` / `E 4` / `O 3` / `A 2` / `H 2` / `N 2` / `U 2` / `W 2` / `C 1` / `M 1` / `Q 1` / `Y 1` | 與預期輸出完全一致 | 驗證官方範例的大小寫合併、標點數字忽略及雙重排序順序 |
| **Boundary case** | `1` / `12345 !@#$%` | （無任何輸出） | （無任何輸出） | 測試文章中完全沒有英文字母時（ `max == 0` ）不會輸出零次字母 |
| **Edge case** | `2` / `zZz` / `aAa` | `A 3` / `Z 3` | `A 3` / `Z 3` | 測試出現次數相同時嚴格按 `'A'` 在 `'Z'` 前的字典序輸出，且 `cin.ignore()` 未漏讀末行 |
| **Stress case** | 多行長字串與高頻重複字母測資 | 皆在毫秒內依正確順序輸出統計結果 | Accepted | 驗證計數桶雙層掃描的執行效率與穩定性 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 未清除 `cin >> n` 換行符且僅按 `'A'` ～ `'Z'` 輸出 | 補上 `cin.ignore()` 並以 `times` 遞減、 `ch` 遞增雙層掃描輸出 |
| **Edge Cases** | 漏讀最後一行文字且排序不符合題意 | 精準讀取全部 $n$ 行、過濾零次字母、同頻率依字母序輸出 |
| **Output Handling** | 順序錯誤 | 嚴格符合「次數由大到小、同次數字母由小到大」 |
| **Complexity** | $O(\sum L)$ （未完成） | $O(\sum L)$ 時間、 $O(1)$ 空間 |
| **Code Quality** | 缺少輸入緩衝區清理與頻率排序 | 無需自訂 `struct` 與 `sort` 、結構簡潔、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在 `cin >> n` 後立刻補上 `cin.ignore()` 解決混合輸入對齊問題，並開 `count[128]` 直接以 ASCII 碼作為陣列下標避免索引偏移計算；輸出時善用「先找最大頻率 `max` ，再由 `max` 往下枚舉頻率、由 `'A'` 往 `'Z'` 枚舉字母」的計數桶掃描法，省去撰寫自訂排序比較器的麻煩，大幅降低出錯率。
- **學到的教訓（Lesson learned）：** 當排序的鍵值（頻率）為正整數且字母種類固定只有 26 個時，利用雙層迴圈「外層枚舉頻率、內層枚舉字母」往往比宣告 `struct` 搭配 `std::sort` 更簡潔直觀。
- **下一步行動（Next action）：** 未來遇到「先讀行數 $n$ 再逐行 `getline` 」的字元統計題時，延續 `cin >> n; cin.ignore();` 與 ASCII 頻率陣列的標準組合。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10008 - What's Cryptanalysis? | Gemini | 協助將一次 AC 的頻率桶雙層掃描邏輯、輸入緩衝區處理與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
