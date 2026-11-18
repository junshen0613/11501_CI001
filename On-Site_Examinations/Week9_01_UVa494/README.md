# Code Review Report: UVa 494 - Kindergarten Counting Game

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 494
- **Problem Title:** Kindergarten Counting Game
- **Problem Link:** https://onlinejudge.org/external/4/494.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期試圖使用 `stringstream` 以空白切分單字的未完成草稿與最終狀態機 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa494.cpp](src/UVa494.cpp)
- **Review Date:** 2026-11-03

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行文字測試資料，持續讀取直到檔案結尾（EOF）。每一行包含任意數量的字元，可能由英文字母（大小寫 `A` ～ `Z` 、 `a` ～ `z` ）、空白、數字以及各種標點符號組成（也可能包含空行）。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一行輸入，輸出一行單一整數，代表該行文字中包含的「單字（Word）」總數。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 本題對「單字（Word）」的定義為：**由一個或多個連續英文字母組成的最長序列**。
  - 任何**非英文字母**的字元（不僅限於空白，還包含標點符號如 `!` 、 `,` 、 `.` 、 `-` 或數字 `0` ～ `9` ）皆視為單字之間的分隔符。例如 `"Meep!Meep!"` 中間雖無空白，但因為 `!` 非英文字母，所以包含 `2` 個單字；而 `"123"` 則包含 `0` 個單字。
- **核心解決任務？（What is the core task you must solve?）**
  - 逐行讀取整行字串直到 EOF，統計每行中「連續英文字母區塊（Contiguous alphabetic runs）」的出現次數並輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 直覺上統計一行有幾個單字常會想到用 `cin >> word` 或 `stringstream` 依空白切分；但仔細看題目定義後發現，單字是由「連續英文字母」構成，標點符號或數字也能切開單字（例如 `Hello,World` 算兩個單字）。因此不能用空白切分，必須逐字元掃描並判斷是否為英文字母。
- **一開始注意到的困難、風險或模糊之處？**
  - 若只計算「字母接非字母」的轉換次數，當單字位於整行最末尾（後面緊接換行而非標點空白）時容易漏算最後一個單字；相反地，使用一個布林狀態變數 `a` 記錄「目前是否正處於一個單字內部」，只要在 `!a` （尚未進入單字）時遇到英文字母（ `isalpha(line[i])` ），就立刻將計數器 `count++` 並設 `a = true` ，直到遇到非英文字母才設回 `a = false` ，就能完全避免行尾單字漏算的問題。
- **為什麼最初的草稿尚未完整？**
  - 使用 `stringstream` 以空白切分 token 的草稿會把 `"Meep!Meep!"` 誤算為 `1` 個單字、把 `"123"` 誤算為 `1` 個單字，完全不符合題目對單字的定義。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `while (getline(cin, line))` 逐行讀取輸入；每行初始化計數器 `int count = 0;` 與狀態旗標 `bool a = false;` ，以迴圈逐一檢查每個字元 `line[i]` ：
    1. 若 `isalpha(line[i])` 為真：當 `!a` 時表示新單字開始，執行 `count++; a = true;` ；若 `a` 已為 `true` 表示仍在同一個單字中，計數不變。
    2. 否則（遇到空白、數字或任何標點符號）：將狀態重置為 `a = false;` 。
  - 整行掃描完畢後輸出 `count << "\n"` 。
- **為什麼這個方法有效？**
  - 雙狀態有限狀態機（DFA：狀態 `false` 代表在單字外，狀態 `true` 代表在單字內）在每次發生 `false -> true` 狀態轉移時精確累加一次計數，因此無論單字前後是空白、標點、數字或是行首與行尾邊界，都能不重不漏地計算出所有連續英文字母區塊數量，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 空行（ `line` 長度為 `0` ，迴圈不執行並輸出 `0` ）、整行只有空白與標點符號（如 `"   !@# 123 "` ，輸出 `0` ）、兩個單字間僅隔標點或數字無空白（如 `"abc123def"` 或 `"Meep!Meep!"` ，輸出 `2` ），以及單字直接緊貼行首與行尾的情況。

### Complexity Analysis
- **Time Complexity:** 每行 $O(L)$ （ $L$ 為該行字元長度），總計所有行字元總數為 $O(\sum L)$ 。
- **Space Complexity:** $O(L)$ ，僅使用單一 `string line` 儲存當前行與常數個狀態變數 `count, a, i` 。
- **Explanation:** 每個字元僅被存取與分類一次，時間與空間複雜度皆為最優的線性級別。

---

## 4. Pseudocode
```text
START
1. WHILE 成功讀取一整行字串 line (直到 EOF):
2.     初始化 count = 0, a = false
3.     FOR i = 0 TO line.length() - 1:
4.         IF isalpha(line[i]) 為真 THEN
5.             IF a == false THEN
6.                 count = count + 1
7.                 a = true
8.             END IF
9.         ELSE
10.            a = false
11.        END IF
12.    END FOR
13.    輸出 count 並換行
14. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期誤用空白切分單字的未完成草稿)
```cpp
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// 撰寫過程中的未完成草稿：使用 stringstream 依空白切分，無法將標點符號與數字視為單字分隔符
int main() {
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string word;
        int count = 0;
        while (ss >> word) count++;
        cout << count << "\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿僅以空白字元分隔單字，遇到 `"Meep!Meep!"` 會誤輸出 `1` （正確應為 `2` ），遇到 `"42"` 會誤輸出 `1` （正確應為 `0` ）；改用 `isalpha()` 搭配布林狀態變數 `a` 逐字元掃描後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<cctype>
#include<string>
using namespace std;

int main()
{
    string line;
    while (getline(cin, line)) {
        int count = 0;
        bool a = false;
        for (int i = 0; i < line.length(); i++) {
            if (isalpha(line[i])) {
                if (!a) {
                    count++;
                    a = true;
                }
            }
            else {
                a = false;
            }
        }
        cout << count << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 狀態變數 `a` 精確維持「當前位置是否位於連續英文字母序列內」的不變量；每次由非字母字元（或行首）進入英文字母時觸發唯一一次 `count++` ，確保所有由標點、數字或空白分隔的英文單字皆被正確統計，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `Meep Meep!` / `I tot I taw a putty tat.` / `I did! I did! I did taw a putty tat.` / `Shsssssssssh ... I am hunting wabbits. Heh Heh Heh Heh ...` | `2` / `7` / `10` / `9` | `2` / `7` / `10` / `9` | 驗證官方範例多行含標點與省略號的單字計數 |
| **Boundary case** | `""` （空行） / `"   "` （純空白） / `"a"` （單一字母） | `0` / `0` / `1` | `0` / `0` / `1` | 測試空行、無字母行以及單字元邊界情況 |
| **Edge case** | `Meep!Meep!` / `word123word` / `12345!@#$%` | `2` / `2` / `0` | `2` / `2` / `0` | 測試標點符號與數字夾在兩單字中間（無空白）以及全符號行 |
| **Stress case** | UVa 官方多行長字串連續測資 | 全部通過 | Accepted | 驗證 `getline` 與線性掃描在官方測資下的穩定性與效能 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 以空白為界切分 `stringstream` | 逐字元呼叫 `isalpha()` 並以布林狀態機偵測單字起點 |
| **Edge Cases** | 無法處理無空白相連的 `Meep!Meep!` 或純數字行 | 精準切分標點、數字、空白，並安全處理空行與行尾單字 |
| **Output Handling** | 對含標點或數字的字串計數錯誤 | 每行精確輸出連續英文字母區塊總數 |
| **Complexity** | $O(\sum L)$ | $O(\sum L)$ 時間、 $O(L)$ 空間 |
| **Code Quality** | 依賴空白分隔的預設假設 | 善用 `<cctype>` 的 `isalpha` 與狀態旗標、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在動手前先確認題目對「單字」的嚴格定義（連續英文字母），果斷捨棄空白切分的做法，改用單一布林變數 `a` 記錄「是否在單字中」，只在進入單字的瞬間（ `!a` ）將計數器加 1 ，讓行首、行尾與多重標點符號的邊界自然統一處理。
- **複盤發現的細節優化（Code Review Insight）：** C++ 標準函式庫 `<cctype>` 的 `isalpha(int ch)` 規定參數必須是 `unsigned char` 值或 `EOF` ，在有號 `char` 平台若遇到擴展字元（負值）可能產生未定義行為；未來養成習慣寫成 `isalpha(static_cast<unsigned char>(line[i]))` 會讓程式碼具備跨平台滿分防禦力。
- **下一步行動（Next action）：** 未來處理字串分段統計（如單字數、連續區塊數）時，優先採用「狀態布林旗標 + 進入區塊瞬間累加」的單趟掃描狀態機模板。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 494 - Kindergarten Counting Game | Gemini | 協助將一次 AC 的狀態機掃描邏輯、標點分隔邊界與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
