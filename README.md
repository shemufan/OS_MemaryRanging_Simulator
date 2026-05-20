# OS_MemaryRanging_Simulator

## 一、项目简介

`OS_MemaryRanging_Simulator` 是一个使用 C++ 实现的操作系统内存管理模拟项目，主要用于模拟**请求分页存储管理方式**下作业的执行过程。

本项目以操作系统课程中的请求分页管理为背景，模拟一个包含 320 条指令的作业在有限物理内存块中的执行过程。系统将每 10 条指令划分为 1 个页面，因此该作业共有 32 个页面。系统为该作业分配 4 个物理内存块，初始状态下所有页面均未调入内存。

程序在执行过程中会依次访问生成的指令序列，根据指令号计算页号和页内偏移，通过页表判断页面是否已经在内存中。如果页面命中，则直接完成地址转换并输出物理地址；如果页面不在内存中，则产生缺页中断，并根据 FIFO 或 LRU 页面置换算法完成页面调入或页面置换。最终程序会统计并输出缺页次数和缺页率。

本项目的主要目标是加深对以下内容的理解：

- 请求分页存储管理的基本原理
- 页、页表、物理块之间的关系
- 逻辑地址到物理地址的转换过程
- 缺页中断的处理流程
- FIFO 和 LRU 页面置换算法的实现方式
- 程序局部性原理在指令访问序列中的体现

---

## 二、项目实现功能

本项目主要实现了以下功能：

### 1. 指令序列生成

系统自动生成 320 条指令访问序列，用于模拟作业执行过程。指令编号范围为：

```text
0 ~ 319
```

生成的指令序列体现程序执行中的局部性特征，包括：

- 顺序执行指令
- 跳转到前地址部分执行
- 跳转到后地址部分执行

### 2. 页面划分

每页存放 10 条指令，因此 320 条指令共划分为 32 个页面：

```text
页面大小：10 条指令
指令总数：320 条
页面总数：320 / 10 = 32 页
```

### 3. 页表管理

系统维护一个页表，用于记录每个页面的状态，包括：

- 页号
- 是否在内存中
- 所在物理块号
- 最近访问时间

页表用于支持页面查询、地址转换、页面调入、页面换出以及 LRU 算法中的最近访问时间判断。

### 4. 物理内存块管理

系统为作业分配 4 个物理内存块。程序会实时维护每个物理块中当前存放的页面。

当发生缺页时，系统会先判断是否存在空闲物理块：

- 如果存在空闲物理块，则直接将页面调入该物理块。
- 如果 4 个物理块均已被占用，则执行页面置换算法，选择一个页面换出。

### 5. 地址转换

系统根据访问的指令号计算页号和页内偏移：

```cpp
pageNo = instructionNo / PAGE_SIZE;
offset = instructionNo % PAGE_SIZE;
```

如果该页已经在物理块 `blockNo` 中，则物理地址计算公式为：

```cpp
physicalAddress = blockNo * PAGE_SIZE + offset;
```

例如，访问第 126 条指令：

```text
页号 = 126 / 10 = 12
页内偏移 = 126 % 10 = 6
```

如果第 12 页存放在物理块 2 中，则物理地址为：

```text
物理地址 = 2 * 10 + 6 = 26
```

### 6. 缺页处理

当访问的页面不在内存中时，系统会产生缺页。缺页处理过程如下：

```text
1. 缺页次数加 1
2. 判断是否存在空闲物理块
3. 如果有空闲块，则直接调入页面
4. 如果没有空闲块，则执行页面置换算法
5. 更新页表信息
6. 更新物理内存块状态
7. 输出调页后的物理地址
```

### 7. 页面置换算法

本项目实现了两种页面置换算法：

- FIFO 页面置换算法
- LRU 页面置换算法

用户可以在程序运行时选择使用哪一种算法。

### 8. 缺页率统计

程序执行完 320 条指令后，会统计：

- 总指令数
- 缺页次数
- 缺页率
- 使用的页面置换算法

缺页率计算公式为：

```cpp
pageFaultRate = pageFaultCount / totalInstructionCount
```

显示时通常以百分比形式输出。

---

## 三、项目运行环境和运行方法

### 1. 开发环境

本项目使用 C++ 编写，推荐运行环境如下：

```text
操作系统：Windows / Linux / macOS
编程语言：C++17
构建工具：CMake
编译器：g++ / clang++ / MSVC
```

### 2. 项目目录结构

项目采用模块化结构组织代码：

```text
OS_MemaryRanging_Simulator/
│
├── CMakeLists.txt
├── README.md
│
├── include/
│   ├── Config.h
│   ├── FIFOReplacement.h
│   ├── InstructionGenerator.h
│   ├── JsonExporter.h
│   ├── LRUReplacement.h
│   ├── MemoryBlock.h
│   ├── MemoryManager.h
│   ├── PageTable.h
│   ├── PageTableEntry.h
│   ├── ReplacementAlgorithm.h
│   ├── SimulationStep.h
│   └── Simulator.h
│
├── src/
│   ├── FIFOReplacement.cpp
│   ├── InstructionGenerator.cpp
│   ├── JsonExporter.cpp
│   ├── LRUReplacement.cpp
│   ├── MemoryManager.cpp
│   ├── PageTable.cpp
│   ├── Simulator.cpp
│   └── main.cpp
│
├── frontend/
│   ├── index.html
│   ├── style.css
│   └── app.js
│
└── output/
    ├── simulation_result.json
    └── simulation_data.js
```

### 3. 编译方法

在项目根目录下执行：

```bash
g++ src/*.cpp -I include -o simulator.exe
```

### 4. 运行方法

编译完成后，进入生成目录运行程序。

Linux / macOS：

```bash
./simulator.exe
```

Windows：

```bash
simulator.exe
```


### 5. 程序运行流程

程序启动后，用户需要选择页面置换算法：

```text
请求分页存储管理模拟系统
1. FIFO 页面置换算法
2. LRU 页面置换算法
请选择算法：
```

输入 `1` 表示使用 FIFO 页面置换算法，输入 `2` 表示使用 LRU 页面置换算法。

程序随后会自动生成指令访问序列，并依次模拟每条指令的访问过程。

---

## 四、功能实现说明

## 4.1 系统总体流程

系统整体执行流程如下：

```text
开始
│
├── 初始化页表
├── 初始化物理内存块
├── 生成 320 条指令访问序列
│
├── 依次访问每条指令
│   │
│   ├── 计算页号和页内偏移
│   ├── 查询页表
│   │
│   ├── 如果页面在内存中
│   │   ├── 计算物理地址
│   │   ├── 输出命中信息
│   │   └── 更新访问时间
│   │
│   └── 如果页面不在内存中
│       ├── 缺页次数加 1
│       ├── 判断是否有空闲物理块
│       ├── 有空闲块则直接调入页面
│       ├── 无空闲块则执行页面置换
│       ├── 更新页表
│       ├── 更新物理块状态
│       └── 输出调页后的物理地址
│
├── 输出最终统计结果
└── 结束
```

---

## 4.2 核心配置

项目中的基本参数在 `Config.h` 中统一定义：

```cpp
const int INSTRUCTION_COUNT = 320;
const int PAGE_SIZE = 10;
const int PAGE_COUNT = 32;
const int MEMORY_BLOCK_COUNT = 4;
```

这样可以使项目参数更加集中，便于后续修改和维护。

---

## 4.3 指令序列模拟方式

为了模拟程序执行中的局部性原理，系统按照一定规则生成指令访问序列。

基本思想如下：

```text
1. 在 0 ~ 319 之间随机选择一条起始指令 m
2. 顺序执行下一条指令 m + 1
3. 跳转到前地址部分 0 ~ m - 1 中的某条指令 m1
4. 顺序执行 m1 + 1
5. 跳转到后地址部分 m1 + 2 ~ 319 中的某条指令 m2
6. 顺序执行 m2 + 1
7. 重复上述过程，直到生成 320 条指令
```

这种方式能够体现：

- 顺序执行特征
- 前地址访问特征
- 后地址访问特征
- 程序访问的局部性原理

其中，顺序执行体现了程序的时间局部性和空间局部性；前后地址跳转则模拟了分支、循环和跳转指令带来的非连续访问。

---

## 4.4 页表设计

页表是请求分页管理中的核心数据结构。

本项目中，每个页表项包含以下信息：

```cpp
class PageTableEntry {
public:
    int pageNo;
    int blockNo;
    bool inMemory;
    int lastVisitTime;
};
```

字段说明如下：

| 字段 | 含义 |
|---|---|
| `pageNo` | 页面编号 |
| `blockNo` | 页面所在的物理块号 |
| `inMemory` | 页面是否已经调入内存 |
| `lastVisitTime` | 页面最近一次被访问的时间，用于 LRU 算法 |

页表支持以下操作：

- 判断页面是否在内存中
- 查询页面所在物理块号
- 页面调入时更新页表项
- 页面换出时重置页表项
- 页面命中时更新最近访问时间

---

## 4.5 物理内存块设计

系统为作业分配 4 个物理块，每个物理块记录当前存放的页面。

物理块结构如下：

```cpp
class MemoryBlock {
public:
    int blockNo;
    int pageNo;
};
```

字段说明如下：

| 字段 | 含义 |
|---|---|
| `blockNo` | 物理块编号 |
| `pageNo` | 当前物理块中存放的页面编号，`-1` 表示空闲 |

内存块管理模块主要负责：

- 查找空闲物理块
- 将页面装入指定物理块
- 从物理块中移除页面
- 根据页面查找所在物理块
- 输出当前内存块状态

---

## 4.6 FIFO 页面置换算法

FIFO 是 First In First Out 的缩写，即先进先出页面置换算法。

算法思想：

```text
最早进入内存的页面，在需要置换时最先被淘汰。
```

实现方式：

```text
1. 使用队列保存页面进入内存的先后顺序
2. 页面调入内存时，将页号加入队尾
3. 当发生缺页且内存块已满时，选择队头页面作为淘汰页面
4. 将队头页面出队
5. 将新页面调入被释放的物理块，并加入队尾
```

FIFO 的特点：

- 实现简单
- 运行效率高
- 不需要记录页面访问时间
- 但可能淘汰近期仍然频繁使用的页面

FIFO 的核心逻辑示意：

```cpp
void FIFOReplacement::onPageLoaded(int pageNo) {
    pageQueue.push(pageNo);
}

int FIFOReplacement::selectVictimPage(PageTable&, MemoryManager&) {
    int victim = pageQueue.front();
    pageQueue.pop();
    return victim;
}
```

---

## 4.7 LRU 页面置换算法

LRU 是 Least Recently Used 的缩写，即最近最久未使用页面置换算法。

算法思想：

```text
当需要进行页面置换时，淘汰当前在内存中最长时间没有被访问的页面。
```

实现方式：

```text
1. 系统维护一个当前时间 currentTime
2. 每访问一条指令，currentTime 加 1
3. 页面命中时，更新该页面的 lastVisitTime
4. 页面调入时，也更新该页面的 lastVisitTime
5. 当需要页面置换时，遍历所有在内存中的页面
6. 选择 lastVisitTime 最小的页面进行淘汰
```

LRU 的特点：

- 更符合程序局部性原理
- 通常比 FIFO 有更低的缺页率
- 需要维护页面最近访问时间
- 实现复杂度略高于 FIFO

LRU 的核心逻辑示意：

```cpp
int LRUReplacement::selectVictimPage(PageTable& pageTable,
                                     MemoryManager&) {
    int victimPage = -1;
    int minTime = INT_MAX;

    for (int pageNo = 0; pageNo < PAGE_COUNT; pageNo++) {
        PageTableEntry entry = pageTable.getEntry(pageNo);

        if (entry.inMemory && entry.lastVisitTime < minTime) {
            minTime = entry.lastVisitTime;
            victimPage = entry.pageNo;
        }
    }

    return victimPage;
}
```

---

## 4.8 缺页率统计

当所有 320 条指令执行完成后，程序会统计缺页次数并计算缺页率。

计算公式如下：

```cpp
pageFaultRate = static_cast<double>(pageFaultCount) / totalInstructions;
```

输出示例：

```text
总指令数: 320
缺页次数: 86
缺页率: 26.875%
使用算法: LRU
```

由于指令序列是随机生成的，因此每次运行时缺页次数和缺页率可能会有所不同。

---

## 五、前端可视化

v2.0 新增了基于 HTML + CSS + JavaScript 的静态前端可视化页面，可直接在浏览器中查看模拟过程。

### 5.1 前后端数据连接

C++ 模拟器在运行结束后会自动生成两份数据文件：

| 文件 | 格式 | 用途 |
|---|---|---|
| `output/simulation_result.json` | 纯 JSON | 通用数据交换，供 fetch 读取 |
| `output/simulation_data.js` | JavaScript | 将 JSON 包裹为 `var SIMULATION_DATA = {...};`，供 `<script>` 标签直接引入 |

前端加载数据的优先级：

1. 检查 `window.SIMULATION_DATA` 是否存在（通过 `<script>` 标签引入）
2. 如果不存在，则使用 `fetch('../output/simulation_result.json')` 异步加载

这种双通道设计使得前端**既可以直接双击 HTML 打开（无需服务器），也可以通过 HTTP 服务器访问**。

### 5.2 SimulationStep 数据结构

C++ 端新增 `SimulationStep` 结构体，记录每一步模拟的完整状态：

```cpp
struct SimulationStep {
  int stepNo;                  // 当前步骤编号
  int instructionNo;           // 访问的指令号
  int pageNo;                  // 页号
  int offset;                  // 页内偏移
  bool pageFault;              // 是否缺页
  int blockNo;                 // 所在物理块号
  int physicalAddress;         // 物理地址
  int loadedPage;              // 调入页面，-1 表示无
  int victimPage;              // 淘汰页面，-1 表示无
  std::vector<int> memoryState;// 4 个物理块存放的页面，-1 表示空闲
  int pageFaultCount;          // 累计缺页次数
  double pageFaultRate;        // 当前缺页率
};
```

Simulator 在每次指令访问后自动记录一个 `SimulationStep`，最终通过 `JsonExporter` 导出。

### 5.3 JSON 数据格式

导出的 JSON 结构如下：

```json
{
  "algorithm": "LRU",
  "totalInstructions": 320,
  "pageSize": 10,
  "pageCount": 32,
  "memoryBlockCount": 4,
  "steps": [
    {
      "stepNo": 1,
      "instructionNo": 126,
      "pageNo": 12,
      "offset": 6,
      "pageFault": true,
      "blockNo": 0,
      "physicalAddress": 6,
      "loadedPage": 12,
      "victimPage": -1,
      "memoryState": [12, -1, -1, -1],
      "pageFaultCount": 1,
      "pageFaultRate": 0.003125
    }
  ]
}
```

### 5.4 前端功能

| 功能 | 说明 |
|---|---|
| 算法标识 | 右上角显示当前使用的算法（FIFO / LRU） |
| 步骤进度条 | 显示当前步骤 / 总步骤，蓝色渐变填充 |
| 指令信息 | 显示指令号、页号、页内偏移、物理地址 |
| 访问结果 | 命中显示绿色 ✔，缺页显示红色 ✘ |
| 调入/淘汰 | 显示 loadedPage 和 victimPage，-1 显示为"无" |
| 物理内存块 | 4 个卡片显示当前各块存放的页面，空闲显示"空闲"，当前访问块橙色高亮 |
| 统计信息 | 实时显示累计缺页次数和缺页率 |
| 播放控制 | 上一步 / 下一步 / 自动播放（600ms）/ 暂停 / 重置 |
| 键盘快捷键 | ← → 切换步骤，空格 播放/暂停，R 重置 |
| 响应式布局 | 2×2 网格布局，移动端自动切换为单列 |

### 5.5 前端使用方法

**方式一（推荐）：直接打开**

先运行 C++ 模拟器生成数据文件，然后双击打开：

```
frontend/index.html
```

浏览器通过 `<script>` 标签直接加载 `output/simulation_data.js`，无需任何服务器。

**方式二：HTTP 服务器**

在项目根目录启动 HTTP 服务器：

```bash
cd os_memorypaging_simulator
python3 -m http.server 8000
```

浏览器访问：

```
http://localhost:8000/frontend/index.html
```

此时前端优先读取 `<script>` 引入的全局变量；若跨网络时 JS 文件不可用，自动回退到 `fetch` 方式加载 JSON。

### 5.6 前端架构

```text
frontend/
├── index.html    # 页面结构，2×2 网格 + 控制栏
├── style.css     # 样式：命中绿/缺页红/活跃块橙，响应式布局
└── app.js        # 逻辑：数据加载、步骤渲染、播放控制、键盘事件
```

前端为零依赖纯静态页面，无需 npm、框架或构建工具，在任何现代浏览器中均可运行。

---

## 六、项目亮点

### 1. 模块化设计清晰

项目将不同功能拆分为多个模块，包括：

- 指令序列生成模块
- 页表管理模块
- 物理内存管理模块
- 页面置换算法模块
- 模拟控制模块
- JSON 导出模块
- 前端可视化模块

每个模块职责清晰，便于理解、维护和扩展。

### 2. 面向对象设计合理

项目使用 C++ 面向对象思想进行设计，将页表、内存块、置换算法等抽象为独立类，提高了代码的可读性和可维护性。

### 3. 页面置换算法具有可扩展性

项目定义了统一的页面置换算法接口 `ReplacementAlgorithm`，FIFO 和 LRU 均继承该接口实现。

这种设计使得后续扩展其他置换算法更加方便，例如：

- OPT 最佳置换算法
- Clock 时钟置换算法
- Second Chance 二次机会算法

### 4. 完整模拟请求分页过程

项目完整模拟了从逻辑地址访问到物理地址转换的全过程，包括：

```text
指令访问
页号计算
页表查询
页面命中
缺页中断
页面调入
页面置换
地址转换
缺页率统计
```

能够较好地体现请求分页存储管理的基本思想。

### 4. 多格式结果输出

每次模拟运行自动生成以下文件：

| 文件 | 内容 |
|---|---|
| `result.txt` | 完整的控制台输出（每次访问详情 + 最终统计） |
| `output/simulation_result.json` | 结构化 JSON 数据，包含每一步的完整模拟状态 |
| `output/simulation_data.js` | 等同于 JSON 包裹为 JS 全局变量，供前端直接引入 |

JSON 输出示例：
```
{
  "algorithm": "FIFO",
  "totalInstructions": 320,
  "pageSize": 10,
  "pageCount": 32,
  "memoryBlockCount": 4,
  "steps": [
    {
      "stepNo": 1,
      "instructionNo": 1,
      "pageNo": 0,
      "offset": 1,
      "pageFault": true,
      "blockNo": 0,
      "physicalAddress": 1,
      "loadedPage": 0,
      "victimPage": -1,
      "memoryState": [0, -1, -1, -1],
      "pageFaultCount": 1,
      "pageFaultRate": 0.003125
    },
}
```

txt 输出实例：
```
访问指令：162 页号：16 页内偏移：2
命中！物理块：2 物理地址为：22
当前内存块状态: [22, 30, 16, 9]
------------------------
========== 内存统计信息 ==========
总指令数: 320
缺页次数 157
缺页率: 49.0625%
使用算法: LRU
==================================
```

前端页面展示：

![前端页面展示](./assets/frontend-demo.png)

便于撰写实验报告和进行数据分析。

### 5. 支持 FIFO 与 LRU 对比

项目同时实现 FIFO 和 LRU 两种页面置换算法，用户可以在程序运行时选择不同算法进行模拟，便于观察不同算法对缺页次数和缺页率的影响。

### 6. 前端可视化交互

新增纯静态前端可视化页面，支持分步查看、自动播放、暂停/重置等交互操作。命中/缺页分别以绿色/红色实时标记，当前访问的物理块橙色高亮。页面零依赖，可直接双击打开，无需服务器或构建工具。键盘快捷键支持（← → 空格 R），适合课程设计展示。

---

## 七、项目改进方向

虽然本项目已经完成了请求分页存储管理的基本模拟功能，但仍然可以从以下几个方面继续改进。

### 1. 增强前端可视化

v2.0 已实现基础前端可视化。后续可进一步增强：

- 页表完整状态展示（32 页 × 每页状态）
- 缺页率实时折线图
- FIFO 与 LRU 双栏对比模式
- 页面置换动画过渡效果
- 支持运行时切换算法并重新模拟

### 2. 增加更多页面置换算法

目前项目实现了 FIFO 和 LRU。后续可以继续扩展：

- OPT 最佳置换算法
- Clock 页面置换算法
- LFU 最少使用算法
- Second Chance 二次机会算法

通过对比不同算法的缺页率，可以更深入地分析页面置换策略的优劣。

### 3. 支持自定义参数

当前项目中的指令总数、页面大小、页面数量和物理块数量主要通过配置文件定义。

后续可以支持用户在运行时输入参数，例如：

```text
指令总数
页面大小
物理块数量
页面置换算法
```

这样可以提高程序的灵活性。

### 4. 增加算法对比统计

可以让程序一次性运行 FIFO 和 LRU 两种算法，并输出对比结果：

```text
算法    缺页次数    缺页率
FIFO    92          28.75%
LRU     86          26.875%
```

这样可以更直观地比较不同页面置换算法的效果。

---

## 八、项目总结

本项目使用 C++ 实现了一个请求分页存储管理模拟系统，完整模拟了作业执行过程中页面访问、页表查询、缺页中断、页面调入、页面置换和缺页率统计等过程。同时新增了纯静态前端可视化页面，支持在浏览器中分步查看和自动播放整个模拟过程。

通过本项目，可以更加直观地理解请求分页系统的工作机制，掌握页表在地址转换中的作用，理解物理内存块有限时页面置换算法的重要性。同时，通过 FIFO 和 LRU 两种算法的实现与对比，也可以进一步理解不同页面置换策略对系统性能的影响。前端可视化页面使模拟过程更加生动，适合课程设计展示和实验报告演示。

整体来看，本项目结构清晰、功能完整、扩展性较好，能够满足操作系统课程中请求分页存储管理模拟实验的基本要求。

