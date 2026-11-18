# Code Review Report: UVa 579 - ClockHands

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 579
- **Problem Title:** ClockHands
- **Problem Link:** https://onlinejudge.org/external/5/579.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期未計入分針帶動時針偏移與未處理反角之草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa579.cpp](src/UVa579.cpp)
- **Review Date:** 2026-9-29

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，每一行包含一個以 `H:MM` 格式表示的 12 小時制時間（其中 $1 \le H \le 12$ ， $00 \le MM \le 59$ ）。當輸入為 `0:00` 時代表輸入結束，不需要輸出該行結果。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組非 `0:00` 的時間，輸出一行浮點數，代表該時刻類比時鐘「時針」與「分針」之間較小的夾角（範圍介於 $0.000^\circ$ 至 $180.000^\circ$ 之間），並四捨五入至小數點後三位。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 輸入的小時與分鐘之間夾有一個冒號字元 `:`，且小時範圍為 `1` 到 `12`（`12` 點整時時針與分針重合於 $0^\circ$ ）。
  - 時針並非整點才跳動，而是隨分針連續移動：每小時走 $360^\circ / 12 = 30^\circ$，每分鐘額外移動 $30^\circ / 60 = 0.5^\circ$。
  - 分針每分鐘走 $360^\circ / 60 = 6^\circ$。
  - 輸出必須固定顯示三位小數（例如 `90.000`）。
- **核心解決任務？（What is the core task you must solve?）**
  - 解析 `H:MM` 輸入，分別計算時針與分針相對於 12 點鐘方向的絕對角度，取兩者之劣弧夾角（ $\le 180^\circ$ ）並格式化輸出至小數點後三位。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 利用 `cin >> h >> unit >> m` 依序讀取小時整數、冒號字元與分鐘整數；接著分別算出時針角度與分針角度，相減後取絕對值。
- **一開始注意到的困難、風險或模糊之處？**
  - 有四個常見的細節陷阱需要避開：(1) `12:xx` 時小時為 `12`，必須先做 `h % 12` 歸零為 $0^\circ$；(2) 時針角度必須加上 `m * 0.5` 的分鐘偏移量；(3) 浮點數取絕對值必須使用 `<cmath>` 的 `fabs()`（避免在部分編譯環境誤呼叫整數版 `abs()` 截斷 `.5` 小數）；(4) 兩針夾角若大於 $180^\circ$，必須用 `360.0 - diff` 取較小的劣弧夾角。
- **為什麼最初的草稿尚未完整？**
  - 若只算 `(h % 12) * 30.0` 而忽略 `m * 0.5` 的時針微幅移動，或未用 `min(diff, 360.0 - diff)` 修正優角（ $> 180^\circ$ ），在非整點時刻（如 `9:00` 或 `12:30`）就會得到錯誤角度。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `while (cin >> h >> unit >> m)` 讀取輸入並以 `if (h == 0 && m == 0) break;` 判斷終止；計算時針角度 `hangle = (h % 12) * 30.0 + m * 0.5` 與分針角度 `mangle = m * 6.0`，取浮點數差值 `diff = fabs(hangle - mangle)` 後，以 `min(diff, 360.0 - diff)` 取得不超過 $180^\circ$ 的最小夾角，並使用 `cout << fixed << setprecision(3) << ans << "\n";` 輸出。
- **為什麼這個方法有效？**
  - 以 12 點鐘方向為 $0^\circ$ 基準線，時針與分針的位置皆是時間的線性函數，無需拆解字串即可透過 `char unit` 乾淨解析 `:` 分隔符；搭配 `fabs` 保留 `0.5` 小數精度，以及 `min(diff, 360.0 - diff)` 處理圓周劣弧，首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 終止條件 `0:00`、12 點整重合（`12:00` 輸出 `0.000`）、含半度小數的時刻（如 `12:30` 輸出 `165.000`、`3:15` 輸出 `7.500`），以及夾角大於 $180^\circ$ 需取補角的時刻（如 `9:00` 差值 $270^\circ$ 需轉換為 `90.000`）。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$，總計 $T$ 組測資為 $O(T)$。
- **Space Complexity:** $O(1)$，僅使用常數個整數、字元與雙精度浮點數變數。
- **Explanation:** 每筆測資僅執行常數次浮點數四則運算與格式化輸出，執行速度極快。

---

## 4. Pseudocode
```text
START
1. WHILE 成功讀取小時 h、分隔字元 unit、分鐘 m:
2.     IF h == 0 AND m == 0 THEN
3.         BREAK (結束程式)
4.     END IF
5.     hangle = (h % 12) * 30.0 + m * 0.5
6.     mangle = m * 6.0
7.     diff = fabs(hangle - mangle)
8.     ans = min(diff, 360.0 - diff)
9.     以固定小數點後 3 位格式輸出 ans 並換行
10. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期未計入時針分鐘偏移與劣弧修正的草稿)
```cpp
#include <iostream>
#include <cmath>
using namespace std;

// 撰寫過程中的未完成草稿：漏掉時針隨分鐘移動的 m * 0.5 偏移量，且未將超過 180 度的夾角轉換為劣弧
int main() {
    int h, m;
    char unit;
    while (cin >> h >> unit >> m) {
        if (h == 0 && m == 0) break;
        double hangle = (h % 12) * 30.0;
        double mangle = m * 6.0;
        cout << fabs(hangle - mangle) << "\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿將時針固定在整點刻度（缺少 `+ m * 0.5`），且未用 `min(diff, 360.0 - diff)` 處理大於 $180^\circ$ 的夾角（例如 `9:00` 會輸出 `270` 而非 `90.000`），也缺少 `fixed << setprecision(3)` 格式化輸出。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
int main()
{
	int h, m;
	char unit;
	while (cin >> h >> unit >> m) {
		if (h == 0 && m == 0) { break; }
		double hangle = (h % 12) * 30.0 + m * 0.5;
		double mangle = m * 6.0;
		double diff = fabs(hangle - mangle);
		double ans = min(diff, 360.0 - diff);
		cout << fixed << setprecision(3) << ans << "\n";
	}
	return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 透過 `(h % 12) * 30.0 + m * 0.5` 精確還原時針的連續角度，搭配 `fabs` 保留小數精度與 `min(diff, 360.0 - diff)` 確保夾角恆落在 $[0^\circ, 180^\circ]$ 區間內，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `12:00` / `9:00` / `8:10` / `0:00` | `0.000` / `90.000` / `175.000` | `0.000` / `90.000` / `175.000` | 驗證官方範例的重合、優角取補角（ $270^\circ \rightarrow 90^\circ$ ）與一般時刻 |
| **Boundary case** | `6:00` / `12:01` / `11:59` / `0:00` | `180.000` / `5.500` / `5.500` | `180.000` / `5.500` / `5.500` | 測試最大夾角 $180^\circ$ 與 `12` 點整前後跨零點的對稱性 |
| **Edge case** | `3:15` / `12:30` / `0:00` | `7.500` / `165.000` | `7.500` / `165.000` | 驗證時針隨分鐘偏移的 `0.5` 小數精度未被截斷 |
| **Stress case** | 完整 12 小時內所有 720 分鐘時刻 | 皆輸出精確至三位小數的劣弧角度 | Accepted | 驗證程式在所有合法時刻組合下的精度與穩定性 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 未計入時針的分鐘偏移且未修正 $>180^\circ$ 優角 | 完整計算 `m * 0.5` 偏移並取 `min(diff, 360.0 - diff)` |
| **Edge Cases** | `12:xx` 與 `9:00` 等時刻角度錯誤 | 正確處理 `h == 12` 歸零、半度小數與 `0:00` 終止 |
| **Output Handling** | 預設浮點格式（位數不固定） | 使用 `fixed << setprecision(3)` 嚴格輸出三位小數 |
| **Complexity** | $O(1)$（未完成） | $O(1)$ per case |
| **Code Quality** | 缺少精度格式化與劣弧轉換 | 簡潔精準、善用 `char unit` 解析冒號、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在實作前先確認四個幾何與語法細節——用 `char unit` 吃掉冒號、用 `h % 12` 處理 12 點鐘、用 `fabs` 避免整數截斷小數，以及用 `min(diff, 360.0 - diff)` 處理圓周劣弧，讓程式一次就做到位。
- **學到的教訓（Lesson learned）：** 在 C++ 處理浮點數絕對值時應明確使用 `fabs()` 並搭配 `<iomanip>` 的 `fixed << setprecision(k)` 控制小數位數，能有效避免浮點精度與格式錯誤。
- **下一步行動（Next action）：** 未來遇到幾何角度、浮點數格式化或含特定分隔符號（如 `:`、`/`）的輸入題時，延續 `cin >> num1 >> sep >> num2` 與 `<iomanip>` 的標準寫法。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 579 - ClockHands | Gemini | 協助將一次 AC 的幾何角度推導、浮點數細節與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
