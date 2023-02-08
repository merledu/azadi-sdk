add_library(src 
    gpio.c
    i2c.c
    tic.c
    isr_spi_rx.c
    isr_spi_tx.c
    plic.c
    pwm.c
    spi.c
    timer.c
    uart.c
    utils.c
)

target_include_directories( src PUBLIC "${PROJECT_SOURCE_DIR}/include" )