# Code Review Report: UVa 10071 - Back to High School Physics

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10071
- **Problem Title:** Back to High School Physics
- **Problem Link:** https://onlinejudge.org/external/100/10071.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted
- **Source Code (Initial/Fail):** N/A（第一週因大二以上加退選時程尚未加選，未參加現場上機考，此為課後補寫之初版草稿）
- **Source Code (Final/Accepted):** [src/UVa10071.cpp](src/UVa10071.cpp)
- **Review Date:** 

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料直到檔案結尾（EOF）。每一行提供兩個整數：質點在時間 $t$ 時的速度 $v$（ $-100 \le v \le 100$ ），以及經過的時間 $t$（ $0 \le t \le 200$ ）。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組 $(v, t)$，輸出一行單一整數，代表該質點從靜止（ $v_0 = 0$ ）開始做等加速度運動，在經過 $2t$ 秒後的總位移。
- **主要規則與限制條件？（What are the main rules or constraints?）**
  - 加速度 $a$ 為定值，且 $t = 0$ 時的初速度為 $0$。
  - 速度 $v$ 可能為負數、零或正數，而時間 $t$ 必為非負整數（包含 $t = 0$）。
- **核心解決任務？（What is the core task you must solve?）**
  - 利用等加速度運動學公式推導出 $2t$ 時間內的位移化簡式，並針對每組輸入持續計算輸出直到 EOF。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 補寫時最初的想法是先用 $a = v / t$ 算出加速度，再代入位移公式 $s = \frac{1}{2} a (2t)^2$ 計算結果。
- **一開始注意到的困難、風險或模糊之處？**
  - 當測資出現 $t = 0$ 時，計算 `a = v / t` 會發生「除以零」的執行期錯誤（Runtime Error / `SIGFPE`）；此外，若使用整數除法 `v / t`，當 $v$ 不能被 $t$ 整除時會發生無條件捨去誤差。
- **為什麼最初的想法不夠完整或沒有效率？**
  - 先求加速度 $a$ 再代回公式會引入不必要的除法與浮點數誤差，且在 $t = 0$ 的邊界情況下會直接當機。

### Final Strategy
- **最終採用什麼方法？**
  - 在寫程式前先將運動學公式進行代數化簡：
    $$s(2t) = \frac{1}{2} a (2t)^2 = \frac{1}{2} \left(\frac{v}{t}\right) (4t^2) = 2vt$$
  - 直接在 `while (cin >> v >> t)` 迴圈內輸出 `2 * v * t`。
- **為什麼這個方法有效？**
  - 由於初速為 $0$ 且等加速度運動的速度隨時間線性變化，在 $[0, 2t]$ 區間內的平均速度恰好就是時間中點 $t$ 時的速度 $v$，因此總位移即為「平均速度 $v \times$ 總時間 $2t = 2vt$」。全程僅需整數乘法，完全避開除法問題。
- **考慮了哪些邊界條件（Edge cases）？**
  - $t = 0$（原本 $a = v/t$ 會除以零當機）、負速度 $v < 0$（反向運動位移為負），以及最大乘積 $\vert{}2 \cdot 100 \cdot 200\vert{} = 40000$（遠小於 32 位元 `int` 上限，無溢位風險）。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(1)$，總計 $T$ 組測資為 $O(T)$。
- **Space Complexity:** $O(1)$，僅使用兩個整數變數 $v$ 與 $t$。
- **Explanation:** 每筆測資只需執行一次整數乘法，時間與空間開銷皆為常數級別。

---

## 4. Pseudocode
```text
START
1. WHILE 持續讀取整數 v 與 t 直到 EOF:
2.     計算 displacement = 2 * v * t
3.     輸出 displacement 並換行
4. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Fail Code
```cpp
#include <bits/stdc++.h>
using namespace std;

// 第一週因加退選尚未入班而缺考；此為課後補寫時最初的未完成草稿（存在除以 t 當機與缺少 EOF 迴圈問題）
int main() {
    int v, t;
    cin >> v >> t;
    int a = v / t;
    cout << 0.5 * a * (2 * t) * (2 * t) << "\n";
    return 0;
}
```

**Why it failed:**
- **未完成／缺陷原因：** 第一週開學時因大二以上加退選時程尚未完成加選，未參加當週現場上機考；課後補寫草稿時，若直接計算 `a = v / t` 會在 $t = 0$ 時觸發除以零錯誤（Runtime Error），且當 $v$ 無法被 $t$ 整除時會因整數除法截斷小數導致答案錯誤。
- **會導致錯誤的測資情境：** 輸入 `0 0`（程式崩潰）或輸入 `3 2`（整數除法 `3 / 2 = 1` 導致錯誤輸出 `8`，正確應為 `12`）。

### Correct Code
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int v, t;
    while (cin >> v >> t) {
        cout << 2 * v * t << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 透過代數約分將分母的 $t$ 消去（ $s = \frac{1}{2} \cdot \frac{v}{t} \cdot 4t^2 = 2vt$ ），使所有運算皆為精確的整數乘法。
- **如何解決原本失敗的情境：** 輸入 `0 0` 時，`2 * 0 * 0` 安全輸出 `0`；輸入 `3 2` 時，`2 * 3 * 2` 精確輸出 `12`；`while (cin >> v >> t)` 確保所有測資皆處理完畢直到 EOF。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `5 12` | `120` | `120` | 驗證一般正速度與正時間的計算 |
| **Boundary case** | `0 0` 與 `-100 200` | `0` 與 `-40000` | `0` 與 `-40000` | 測試 $t=0$ 零時間邊界與題目允許的最大/最小乘積 |
| **Edge case** | `3 2` 與 `-5 4` | `12` 與 `-40` | `12` 與 `-40` | 驗證 $v$ 無法被 $t$ 整除以及負速度的情況 |
| **Stress case** | $10^5$ 組 $[-100, 100] \times [0, 200]$ 測資 | 皆輸出精確的 $2vt$ | 皆輸出精確的 $2vt$ | 驗證連續讀取至 EOF 的執行效率 |

- **關於補寫與測試的說明：** 補寫完成後已於本地端測試上述四類測資，並正式提交至 UVa Online Judge 確認取得 Accepted。

---

## 7. Difference and Reflection

### Key Differences
| Item | Fail Code (Initial Draft) | Correct Code |
| :--- | :--- | :--- |
| **Logic** | 先求加速度 $a = v/t$ 再代公式 | 直接使用化簡後的公式 $2vt$ |
| **Edge Cases** | $t = 0$ 時當機；$t \nmid v$ 時失真 | 完美支援 $t = 0$、負速度與非整除組合 |
| **Output Handling** | 僅處理單行輸入 | 使用 `while (cin >> v >> t)` 處理至 EOF |
| **Complexity** | $O(1)$ | 每組 $O(1)$ |
| **Code Quality** | 存在除法風險且缺少多筆測資迴圈 | 簡潔、零誤差的純整數運算 |

### Reflection
- **根本原因（Root cause）：** 第一週因加退選尚未入班而錯過現場練習，補題時初期容易直接照搬物理公式而不先做代數化簡，也容易忘記 UVa 預設多筆測資直到 EOF 的輸入規範。
- **學到的教訓（Lesson learned）：** 撰寫數學或物理計算題前，務必先做代數化簡，盡可能消去分母與浮點數運算，能大幅降低邊界錯誤與溢位風險。
- **下一步行動（Next action）：** 遇到公式推導題時先化簡至最簡整數形式，並在 UVa 題目中預設使用 `while (cin >> ...)` 讀取多筆輸入。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10071 - Back to High School Physics | Gemini | 協助確認位移公式的代數化簡與邊界條件，並整理 Code Review Report 格式 | 親自於本地編譯測試 $t=0$、$v<0$ 等測資，並上傳 UVa 確認取得 Accepted |

---

## 9. Final Re-review Checklist
- [x] The problem information, source-code links, and submission result are accurate.
- [x] The problem statement and reflection are written in my own words.
- [x] The strategy, pseudocode, and complexity analysis match the final code.
- [x] The fail-code explanation identifies a reproducible failing case or clearly explains what was incomplete.
- [x] The test table includes actual evidence for normal, boundary, and edge cases.
- [x] The AI usage record is complete and accurate.
