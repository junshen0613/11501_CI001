# Code Review Report: UVa 11677 - Alarm Clock

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11677
- **Problem Title:** Alarm Clock
- **Problem Link:** https://onlinejudge.org/external/116/11677.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期未處理跨午夜負數差值的草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa11677.cpp](src/UVa11677.cpp)
- **Review Date:** 2026-9-29

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，每一行包含四個整數 $H_1, M_1, H_2, M_2$（$0 \le H_1, H_2 \le 23$，$0 \le M_1, M_2 \le 59$），分別代表當前時間與鬧鐘設定時間（24 小時制）。當四個數字皆為 `0`（`0 0 0 0`）時代表輸入結束，不需要輸出該行結果。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組非 `0 0 0 0` 的時間，輸出一行單一整數，代表從當前時間到下一次鬧鐘響起之間總共有幾分鐘的睡眠時間。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 鬧鐘響起的時間永遠在當前時間之後（若當前時間與鬧鐘時間的時、分完全相同，代表必須等到隔天同一時刻，共 $24 \times 60 = 1440$ 分鐘；但本題實測中若兩時刻相同且非終止訊號，則差值為 `0` 或依題意跨日處理，一般測資皆為不同時刻）。
  - 若鬧鐘時間的數字小於當前時間（例如 `23:59` 到 `00:34`），代表時間跨越了午夜（00:00），必須加上一天的總分鐘數 $1440$。
  - 終止條件必須四個變數同時為 `0` 才結束（例如 `0 0 0 1` 或 `1 0 0 0` 都是合法測資，不可提早跳出）。
- **核心解決任務？（What is the core task you must solve?）**
  - 持續讀取多組 24 小時制起訖時間直到 `0 0 0 0` 為止，將時間轉換為總分鐘數並正確處理跨午夜情況後輸出相差分鐘數。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 考慮直接用小時相減 `h2 - h1` 再乘以 60 加上 `m2 - m1`，遇到 `m2 < m1` 時向小時借位、遇到 `h2 < h1` 時加 24 小時。
- **一開始注意到的困難、風險或模糊之處？**
  - 分開處理小時與分鐘的借位容易在邊界條件（例如 `h1 == h2` 但 `m2 < m1`，如 `10:30` 到 `10:15`）時漏判跨日而算出負數；相對地，若先把兩個時間都換算成「從 00:00 起算的總分鐘數」，所有借位問題都會自動消失。
- **為什麼最初的草稿尚未完整？**
  - 僅計算 `end - start` 的草稿在遇到跨午夜（`end < start`）時會輸出負數分鐘，且尚未包含 `0 0 0 0` 終止條件。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `while (cin >> h1 >> m1 >> h2 >> m2)` 讀取輸入，首先檢查 `if (h1 == 0 && m1 == 0 && h2 == 0 && m2 == 0) break;`；接著將兩個時刻統一換算為總分鐘數 `start = h1 * 60 + m1` 與 `end = h2 * 60 + m2`，計算 `diff = end - start`，若 `diff < 0` 則執行 `diff += 1440` 補上一天的分鐘數後輸出。
- **為什麼這個方法有效？**
  - 一天固定為 $24 \times 60 = 1440$ 分鐘，將二維的 `(小時, 分鐘)` 映射到一維的 `[0, 1439]` 分鐘軸後，跨日時間差就簡化為單一判斷 `if (diff < 0) diff += 1440;`，完全不會出現小時相同但分鐘倒退的借位錯誤，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 終止條件 `0 0 0 0`、僅部分為零的合法測資（如 `0 0 1 0` 與 `23 0 0 0`）、同小時但跨日（如 `12 30 12 15`，差 `1425` 分鐘），以及午夜前 1 分鐘到午夜後（`23 59 0 34`）。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$，總計 $T$ 組測資為 $O(T)$。
- **Space Complexity:** $O(1)$，僅使用常數個整數變數 `h1, m1, h2, m2, start, end, diff`。
- **Explanation:** 每筆測資僅需兩次乘法、兩次加法與一次條件判斷，在常數時間內即可完成。

---

## 4. Pseudocode
```text
START
1. WHILE 成功讀取四個整數 h1, m1, h2, m2:
2.     IF h1 == 0 AND m1 == 0 AND h2 == 0 AND m2 == 0 THEN
3.         BREAK (結束程式)
4.     END IF
5.     start = h1 * 60 + m1
6.     end = h2 * 60 + m2
7.     diff = end - start
8.     IF diff < 0 THEN
9.         diff = diff + 1440
10.    END IF
11.    輸出 diff 並換行
12. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期尚未加入跨午夜補正與終止條件的草稿)
```cpp
#include <iostream>
using namespace std;

// 撰寫過程中的未完成草稿：僅換算分鐘並直接相減，尚未處理跨午夜 (diff < 0) 與 0 0 0 0 終止條件
int main() {
    int h1, m1, h2, m2;
    cin >> h1 >> m1 >> h2 >> m2;
    int start = h1 * 60 + m1;
    int end = h2 * 60 + m2;
    cout << end - start << "\n";
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿在鬧鐘時間跨越午夜（例如 `23:59` 至 `00:34`）時會輸出負數 `-1405`，且缺少多筆讀取迴圈與 `0 0 0 0` 結束判斷。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<cmath>
#include<algorithm>
using namespace std;
int main()
{
	int h1, m1, h2, m2;
	while (cin >> h1 >> m1 >> h2 >> m2) {
		if (h1 == 0 && m1 == 0 && h2 == 0 && m2 == 0) { break; }
		int start = h1 * 60 + m1;
		int end = h2 * 60 + m2;
		int diff = end - start;
		if (diff < 0) {
			diff += 1440;
		}
		cout << diff << "\n";
	}
	return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 將時刻統一線性化為每日總分鐘數 `h * 60 + m`，並利用模 $1440$ 的概念在 `diff < 0` 時加上 `1440`，確保所有同日與跨午夜的時間差皆為正確的正整數，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `1 5 3 5` / `23 59 0 34` / `21 33 21 10` / `0 0 0 0` | `120` / `35` / `1417` | `120` / `35` / `1417` | 驗證官方範例的同日、跨午夜以及同小時跨日情況 |
| **Boundary case** | `0 0 23 59` / `23 59 0 0` / `0 0 0 0` | `1439` / `1` | `1439` / `1` | 測試一天內最大時間差（1439 分鐘）與跨午夜最小差（1 分鐘） |
| **Edge case** | `0 0 0 1` / `0 1 0 0` / `0 0 0 0` | `1` / `1439` | `1` / `1439` | 測試包含多個 `0` 的合法測資不會誤觸發 `0 0 0 0` 終止條件 |
| **Stress case** | UVa 官方多筆連續測資 | 全部通過 | Accepted | 驗證程式在官方評測集下的正確性與執行效率 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 直接計算 `end - start` | 加上 `if (diff < 0) diff += 1440;` 處理跨日 |
| **Edge Cases** | 跨午夜時輸出負數，且無法處理同小時跨日 | 完美處理所有跨午夜與含 `0` 時間組合 |
| **Output Handling** | 僅讀取一組測資即結束 | 使用 `while` 迴圈持續讀取直到 `0 0 0 0` 跳出 |
| **Complexity** | $O(1)$（未完成） | $O(1)$ per case |
| **Code Quality** | 缺少終止與跨日條件 | 單位統一、邏輯簡潔、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 不直接在「小時」與「分鐘」兩個維度上做複雜的 `if-else` 借位判斷，而是先統一換算成「總分鐘數」再處理跨日加 `1440`，大幅降低邏輯出錯機率。
- **學到的教訓（Lesson learned）：** 處理時間、角度或循環座標（週期性問題）時，先將複合單位換算成單一最小單位，並利用週期常數（如 $1440$ 分鐘）修正負值，是最乾淨且不易漏判邊界的標準技巧。
- **下一步行動（Next action）：** 未來遇到時鐘、鬧鐘或圓形循環距離計算題時，優先採用統一最小單位加上週期模運算的寫法。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11677 - Alarm Clock | Gemini | 協助將一次 AC 的單位換算策略、邊界條件與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
