
/* auto-generated by gen_syscalls.py, don't edit */

#ifndef _ASMLANGUAGE

#include <syscall_list.h>
#include <syscall_macros.h>

#ifdef __cplusplus
extern "C" {
#endif

K_SYSCALL_DECLARE2(K_SYSCALL_I2C_CONFIGURE, i2c_configure, int, struct device *, dev, u32_t, dev_config);

K_SYSCALL_DECLARE4(K_SYSCALL_I2C_TRANSFER, i2c_transfer, int, struct device *, dev, struct i2c_msg *, msgs, u8_t, num_msgs, u16_t, addr);

K_SYSCALL_DECLARE2(K_SYSCALL_I2C_SLAVE_REGISTER, i2c_slave_register, int, struct device *, dev, struct i2c_slave_config *, cfg);

K_SYSCALL_DECLARE2(K_SYSCALL_I2C_SLAVE_UNREGISTER, i2c_slave_unregister, int, struct device *, dev, struct i2c_slave_config *, cfg);

K_SYSCALL_DECLARE1(K_SYSCALL_I2C_SLAVE_DRIVER_REGISTER, i2c_slave_driver_register, int, struct device *, dev);

K_SYSCALL_DECLARE1(K_SYSCALL_I2C_SLAVE_DRIVER_UNREGISTER, i2c_slave_driver_unregister, int, struct device *, dev);

#ifdef __cplusplus
}
#endif

#endif
