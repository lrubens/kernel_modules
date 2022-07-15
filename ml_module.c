/* #include "ml_module.h" */
#include "common.h"
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/random.h>
/* #include <asm/fpu/api.h> */
#include <linux/slab.h>
#include <linux/ktime.h>
#include "asm/neon.h"
/* #include <asm/neon/api.h> */


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rubens Lacouture");
MODULE_DESCRIPTION("Simple kernel module");
MODULE_VERSION("0.01");

extern int forward_pass(matrix *input);

static int __init ml_module_init(void) {
    printk(KERN_INFO "Starting ML in Kernel test");

    kernel_neon_begin();

    REAL in[NR_FEAT] = {0};
    matrix input = {1, NR_FEAT, in};
    int output;

    ktime_t start_time, stop_time, elapsed_time;
    start_time = ktime_get();
    output = forward_pass(&input);
    stop_time = ktime_get();
    elapsed_time = ktime_sub(stop_time, start_time);
    printk(KERN_INFO "Elapsed times: %lld\n", ktime_to_ns(elapsed_time));
    printk(KERN_INFO "pred: %d", output);
    /* output = forward_pass(&input); */

    kernel_neon_end();

    return 0;
}

static void __exit ml_module_exit(void) {
    printk(KERN_INFO "Done");
}

module_init(ml_module_init);
module_exit(ml_module_exit);

