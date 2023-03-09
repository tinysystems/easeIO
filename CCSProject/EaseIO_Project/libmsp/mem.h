#ifndef _LIBMSP_MEM_H
#define _LIBMSP_MEM_H

/* The linker script needs to allocate these sections into FRAM region. */
#define __nv    __attribute__((section(".persistent")))
#define __ro_nv __attribute__((section(".persistent")))
#define __hifram    __attribute__((section(".persistent_hifram")))
#define __ro_hifram    __attribute__((section(".persistent_hifram")))
#endif // _LIBMSP_MEM_H
