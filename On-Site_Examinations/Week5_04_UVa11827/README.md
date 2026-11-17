# Code Review Report: UVa 11827 - Maximum GCD

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 11827
- **Problem Title:** Maximum GCD
- **Problem Link:** https://onlinejudge.org/external/118/11827.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期未清除 `cin >> t` 殘留換行符的未完成草稿與最終 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa11827.cpp](src/UVa11827.cpp)
- **Review Date:** 2026-10-6

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $N$ ，代表測試資料的組數。接下來的 $N$ 行中，每一行都包含 $M$ 個（ $1 < M < 100$ ）以空格分隔的正整數，且所有數字皆小於 $2^{31}$ 。每行包含的整數個數 $M$ 並未事先給定。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一行測資，從該行所有不同的位置數對 $(i, j)$ （ $i \neq j$ ）中，找出所有兩兩最大公因數 $\gcd(a_i, a_j)$ 的最大值，並輸出一行該最大公因數。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 每行的數字個數 $M$ 不固定（最多不超過 99 個），必須以「整行讀取」的方式解析，不能跨行誤讀下一組測資的數字。
  - 若同一行中出現兩個相同的正整數 $x$ （例如 `5 5` ），因位於不同索引位置（ $i \neq j$ ），它們的最大公因數 $\gcd(x, x) = x$ 也必須納入比較。
  - 任兩個正整數的最大公因數至少為 $1$ 。
- **核心解決任務？（What is the core task you must solve?）**
  - 正確切分每行不定個數的正整數存入動態陣列，並兩兩計算最大公因數以找出該行的最大 $\gcd$ 值。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 因為每行整數數量未知，必須使用 `getline(cin, line)` 讀取整行字串，再透過 `stringstream` 逐一抽取出整數放入 `vector<int> nums` 中；接著用兩層迴圈枚舉所有 $0 \le i < j < \text{nums.size()}$ 的數對，呼叫輾轉相除法 `gcd(nums[i], nums[j])` 並維護最大值 `max_ans` 。
- **一開始注意到的困難、風險或模糊之處？**
  - 在 C++ 中混合使用 `cin >> t;` 與 `getline(cin, line);` 時，`cin >> t` 會把第一行數字後方的換行字元 `\n` 留在輸入緩衝區中；若不先用一次 `getline` 把該換行字元消耗掉，迴圈第一次呼叫 `getline` 就會讀到空字串，導致第一組測資的 `nums` 為空並使後續測資全部錯位。
- **為什麼最初的草稿尚未完整？**
  - 未在 `cin >> t` 之後清除緩衝區換行符的草稿會造成第一組測資讀入空行、輸出錯誤的預設值 `1` 且漏算最後一組測資。

### Final Strategy
- **最終採用什麼方法？**
  - 先讀取 `cin >> t;` 並緊接著執行一次 `getline(cin, line);` 清空首行殘留的換行字元；進入 `while (t--)` 後，每輪以 `getline(cin, line)` 讀取整行測資，透過 `stringstream ss(line)` 將該行所有整數存入 `vector<int> nums` ；初始化 `int max_ans = 1;` ，利用雙層迴圈遍歷所有 `i < j` 的索引組合並持續更新 `max_ans = max(max_ans, gcd(nums[i], nums[j]))` 後輸出。
- **為什麼這個方法有效？**
  - `getline` 搭配 `stringstream` 完美隔離了不同行測資的邊界，無論每行有幾個數字或數字間有多少空格都能精準解析；雙層迴圈遍歷所有不同位置的數對 $(i, j)$ （包含數值相同但位置不同的元素），配合迭代式歐幾里得演算法 `gcd`，在 $M < 100$ 的規模下瞬間即可得出精確最大值，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 首行 `cin >> t` 後的換行符處理、一行僅有兩個互質數字（如 `7 13` ，輸出 `1` ）、一行內包含重複數字（如 `12 12 5` ，輸出 `12` ），以及數字接近 $2^{31} - 1$ 的大數 `gcd` 計算。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(M^2 \log(\max A_i))$ ，總計 $N$ 組測資為 $O(N \cdot M^2 \log(\max A_i))$ 。
- **Space Complexity:** $O(M)$ ，使用 `string` 與 `vector<int>` 儲存單行最多 $M$ 個整數。
- **Explanation:** 每行最多 $M < 100$ 個數字，雙層迴圈最多執行 $\frac{99 \times 98}{2} = 4851$ 次 `gcd` 呼叫，每次輾轉相除法最多約 $\log_2(2^{31}) \approx 31$ 步，單組總運算量僅約 $1.5 \times 10^5$ 次，執行速度極快。

---

## 4. Pseudocode
```text
FUNCTION gcd(a, b):
    WHILE b != 0:
        temp = a % b
        a = b
        b = temp
    END WHILE
    RETURN a
END FUNCTION

START
1. 讀取測資筆數 t
2. 呼叫一次 getline 消耗首行數字後的換行字元
3. WHILE t > 0 (每次執行後 t 減 1):
4.     讀取一整行字串 line
5.     將 line 放入 stringstream 並依序讀取所有整數存入陣列 nums
6.     初始化 max_ans = 1
7.     FOR i = 0 TO nums.size() - 1:
8.         FOR j = i + 1 TO nums.size() - 1:
9.             max_ans = max(max_ans, gcd(nums[i], nums[j]))
10.        END FOR
11.    END FOR
12.    輸出 max_ans 並換行
13. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期未清除緩衝區換行符的未完成草稿)
```cpp
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// 撰寫過程中的未完成草稿：cin >> t 後未先執行 getline 吃掉殘留的 '\n'，會導致第一次 getline 讀到空行
int main() {
    int t;
    cin >> t;
    string line;
    while (t--) {
        getline(cin, line); // 首輪會直接讀到第一行 t 後方的換行字元
        stringstream ss(line);
        vector<int> nums;
        int x;
        while (ss >> x) nums.push_back(x);
        // ... 後續計算 max gcd
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿在 `cin >> t;` 之後未清除輸入緩衝區中的換行符號，導致迴圈第一次 `getline` 讀入空字串、使 `nums` 為空並輸出錯誤的初始值 `1` ，且會少讀取最後一行實際測資。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<vector> 
#include<string> 
#include<sstream> 
#include<algorithm>
using namespace std;
int gcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}
int main()
{
    int t;
    cin >> t;
    string line;
    getline(cin, line);
    while (t--) {
        getline(cin, line);
        stringstream ss(line);
        vector<int> nums;
        int x;
        while (ss >> x) {
            nums.push_back(x);
        }
        int max_ans = 1;
        for (int i = 0; i < nums.size(); i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                max_ans = max(max_ans, gcd(nums[i], nums[j]));
            }
        }
        cout << max_ans << "\n";
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 在 `cin >> t;` 後立即以 `getline(cin, line);` 清空殘留換行符，確保後續每次 `getline` 皆精準對齊一行測資；透過 `stringstream` 解析不定數量整數並遍歷所有 $i < j$ 索引數對取最大 `gcd` ，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `3` / `10 20 30 40` / `7 5 12` / `125 15 25` | `20` / `1` / `25` | `20` / `1` / `25` | 驗證官方範例多行不定長度輸入與最大公因數計算 |
| **Boundary case** | `2` / `2 3` / `2147483646 1073741823` | `1` / `1073741823` | `1` / `1073741823` | 測試最小元素個數（ $M = 2$ ）與接近 $2^{31} - 1$ 的大數極值 |
| **Edge case** | `2` / `15 15 4` / `100   200   300` | `15` / `100` | `15` / `100` | 測試同列重複數字（ $i \neq j$ 但值相等）與多重連續空格解析 |
| **Stress case** | `100` 組每行 $99$ 個隨機正整數測資 | 皆在毫秒內輸出精確最大 GCD | Accepted | 驗證 $M < 100$ 上限下雙層迴圈與 `stringstream` 的效能 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 混用 `cin >>` 與 `getline` 時未清除殘留換行符 | 補上 `getline(cin, line);` 消耗首行換行字元 |
| **Edge Cases** | 首組測資讀到空字串且後續資料全數錯位 | 精準對齊每一行不定個數測資、支援重複數字 |
| **Output Handling** | 首行誤輸出預設值 `1` 且遺漏末行測資 | 嚴格對應 $t$ 行測資逐行輸出最大 `gcd` |
| **Complexity** | 未完成 | $O(N \cdot M^2 \log(\max A_i))$ |
| **Code Quality** | 輸入緩衝區處理不完整 | 結合 `getline` 、 `stringstream` 與 `vector` ，結構穩健 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 動手前就意識到 `cin >> t` 之後接 `getline` 必須先消耗掉第一行殘留的 `\n` ，並使用 `stringstream` 解析一行內不定數量的數字，完美避開了「未知每行幾個整數」的輸入陷阱。
- **學到的教訓（Lesson learned）：** 凡是遇到「先讀一個整數 $T$ ，接著逐行讀入不定長度字串或數字」的題型，`cin >> t` 後面緊跟 `getline(cin, dummy)` 是標準且不可或缺的防呆起手式。
- **下一步行動（Next action）：** 未來處理任何混合 `cin >>` 與 `getline` 的字串／行解析題時，固定先清理緩衝區換行符，再用 `stringstream` 切分資料。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 11827 - Maximum GCD | Gemini | 協助將一次 AC 的整行輸入解析技巧、雙層迴圈邊界與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
