#ifndef  __TVOS_HAL_LINUX_ADAPTER_H__
#define __TVOS_HAL_LINUX_ADAPTER_H__

#ifdef LINUX_OS

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

typedef struct hw_module_t
{

} hw_module_t;

/**
 * Get the module info associated with a module by id.
 *
 * @return: 0 == success, <0 == error and *module == NULL
 */
static inline int hw_get_module(const char *id, const struct hw_module_t **module)
{
    return 0;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

#endif /* __TVOS_HAL_LINUX_ADAPTER_H__ */

