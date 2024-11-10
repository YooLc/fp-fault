#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/processor.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("o1-preview-hah");
MODULE_DESCRIPTION("A module to read and modify CR0.NE");
MODULE_VERSION("1.0");

static int __init cr0_ne_init(void) {
    unsigned long cr0;

    cr0 = read_cr0();
    pr_info("Original CR0: 0x%lx\n", cr0);
    pr_info("Original CR0.NE: %lu\n", (cr0 >> 5) & 0x1);

    // 清除 CR0.NE 位（第5位）
    cr0 &= ~(1UL << 5);
    write_cr0(cr0);

    cr0 = read_cr0();
    pr_info("Modified CR0: 0x%lx\n", cr0);
    pr_info("Modified CR0.NE: %lu\n", (cr0 >> 5) & 0x1);

    return 0;
}

static void __exit cr0_ne_exit(void) {
    unsigned long cr0;

    // 恢复 CR0.NE 位（设置第5位）
    cr0 = read_cr0();
    cr0 |= (1UL << 5);
    write_cr0(cr0);

    pr_info("CR0.NE restored.\n");
}

module_init(cr0_ne_init);
module_exit(cr0_ne_exit);