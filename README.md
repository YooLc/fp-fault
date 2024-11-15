# Intel CPU x87 浮点数性能异常的分析 - 实验代码

实验报告: [report.md](report.md)

为了防止反作弊机制，公布我提交的作业 `.zip` 文件的 SHA 256 哈希值为: `1576c7e14cc9ed90d9d4f4c86a82e35058af0ac4c99a247b173064ef640fbcf5`

## 文件内容

`cr-write` 文件夹包含了读写 `cr0.ne` 位的 Linux Kernel Module

在该目录下使用 `make && make install` 可以安装该内核模块并修改 `cr0.ne` 位

`machin_clear` 相关的文件测试了在正常浮点数运算情况下手动触发 Machine Clear 的影响

其余文件是对 Intel CPU x87/SSE/AVX 在 正常浮点数 / Inf / NaN 等输入下， fadd / fmul 性能的自动测试代码，构建方法请参考下面。

## 编译运行

请安装 `gcc`, `cmake` 等构建工具进行构建

自动编译运行:

```bash
./run.sh
```

手动编译运行:

```bash
cmake -B build
cmake --build build
./build/fp-fault
```
