# Code Review Report: UVa 401 - Palindromes

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 401
- **Problem Title:** Palindromes
- **Problem Link:** https://onlinejudge.org/external/4/401.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期僅使用 `left < right` 漏檢奇數長度中心字元的未完成草稿與最終 `left <= right` 完整 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa401.cpp](src/UVa401.cpp)
- **Review Date:** 2026-11-10

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，持續讀取直到檔案結尾（EOF）。每一行包含一個由大寫英文字母（ `A` ～ `Z` ）與數字（ `1` ～ `9` ，不含 `0` ）組成的字串，字串中不包含空白字元。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一個字串 `S` ，同時判斷它是否為「普通迴文（Regular palindrome）」以及「鏡像字串（Mirrored string）」，並依四種組合輸出對應結果，且**每組輸出之後都必須額外印出一個空行**：
    1. 既非迴文也非鏡像：`S -- is not a palindrome.`
    2. 非迴文但為鏡像：`S -- is a mirrored string.`
    3. 為迴文但非鏡像：`S -- is a regular palindrome.`
    4. 同時為迴文與鏡像：`S -- is a mirrored palindrome.`
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 只有題目對照表列出的 21 個字元具備合法鏡像（如 `E <-> 3` 、 `J <-> L` 、 `S <-> 2` 、 `Z <-> 5` ，以及 `A, H, I, M, O, T, U, V, W, X, Y, 1, 8` 鏡像為自己）；其餘字元（包含 `0` ）皆無鏡像。
  - 若字串長度為奇數，正中央的字元（索引 $\lfloor L / 2 \rfloor$ ）必須具備**自我鏡像**（即 `get_mirror(mid) == mid` ），整個字串才能成為鏡像字串。
  - 每一組輸出句子後方必須接一個空行（即輸出兩個換行符 `\n\n` ）。
- **核心解決任務？（What is the core task you must solve?）**
  - 建立字元鏡像查詢函式，並以雙指標由字串兩端向中間同步檢查普通迴文條件與鏡像對應條件，最後依四種狀態輸出精確句型與空行。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 迴文與鏡像都屬於首尾對稱性質，可以使用雙指標（Two Pointers）`left = 0` 與 `right = s.length() - 1` 由外向內同步掃描，用兩個布林旗標 `is_palid` 與 `is_mirror` 同時追蹤兩種性質是否成立；至於字元鏡像對照，獨立寫一個 `switch` 查詢函式 `get_mirror(char c)` 最直觀且不易打錯。
- **一開始注意到的困難、風險或模糊之處？**
  - 有三個關鍵陷阱必須防範：第一，雙指標迴圈條件必須寫成 `while (left <= right)` （包含等號 `<=` ），因為當字串長度為奇數時，正中央字元雖然一定滿足 `s[left] == s[right]` （普通迴文成立），但如果該中心字元本身沒有鏡像（例如 `"ADA"` 中的 `'D'` ），`get_mirror('D')` 會回傳 `0` 而使 `is_mirror` 變為 `false` ；第二，對照表中數字只有 `1, 2, 3, 5, 8` ，不可誤加入 `'0'` ；第三，每組輸出後方都必須多印一個空行（ `\n\n` ）。
- **為什麼最初的草稿尚未完整？**
  - 迴圈條件寫成 `while (left < right)` 的草稿會跳過奇數長度字串的正中央字元，導致像 `"ADA"` 或 `"B"` 這類字串被誤判為 `is a mirrored palindrome.` 。

### Final Strategy
- **最終採用什麼方法？**
  - 撰寫 `char get_mirror(char c)` 函式，透過 `switch` 精確映射 21 個有效鏡像字元，無效字元一律回傳 `0` ；在 `main()` 中使用 `while (cin >> s)` 讀取字串，初始化 `is_palid = true` 、 `is_mirror = true` 、 `left = 0` 、 `right = s.length() - 1` ，在 `while (left <= right)` 迴圈內同步驗證 `s[left] == s[right]` 與 `get_mirror(s[left]) == s[right]` （一旦兩者皆為 `false` 即提早 `break` ），最後依四種布林組合輸出對應字串與 `\n\n` 。
- **為什麼這個方法有效？**
  - `while (left <= right)` 確保奇數長度字串的中心字元在 `left == right` 時也會執行 `m = get_mirror(s[left])` 並檢查 `m == s[right]` ，只有在中心字元為自我鏡像字元時才維持 `is_mirror = true` ；單趟雙指標掃描時間為 $O(L)$ 且提早剪枝降低無效比較，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 單一字元字串（長度 $1$ ，如 `"A"` 為鏡像迴文、 `"B"` 為普通迴文）、奇數長度且中心字元無鏡像（如 `"ADA"` 應為普通迴文而非鏡像迴文）、偶數長度純鏡像非迴文（如 `"3AIAE"` 、 `"2S"` ）、包含無效字元 `'0'` ，以及每組輸出後的空行格式。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(L)$ （ $L$ 為字串長度），總計 $T$ 組測資為 $O(\sum L)$ 。
- **Space Complexity:** $O(L)$ ，僅使用單一 `string s` 與常數個指標和布林變數。
- **Explanation:** 雙指標從兩端向中心移動最多執行 $\lceil L / 2 \rceil$ 次迭代，每次查詢 `get_mirror` 為 $O(1)$ 常數時間，整體為最優線性複雜度。

---

## 4. Pseudocode
```text
FUNCTION get_mirror(c):
    依題目鏡像表回傳 c 的鏡像字元
    若 c 無對應鏡像字元則回傳 0
END FUNCTION

START
1. WHILE 成功讀取字串 s (直到 EOF):
2.     初始化 is_palid = true, is_mirror = true
3.     left = 0, right = s.length() - 1
4.     WHILE left <= right:
5.         IF s[left] != s[right] THEN
6.             is_palid = false
7.         END IF
8.         m = get_mirror(s[left])
9.         IF m == 0 OR m != s[right] THEN
10.            is_mirror = false
11.        END IF
12.        IF NOT is_palid AND NOT is_mirror THEN
13.            BREAK
14.        END IF
15.        left = left + 1
16.        right = right - 1
17.    END WHILE
18.    根據 (is_palid, is_mirror) 的四種組合輸出對應句型並加上兩個換行符號
19. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期雙指標條件未包含中心點 `left < right` 的草稿)
```cpp
#include <iostream>
#include <string>
using namespace std;

// 撰寫過程中的未完成草稿：使用 left < right 會漏檢奇數長度字串的正中央字元是否具備自我鏡像
// 例如輸入 "ADA" 或 "B" 時，會誤判為 mirrored palindrome
int main() {
    string s;
    while (cin >> s) {
        bool is_palid = true, is_mirror = true;
        int left = 0, right = s.length() - 1;
        while (left < right) { // 缺少 '=' 號，漏掉正中央字元檢查
            if (s[left] != s[right]) is_palid = false;
            // ... 檢查鏡像字元
            left++;
            right--;
        }
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿的迴圈條件為 `left < right` ，當字串長度為奇數時會直接跳過正中央字元，導致中心字元不具備鏡像的迴文（如 `"ADA"` 、 `"B"` ）被誤判為鏡像迴文；將條件改為 `left <= right` 並補齊四種輸出句型與空行後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<string>
using namespace std;
char get_mirror(char c) {
    switch (c) {
    case'A':return'A';
    case'E':return'3';
    case'H':return'H';
    case'I':return'I';
    case'J':return'L';
    case'L':return'J';
    case'M':return'M';
    case'O':return'O';
    case'S':return'2';
    case'T':return'T';
    case'U':return'U';
    case'V':return'V';
    case'W':return'W';
    case'X':return'X';
    case'Y':return'Y';
    case'Z':return'5';
    case'1':return'1';
    case'2':return'S';
    case'3':return'E';
    case'5':return'Z';
    case'8':return'8';
    default:return 0;
    }
}
int main()
{
    string s;
    while (cin >> s) {
        bool is_palid = true;
        bool is_mirror = true;
        int left = 0;
        int right = s.length() - 1;
        while (left <= right) {
            if (s[left] != s[right]) {
                is_palid = false;
            }
            char m = get_mirror(s[left]);
            if (m == 0 || m != s[right]) {
                is_mirror = false;
            }
            if (!is_palid && !is_mirror) {
                break;
            }
            left++;
            right--;
        }
        if (!is_palid && !is_mirror) {
            cout << s << " -- is not a palindrome.\n\n";
        }
        else if(!is_palid&&is_mirror){
            cout << s << " -- is a mirrored string.\n\n";
        }
        else if (is_palid && !is_mirror) {
            cout << s << " -- is a regular palindrome.\n\n";
        }
        else {
            cout << s << " -- is a mirrored palindrome.\n\n";
        }
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 迴圈條件 `left <= right` 確保包含奇數長度中心點在內的所有對稱位置 `(left, right)` 皆同時接受普通相等性與鏡像映射檢驗；`get_mirror` 精確過濾 21 個合法鏡像字元，並在雙條件皆失效時提早 `break` ，最後依四種布林狀態精準輸出句子與空行，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `NOTAPALINDROME` / `ISAPALINILAPASI` / `2A3MEAS` / `ATOYOTA` | `NOTAPALINDROME -- is not a palindrome.` / `ISAPALINILAPASI -- is a regular palindrome.` / `2A3MEAS -- is a mirrored string.` / `ATOYOTA -- is a mirrored palindrome.` （每行後皆附空行） | 與預期輸出完全一致 | 驗證官方範例四種分類結果與每組輸出後的空行格式 |
| **Boundary case** | `A` / `B` / `3E` / `0` | `A -- is a mirrored palindrome.` / `B -- is a regular palindrome.` / `3E -- is a mirrored string.` / `0 -- is a regular palindrome.` | 與預期輸出完全一致 | 測試單一字元（自我鏡像 vs. 非自我鏡像）與數字 `'0'` 無鏡像邊界 |
| **Edge case** | `ADA` / `AMA` / `JL` | `ADA -- is a regular palindrome.` / `AMA -- is a mirrored palindrome.` / `JL -- is a mirrored string.` | 與預期輸出完全一致 | 驗證 `left <= right` 正確檢驗奇數長度中心字元及非對稱字母互為鏡像（ `J <-> L` ） |
| **Stress case** | UVa 官方多行混合字母與數字測資 | 全部分類與空行精確無誤 | Accepted | 驗證雙指標提早剪枝與查表函式在官方測資下的穩定性 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 雙指標條件寫成 `left < right` （漏檢中心點） | 雙指標條件使用 `left <= right` ，同步檢查 `is_palid` 與 `is_mirror` |
| **Edge Cases** | 奇數長度中心點無鏡像時會誤判 | 精確涵蓋單字元、奇數長度中心點、無效字元 `'0'` 與互為鏡像字元對 |
| **Output Handling** | 缺少四種分類句型與輸出空行 | 精確輸出四種對應句型並於每組後附上空行 `\n\n` |
| **Complexity** | $O(L)$ （未完成） | $O(\sum L)$ 時間、 $O(L)$ 空間 |
| **Code Quality** | 邊界條件不完整 | 查表函式清晰、提早 `break` 剪枝、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 在設計雙指標迴圈時特別留意到奇數長度字串的正中央字元（ `left == right` ）對普通迴文無影響、但對鏡像字串有決定性影響，因此堅持寫成 `while (left <= right)` ；同時把 21 個鏡像字元獨立封裝成 `get_mirror(char c)` ，讓主程式的雙指標邏輯非常乾淨易讀，並仔細核對了題目要求每組輸出後皆須空一行的格式。
- **學到的教訓（Lesson learned）：** 使用雙指標由兩端向中間檢查對稱性質時，是否包含 `left == right` 取決於「單一元素自身是否仍需滿足條件」——普通迴文 `s[i] == s[i]` 恆成立可不檢，但鏡像或反轉互補性質（如 DNA 互補或字元鏡像）必須檢驗中心點，統一寫 `left <= right` 是最安全的習慣。
- **下一步行動（Next action）：** 未來解雙指標對稱或查表映射題時，延續「查表邏輯抽成獨立 `switch` ／陣列函式 + 雙指標一律寫 `left <= right` + 提早剪枝」的標準寫法。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 401 - Palindromes | Gemini | 協助將一次 AC 的雙指標對稱檢查邏輯、奇數中心點邊界與複雜度分析整理成標準報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
