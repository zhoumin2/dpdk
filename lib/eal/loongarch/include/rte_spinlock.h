/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2022 Loongson Technology Corporation Limited
 */

#ifndef _RTE_SPINLOCK_LOONGARCH_H_
#define _RTE_SPINLOCK_LOONGARCH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <rte_common.h>
#include "generic/rte_spinlock.h"

#ifndef RTE_FORCE_INTRINSICS
static inline void
rte_spinlock_lock(rte_spinlock_t *sl)
{
    int temp = 0;
    __asm__ __volatile__(
        "1: ll.w %[temp], %[lock] \n"
        "   bnez %[temp], 1b \n"
        "   li.w %[temp], 1 \n"
        "   sc.w %[temp], %[lock] \n"
        "   beqz %[temp], 1b \n"
        : [lock] "+m" (sl->locked),
          [temp] "+&r"(temp)
        : "m"(sl->locked)
        : "memory"
        );
}

static inline void
rte_spinlock_unlock (rte_spinlock_t *sl)
{
    int temp = 0;
    __asm__ __volatile__(
        "1: ll.w %[temp], %[lock] \n"
        "   li.w %[temp], 0 \n"
        "   sc.w %[temp], %[lock] \n"
        "   beqz %[temp], 1b \n"
        : [lock] "+m" (sl->locked),
          [temp] "+&r"(temp)
        : "m"(sl->locked)
        : "memory"
        );
}

static inline int
rte_spinlock_trylock (rte_spinlock_t *sl)
{
    int temp = 0, res = 1;
    __asm__ __volatile__(
        "1: ll.w %[res], %[lock] \n"
        "   li.w %[temp], 1 \n"
        "   sc.w %[temp], %[lock] \n"
        "   beqz %[temp], 1b \n"
        : [lock] "+m" (sl->locked),
          [res] "=&r" (res),
          [temp] "+&r"(temp)
        : "m"(sl->locked)
        : "memory"
        );

    return res == 0;
}
#endif

static inline int rte_tm_supported(void)
{
	return 0;
}

static inline void
rte_spinlock_lock_tm(rte_spinlock_t *sl)
{
	rte_spinlock_lock(sl); /* fall-back */
}

static inline int
rte_spinlock_trylock_tm(rte_spinlock_t *sl)
{
	return rte_spinlock_trylock(sl);
}

static inline void
rte_spinlock_unlock_tm(rte_spinlock_t *sl)
{
	rte_spinlock_unlock(sl);
}

static inline void
rte_spinlock_recursive_lock_tm(rte_spinlock_recursive_t *slr)
{
	rte_spinlock_recursive_lock(slr); /* fall-back */
}

static inline void
rte_spinlock_recursive_unlock_tm(rte_spinlock_recursive_t *slr)
{
	rte_spinlock_recursive_unlock(slr);
}

static inline int
rte_spinlock_recursive_trylock_tm(rte_spinlock_recursive_t *slr)
{
	return rte_spinlock_recursive_trylock(slr);
}

#ifdef __cplusplus
}
#endif

#endif /* _RTE_SPINLOCK_LOONGARCH_H_ */
