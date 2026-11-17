# Code Review Report: UVa 11172 - Relational Operator

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11172
- **Problem Title:** Relational Operator
- **Problem Link:** https://onlinejudge.org/external/111/11172.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted
- **Source Code (Initial/Fail):** [src/UVa11172_fail.cpp](src/UVa11172_fail.cpp)
- **Source Code (Final/Accepted):** [src/UVa11172.cpp](src/UVa11172.cpp)
- **Review Date:** 2026-11-18

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $t$（$t < 15$），代表接下來總共有幾組測試資料。接下來的 $t$ 行中，每一行都包含兩個整數 $a$ 與 $b$（$\vert{}a\vert{}, \vert{}b\vert{} < 1000000001$）。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一對整數 $(a, b)$，各自輸出一行對應的關係運算子：若 $a < b$ 輸出 `<`；若 $a > b$ 輸出 `>`；若兩者相等則輸出 `=`。
- **主要規則與限制條件？（What are the main rules or constraints?）**
  - 輸入採用「先給測資筆數 $n$」的格式（而非讀到 EOF 為止）。
  - 數值範圍在 $[-10^9, 10^9]$ 之間，包含負整數與零。
- **核心解決任務？（What is the core task you must solve?）**
  - 依照指定的測資筆數 $n$ 依序讀取每對整數，並透過正確的關係運算子判斷兩數大小關係後輸出對應符號。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 先讀取測資筆數 `n` 並用 `while (n--)` 迴圈逐筆讀入 `a` 與 `b`，依序使用 `if`、`else if`、`else` 判斷大於、等於、小於三種情況。
- **一開始注意到的困難、風險或模糊之處？**
  - 需確認測資數量是由第一行的 `n` 控制，且輸入範圍 $\pm 10^9$ 落在 32 位元 `int` 安全範圍內。但在撰寫條件判斷時，手誤將 `else if (a == b)` 寫成賦值運算子 `else if (a = b)`。
- **為什麼最初的程式碼會失敗？**
  - 在 C++ 中，表達式 `a = b` 會將 `b` 的值指派給 `a` 並回傳指派後的值。只要 `b != 0`，`else if (a = b)` 就會被判定為 `true`，導致所有 $a < b$ 且 $b \neq 0$ 的測資全部錯誤輸出 `=`。

### Final Strategy
- **最終採用什麼方法？**
  - 修正條件分支的邏輯與運算子：先判斷 `if (a < b)` 輸出 `<`，再判斷 `else if (a > b)` 輸出 `>`，最後用 `else` 處理唯一剩下的 `a == b` 情況並輸出 `=`。
- **為什麼這個方法有效？**
  - 有號 32 位元 `int` 足以完整涵蓋 $\pm 10^9$ 範圍；嚴格區分嚴格不等式（`<`、`>`）與最後的 `else` 分支，徹底杜絕誤用賦值運算子 `=` 的語法陷阱，也不涉及任何加減法溢位風險。
- **考慮了哪些邊界條件（Edge cases）？**
  - $a < b$ 且 $b \neq 0$（原版會誤判為 `=`）、$a < 0$ 且 $b = 0$（原版因賦值結果為 `0` 才巧合進入 `else`）、兩數相等（包含 `0 0`），以及 $\pm 10^9$ 上下界極值。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$，總計 $n$ 組測資為 $O(n)$。
- **Space Complexity:** $O(1)$，僅使用三個整數變數 $n, a, b$。
- **Explanation:** 每次迭代僅執行兩次整數讀取與最多兩次關係比較，在 $t < 15$ 的限制下瞬間即可完成。

---

## 4. Pseudocode
```text
START
1. 讀取測資筆數 n
2. WHILE n > 0 (每次執行後 n 減 1):
3.     讀取兩個整數 a 與 b
4.     IF a < b THEN
5.         輸出 "<" 並換行
6.     ELSE IF a > b THEN
7.         輸出 ">" 並換行
8.     ELSE
9.         輸出 "=" 並換行
10.    END IF
11. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code
```cpp
#include<iostream>
using namespace std;
int main(){
   int n;
   cin>>n;
  while(n--){
  int a,b;
    cin>>a>>b;
     if(a>b){
     cout<<">"<<"\n";
     }else if(a=b){
      cout<<"="<<"\n";
     }else{
     cout<<"<"<<"\n";
     }
  }
  return 0;
}
```

**Why it failed:**
- **直接技術原因：** 在 `else if (a = b)` 中誤將「相等比較運算子 `==`」寫成「賦值運算子 `=`」。當 `a <= b` 進入此分支時，程式會把 `b` 賦值給 `a`，只要 `b != 0` 該條件就恆成立（`true`），導致本該輸出 `<` 的測資全部錯誤輸出 `=`。
- **會導致錯誤的測資情境：** 輸入 `10 20` 時，`10 > 20` 為假，進入 `else if (a = 20)` 後條件為真（非零），錯誤輸出 `=` 而非 `<`。

### Correct Code
```cpp
#include<iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    while (n--) {
        int a, b;
        cin >> a >> b;
        if (a < b) {
            cout << "<" << "\n";
        }
        else if (a > b) {
            cout << ">" << "\n";
        }
        else{
            cout << "=" << "\n";
        }
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 透過嚴格不等式 `a < b` 與 `a > b` 依序排除小於和大於的情況，最後直接以 `else` 涵蓋相等條件，避免手誤寫出 `=` 賦值陷阱。
- **如何解決原本失敗的情境：** 輸入 `10 20` 時，第一個條件 `if (10 < 20)` 直接成立並精確輸出 `<`，不會進入後續分支。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `3` / `10 20` / `20 10` / `10 10` | `<` / `>` / `=` | `<` / `>` / `=` | 驗證官方範例的三種基本大小關係（修正原版 `10 20` 誤判為 `=` 的錯誤） |
| **Boundary case** | `2` / `-1000000000 1000000000` / `1000000000 -1000000000` | `<` / `>` | `<` / `>` | 測試題目規範的 $\pm 10^9$ 上下界極值 |
| **Edge case** | `3` / `-5 -2` / `0 0` / `-100 0` | `<` / `=` / `<` | `<` / `=` / `<` | 測試負數比較、零值相等以及 `b = 0` 的特殊賦值邊界 |
| **Stress case** | `14` 組最大上限交錯測資 | 皆輸出正確符號 | 皆輸出正確符號 | 驗證在 $t < 15$ 上限下迴圈次數與輸出完全一致 |

- **關於先前失敗測資的修正說明：** 原本 `10 20` 與 `-5 -2` 等 $a < b$ 且 $b \neq 0$ 的測資在 Fail Code 中皆因 `a = b` 誤輸出 `=`；將判斷條件改為 `if (a < b)`、`else if (a > b)`、`else` 後，所有測資皆正確通過並獲得 Accepted。

---

## 7. Difference and Reflection

### Key Differences
| Item | Fail Code | Correct Code |
| :--- | :--- | :--- |
| **Logic** | `else if (a = b)` 誤用賦值運算子 `=` | 使用 `if (a < b)`、`else if (a > b)`、`else` 嚴格比較 |
| **Edge Cases** | 所有 $a < b$ 且 $b \neq 0$ 的情況皆誤判為 `=` | 正確處理所有大小關係、零值與負數 |
| **Output Handling** | 對 $a < b$ 輸出錯誤的 `=` | 嚴格對應三種關係輸出正確符號 |
| **Complexity** | $O(n)$ | $O(n)$ |
| **Code Quality** | 存在賦值語意錯誤且縮排較不整齊 | 條件互斥清晰、縮排規範 |

### Reflection
- **根本原因（Root cause）：** 打字過快時將條件判斷的雙等號 `==` 誤打成單等號 `=`，且在 C++ 中賦值表達式本身具有回傳值而不會產生編譯錯誤（僅為編譯器警告），導致產生隱蔽的邏輯 Bug。
- **學到的教訓（Lesson learned）：** 在 C++ 撰寫 `if` 條件判斷時務必仔細檢查 `==` 與 `=`，或優先將「相等情況」留給最後的 `else` 分支處理以減少手誤機率；同時建議編譯時開啟 `-Wall` 警告選項以即時抓出 `suggest parentheses around assignment used as truth value` 提示。
- **下一步行動（Next action）：** 每次提交前先用官方範例測資完整跑過一遍（尤其是 `<`、`>`、`=` 三種分支都要測到），並開啟編譯器警告檢查低級語法失誤。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11172 - Relational Operator | Gemini | 協助分析 `else if (a = b)` 賦值陷阱的技術成因，並整理對照報告格式 | 親自修正條件判斷邏輯、本地測試所有分支案例並通過 UVa Online Judge Accepted 評測 |

---
