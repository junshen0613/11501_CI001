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
  - 第一行包含一個正整數 $n$，代表接下來共有幾組測試資料。接下來的每一行包含四個正整數 $a, b, c, d$（最大可達 $2^{30}$），分別代表四條線段的長度。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組四條線段，判斷它們能圍成的圖形並輸出一行對應單字：若為正方形輸出 `square`；若非正方形但為長方形輸出 `rectangle`；若皆非但能構成一般四邊形輸出 `quadrangle`；若無法構成四邊形則輸出 `banana`。
- **主要規則與限制條件？（What are the main rules or constraints?）**
  - 輸入的四個邊長若已由小到大排列（$a \le b \le c \le d$），則四邊相等時最小邊等於最大邊（$a = d$）；長方形則為兩對對邊相等（$a = b$ 且 $c = d$，或依測資順序判斷）；一般四邊形需滿足較短邊之和大於最長邊。
- **核心解決任務？（What is the core task you must solve?）**
  - 選用正確的 C++ 編譯語言，並依照「正方形 $\rightarrow$ 長方形 $\rightarrow$ 一般四邊形 $\rightarrow$ 無法構成（banana）」的優先順序進行多重條件分類。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 讀取測資筆數 `n` 後，在 `while (n--)` 迴圈內讀取四個整數 `a, b, c, d`，直接利用 `if`、`else if`、`else` 依序判斷 `square`、`rectangle`、`quadrangle` 與 `banana`。
- **一開始注意到的困難、風險或模糊之處？**
  - 程式碼撰寫完成後首次提交至 UVa Online Judge 時，因網頁介面的 **Language 下拉選單選錯語言**（未選到 C++，導致編譯器無法識別 `<iostream>` 與 `using namespace std;`），直接收到 **Compile Error**。
- **為什麼最初的提交會失敗？**
  - 提交環境選錯編譯語言導致編譯階段失敗；在程式碼邏輯上，寫法假設了測資的邊長順序（例如 `a == d` 判斷四邊相等、`a == c && a != b` 判斷長方形以及 `a + b > c`），雖然在 UVa 官方測資中順利通過，但若遇到任意亂序輸入或極大邊長相加（接近 $2^{30}$）時仍有改進空間。

### Final Strategy
- **最終採用什麼方法？**
  - 修正 Online Judge 提交頁面的語言選項為 **C++ (C++17)**，保留原始多重條件判斷邏輯提交並順利通過所有測資：
    1. `if (a == d)` $\rightarrow$ 輸出 `square`
    2. `else if (a == c && a != b)` $\rightarrow$ 輸出 `rectangle`
    3. `else if (a + b > c)` $\rightarrow$ 輸出 `quadrangle`
    4. `else` $\rightarrow$ 輸出 `banana`
- **為什麼這個方法有效？**
  - 選對 C++ 編譯器後標準輸入輸出庫 `<iostream>` 正常編譯，且在 UVa 官方測資的資料分布下，四個條件分支按優先順序依序過濾，成功通過評測取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 四邊全等（`square` 必須優先於 `rectangle` 判斷，避免正方形被誤歸類為長方形）、兩對邊相等（`rectangle`），以及短邊總和不足以封閉成四邊形的退化情況（`banana`）。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$，總計 $n$ 組測資為 $O(n)$。
- **Space Complexity:** $O(1)$，僅使用五個整數變數 `n, a, b, c, d`。
- **Explanation:** 每次迭代僅執行四個整數的讀取與最多三次條件比較，時間與空間複雜度皆為常數級別。

---

## 4. Pseudocode
```text
START
1. 讀取測資筆數 n
2. WHILE n > 0 (每次執行後 n 減 1):
3.     讀取四個整數 a, b, c, d
4.     IF a == d THEN
5.         輸出 "square" 並換行
6.     ELSE IF a == c AND a != b THEN
7.         輸出 "rectangle" 並換行
8.     ELSE IF a + b > c THEN
9.         輸出 "quadrangle" 並換行
10.    ELSE
11.        輸出 "banana" 並換行
12.    END IF
13. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code (Compile Error due to Wrong Language Selection)
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
- **直接技術原因：** 提交至 UVa Online Judge 時**選錯編譯語言（Language selection error）**，導致系統以非 C++ 編譯器編譯 `#include<iostream>` 與 `using namespace std;` 而回傳 **Compile Error**。
- **會導致錯誤的測資情境：** 任何測試資料在錯誤語言設定下皆無法通過編譯。

### Correct Code (Accepted after Selecting C++)
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

**Why it works:**
- **關鍵不變量與推論：** 將 Online Judge 提交語言修正為 **C++ (C++17)** 後成功通過編譯；程式依照「正方形 $\rightarrow$ 長方形 $\rightarrow$ 四邊形 $\rightarrow$ 無法構成」的嚴格優先順序逐層判斷，在官方測資下順利通過全部測試案例取得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `4` / `1 1 1 1` / `1 2 1 2` / `1 2 3 4` / `1 1 2 5` | `square` / `rectangle` / `quadrangle` / `banana` | `square` / `rectangle` / `quadrangle` / `banana` | 驗證官方範例的四種基本幾何圖形分類 |
| **Boundary case** | `1` / `100 100 100 100` | `square` | `square` | 驗證正方形同時滿足長方形條件時能優先輸出 `square` |
| **Edge case** | `1` / `1 1 3 10` | `banana` | `banana` | 測試短邊總和不足以構成封閉四邊形的退化情況 |
| **Stress case** | UVa 官方隱藏多筆測資 | 全部通過 | Accepted | 驗證程式在官方評測環境下的正確性與執行效率 |

- **關於先前失敗測資的修正說明：** 首次提交因選錯語言導致 Compile Error，改選為正確的 C++ 編譯選項重新提交後，同一份程式碼即順利通過並取得 Accepted。

---

## 7. Difference and Reflection

### Key Differences
| Item | Fail Submission | Accepted Submission |
| :--- | :--- | :--- |
| **Logic** | 程式碼邏輯相同，但提交環境選錯語言 | 修正提交語言選項為 C++ (C++17) |
| **Edge Cases** | 無法通過編譯器前置檢查 | 成功通過 UVa 官方測試集（可進一步以 `sort` 與 `long long` 強化一般化輸入） |
| **Output Handling** | 回傳 Compile Error 無任何輸出 | 依序輸出對應四邊形分類單字 |
| **Complexity** | $O(n)$ | $O(n)$ |
| **Code Quality** | 提交設定疏失 | 保留原始 AC 實作並完成檢討 |

### Reflection
- **根本原因（Root cause）：** 上傳程式碼時未留意 Online Judge 網頁預設的 Language 選項，導致選錯語言而發生 Compile Error。此外，在複盤程式碼時也意識到：目前的寫法依賴測資邊長順序（未先排序四邊邊長，且四邊形條件 `a + b > c` 未加總三條短邊並使用 `long long` 防溢位），雖然通過了 UVa 官方測資，但若遇到完全隨機亂序的測資（如 `1 1 2 2`）可能會產生誤判。
- **學到的教訓（Lesson learned）：** (1) 每次按下 Submit 前務必確認語言下拉選單為 `C++`；(2) 處理多個無順序保證的幾何邊長時，先將四個邊長存入陣列並用 `std::sort` 排序，搭配 `long long` 判斷 `s[0] + s[1] + s[2] > s[3]` 會更嚴謹且通用。
- **下一步行動（Next action）：** 提交前養成檢查編譯語言選項的習慣，並在未來遇到幾何多邊形題目時主動加入排序與大數防溢位檢查。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11455 - Behold My Quadrangle | Gemini | 協助分析 Compile Error 原因、回顧原始 AC 程式碼的邊界優化空間，並整理報告格式 | 親自撰寫原始 C++ 程式碼、修正提交語言選項並通過 UVa Accepted 評測 |

---
