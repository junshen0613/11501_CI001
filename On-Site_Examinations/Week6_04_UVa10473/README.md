# Code Review Report: UVa 10473 - Simple Base Conversion

## 1. Problem Information
- **Platform:** UVa
- **Problem ID:** 10473
- **Problem Title:** Simple Base Conversion
- **Problem Link:** https://onlinejudge.org/external/104/10473.pdf
- **Language / Version:** C++ (C++17)
- **Submission Result:** Accepted (First Submission AC)
- **Source Code (Initial/Fail):** N/A（本題首次提交即取得 Accepted，無退件之 Fail Code；第 5 節對照撰寫初期僅處理單向十進位轉十六進位的未完成草稿與最終雙向轉換 AC 版本）
- **Source Code (Final/Accepted):** [src/UVa10473.cpp](src/UVa10473.cpp)
- **Review Date:** 2026-10-13

---

## 2. Problem Statement in My Own Words
- **輸入是什麼？（What is the input?）**
  - 多行測試資料，每一行包含一個非負整數（大小不超過 $2^{31}$ ），其格式為以下兩種之一：
    1. **十進位整數**（不帶前綴，例如 `4` 、 `123456` ）。
    2. **十六進位整數**（以 `0x` 開頭，英文字母皆為大寫 `A` ～ `F` ，例如 `0x8068` ）。
  - 當讀到負數（例如 `-1` 或任何以 `-` 開頭的數字）時代表輸入結束，不需要處理或輸出該行結果。
- **預期輸出是什麼？（What is the expected output?）**
  - 針對每一行非負整數，進行雙向進位轉換並輸出一行結果：
    - 若輸入為**十六進位**（ `0x...` ），輸出其對應的**十進位**整數。
    - 若輸入為**十進位**，輸出其對應的**十六進位**整數，必須加上小寫前綴 `0x` ，且十六進位字母（ `A` ～ `F` ）必須為**大寫**。
- **主要規則與限制條件？（What is the main rules or constraints?）**
  - 數值上限可達 $2^{31}$ （即 `2147483648` 或 `0x80000000` ），超過 32 位元有號 `int` 的最大值（ $2^{31} - 1 = 2147483647$ ），因此必須使用 64 位元整數 `long long` 儲存。
  - 十六進位輸出的前綴 `0x` 中的 `x` 為**小寫**，但數字部分的英文字母 `A` ～ `F` 必須為**大寫**。
  - 終止訊號為任意負數（以負號 `'-'` 開頭）。
- **核心解決任務？（What is the core task you must solve?）**
  - 判斷輸入字串是否以 `0x` 開頭，分別執行「十六進位 $\rightarrow$ 十進位」或「十進位 $\rightarrow$ 大寫十六進位（含 `0x` 前綴）」的轉換直到遇到負數為止。

---

## 3. Thinking Logic and Solution Strategy

### Initial Thoughts
- **最初的想法是什麼？**
  - 因為同一份測資會混合出現純數字（十進位）與含 `0x` 的字串（十六進位），最方便的方式是一律以 `string s` 讀入整行 token，先檢查 `s[0] == '-'` 判斷是否結束，再根據前兩個字元是否為 `0x` 決定轉換方向。
- **一開始注意到的困難、風險或模糊之處？**
  - 有三個關鍵細節需要注意：第一，題目數值上限為 $2^{31}$ ，若用 `stoi` 或 `int` 會在 `2147483648` 時發生溢位（ `out_of_range` ），必須改用 `stoll` 與 `long long` ；第二，使用 `cout << hex` 切換十六進位輸出後，必須加上 `uppercase` 讓 `A` ～ `F` 變大寫，並手動輸出 `"0x"` 前綴（因為 C++ 預設 `hex` 不印 `0x` ，且 `showbase` 搭配 `uppercase` 會把 `0x` 變成大寫 `0X` ，不符合題目小寫 `0x` 的規定）；第三，輸出完十六進位後要立刻用 `dec` 切回十進位模式，避免影響下一筆十進位輸出。
- **為什麼最初的草稿尚未完整？**
  - 僅使用 `std::hex` / `std::dec` 格式化流或僅處理單向轉換的草稿無法同時支援 `0x` 字串識別與雙向進位轉換，且容易在 `0x` 大小寫與 `2^{31}` 溢位上出錯。

### Final Strategy
- **最終採用什麼方法？**
  - 使用 `while (cin >> s)` 讀取字串：
    1. 若 `s[0] == '-'` 則立即 `break` 結束程式。
    2. 若為 `0x` / `0X` 開頭的十六進位字串，呼叫 `stoll(s, nullptr, 16)` 直接以 16 為基底解析為 `long long` 並輸出十進位數值。
    3. 否則視為十進位字串，先以 `stoll(s)` 轉為 `long long` ，手動印出 `"0x"` 後，透過 `cout << uppercase << hex << val << dec << "\n";` 輸出大寫十六進位並立即還原十進位流狀態。
- **為什麼這個方法有效？**
  - `std::stoll(s, nullptr, 16)` 內建支援 `0x` 前綴與大小寫十六進位字元解析，且回傳 64 位元 `long long` ，完美涵蓋 $2^{31}$ 上限；手動輸出 `"0x"` 搭配 `uppercase << hex` 精準滿足「小寫 `0x` + 大寫 `A-F` 」的格式要求，並在同語句末段以 `dec` 重置狀態，因此首次提交即順利取得 Accepted。
- **考慮了哪些邊界條件（Edge cases）？**
  - 最小值 `0` （輸出 `0x0` ）與 `0x0` （輸出 `0` ）、題目上限 $2^{31} = 2147483648$ （輸出 `0x80000000` ）與 `0x80000000` （輸出 `2147483648` ）、包含十六進位字母 `A` ～ `F` 的數值（確認大寫輸出），以及任意負數終止訊號（如 `-1` 、 `-42` ）。

### Complexity Analysis
- **Time Complexity:** 每組測資 $O(L)$ （ $L$ 為輸入字串長度， $L \le 12$ ），總計 $T$ 組測資為 $O(T)$ 。
- **Space Complexity:** $O(L)$ ，僅使用單一 `string s` 與 `long long val` 。
- **Explanation:** 每次轉換僅掃描最多 12 個字元的字串進行進位解析與格式化輸出，單筆時間與空間皆為常數級別。

---

## 4. Pseudocode
```text
START
1. WHILE 成功讀取字串 s:
2.     IF s[0] == '-' THEN
3.         BREAK (結束程式)
4.     END IF
5.     IF s 以 "0x" 或 "0X" 開頭 THEN
6.         val = stoll(s, base = 16)
7.         以十進位輸出 val 並換行
8.     ELSE
9.         val = stoll(s, base = 10)
10.        輸出 "0x" + 大寫十六進位(val)，並將輸出流還原為十進位模式
11.    END IF
12. END WHILE
END
```

---

## 5. Fail Code vs Correct Code

### Initial Incomplete Draft (本題首次提交即 AC，此為撰寫初期僅處理十進位轉十六進位的草稿)
```cpp
#include <iostream>
#include <string>
using namespace std;

// 撰寫過程中的未完成草稿：僅能將十進位轉為十六進位，尚未處理 0x 開頭的十六進位輸入與負數終止條件
int main() {
    long long val;
    while (cin >> val && val >= 0) {
        cout << "0x" << uppercase << hex << val << dec << "\n";
    }
    return 0;
}
```

**Why it was incomplete:**
- **未完成之處：** 該草稿以 `long long` 直接讀取，遇到 `0x8068` 這類十六進位字串時會導致 `cin >> val` 讀取失敗並提早結束程式；改用 `string s` 讀入並搭配 `stoll(..., 16)` 判斷 `0x` 前綴後首次提交即通過評測。

### Correct Code (First Submission Accepted)
```cpp
#include <iostream>
#include<string>
using namespace std;

int main()
{
    string s;
    while (cin >> s) {
        if (s[0] == '-')break;
        if (s.size() >= 2 && s[0] == '0' && (s[1] == 'x') || s[1] == 'X') {
            long long val = stoll(s, nullptr, 16);
            cout << val << "\n";
        }
        else {
            long long val = stoll(s);
            cout << "0x";
            cout << uppercase << hex << val << dec << "\n";
        }
    }
    return 0;
}
```

**Why it works:**
- **關鍵不變量與推論：** 統一以 `string` 接收輸入後分流處理：對 `0x` 字串使用 `stoll(s, nullptr, 16)` 精確轉為十進位，對十進位字串使用 `stoll(s)` 轉整數後以 `"0x"` 搭配 `uppercase << hex` 輸出大寫十六進位並立即恢復 `dec` 狀態，首次提交即通過 UVa 官方評測獲得 Accepted。

---

## 6. Test Evidence

| Test Category | Input Summary | Expected Result | Actual Result | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **Normal case** | `4` / `7` / `44` / `0x8068` / `-1` | `0x4` / `0x7` / `0x2C` / `32872` | `0x4` / `0x7` / `0x2C` / `32872` | 驗證官方範例的十進位與十六進位雙向轉換與大寫 `C` 輸出 |
| **Boundary case** | `0` / `0x0` / `2147483648` / `0x80000000` / `-1` | `0x0` / `0` / `0x80000000` / `2147483648` | `0x0` / `0` / `0x80000000` / `2147483648` | 測試零值雙向轉換與題目上限 $2^{31}$ （驗證 `long long` 未溢位） |
| **Edge case** | `255` / `0xFF` / `171` / `0xAB` / `-99` | `0xFF` / `255` / `0xAB` / `171` | `0xFF` / `255` / `0xAB` / `171` | 測試全為英文字母的十六進位表示與非 `-1` 的負數終止訊號 |
| **Stress case** | UVa 官方多筆交替進位測資 | 全部通過 | Accepted | 驗證連續切換 `hex` 與 `dec` 輸出流狀態無殘留污染 |

- **關於評測結果的說明：** 本題在本地測試上述測資無誤後，首次提交至 UVa Online Judge 即獲得 Accepted，無任何退件或修正紀錄。

---

## 7. Difference and Reflection

### Key Differences
| Item | Initial Incomplete Draft | Correct Code (First-Submission AC) |
| :--- | :--- | :--- |
| **Logic** | 僅支援十進位轉十六進位單向轉換 | 使用 `string` 分流與 `stoll` 實現雙向進位轉換 |
| **Edge Cases** | 遇到 `0x` 輸入會使 `cin` 讀取失敗 | 完整支援 `0` 、 $2^{31}$ 上限、大寫字母與任意負數終止 |
| **Output Handling** | 僅能輸出十六進位 | 精準控制小寫 `0x` 與大寫 `A-F` ，並用 `dec` 還原流狀態 |
| **Complexity** | $O(1)$ （未完成） | $O(1)$ per case |
| **Code Quality** | 無法處理混合格式輸入 | 善用標準庫 `stoll` 與 I/O 操縱子、一次通過評測 |

### Reflection
- **成功一次 AC 的關鍵（Design choice）：** 避開了 `cout << showbase << uppercase << hex` 會把前綴也印成大寫 `0X` 的陷阱，改用手動輸出 `"0x"` 搭配 `uppercase << hex << val << dec` ，同時選用 `stoll` 與 `long long` 防止 $2^{31}$ 在 32 位元 `int` 下溢位。
- **複盤發現的潛在優化點（Code Review Insight）：** 第 10 行條件判斷 `if (s.size() >= 2 && s[0] == '0' && (s[1] == 'x') || s[1] == 'X')` 因為 C++ 中 `&&` 的運算優先權高於 `||` ，實際解析為 `(s.size() >= 2 && s[0] == '0' && s[1] == 'x') || (s[1] == 'X')` 。在 C++11 標準下單字元字串 `"0"` 的 `s[1]` 為 `'\0'` 故安全通過，但加上明確括號寫成 `if (s.size() >= 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))` 能徹底杜絕單字元字串的越界讀取風險。
- **下一步行動（Next action）：** 未來在混合使用 `&&` 與 `||` 的條件判斷中，一律為 `||` 子條件加上外層括號，並持續注意 `cout` 進位操縱子的狀態還原。

---

## 8. AI Usage Disclaimer
- AI tools, if used, were used only to support learning, such as clarifying concepts or reviewing explanations.
- I independently understood, verified, and completed the solution and reflection in this report.

### AI Usage Record
| Problem ID / Title | AI Tool Used | How It Was Used | Verification Performed Independently |
| :--- | :--- | :--- | :--- |
| UVa 10473 - Simple Base Conversion | Gemini | 協助進行事後 Code Review（檢視 `&&` 與 `||` 括號優先權與 `showbase` 細節）並整理報告格式 | 親自獨立撰寫 C++ 程式碼並於首次提交即通過 UVa Online Judge Accepted 評測 |

---
