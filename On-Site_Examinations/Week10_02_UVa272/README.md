# Code Review Report: UVa 272 - TEX Quotes

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 272
- **Problem Title:** TEX Quotes
- **Problem Link:** https://onlinejudge.org/external/2/272.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期以行讀取並在每行內部重置引號狀態的未完成草稿與最終跨行字元流 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa272.cpp](src/UVa272.cpp)
- **Review Date:** 2026-11-10

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 一篇包含多行英文文字的輸入檔，持續讀取直到檔案結尾（EOF）。文中包含成對出現的標準 ASCII 雙引號字元 `"` （ASCII `34` ），以及一般字母、數字、空白、縮排與換行符號（文中的單引號 `'` 則保持原樣不需更動）。
- **預期輸出是什麼？（What is the expected output?）**
  - 將整篇文章原封不動輸出（包含所有的空白與換行位置），但把文章中出現的雙引號 `"` 依出現順序兩兩配對替換為 TeX 格式的引號：
    - 第 $1, 3, 5, \dots$ 個（奇數次出現，即開引號）替換為兩個反引號 `` `` `` 。
    - 第 $2, 4, 6, \dots$ 個（偶數次出現，即閉引號）替換為兩個單引號 `''` 。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 一對引號**可能跨越多行**（例如左引號出現在第 1 行，右引號出現在第 3 行），因此引號的奇偶狀態必須在整份檔案讀取期間持續維持，**絕不能在每行結束時重置**。
  - 文章內的所有空白字元（包含連續空格、Tab 與換行）都必須精確保留，不可使用會忽略空白的 `cin >>` 讀取。
  - 文中原有的單引號 `'` （例如 `"It's"` 中的 `'` ）不可被替換，只有雙引號 `"` 需要轉換。
- **核心解決任務？（What is the core task you must solve?）**
  - 逐字元讀取整份輸入直到 EOF，維護全域布林旗標交替將遇到的 `"` 替換為 `` `` `` 或 `''` ，其餘字元原樣輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 本題要求精確保留所有空白與換行，且只需將單一字元 `"` 依奇偶次出現替換為兩個字元；因此最直接且無記憶體上限的方法，是利用 `cin.get(c)` 逐字元（Character-by-character）讀取輸入流直到 EOF，並用一個全域布林變數 `first` 記錄「下一個遇到的 `"` 是否為左引號」。
- **一開始注意到的困難、風險或模糊之處？**
  - 有兩個關鍵細節必須注意：第一，`bool first = true;` 必須宣告在 `while (cin.get(c))` 迴圈**外部**，因為官方範例中的引述句子本身就跨越了兩行，若每行重置狀態就會把第二行的右引號誤印成左引號；第二，必須使用 `cin.get(c)` 而非 `cin >> c` ，因為 `cin >> c` 預設會跳過空白與換行符號，導致整篇文章的排版全毀。
- **為什麼最初的草稿尚未完整？**
  - 若在每行開始時重置布林旗標，或使用 `cin >> c` 讀取字元，都會在跨行引號與空白保留上產生錯誤。

### Final Strategy
- **最終採用什麼方法？**
  - 在 `main()` 中宣告字元變數 `char c;` 與全域狀態旗標 `bool first = true;` ；透過 `while (cin.get(c))` 逐一讀取每個字元（包含 `' '` 與 `'\n'` ）：
    1. 若 `c == '"'` ：當 `first` 為 `true` 時輸出 `"``"` ，否則輸出 `"''"` ，並隨即執行 `first = !first;` 切換狀態。
    2. 否則（任何其他字元，包含單引號 `'` 、空白與換行）：直接原樣輸出 `cout << c;` 。
- **為什麼這個方法有效？**
  - `cin.get(c)` 以無格式（Unformatted）方式逐位元組讀取標準輸入直到 EOF，完整保留所有空白與換行結構；布林旗標 `first` 在整份檔案生命週期內嚴格在 `true` 與 `false` 之間交替切換，完美處理單行多對引號與跨越多行的引號配對，且空間複雜度僅為 $O(1)$ ，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 跨越多行的雙引號配對（如官方範例第一句跨兩行）、同一行內包含多對雙引號（如 `"A" and "B"` 輸出 `` ``A'' and ``B'' `` ）、包含普通單引號的縮寫字（如 `don't` 中的 `'` 保持不變）、連續空格與空行，以及完全不含雙引號的純文字段落。

### Complexity Analysis
- **Time Complexity:** $O(N)$ ，其中 $N$ 為整份輸入檔案的總字元數。
- **Space Complexity:** $O(1)$ ，僅使用一個 `char c` 與一個 `bool first` ，不需配置任何字串或緩衝陣列。
- **Explanation:** 每個輸入字元僅被讀取、判斷並輸出一次，無論單行有多長或文章有多少行皆在常數額外記憶體下線性完成。

---

## 4. Pseudocode
```text
START
1. 宣告字元變數 c 與狀態旗標 first = true
2. WHILE 成功透過 cin.get(c) 讀取下一個字元 (直到 EOF):
3.     IF c == '"' THEN
4.         IF first == true THEN
5.             輸出 "``"
6.         ELSE
7.             輸出 "''"
8.         END IF
9.         first = NOT first
10.    ELSE
11.        原樣輸出字元 c
12.    END IF
13. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期使用 `cin >> c` 忽略空白與換行的草稿)
```cpp
#include <iostream>
using namespace std;

// 撰寫過程中的未完成草稿：使用 cin >> c 會自動跳過所有空白字元與換行符號，導致輸出黏成一團
int main() {
    char c;
    bool first = true;
    while (cin >> c) {
        if (c == '"') {
            cout << (first ? "``" : "''");
            first = !first;
        } else {
            cout << c;
        }
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿使用格式化輸入 `cin >> c` ，會將原文中的所有空白與換行符號全部吞掉；改用無格式字元讀取 `while (cin.get(c))` 後，完整保留原文章排版並於首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
using namespace std;
int main()
{
    char c;
    bool first = true;
    while (cin.get(c)) {
        if (c == '"') {
            if (first) {
                cout << "``";
            }
            else {
                cout << "''";
            }
            first = !first;
        }
        else {
            cout << c;
        }
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** `cin.get(c)` 逐一提取輸入流中的每一個字元（包含所有空白與換行），且布林變數 `first` 在整份輸入過程中維持「下一個雙引號是否為奇數次出現（開引號）」的不變量，遇到 `"` 即輸出對應的 `` `` `` 或 `''` 並反轉 `first` ，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `"To be or not to be," quoth the Bard, "that` / `is the question".` / `The programming contestant replied: "I must disagree.` / `To `C' or not to `C', that is The Question!"` | `` ``To be or not to be,'' quoth the Bard, ``that `` / ``is the question''.`` / ``The programming contestant replied: ``I must disagree.`` / ``To `C' or not to `C', that is The Question!''`` | 與預期輸出完全一致 | 驗證官方範例的跨行雙引號配對、空白換行保留以及單引號 `'` 不受影響 |
| **Boundary case** | `""` （空引號對） / `""` （空行） | `` ``'' `` / `""` （空行） | `` ``'' `` / `""` （空行） | 測試相鄰雙引號連續出現與空行原樣輸出 |
| **Edge case** | `"Line 1` / （空行） / `Line 3"` / `   Indented   text   ` | `` ``Line 1 `` / （空行） / ``Line 3''`` / `   Indented   text   ` | 與預期輸出完全一致 | 測試跨越空行的長距離引號狀態維持與多重連續空白保留 |
| **Stress case** | UVa 官方長篇多行英文文章測資 | 全文排版與引號配對精確無誤 | Accepted | 驗證 $O(1)$ 空間字元流處理在長文本下的穩定性與效能 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 使用 `cin >> c` 讀取字元（略過空白與換行） | 使用 `cin.get(c)` 無格式逐字元讀取（保留所有空白與換行） |
| **Edge Cases** | 遺失所有空白、縮排與換行結構 | 完整保留連續空白、空行、單引號 `'` 與跨行引號狀態 |
| **Output Handling** | 所有文字黏在一起輸出 | 與原文排版完全一致，僅將 `"` 交替替換為 `` `` `` 與 `''` |
| **Complexity** | $O(N)$ （未完成） | $O(N)$ 時間、 $O(1)$ 空間 |
| **Code Quality** | 輸入方法選用錯誤 | 僅需 `<iostream>` 、常數空間、結構極簡、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在動手前就確認本題需要「原樣保留所有空白與換行」且「引號配對會跨行」，因此直接選用 `while (cin.get(c))` 搭配外層 `bool first = true;` 狀態切換，不需要額外處理整行字串切片或擔心單行過長，程式碼僅 20 行便一次通過評測。
- **學到的教訓（Lesson learned）：** 在 C++ 中處理文字過濾或字元替換題時，若題目要求保留原始空白與換行，使用 `cin.get(c)` 逐字元流式處理比 `cin >>` 安全得多，且只需要 $O(1)$ 記憶體。
- **下一步行動（Next action）：** 未來遇到「逐字元替換且需保留原始格式與跨行狀態」的題目時，繼續採用 `while (cin.get(c))` 搭配外層狀態旗標的流式處理模板。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 272 - TEX Quotes | Gemini | 協助將一次 AC 的字元流狀態機邏輯、跨行邊界與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
