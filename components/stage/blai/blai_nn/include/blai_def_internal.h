#ifndef __BLAI_DEF_INTERNAL_H__
#define __BLAI_DEF_INTERNAL_H__

//#define BLAI_DEBUG
//#define BLAI_PROFILING
//#define BLAI_SHOW_NETWORK

#ifdef BLAI_DEBUG
#define BLAI_NPU_OPS_DEBUG
#define BLAI_SHOW_INST
//#define BLAI_MEMALLOC_DEBUG
//#define BLAI_NPU_HALT_EACH_LAYER
#endif

#ifdef BLAI_PROFILING
//#define BLAI_PROFILING_EACH_LAYER
#endif


#endif /* __BLAI_DEF_INTERNAL_H__ */

