Absolutely—here is your **clean, copy-paste ready `.md` file** (no extra explanation, just structured Markdown):

---

```md
# Module 12 Assignment — Operating Systems

---

## Q1) Disadvantages of Fixed-Sized Partitioning

1. **Internal Fragmentation**  
   Memory inside a partition may be wasted if the process is smaller than the partition size.

2. **Limited Number of Processes**  
   The number of processes is restricted by the fixed number of partitions.

3. **Process Size Limitation**  
   A process larger than the partition size cannot be loaded, even if total memory is available.

---

## Q2) Dynamic Partitioning

### Given Free Blocks:
`5M, 3M, 4M, 6M, 2M, 4M, 3M`

Last allocation marked as **X**.

New request: **2 MB**

---

### Best Fit

- Selects the smallest block that fits.
- Best match: **2M block**

**Result:**
- Entire 2M block is allocated.

```

[Used][5M free][Used][3M free][Used][4M free][Used][6M free][X][2M allocated][Used][4M free][Used][3M free]

```

---

### First Fit

- Selects first block large enough.
- First match: **5M block**

**Result:**
- Allocate 2M from 5M → 3M remains free.

```

[Used][2M allocated][3M free][Used][3M free][Used][4M free][Used][6M free][X][2M free][Used][4M free][Used][3M free]

```

---

### Next Fit

- Starts from **X**, scans right.
- First match after X: **2M block**

**Result:**
- Entire 2M block allocated.

```

[Used][5M free][Used][3M free][Used][4M free][Used][6M free][X][2M allocated][Used][4M free][Used][3M free]

```

---

## Q3) Buddy System

### Total Memory:
`2 MB = 2048 KB`

---

### Sequence of Operations

#### Initial
```

[2048 free]

```

---

#### A requests 156 KB → 256 KB
```

[A256][256 free][512 free][1024 free]

```

---

#### B requests 448 KB → 512 KB
```

[A256][256 free][B512][1024 free]

```

---

#### C requests 511 KB → 512 KB
```

[A256][256 free][B512][C512][512 free]

```

---

#### Release B
```

[A256][256 free][512 free][C512][512 free]

```

---

#### D requests 259 KB → 512 KB
```

[A256][256 free][D512][C512][512 free]

```

---

#### E requests 97 KB → 128 KB
```

[A256][256 free][D512][C512][E128][128 free][256 free]

```

---

#### F requests 75 KB → 128 KB
```

[A256][256 free][D512][C512][E128][F128][256 free]

```

---

#### Release C
```

[A256][256 free][D512][512 free][E128][F128][256 free]

```

---

#### Release F
```

[A256][256 free][D512][512 free][E128][128 free][256 free]

```

---

#### Release A (merge 256 + 256 → 512)
```

[512 free][D512][512 free][E128][128 free][256 free]

```

---

#### Release D (merge 512 + 512 → 1024)
```

[1024 free][512 free][E128][128 free][256 free]

```

---

#### Release E (full merge back)
```

[2048 free]

```

---

## Q3(B) Binary Tree after Release C

```

2048
├── 1024
│   ├── 512
│   │   ├── 256 (A)
│   │   └── 256 (Free)
│   └── 512 (D)
└── 1024
├── 512 (Free)
└── 512
├── 256
│   ├── 128 (E)
│   └── 128 (F)
└── 256 (Free)

```

---

### Memory Mapping

```

0–255     → A
256–511   → Free
512–1023  → D
1024–1535 → Free
1536–1663 → E
1664–1791 → F
1792–2047 → Free

```

---

## Q4) Paging

### Given:
- Page size = 16 bytes
- Memory is 2-byte addressable
- Locations per page = 16 / 2 = 8

---

### Page Table

| Page | Frame |
|------|------|
| 0 | 14 |
| 1 | 22 |
| 2 | 10 |
| 3 | 17 |
| 4 | 12 |
| 5 | 9 |
| 6 | 31 |

---

## Q4(A) Logical Address = 49

### Step 1: Page Number
```

49 / 8 = 6

```

### Step 2: Offset
```

49 mod 8 = 1

```

### Step 3: Frame
```

Page 6 → Frame 31

```

### Step 4: Physical Address
```

(31 × 8) + 1 = 249

```

### Final Answer:
```

49 → 249

```

---

## Q4(B) Logical Address = 22

### Step 1: Page Number
```

22 / 8 = 2

```

### Step 2: Offset
```

22 mod 8 = 6

```

### Step 3: Frame
```

Page 2 → Frame 10

```

### Step 4: Physical Address
```

(10 × 8) + 6 = 86

```

### Final Answer:
```

22 → 86

```

---

# Final Summary

- **Best Fit:** 2M block  
- **First Fit:** first 5M block  
- **Next Fit:** 2M block after X  
- **49 → 249**  
- **22 → 86**

---
```

---

If you want, I can also:

* convert this to a **perfectly formatted PDF/Word submission**
* or add **diagrams (cleaner memory strips)** to make it look top-tier for grading
