# Code Review Report: UVa 12468 - Zapping

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 12468
- **Problem Title:** Zapping
- **Problem Link:** https://onlinejudge.org/external/124/12468.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期未考慮跨 99/0 循環最短路徑的草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa12468.cpp](src/UVa12468.cpp)
- **Review Date:** 2026-9-29

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，每一行包含兩個整數 $a$ 與 $b$（ $0 \le a, b \le 99$ ），分別代表電視目前的頻道編號與目標頻道編號。當輸入為 `-1 -1` 時代表輸入結束，不需要輸出該行結果。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組非 `-1 -1` 的頻道對，輸出一行單一整數，代表遙控器只按「上一個頻道（ $\triangle$ ）」或「下一個頻道（ $\bigtriangledown$ ）」按鈕，從 $a$ 切換到 $b$ 所需的最少按鍵次數。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 頻道總數為 100 個（編號 `0` 到 `99`），且為首尾相連的環狀結構：在頻道 `99` 按「上」會跳到 `0`，在頻道 `0` 按「下」會跳到 `99`。
  - 終止條件為 `-1 -1`，必須兩者同時為 `-1` 才結束讀取。
- **核心解決任務？（What is the core task you must solve?）**
  - 計算環狀 100 個頻道上兩點 $a$ 與 $b$ 之間的最短圓周距離 $\min(\vert{}a - b\vert{}, 100 - \vert{}a - b\vert{})$。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 直覺上從頻道 $a$ 轉到頻道 $b$ 需要按 `abs(a - b)` 次按鈕；但因為頻道 `0` 和 `99` 相連成一個圓圈，也可以往反方向繞過邊界切換。
- **一開始注意到的困難、風險或模糊之處？**
  - 若只計算直接差值 `abs(a - b)`，在跨邊界切換（例如從 `0` 轉到 `99`，或從 `90` 轉到 `5`）時會算出遠大於 50 的繞遠路步數；此外需要確保終止條件正確判斷 `-1 -1`。
- **為什麼最初的草稿尚未完整？**
  - 僅輸出 `abs(a - b)` 的草稿把頻道當成線段而非圓環，無法求出跨 `99 <-> 0` 邊界的最短按鍵次數。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `while (cin >> a >> b && (a != -1 || b != -1))` 讀取每對頻道，先計算順向／逆向直線距離 `int diff = abs(a - b);`，再透過 `min(diff, 100 - diff)` 比較「不跨邊界」與「跨 `99 <-> 0` 邊界」兩條路徑的按鍵次數並輸出較小值。
- **為什麼這個方法有效？**
  - 100 個頻道構成周長為 100 的整數環，環上任意兩點 $a, b$ 將圓周分割為兩段互補弧長，長度分別為 `diff = |a - b|` 與 `100 - diff`；兩者取最小值即為嚴格意義上的環狀最短距離（且最大值不超過 50），因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 跨邊界相鄰頻道（`0` 與 `99`，最短距離為 `1`）、起點與終點相同（`a == b`，距離為 `0`）、圓環對徑最遠距離（`0` 與 `50`，兩側皆為 `50`），以及終止訊號 `-1 -1`。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$，總計 $T$ 組測資為 $O(T)$。
- **Space Complexity:** $O(1)$，僅使用三個整數變數 `a, b, diff`。
- **Explanation:** 每筆測資只需執行一次絕對值減法、一次減法與一次取最小值運算，時間與空間皆為常數級別。

---

## 4. Pseudocode
```text
START
1. WHILE 成功讀取兩個整數 a, b 且 (a != -1 OR b != -1):
2.     diff = abs(a - b)
3.     ans = min(diff, 100 - diff)
4.     輸出 ans 並換行
5. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期僅計算直線距離的草稿)
```cpp
#include <iostream>
#include <cmath>
using namespace std;

// 撰寫過程中的未完成草稿：僅計算直線差值 abs(a - b)，尚未考慮跨過 99 <-> 0 環狀邊界的更短路徑
int main() {
    int a, b;
    while (cin >> a >> b && (a != -1 || b != -1)) {
        cout << abs(a - b) << "\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿未考慮頻道 `99` 與 `0` 首尾相連的環狀特性，當輸入 `0 99` 時會誤輸出 `99` 而非最短的 `1` 次按鍵；補上 `min(diff, 100 - diff)` 後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
    int a, b;
    while (cin >> a >> b && (a != -1 || b != -1)) {
        int diff = abs(a - b);
        cout << min(diff, 100 - diff) << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 因為頻道總數為 100 的循環結構，從 $a$ 到 $b$ 的兩條路徑步數總和恆為 `100`；透過 `min(diff, 100 - diff)` 必能選出不超過 50 步的最短按鍵次數，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `3 9` / `0 99` / `12 27` / `-1 -1` | `6` / `1` / `15` | `6` / `1` / `15` | 驗證官方範例的不跨邊界與跨邊界切換步數 |
| **Boundary case** | `0 50` / `99 49` / `0 0` / `-1 -1` | `50` / `50` / `0` | `50` / `50` / `0` | 測試最大可能距離（50 步）與原地不動（0 步） |
| **Edge case** | `99 0` / `2 98` / `98 2` / `-1 -1` | `1` / `4` / `4` | `1` / `4` / `4` | 測試由高頻道往低頻道跨 0 切換的對稱性 |
| **Stress case** | UVa 官方多筆連續測資 | 全部通過 | Accepted | 驗證程式在官方評測集下的正確性與執行效率 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 僅計算單向直線差 `abs(a - b)` | 使用 `min(diff, 100 - diff)` 計算環狀最短路徑 |
| **Edge Cases** | 跨 `99 <-> 0` 切換時算出錯誤步數 | 完美支援順逆時針跨邊界、相同頻道與對徑距離 |
| **Output Handling** | 無法得出跨界最小步數 | 精確輸出最少按鍵次數並於 `-1 -1` 結束 |
| **Complexity** | $O(1)$（未完成） | $O(1)$ per case |
| **Code Quality** | 缺少環狀補數比較 | 結構極簡、邏輯嚴謹、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在寫程式前就看出這題與前幾題的「時鐘／週期」概念相通——只要總長度固定為 $N$（此處 $N = 100$），圓環上兩點的最短距離永遠就是 `min(diff, N - diff)`，一行公式即可解決所有方向分類討論。
- **學到的教訓（Lesson learned）：** 遇到圓形、環狀陣列或循環頻道問題時，不需要拆成 `a < b` 與 `a > b` 兩種情況分別討論跨界公式，直接用 `abs(a - b)` 與 `N - abs(a - b)` 取 `min` 最不易出錯。
- **下一步行動（Next action）：** 未來遇到週期性或環狀距離計算題時，優先套用 `min(diff, period - diff)` 的對稱公式化簡條件判斷。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 12468 - Zapping | Gemini | 協助將一次 AC 的環狀最短距離概念、邊界測資與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
