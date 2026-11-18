# Code Review Report: UVa 10252 - Common Permutation

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10252
- **Problem Title:** Common Permutation
- **Problem Link:** https://onlinejudge.org/external/102/10252.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期使用 `cin >> s >> t` 讀取而無法處理空行的未完成草稿與最終 `getline` 頻率交集 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa10252.cpp](src/UVa10252.cpp)
- **Review Date:** 2026-11-03

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多組測試資料，持續讀取直到檔案結尾（EOF）。每組測資由連續兩行組成，分別為兩個由小寫英文字母組成的字串 $a$ 與 $b$ （長度皆不超過 $1000$ ，且**允許空行**）。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一組字串對 $(a, b)$ ，輸出一行滿足以下條件的最長字串 $x$ ：
    1. $x$ 的某種排列是 $a$ 的子序列（Subsequence），且 $x$ 的某種排列也是 $b$ 的子序列（白話而言： $x$ 由 $a$ 與 $b$ **共同擁有的所有字母**組成，若某字母在 $a$ 出現 $c_1$ 次、在 $b$ 出現 $c_2$ 次，則該字母在 $x$ 中出現 $\min(c_1, c_2)$ 次）。
    2. 在所有最長解中，輸出**字典序（Alphabetical order）最小**的那一個（即所有共同字母依 `'a'` 到 `'z'` 遞增排列）。
    3. 若兩字串沒有任何共同字母（或其中一行為空行），則輸出一個空行。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 每組測資嚴格佔用兩行，其中一行或兩行皆可能是**空字串（空行）**，因此不可使用會自動跳過換行與空白的 `cin >> s >> t` 讀取，必須使用 `getline` 成對讀入。
  - 輸出字串必須按 `'a'` 到 `'z'` 的字母順序排列（而非依照原本字串中的出現順序）。
- **核心解決任務？（What is the core task you must solve?）**
  - 成對讀取每兩行字串直至 EOF，分別統計 26 個小寫英文字母在兩字串中的出現次數，並依 `'a'` 到 `'z'` 順序各輸出 `min(count1[ch], count2[ch])` 次。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 因為可以任意重新排列（Permutation） $x$ 的字元，字元在原字串 $a$ 或 $b$ 中的先後位置完全不重要，唯一決定 $x$ 的就是「每個字母在 $a$ 與 $b$ 中各自出現了幾次」。對於任意字母 `ch` ，它最多能被放入共同子序列的次數就是 $\min(\text{count}_a[\text{ch}], \text{count}_b[\text{ch}])$ ；而要讓 $x$ 字典序最小，只要從 `'a'` 到 `'z'` 依序輸出這些共同字母即可。
- **一開始注意到的困難、風險或模糊之處？**
  - 本題最著名的陷阱在於測資包含**空行**（例如第一行為空行 `""` 、第二行為 `"abc"` ）：如果用 `cin >> s >> t` 讀取，`cin` 會自動忽略換行符號並把下一組測資的第一行當成這一組的 `t` ，導致後面所有測資兩兩錯位而 Wrong Answer；改用 `while (getline(cin, s)) { getline(cin, t); ... }` 就能嚴格以「每兩行為一組」讀取，完美保留空行。
- **為什麼最初的草稿尚未完整？**
  - 使用 `cin >> s >> t` 的草稿在遇到含空行的測資時會發生行對齊錯亂，且需在每組測資內部重新歸零兩個頻率統計陣列。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `while (getline(cin, s))` 讀取每組第一行，緊接著執行 `getline(cin, t);` 讀取第二行；在迴圈內部宣告 `int count1[128] = { 0 };` 與 `int count2[128] = { 0 };` 分別統計 `s` 與 `t` 中各小寫字母的出現次數；最後以 `for (char ch = 'a'; ch <= 'z'; ch++)` 遍歷 26 個字母，計算 `int common = min(count1[ch], count2[ch]);` 並輸出 `common` 個 `ch` 字元後換行。
- **為什麼這個方法有效？**
  - `getline` 成對讀取確保空行被正確讀為長度 `0` 的字串（輸出空行而不影響後續測資）；頻率陣列交集 $\min(\text{count}_1[\text{ch}], \text{count}_2[\text{ch}])$ 精確計算出最大共同多重集合，且由 `'a'` 到 `'z'` 的固定遍歷順序天然保證輸出結果為字典序最小的最長共同排列，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 其中一行或兩行皆為空行（輸出空行）、兩字串完全沒有共同字母（輸出空行）、包含重複字母的共同子序列（如 `"walking"` 與 `"down"` 共同擁有 `'n'` 與 `'w'` 輸出 `"nw"` ； `"pretty"` 與 `"women"` 共同擁有 `'e'` 與 `'t'` 輸出 `"et"` ），以及兩字串完全相同的情況。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(\vert{}s\vert{} + \vert{}t\vert{} + 26) = O(\vert{}s\vert{} + \vert{}t\vert{})$ ，總計 $T$ 組測資為 $O(\sum (\vert{}s\vert{} + \vert{}t\vert{}))$ 。
- **Space Complexity:** $O(1)$ 額外空間（使用固定長度 128 的兩個整數陣列 `count1[128]` 、 `count2[128]` 與輸入緩衝字串 `s, t` ）。
- **Explanation:** 在單行長度不超過 $1000$ 的限制下，每組測資僅需各掃描一次 `s` 與 `t` ，再掃描 26 個英文字母即可輸出，時間與空間皆為最優的線性級別。

---

## 4. Pseudocode
```text
START
1. WHILE 成功讀取第一行字串 s (直到 EOF):
2.     讀取第二行字串 t
3.     初始化計數陣列 count1[0..127] = 0, count2[0..127] = 0
4.     FOR 每個字元 c IN s:
5.         IF isalpha(c) 為真 THEN
6.             count1[tolower(c)] = count1[tolower(c)] + 1
7.         END IF
8.     END FOR
9.     FOR 每個字元 c IN t:
10.        IF isalpha(c) 為真 THEN
11.            count2[tolower(c)] = count2[tolower(c)] + 1
12.        END IF
13.    END FOR
14.    FOR ch = 'a' TO 'z':
15.        common = min(count1[ch], count2[ch])
16.        重複輸出字元 ch 共 common 次
17.    END FOR
18.    輸出換行符號
19. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期使用 `cin >> s >> t` 無法處理空行的未完成草稿)
```cpp
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// 撰寫過程中的未完成草稿：使用 cin >> s >> t 會跳過空行，導致測資包含空行時所有後續字串兩兩錯位
int main() {
    string s, t;
    while (cin >> s >> t) {
        int count1[128] = { 0 }, count2[128] = { 0 };
        for (char c : s) count1[c]++;
        for (char c : t) count2[c]++;
        for (char ch = 'a'; ch <= 'z'; ch++) {
            for (int k = 0; k < min(count1[ch], count2[ch]); k++) cout << ch;
        }
        cout << "\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿使用 `cin >> s >> t` 讀取字串，遇到空行測資時會直接略過空行並將下一組測資的第一行誤讀為 `t` ，造成整份測資錯位 WA；改用成對的 `getline(cin, s)` 與 `getline(cin, t)` 後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<string>
#include<cctype>

using namespace std;
int main()
{
	string s, t;
	while (getline(cin, s)) {
		getline(cin, t);
		int count1[128] = { 0 }; 
		int count2[128] = { 0 };
		for (char c : s) {
			if (isalpha(c)) {
				count1[tolower(c)]++;
			}
		}
		for (char c : t) {
			if (isalpha(c)) {
				count2[tolower(c)]++;
			}
		}
		for (char ch = 'a'; ch <= 'z'; ch++) {
			int common = min(count1[ch], count2[ch]);
			for (int times = common; times >= 1; times--) {
				cout << ch;
			}
		}
		cout << "\n";
	}
	return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 透過成對 `getline` 嚴格保持兩行一組的讀取對齊（包含空行），利用 `count1` 與 `count2` 精確計算兩字串的字母多重集合交集 $\min(\text{count}_1[\text{ch}], \text{count}_2[\text{ch}])$ ，並按 `'a'` 至 `'z'` 順序輸出，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `pretty` / `women` / `walking` / `down` / `the` / `street` | `e` / `nw` / `et` | `e` / `nw` / `et` | 驗證官方範例三組字串的共同字母交集與字典序排列 |
| **Boundary case** | `""` （空行） / `abc` / `""` （空行） / `""` （空行） | `""` （空行） / `""` （空行） | `""` （空行） / `""` （空行） | 測試其中一行或兩行皆為空行時不會發生讀入錯位 |
| **Edge case** | `abc` / `def` / `aabbcc` / `ccbbaa` | `""` （空行） / `aabbcc` | `""` （空行） / `aabbcc` | 測試完全無交集（輸出空行）與多重複字元全交集的排序輸出 |
| **Stress case** | 多組長度達 $1000$ 字元之字串測資 | 皆在毫秒內輸出精確共同排列 | Accepted | 驗證線性掃描與固定 128 大小陣列在最大長度下的效能 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 使用 `cin >> s >> t` 讀取字串 | 使用成對 `getline(cin, s)` 與 `getline(cin, t)` 讀取整行 |
| **Edge Cases** | 遇到空行測資時會發生後續測資全部錯位 | 完美保留空行並安全輸出對應空行 |
| **Output Handling** | 空行測資輸出組數與內容錯誤 | 嚴格對應每兩行一組輸出字典序最小共同排列 |
| **Complexity** | $O(\sum (|s| + |t|))$ （未完成） | $O(\sum (|s| + |t|))$ 時間、 $O(1)$ 額外空間 |
| **Code Quality** | 未防範空行輸入陷阱 | 善用 `getline` 、 ASCII 頻率交集與雙層輸出、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在動手前就注意到本題測資可能包含「空行」，因此果斷捨棄會自動略過換行符的 `cin >>` ，改用 `while (getline(cin, s)) { getline(cin, t); ... }` 成對讀取整行；同時將最長共同排列問題轉化為「兩頻率陣列取 `min` 交集並由 `'a'` 印到 `'z'` 」，使時間複雜度保持在最優的線性時間。
- **學到的教訓（Lesson learned）：** 在 UVa 字串題中，只要題目規定「每組測資佔固定行數（如兩行一組）」且允許空字串輸入，一律使用 `getline` 讀取整行才是唯一不會因空行錯位的安全做法。
- **下一步行動（Next action）：** 未來解多行配對字串題時，延續「成對 `getline` 讀入 + 固定大小 ASCII 頻率陣列交集」的標準做法。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10252 - Common Permutation | Gemini | 協助將一次 AC 的多重集合交集原理、空行輸入邊界與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
