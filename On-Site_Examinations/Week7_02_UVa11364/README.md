# Code Review Report: UVa 11364 - Optimal Parking

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11364
- **Problem Title:** Optimal Parking
- **Problem Link:** https://onlinejudge.org/external/113/11364.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期將所有座標存入陣列排序的未完成草稿與最終 $O(1)$ 空間線上求極值 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa11364.cpp](src/UVa11364.cpp)
- **Review Date:** 2026-10-20

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $t$ （ $1 \le t \le 100$ ），代表測試資料的組數。每組測試資料包含兩行：第一行為一個正整數 $n$ （ $1 \le n \le 20$ ），代表要拜訪的商店數量；第二行為 $n$ 個整數 $x_1, x_2, \dots, x_n$ （ $0 \le x_i \le 99$ ），代表各家商店在一維直線街道上的門牌座標（順序未排序）。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組測資，輸出一行單一整數，代表 Michael 選擇最佳停車位置後，從停車點出發、走訪完所有 $n$ 家商店、最後再走回停車點取車所需的最短總步行距離。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 所有商店皆位於同一條一維直線街道上，座標範圍為 `0` 到 `99` 。
  - 必須從停車位置 $p$ 出發，經過所有商店（拜訪順序可任意安排），最後回到原停車點 $p$ 。
  - 輸入的商店座標順序是隨機的（未必由小到大排列）。
- **核心解決任務？（What is the core task you must solve?）**
  - 找出該組商店座標的最小值 $x_{\min}$ 與最大值 $x_{\max}$ ，並計算來回一趟的最短總距離 $2 \times (x_{\max} - x_{\min})$ 。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 最初直覺會想把 $n$ 個座標存進陣列並由小到大排序，甚至去計算中位數或平均數當作最佳停車位；但進一步畫出數線分析後發現：只要將車停在區間 $[x_{\min}, x_{\max}]$ 內的任意一點 $p$ ，無論先往左走到 $x_{\min}$ 再折返走到 $x_{\max}$ 最後回到 $p$ ，總步行距離皆為 $(p - x_{\min}) + (x_{\max} - x_{\min}) + (x_{\max} - p) = 2 \times (x_{\max} - x_{\min})$ 。
- **一開始注意到的困難、風險或模糊之處？**
  - 既然答案只取決於極小值 `min_pos` 與極大值 `max_pos` ，就完全不需要宣告陣列或呼叫 `std::sort` ；但必須確保每組測資開始時，這兩個極值追蹤變數的初始值設定在合法座標範圍 $[0, 99]$ 之外（即 `min_pos = 100` 、 `max_pos = -1` ），才能保證讀入第一個座標時一定會正確更新。
- **為什麼最初的草稿尚未完整？**
  - 先用陣列存下所有座標再進行排序的草稿不僅多耗費 $O(n)$ 空間與 $O(n \log n)$ 排序時間，也尚未加上多筆測資重置極值的控制結構。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `if (!(cin >> t)) return 0;` 讀取測資組數；在 `while (t--)` 迴圈內，每組先讀入商店數 `n` ，並於局部作用域初始化 `int min_pos = 100;` 與 `int max_pos = -1;` ；接著透過 `for (int i = 0; i < n; i++)` 逐一讀入座標 `pos` 並即時更新 `min_pos = min(min_pos, pos);` 與 `max_pos = max(max_pos, pos);` ，最後直接輸出 `2 * (max_pos - min_pos)` 。
- **為什麼這個方法有效？**
  - 在一維閉區間 $[x_{\min}, x_{\max}]$ 上，任何從內部點 $p$ 出發並覆蓋兩端點後返回 $p$ 的路徑，每段子區間至少被正向與反向各走過一次，因此 $2 \times (x_{\max} - x_{\min})$ 為嚴格的理論下界；線上（Online）更新極值將空間複雜度壓至 $O(1)$ 、時間複雜度壓至 $O(n)$ ，且初始化 `100` 與 `-1` 精準覆蓋 $[0, 99]$ 邊界，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 僅有 1 家商店的情況（ $n = 1$ ，此時 `min_pos == max_pos` ，車停在店門口步行距離為 `0` ）、所有商店位於同一座標（輸出 `0` ）、座標觸及上下界極值 `0` 與 `99` （輸出 `2 * (99 - 0) = 198` ），以及前組測資範圍大於後組測資的變數重置。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(n)$ ，總計 $t$ 組測資為 $O(t \cdot n)$ 。
- **Space Complexity:** $O(1)$ ，僅使用常數個整數變數 `t, n, min_pos, max_pos, i, pos` 。
- **Explanation:** 在 $t \le 100$ 且 $n \le 20$ 的限制下，每組測資僅需單趟線性掃描比較最小值與最大值，無需配置陣列或排序，執行時間極短。

---

## 4. Pseudocode
```text
START
1. 讀取測資筆數 t (若讀取失敗則結束)
2. WHILE t > 0 (每次執行後 t 減 1):
3.     讀取商店數量 n
4.     初始化 min_pos = 100, max_pos = -1
5.     FOR i = 0 TO n - 1:
6.         讀取商店座標 pos
7.         min_pos = min(min_pos, pos)
8.         max_pos = max(max_pos, pos)
9.     END FOR
10.    輸出 2 * (max_pos - min_pos) 並換行
11. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期使用陣列儲存並排序的未完成草稿)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 撰寫過程中的未完成草稿：使用 vector 儲存所有座標並排序取首尾，尚未簡化為 O(1) 空間線上求極值與多筆測資迴圈
int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    cout << 2 * (a[n - 1] - a[0]) << "\n";
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿僅能處理單組測資，且額外配置了 `vector` 並執行 $O(n \log n)$ 排序；改為在迴圈內直接維護 `min_pos` 與 `max_pos` 後，無需排序即可在 $O(n)$ 時間與 $O(1)$ 空間完成所有測資，首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int main(){
    int t;
    if (!(cin >> t))return 0;
    while (t--){
        int n;
        cin >> n;
        int min_pos = 100;
        int max_pos = -1;
            for (int i = 0; i < n; i++)
            {
                int pos;
                cin >> pos;
                min_pos = min(min_pos, pos);
                max_pos = max(max_pos, pos);
            }
            cout << 2 * (max_pos - min_pos) << "\n";
        }
    }
```

**Why it works:**
- **關鍵不變量與推論：** 每組測資局部宣告 `min_pos = 100` 與 `max_pos = -1` （嚴格位於題目值域 $[0, 99]$ 兩側），在讀取過程中維持兩者為已讀入座標的真實最小與最大值，迴圈結束後直接輸出區間寬度的兩倍 `2 * (max_pos - min_pos)` ，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `2` / `4` / `24 13 89 37` / `6` / `7 30 41 14 39 42` | `152` / `70` | `152` / `70` | 驗證官方範例未排序座標的最短往返距離與多組重置 |
| **Boundary case** | `2` / `1` / `50` / `2` / `0 99` | `0` / `198` | `0` / `198` | 測試單一商店（距離 `0` ）以及座標上下界 `0` 與 `99` 極值 |
| **Edge case** | `1` / `4` / `15 15 15 15` | `0` | `0` | 測試所有商店座標完全重疊時的特殊情況 |
| **Stress case** | `100` 組每組 $20$ 家商店之滿載測資 | 皆在毫秒內輸出精確往返距離 | Accepted | 驗證 $t = 100, n = 20$ 上限下的執行速度與穩定性 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 存入 `vector` 並排序後取頭尾差值 | 線上即時更新 `min_pos` 與 `max_pos` |
| **Edge Cases** | 缺少多組測資控制與極值重置 | `100` 與 `-1` 初始值完美涵蓋 $[0, 99]$ 與 $n = 1$ |
| **Output Handling** | 僅輸出單筆結果 | 每組獨立計算並輸出 `2 * (max_pos - min_pos)` |
| **Complexity** | $O(n \log n)$ 時間、 $O(n)$ 空間（未完成） | $O(t \cdot n)$ 時間、 $O(1)$ 空間 |
| **Code Quality** | 依賴排序與額外記憶體 | 幾何推導透徹、常數空間最優解、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在動手寫程式前先分析一維直線往返的幾何性質，發現「停車位置只要落在 $[x_{\min}, x_{\max}]$ 內，總步行距離恆為 $2(x_{\max} - x_{\min})$ 」，進而直接省去陣列儲存與排序，用兩個極值變數在讀取輸入的同時一次算完。
- **學到的教訓（Lesson learned）：** 當問題的答案只依賴數列的最大值與最小值（如極差、區間跨度）時，不需要先對整組資料排序；只要根據題目給定的值域上限與下限設定好哨兵初始值（如 `min_pos = 100, max_pos = -1` ），就能用 $O(n)$ 時間與 $O(1)$ 空間解決。
- **下一步行動（Next action）：** 未來遇到「求集合跨度、最小包覆區間或往返總距離」的題目時，優先思考是否能簡化為極值差計算並使用線上 $O(1)$ 空間實作。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11364 - Optimal Parking | Gemini | 協助將一次 AC 的一維區間幾何推導、極值哨兵設定與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
