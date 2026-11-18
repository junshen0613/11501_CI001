# Code Review Report: UVa 299 - Train Swapping

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 299
- **Problem Title:** Train Swapping
- **Problem Link:** https://onlinejudge.org/external/2/299.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期實際模擬氣泡排序交換陣列元素的草稿與最終直接計算逆序數對的 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa299.cpp](src/UVa299.cpp)
- **Review Date:** 2026-10-20

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 第一行包含一個正整數 $N$ ，代表測試資料的組數。每組測試資料包含兩行：第一行為一個非負整數 $L$ （ $0 \le L \le 50$ ），代表火車的車廂總數；第二行為 $1$ 到 $L$ 的某個排列（共 $L$ 個以空格分隔的正整數），代表目前各節車廂的編號順序。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組測資，輸出一行 `Optimal train swapping takes S swaps.` ，其中 `S` 為只允許交換「相鄰兩節車廂」的前提下，將車廂重新排列為由小到大（ $1, 2, \dots, L$ ）所需的最少交換次數。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 每次操作只能旋轉轉盤（交換相鄰的兩節車廂），目標是讓車廂編號依嚴格遞增順序排列。
  - 車廂數量上限為 $L \le 50$ ，且可能出現 $L = 0$ （沒有車廂，所需交換次數為 `0` ）的邊界情況。
  - 輸出句型必須精確符合 `Optimal train swapping takes S swaps.` ，包含句尾句點 `.` 。
- **核心解決任務？（What is the core task you must solve?）**
  - 計算給定排列中的「逆序數對（Inversions）」總數，即滿足索引 $i < j$ 但數值 $s[i] > s[j]$ 的元素對數量，並依照指定格式輸出。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 因為每次只能交換相鄰兩節車廂，這正是氣泡排序（Bubble Sort）的操作模型；而從組合數學可知，任何相鄰交換演算法將排列還原為升序的最少交換次數，嚴格等於該排列中的**逆序數對（Inversion Count）**總數。因此甚至不需要真的去交換陣列元素，只要用雙層迴圈統計所有 `i < j` 且 `s[i] > s[j]` 的數對數量即可。
- **一開始注意到的困難、風險或模糊之處？**
  - 需要注意兩個細節：第一，當 $L = 0$ 時（零節車廂），`vector<int> s(0)` 為空，雙層迴圈不執行並自然輸出 `0` 次交換，不可讓程式在 $L = 0$ 時發生陣列越界或讀取錯誤；第二，輸出英文句子必須完整核對單複數與標點（無論 `0` 次或多次，題目固定使用 `swaps.` 複數形式）。
- **為什麼最初的草稿尚未完整？**
  - 實際執行氣泡排序並呼喚 `swap(s[j], s[j + 1])` 的草稿雖然也能算出相同結果，但多了不必要的陣列寫入操作，且尚未加上多組測資 `while (n--)` 封裝與精確輸出句型。

### Final Strategy
- **最終採用什麼方法？**
  - 將單組測資邏輯封裝在 `void solve()` 中：讀入車廂數 `r` 並配置 `vector<int> s(r)` 讀取排列後，初始化 `int count = 0;` ，使用雙層迴圈 `for (int i = 0; i < r; i++)` 與 `for (int j = i + 1; j < r; j++)` 檢查 `if (s[i] > s[j]) count++;` ，最後輸出 `"Optimal train swapping takes " << count << " swaps.\n"` 。
- **為什麼這個方法有效？**
  - 每一次合法的相鄰車廂交換最多只能消除 1 個逆序數對（當原本相鄰兩車廂滿足 $s[k] > s[k + 1]$ 時），且只要陣列尚未完全升序，就必定存在至少一對相鄰逆序元素可供交換，因此最少交換次數恆等於初始逆序數對總數；直接統計逆序數對不修改陣列、邏輯極簡，且在 $L \le 50$ 下最多僅比較 $\frac{50 \times 49}{2} = 1225$ 次，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 零節車廂（ $L = 0$ ，輸出 `0` ）、單節車廂（ $L = 1$ ，輸出 `0` ）、已完全排好序的升序排列（如 `1 2 3` ，輸出 `0` ）、完全逆序的最壞情況（如 `4 3 2 1` ，輸出 $\frac{4 \times 3}{2} = 6$ ），以及最大上限 $L = 50$ （最多 $\frac{50 \times 49}{2} = 1225$ 次交換）。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(L^2)$ ，總計 $N$ 組測資為 $O(N \cdot L^2)$ 。
- **Space Complexity:** $O(L)$ ，使用長度為 $r$ 的 `vector<int> s` 儲存車廂排列。
- **Explanation:** 在 $L \le 50$ 的限制下，雙層迴圈每組最多執行 $1225$ 次整數大小比較，無需任何實體元素交換，執行速度極快。

---

## 4. Pseudocode
```text
FUNCTION solve():
    讀取車廂數量 r
    宣告長度為 r 的整數陣列 s 並依序讀入元素
    初始化 count = 0
    FOR i = 0 TO r - 1:
        FOR j = i + 1 TO r - 1:
            IF s[i] > s[j] THEN
                count = count + 1
            END IF
        END FOR
    END FOR
    輸出 "Optimal train swapping takes " + count + " swaps." 並換行
END FUNCTION

START
1. 讀取測資筆數 n
2. WHILE n > 0 (每次執行後 n 減 1):
3.     呼叫 solve()
4. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期實際模擬氣泡排序交換的草稿)
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 撰寫過程中的未完成草稿：實際執行氣泡排序並修改陣列元素，尚未簡化為直接計算逆序數對與多筆測資封裝
int main() {
    int r;
    cin >> r;
    vector<int> s(r);
    for (int i = 0; i < r; i++) cin >> s[i];
    int count = 0;
    for (int i = 0; i < r - 1; i++) {
        for (int j = 0; j < r - 1 - i; j++) {
            if (s[j] > s[j + 1]) {
                swap(s[j], s[j + 1]);
                count++;
            }
        }
    }
    cout << count << "\n";
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿不僅在內層迴圈執行了多餘的 `swap` 記憶體寫入（且若寫成 `r - 1` 在 $r = 0$ 時可能因無號整數減法產生風險），也尚未封裝為多組測資迴圈與套用題目指定的完整輸出句子；改用直接計數 `i < j` 且 `s[i] > s[j]` 的逆序數對寫法並加上完整句型後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
void solve() {
    int r;
    cin >> r;
    vector<int> s(r);
    for (int i = 0; i < r; i++) {
        cin >> s[i];
    }
    int count = 0;
    for (int i = 0; i < r; i++) {
        for (int j = i + 1; j < r; j++) {
            if (s[i] > s[j]) {
                count++;
            }
        }
    }
    cout << "Optimal train swapping takes " << count << " swaps.\n";
}
int main()
{
    int n;
    if (cin >> n) {
        while (n--) {
            solve();
        }
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 相鄰交換排序的最小步數恆等於排列的逆序數對個數 $\sum_{0 \le i < j < r} [s[i] > s[j]]$ ；使用 `vector<int> s(r)` 安全支援包含 $r = 0$ 在內的所有合法長度，直接統計逆序數對並精確輸出題目指定句型，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `3` / `3` / `1 3 2` / `4` / `4 3 2 1` / `2` / `2 1` | `Optimal train swapping takes 1 swaps.` / `Optimal train swapping takes 6 swaps.` / `Optimal train swapping takes 1 swaps.` | 與預期輸出完全一致 | 驗證官方範例三組測資的逆序數對計算與輸出格式（含 `1 swaps.` 固定複數用法） |
| **Boundary case** | `3` / `0` / `1` / `1` / `5` / `1 2 3 4 5` | `Optimal train swapping takes 0 swaps.`（三行皆同） | 與預期輸出完全一致 | 測試零節車廂（ $L = 0$ ）、單節車廂（ $L = 1$ ）與已排序陣列的 `0` 次交換邊界 |
| **Edge case** | `1` / `5` / `5 4 3 2 1` | `Optimal train swapping takes 10 swaps.` | `Optimal train swapping takes 10 swaps.` | 驗證完全逆序排列達到理論最大逆序數 $\frac{L(L - 1)}{2}$ |
| **Stress case** | 多組 $L = 50$ 完全逆序滿載測資 | 皆在毫秒內輸出 `Optimal train swapping takes 1225 swaps.` | Accepted | 驗證 $L = 50$ 上限下雙層迴圈的執行效率與正確性 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 實際執行氣泡排序並呼叫 `swap` 修改陣列 | 直接統計逆序數對（ `i < j && s[i] > s[j]` ），免除元素交換 |
| **Edge Cases** | 未處理多組測資，且 `r - 1` 寫法在 $r = 0$ 時較不直觀 | `vector<int> s(r)` 與 `i < r` 安全支援 $r = 0$ 至 $r = 50$ |
| **Output Handling** | 僅輸出數字 `count` | 精確輸出 `Optimal train swapping takes count swaps.` |
| **Complexity** | $O(L^2)$ （含陣列寫入） | $O(N \cdot L^2)$ （純讀取比較） |
| **Code Quality** | 僅單組主程式片段 | 使用 `solve()` 模組化封裝、數學等價轉換精煉、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在實作前先運用「相鄰交換最少步數 $=$ 排列逆序數對個數」的數學性質，把原本需要不斷搬移元素的氣泡排序簡化成純粹的雙層比較計數，既減少了陣列寫入操作，也讓迴圈邊界在 $r = 0$ 時完全安全；同時仔細核對了題目範例中即便 `1` 次交換也印 `1 swaps.` 的固定句型。
- **學到的教訓（Lesson learned）：** 將具體操作（相鄰交換）抽象化為組合數學不變量（逆序數對），不僅能讓程式碼更簡短易讀，也為未來遇到更大規模（如 $L \le 10^5$ 需改用 Merge Sort 或 BIT 求逆序數對）的同類題型打下基礎。
- **下一步行動（Next action）：** 未來解排序或排列還原題時，先判斷題目是否只需要「最少交換次數」而非「排序後的陣列本身」，若只需次數則直接計算逆序數對即可。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 299 - Train Swapping | Gemini | 協助將一次 AC 的逆序數對數學等價推導、邊界條件與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
