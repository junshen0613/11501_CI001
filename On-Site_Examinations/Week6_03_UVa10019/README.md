# Code Review Report: UVa 10019 - Funny Encryption Method

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10019
- **Problem Title:** Funny Encryption Method
- **Problem Link:** https://onlinejudge.org/external/100/10019.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期將十六進位還原為大整數再統計位元的未完成草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa10019.cpp](src/UVa10019.cpp)
- **Review Date:** 2026-10-13

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $N$ （ $N \le 1000$ ），代表測試資料的組數。接下來的 $N$ 行中，每一行都包含一個十進位正整數 $M$ （ $0 < M < 10000$ ）。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一個正整數 $M$ ，計算並輸出一行以單一空格分隔的兩個整數 `b1 b2` ：
    - `b1` ：將 $M$ 視為**十進位**整數並轉換為二進位後，其中位元 `1` 的總個數。
    - `b2` ：將 $M$ 的數字字串直接視為**十六進位**整數並轉換為二進位後，其中位元 `1` 的總個數。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 輸入的 $M$ 皆為由數字 `0` 到 `9` 組成的四位數以內正整數（不含 `A` ～ `F` ）。
  - 計算 `b2` 時，不需要真的計算出該十六進位數的十進位數值，只需統計其對應二進位表示中的 `1` 總數即可。
- **核心解決任務？（What is the core task you must solve?）**
  - 針對每組輸入 $M$ ，分別求出其十進位數值與十六進位數值在二進位表示下的 `1` 位元個數 `b1` 與 `b2` 。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 計算 `b1` 很直覺，只要對 `m` 反覆執行除以 2 取餘數（ `x % 2 == 1` ），統計餘數為 `1` 的次數即可；而計算 `b2` 時，最初容易想到先把 `m` 的每位數乘上 $16^k$ 還原成十進位整數 $X_2$ ，再對 $X_2$ 統計二進位 `1` 的個數。
- **一開始注意到的困難、風險或模糊之處？**
  - 若先將 `m` 還原為十六進位對應的十進位數值（例如 $9999_{16} = 39321_{10}$ ），不僅多了一道進位換算，若未來題目位數變長還會有整數溢位風險；進一步分析十六進位與二進位的關係後發現：**每 1 個十六進位數字剛好獨立對應 4 個二進位位元（Nibble），彼此之間完全不會互相進位影響**，因此只需把 `m` 的十進位各位數字逐一取出，分別計算各自二進位 `1` 的個數再相加，就完全等價於 `b2` 。
- **為什麼最初的草稿尚未完整？**
  - 尚未抽出共用的位元計數函式 `sss(int x)` 與逐位拆解計算 `b2` 的草稿無法直接算出十六進位解讀下的 `1` 總數。

### Final Strategy
- **最終採用什麼方法？**
  - 撰寫一個輔助函式 `int sss(int x)` ，透過 `while (x > 0)` 累加 `x % 2 == 1` 的次數並回傳；在 `main()` 中讀取每組 `m` 後：
    1. 直接呼叫 `int b1 = sss(m);` 求得十進位下的 `1` 位元個數。
    2. 使用暫存變數 `temp = m` 搭配 `while (temp > 0)` 逐一取出十進位各位數字 `digit = temp % 10` ，累加 `b2 += sss(digit)` 後執行 `temp /= 10` ，求得十六進位下的 `1` 位元總數。
    3. 輸出 `b1 << " " << b2 << "\n"` 。
- **為什麼這個方法有效？**
  - 因為 $16 = 2^4$ ，任何十六進位數 $\sum_{k=0}^{d} c_k \cdot 16^k$ 的二進位展開就是將每個 $c_k \in [0, 9]$ 的 4 位元二進位區塊直接串接在一起，故總 `1` 的個數嚴格等於 $\sum_{k=0}^{d} \text{popcount}(c_k)$ ；重用同一個 `sss()` 函式既避免了重複程式碼，也完全免除十六進位轉十進位步驟，首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 最小正整數 `1` （ `b1 = 1, b2 = 1` ）、2 的冪次（如 `16` ：十進位 $16_{10} = 10000_2 \implies b_1 = 1$ ；十六進位 $16_{16} = 0001\,0110_2 \implies b_2 = 1 + 2 = 3$ ）、含 `0` 位數的數字（如 `100` ： `sss(0)` 回傳 `0` 不影響加總），以及題目上限 `9999` 。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(\log_2 M)$ ，總計 $N$ 組測資為 $O(N \log_2 M)$ 。
- **Space Complexity:** $O(1)$ ，僅使用常數個整數變數 `t, m, b1, b2, temp, digit, cnt` 。
- **Explanation:** 計算 `b1` 需執行 $\lfloor \log_2 M \rfloor + 1$ 次（最多 14 次）除以 2；計算 `b2` 最多拆解 4 個十進位位數，每位數最多執行 4 次除以 2（共 16 次），單組測資在數十次基本運算內即可完成。

---

## 4. Pseudocode
```text
FUNCTION sss(x):
    cnt = 0
    WHILE x > 0:
        IF x % 2 == 1 THEN
            cnt = cnt + 1
        END IF
        x = x / 2
    END WHILE
    RETURN cnt
END FUNCTION

START
1. 讀取測資筆數 t (若讀取失敗則結束)
2. WHILE t > 0 (每次執行後 t 減 1):
3.     讀取正整數 m
4.     b1 = sss(m)
5.     b2 = 0
6.     temp = m
7.     WHILE temp > 0:
8.         digit = temp % 10
9.         b2 = b2 + sss(digit)
10.        temp = temp / 10
11.    END WHILE
12.    輸出 b1 + " " + b2 並換行
13. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期僅計算十進位位元數 `b1` 的草稿)
```cpp
#include <iostream>
using namespace std;

// 撰寫過程中的未完成草稿：僅實作了十進位轉二進位統計 b1，尚未加入十六進位逐位統計 b2 的邏輯
int main() {
    int t;
    cin >> t;
    while (t--) {
        int m, b1 = 0;
        cin >> m;
        int temp = m;
        while (temp > 0) {
            if (temp % 2 == 1) b1++;
            temp /= 2;
        }
        cout << b1 << "\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿僅算出了十進位解讀下的 `1` 個數 `b1` ，缺少將 `m` 各位數拆開並重複利用位元計數函式累加 `b2` 的步驟；將位元統計邏輯抽成 `sss(int x)` 並補上逐位計算 `b2` 後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
using namespace std;
int sss(int x) {
	int cnt = 0;
	while (x > 0) {
		if (x % 2 == 1)cnt++;
		x /= 2;
	}
	return cnt;
}
int main()
{
	int t;
	if (!(cin >> t))return 0;
	while (t--) {
		int m;
		cin >> m;
		int b1 = sss(m);
		int b2 = 0;
		int temp = m;
		while (temp > 0) {
			int digit = temp % 10;
			b2 += sss(digit);
			temp /= 10;
		}
		cout << b1 << " " << b2 << "\n";
	}
	return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 利用十六進位單一數位與 4-bit 二進位一對一無進位對應的性質，將 `b2` 轉化為各十進位數字的二進位 `1` 個數之和，重用 `sss(int x)` 同時完成 `b1` 與 `b2` 的計算，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `3` / `265` / `111` / `1234` | `3 5` / `6 3` / `5 5` | `3 5` / `6 3` / `5 5` | 驗證官方範例三組測資的 `b1` 與 `b2` 計算結果 |
| **Boundary case** | `2` / `1` / `9999` | `1 1` / `8 8` | `1 1` / `8 8` | 測試最小正整數 $M = 1$ 與題目最大上限 $M = 9999$ |
| **Edge case** | `3` / `10` / `16` / `100` | `2 1` / `1 3` / `3 1` | `2 1` / `1 3` / `3 1` | 測試包含零位數的數字與 2 的冪次在十進位／十六進位下的差異 |
| **Stress case** | `1000` 組最大測資 | 皆在毫秒內輸出正確 `b1 b2` | Accepted | 驗證 $N \le 1000$ 上限下的執行速度與安全性 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 僅在 `main()` 內計算十進位下的 `b1` | 抽出 `sss(x)` 函式，同時支援 `b1` 與逐位計算 `b2` |
| **Edge Cases** | 缺少 `b2` 計算與輸入讀取防護 `!(cin >> t)` | 完整處理含零位數（ `sss(0) == 0` ）與所有正整數上限 |
| **Output Handling** | 僅輸出單一數值 | 嚴格輸出 `b1 b2` 並以單一空格分隔 |
| **Complexity** | $O(\log_2 M)$ （未完成） | $O(\log_2 M)$ per case |
| **Code Quality** | 邏輯重複度高 | 函式重用性佳、無大數轉進位溢位風險、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 透過進位制特性直接發現「把十進位數字當成十六進位解讀時，每個位數的二進位 `1` 個數是完全獨立的」，因此不需要先把數字還原成十六進位數值，直接把二進位 `1` 計數包成 `sss(int x)` 函式並重用兩次即可完成，程式碼既短又不易出錯。
- **學到的教訓（Lesson learned）：** 善用輔助函式（Helper function）封裝重複的位元運算邏輯，並結合進位制（如 $16 = 2^4$ ）的區塊獨立性，往往能省去不必要的數值轉換與溢位風險。
- **下一步行動（Next action）：** 未來遇到涉及二進位、八進位（ $8 = 2^3$ ）或十六進位（ $16 = 2^4$ ）位元統計的題目時，優先利用「每位獨立對應固定位元區塊」的性質簡化實作。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10019 - Funny Encryption Method | Gemini | 協助將一次 AC 的十六進位區塊獨立性原理、邊界案例與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
