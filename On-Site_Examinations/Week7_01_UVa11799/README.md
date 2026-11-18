# Code Review Report: UVa 11799 - Horror Dash

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11799
- **Problem Title:** Horror Dash
- **Problem Link:** https://onlinejudge.org/external/117/11799.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期僅處理單組測資且缺少 `Case i:` 編號的未完成草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa11799.cpp](src/UVa11799.cpp)
- **Review Date:** 2026-10-20

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $T$ （ $T \le 50$ ），代表測試資料的組數。接下來的 $T$ 行中，每一行的第一個正整數為 $N$ （ $1 \le N \le 100$ ），代表該場比賽的參賽人數，緊接著在同一行有 $N$ 個以空格分隔的正整數 $c_1, c_2, \dots, c_N$ （ $1 \le c_i \le 10000$ ），代表每位參賽者的奔跑速度。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對第 $x$ 組測資（從 `1` 開始編號），輸出一行 `Case x: S` ，其中 `S` 代表該組所有參賽者中的最快速度（即所有 $c_i$ 的最大值）。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 扮演小丑的角色必須跑得至少和最快的參賽者一樣快，因此最小所需速度即為該組數列的最大值 $\max(c_1, c_2, \dots, c_N)$ 。
  - 每行的第一個數字 $N$ 是「人數計數」，**不可將 $N$ 本身混入速度最大值比較中**。
  - 輸出格式必須嚴格遵守 `Case i: ans` ，冒號 `:` 與答案之間必須有一個半形空格。
- **核心解決任務？（What is the core task you must solve?）**
  - 針對每組測資先讀取人數 $N$ ，接著讀取 $N$ 個速度數值並找出最大值，最後以 `Case casenum: maxspeed` 格式輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 每組測資的第一個整數已經明確給出接下來有 $N$ 個速度數字，因此不需要把這 $N$ 個數字全部存進陣列或 `vector` 裡，只要在迴圈讀取 `speed` 的同時維護一個最大值變數 `maxspeed = max(maxspeed, speed)` 即可（線上演算法，Online Algorithm）。
- **一開始注意到的困難、風險或模糊之處？**
  - 有三個常見失誤必須避免：第一，`maxspeed` 必須在每一組測資開始時重新初始化為 `0` ，否則上一組測資較大的速度會殘留影響下一組；第二，切勿誤把每行第一個數字 `n` （人數）也拿去跟 `maxspeed` 比較；第三，輸出編號 `casenum` 必須從 `1` 開始遞增，且冒號後面要留一個空格。
- **為什麼最初的草稿尚未完整？**
  - 僅求出單組最大值而未加上外層 `for (int casenum = 1; casenum <= t; casenum++)` 編號迴圈與每輪 `maxspeed = 0` 重置的草稿無法應付多組測試資料。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `if (!(cin >> t)) return 0;` 安全讀取測資總數，以 `for (int casenum = 1; casenum <= t; casenum++)` 控管組別編號；每輪先讀取人數 `cin >> n;` 並將 `int maxspeed = 0;` 歸零，接著用 `for (int i = 0; i < n; i++)` 逐一讀入 `speed` 並執行 `maxspeed = max(maxspeed, speed);` ，最後輸出 `cout << "Case " << casenum << ": " << maxspeed << "\n";` 。
- **為什麼這個方法有效？**
  - 由於所有速度皆為正整數（ $c_i \ge 1$ ），將 `maxspeed` 初始化為 `0` 保證第一次呼叫 `max(0, speed)` 就會更新為第一位參賽者的速度；線上逐一更新最大值使額外空間複雜度降為 $O(1)$ ，且輸出格式與官方規範完全吻合，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 僅有 1 位參賽者的情況（ $N = 1$ ，例如 `1 2` 輸出 `2` ）、人數 $N$ 大於所有速度的情況（如 `10 1 2 ... 1` ，確保 $N = 10$ 不會被誤當成速度最大值）、速度達到上限 $10000$ ，以及前組測資最大值大於後組測資的重置測試。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(N)$ ，總計 $T$ 組測資為 $O(T \cdot N)$ 。
- **Space Complexity:** $O(1)$ ，僅使用常數個整數變數 `t, casenum, n, maxspeed, i, speed` 。
- **Explanation:** 在 $T \le 50$ 且 $N \le 100$ 的限制下，總共最多讀取並比較 $50 \times 100 = 5000$ 個整數，無需配置任何陣列或動態容器即可瞬間完成。

---

## 4. Pseudocode
```text
START
1. 讀取測資筆數 t (若讀取失敗則結束)
2. FOR casenum = 1 TO t:
3.     讀取該組參賽人數 n
4.     初始化 maxspeed = 0
5.     FOR i = 0 TO n - 1:
6.         讀取參賽者速度 speed
7.         maxspeed = max(maxspeed, speed)
8.     END FOR
9.     輸出 "Case " + casenum + ": " + maxspeed 並換行
10. END FOR
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期僅處理單組測資最大值的草稿)
```cpp
#include <iostream>
#include <algorithm>
using namespace std;

// 撰寫過程中的未完成草稿：僅求出單組 n 個數字的最大值，尚未加入多筆測資迴圈與 "Case i: " 編號輸出
int main() {
    int n, maxspeed = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int speed;
        cin >> speed;
        maxspeed = max(maxspeed, speed);
    }
    cout << maxspeed << "\n";
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿缺少讀取總組數 `t` 的外層迴圈、每輪重置 `maxspeed = 0` 的作用域控制，以及題目要求的 `Case casenum: ` 前綴格式；補上外層計數迴圈與格式化輸出後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

int main()
{
    int t;
    if (!(cin >> t))return 0;
    for (int casenum = 1; casenum <= t; casenum++) {
        int n;
        cin >> n;
        int maxspeed = 0;
        for (int i = 0; i < n; i++) {
            int speed;
            cin >> speed;
            maxspeed = max(maxspeed, speed);
        }
        cout << "Case " << casenum << ": " << maxspeed << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 在每輪 `casenum` 迭代開始時於局部作用域重新宣告 `int maxspeed = 0;` ，保證各組測資完全獨立；內層迴圈維持 `maxspeed` 為目前已讀入前 $i$ 個速度的最大值，迴圈結束時即為全域最大值並精確輸出 `Case casenum: maxspeed` ，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `2` / `5 9 3 5 2 6` / `1 2` | `Case 1: 9` / `Case 2: 2` | `Case 1: 9` / `Case 2: 2` | 驗證官方範例多組測資、格式空格與由大組切換到小組時的重置 |
| **Boundary case** | `2` / `1 10000` / `1 1` | `Case 1: 10000` / `Case 2: 1` | `Case 1: 10000` / `Case 2: 1` | 測試單一參賽者（ $N = 1$ ）與速度上下界極值（ $1$ 與 $10000$ ） |
| **Edge case** | `1` / `10 2 3 4 2 3 4 2 3 4 2` | `Case 1: 4` | `Case 1: 4` | 確認人數 $N = 10$ 大於所有速度時不會誤將 $N$ 當成最大值 |
| **Stress case** | `50` 組每組 $100$ 位參賽者之滿載測資 | `Case 1` 至 `Case 50` 皆輸出精確最大值 | Accepted | 驗證 $T = 50, N = 100$ 上限下的執行速度與編號連續性 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 僅讀取並計算單組最大值 | 加入 `casenum` 迴圈逐組獨立計算最大值 |
| **Edge Cases** | 無法處理多組測資與狀態重置 | 每組重新初始化 `maxspeed = 0` 並隔離人數 `n` |
| **Output Handling** | 僅輸出單一數字 | 嚴格符合 `Case casenum: maxspeed` 格式與空格 |
| **Complexity** | $O(N)$ （未完成） | $O(T \cdot N)$ 時間、 $O(1)$ 空間 |
| **Code Quality** | 缺少多組控制結構 | 採用 $O(1)$ 空間線上求最大值、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 採用線上（Streaming）更新 `maxspeed = max(maxspeed, speed)` 的方式，省去宣告陣列或 `vector` 儲存所有速度的記憶體與索引操作，程式碼簡潔且不易出錯；同時延續前面 `Case i: ` 題型的經驗，特別注意冒號後方必須保留一個空格。
- **學到的教訓（Lesson learned）：** 當題目只要求數列的單一統計量（如最大值、最小值或總和）而不需要回頭查詢個別元素時，直接在輸入迴圈內線上更新結果是空間複雜度 $O(1)$ 的最佳實踐。
- **下一步行動（Next action）：** 未來遇到線上統計極值或總和的題型時，優先採用局部變數重置搭配即時更新的 $O(1)$ 空間寫法。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11799 - Horror Dash | Gemini | 協助將一次 AC 的線上求最大值策略、邊界案例與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
