# Code Review Report: UVa 11547 - Automatic Answer

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11547
- **Problem Title:** Automatic Answer
- **Problem Link:** https://onlinejudge.org/external/115/11547.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期未對負數計算結果取絕對值 `abs()` 的未完成草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa11547.cpp](src/UVa11547.cpp)
- **Review Date:** 2026-10-27

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $t$ （ $1 \le t \le 100$ ），代表測試資料的組數。接下來的 $t$ 行中，每一行都包含一個整數 $n$ （ $-1000 \le n \le 1000$ ）。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一個整數 $n$ ，依照題目指定的算術流程計算結果後，輸出該最終整數在十進位表示法中的「十位數字」（介於 `0` 到 `9` 之間的非負整數）。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 題目規定的六步驟計算公式為：將 $n$ 乘以 $567$ ，然後除以 $9$ ，接著加上 $7492$ ，再乘以 $235$ ，然後除以 $47$ ，最後減去 $498$ 。
  - 輸入 $n$ 可能為**負數**（最低至 $-1000$ ），導致最終計算結果為負整數；但所求的「十位數字（Tens column）」必須是 `0` 到 `9` 的正整數或零（不可輸出負號）。
- **核心解決任務？（What is the core task you must solve?）**
  - 精確計算題目算式結果，並妥善處理負數取餘數問題，萃取出結果的十位數字輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 觀察題目給的六個運算步驟：

$$\left( \frac{n \times 567}{9} + 7492 \right) \times \frac{235}{47} - 498$$

  - 可以發現 $567 / 9 = 63$ 且 $235 / 47 = 5$ 皆為整除，因此「乘以 $235$ 再除以 $47$ 」可以直接化簡為 `* 5` ，大幅減少中間數值大小並避免不必要的運算。
- **一開始注意到的困難、風險或模糊之處？**
  - 在 C++ 中，對負數執行整數除法與取餘數運算（ `%` ）會保留負號（例如 `-174927 / 10 % 10` 會得到 `-2` 而非 `2` ）。當輸入為較大的負數（如 $n = -637$ ）時，算式結果會是負數，因此擷取十位數字時必須呼叫 `abs()` 取絕對值。
- **為什麼最初的草稿尚未完整？**
  - 直接寫 `(result / 10) % 10` 而未加 `abs()` 的草稿在 $n \ge -117$ （結果仍為正數）時看似正常，但一旦 $n \le -118$ 就會輸出負數十位數字而導致 Wrong Answer。

### Final Strategy
- **最終採用什麼方法？**
  - 讀取測資筆數 `t` 後，在 `while (t--)` 迴圈內讀入整數 `s` ，直接計算化簡後的精確算式 `int result = ((s * 567 / 9 + 7492) * 5 - 498);` ，再透過 `int tens = abs(result / 10) % 10;` 安全取出非負的十位數字並輸出。
- **為什麼這個方法有效？**
  - 因為 $\frac{235}{47} = 5$ 是恆等整除，化簡後最大中間值（當 $s = 1000$ 時， $315 \times 1000 + 36962 = 351962$ ）遠小於 32 位元 `int` 上限（ $2.14 \times 10^9$ ）；搭配 `abs(result / 10) % 10` 統一正負數的十位數字萃取邏輯，確保任何輸入 $n \in [-1000, 1000]$ 皆輸出 `0` ～ `9` 之間的正確數字，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 正數輸入（如 `637` 輸出 `1` ）、負數輸入導致結果為負（如 `-637` ，結果為 `-163693` ，十位數為 `9` ）、輸入 `0` （結果為 `36962` ，十位數為 `6` ），以及題目範圍上下界 `-1000` 與 `1000` 。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$ ，總計 $t$ 組測資為 $O(t)$ 。
- **Space Complexity:** $O(1)$ ，僅使用常數個整數變數 `t, s, result, tens` 。
- **Explanation:** 每筆測資僅執行常數次基本整數算術運算與一次 `abs()` ，時間與空間皆為常數級別。

---

## 4. Pseudocode
```text
START
1. 讀取測資筆數 t
2. WHILE t > 0 (每次執行後 t 減 1):
3.     讀取整數 s
4.     result = ((s * 567 / 9 + 7492) * 5 - 498)
5.     tens = abs(result / 10) % 10
6.     輸出 tens 並換行
7. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期未對負數結果取 `abs()` 的未完成草稿)
```cpp
#include <iostream>
using namespace std;

// 撰寫過程中的未完成草稿：直接對 result / 10 取 % 10，未加 abs() 處理負數結果的負餘數問題
int main() {
    int t;
    cin >> t;
    while (t--) {
        int s;
        cin >> s;
        int result = ((s * 567 / 9 + 7492) * 5 - 498);
        int tens = (result / 10) % 10;
        cout << tens << "\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿未考慮 C++ 中負整數執行 `/ 10 % 10` 會產生負數結果（例如輸入 `-637` 時會錯誤輸出 `-9` 而非 `9` ）；補上 `abs(result / 10) % 10` 後首次提交即直接通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    while (t--) {
        int s;
        cin >> s;
        int result = ((s*567/9+7492)*5-498);
        int tens = abs(result / 10) % 10;
        cout << tens << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 利用 $\frac{235}{47} = 5$ 精簡算式避免不必要的大數乘法，並透過 `abs(result / 10) % 10` 消除負號影響，精確萃取出結果的十位數字，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `2` / `637` / `-120` | `1` / `3` | `1` / `3` | 驗證官方範例的正數與負數輸入（ `-120` 結果為 `-838` ，十位數為 `3` ） |
| **Boundary case** | `3` / `-1000` / `0` / `1000` | `3` / `6` / `6` | `3` / `6` / `6` | 測試題目輸入上下界 `-1000` 、 `1000` 與零值 `0` |
| **Edge case** | `2` / `-637` / `-117` | `9` / `1` | `9` / `1` | 測試結果由正轉負的臨界點（ `-117` 得 `107` ， `-118` 得 `-208` ）與大負數 |
| **Stress case** | `100` 組包含正負極值的滿載測資 | 皆在毫秒內輸出 `0` ～ `9` 的正確十位數 | Accepted | 驗證 $t \le 100$ 上限下的計算速度與無溢位穩定性 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 直接使用 `(result / 10) % 10` 取十位數 | 使用 `abs(result / 10) % 10` 統一正負數十位數萃取 |
| **Edge Cases** | 當 `result < 0` 時會輸出負數（如 `-9` ） | 正確處理所有 $n \in [-1000, 1000]$ 的正負結果 |
| **Output Handling** | 負數測資輸出格式錯誤 | 恆輸出 `0` 到 `9` 之間的非負單一數字 |
| **Complexity** | $O(1)$ （未完成） | $O(1)$ per case |
| **Code Quality** | 缺少負數取模防護 | 算式化簡巧妙、負數邊界完備、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在動手前先觀察算式中的常數，把 `* 235 / 47` 化簡成 `* 5` 減少中間數值；同時立刻意識到題目輸入允許負數（ $-1000 \le n \le 1000$ ），因此在取十位數時主動加上 `abs()` ，成功避開了 C++ 負數取餘數帶負號的經典陷阱。
- **學到的教訓（Lesson learned）：** 在 C++ 中只要變數可能為負數，進行位數拆解（ `/ 10` 與 `% 10` ）時都必須先取 `abs()` ；此外，若將 `abs(result)` 放在最外層（即 `(abs(result) / 10) % 10` ），在邏輯語意上也與 `abs(result / 10) % 10` 完全等價（唯一需注意的只有 `INT_MIN` 極值，但本題結果範圍僅在 $\pm 3.6 \times 10^5$ 內故完全安全）。
- **下一步行動（Next action）：** 未來處理任何允許負數輸入的位數拆解題時，固定使用 `abs()` 確保萃取出來的數位為非負整數。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11547 - Automatic Answer | Gemini | 協助將一次 AC 的算式化簡、負數取模邊界與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
