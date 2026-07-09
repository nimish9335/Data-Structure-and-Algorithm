# Bitmask Basics

## 📌 Why This Folder Exists

Before any bitmask DP template makes sense, you need automatic,
no-thinking-required fluency with basic bit operations. This folder
is the "alphabet" — everything else in this repo (Generic Templates,
Problems, State Compression DP) is built entirely out of these
few operations, repeated in different combinations.

## 🔑 What is a "Mask"?

A mask is just an integer where each **bit position** represents
whether a specific item is "in" or "out" of a set.

Example with `n = 6` items (numbered 0 to 5):
Reading right to left: item 0 = 0 (out), item 1 = 1 (in), item 2 = 1
(in), item 3 = 0 (out), item 4 = 1 (in), item 5 = 0 (out).

So this mask represents the set **{1, 2, 4}**.

**Key habit: always read bits right-to-left, starting from item 0.**
This trips up almost everyone at first — practice until it's automatic.

## 🔧 The Operations Table (memorize, don't just read)

| Goal | Code | Why it works |
|---|---|---|
| Is item `i` in the mask? | `mask & (1 << i)` | `(1<<i)` has only bit `i` on; AND keeps it only if both have it |
| Add item `i` | `mask \| (1 << i)` | OR forces bit `i` to 1, leaves rest untouched |
| Remove item `i` | `mask & ~(1 << i)` | `~(1<<i)` is all 1s except bit `i`; ANDing zeroes only that bit |
| Toggle item `i` | `mask ^ (1 << i)` | XOR flips exactly bit `i` |
| Full mask (all `n` items) | `(1 << n) - 1` | `1` followed by `n` zeros, minus 1, becomes `n` ones |
| Count items in mask | `__builtin_popcount(mask)` | GCC built-in, counts set bits fast |
| Lowest set bit value | `mask & (-mask)` | Isolates rightmost 1-bit using two's complement trick |
| Remove lowest set bit | `mask & (mask - 1)` | Clears the rightmost 1-bit |
| Loop all subsets of n items | `for (m = 0; m < (1<<n); m++)` | Visits every mask from empty to full exactly once |
| Loop submasks of a mask | see Subset Enumeration.cpp | Visits only real subsets of a specific mask |

## 🧠 Mental Model: "Switch Panel"

Picture `n` light switches in a row. A mask is a snapshot of which
switches are ON. Every operation above is just "flip switch `i`",
"check switch `i`", or "are all switches on/off" — nothing more
exotic than that. If you ever feel confused mid-DP-problem, come back
to this simple picture.

## ✅ How This Connects to Every Other File in the Repo

| Concept here | Used in |
|---|---|
| Check bit set | Every transition loop ("is this item already used?") |
| Set bit | Every transition ("mark item as now used") — `mask \| (1<<next)` |
| Full mask | Every base case check ("have we used everything?") |
| popcount | Occasionally used to track "how many picked so far" as extra state |
| Submask loop | Subset Enumeration.cpp, and any SOS-DP style problem |

## 🎯 Practice Strategy (do this BEFORE touching Generic Templates)

1. Run `Bitmask Basics.cpp`, change `n` and `mask` values, and predict
   each output on paper before running.
2. Write out, by hand, the binary representation of masks `0` through
   `15` for `n = 4`, and list which "items" each represents.
3. Without looking at the reference table, try to write the set/clear/
   toggle/check operations from memory. Repeat until instant.
4. Once this feels automatic, move to **Generic Templates/DFS +
   Memoization.cpp** — the true starting point of bitmask DP itself.