__attribute__((optimize("O0")))
// 1.26ms
void suck_loop(uint64_t loop) {
        loop = loop * 50 * 100;
        uint64_t a;
        while (loop > 0) {
                a = loop / (uint64_t)99;
                a = loop / (uint64_t)77;
                a = loop / (uint64_t)55;
                a = loop / (uint64_t)33;
                a = loop / (uint64_t)11;
                a = loop / (uint64_t)999;
                a = loop / (uint64_t)777;
                a = loop / (uint64_t)555;
                a = loop / (uint64_t)333;
                a = loop / (uint64_t)111;
                a = loop / (uint64_t)9999;
                a = loop / (uint64_t)7777;
                a = loop / (uint64_t)5555;
                a = loop / (uint64_t)3333;
                a = loop / (uint64_t)1111;
                a = loop / (uint64_t)99999;
                a = loop / (uint64_t)77777;
                a = loop / (uint64_t)55555;
                a = loop / (uint64_t)33333;
                a = loop / (uint64_t)11111;
                loop--;
        }
}

int cvi_board_init(void)
{
        uint32_t val;

        // wifi power reset
        mmio_write_32(0x0300104C, 0x3); // GPIOA 26
        val = mmio_read_32(0x03020004); // GPIOA DIR
        val |= (1 << 26); // output
        mmio_write_32(0x03020004, val);

        val = mmio_read_32(0x03020000); // signal level
        val &= ~(1 << 26); // set level to low
        mmio_write_32(0x03020000, val);

        suck_loop(200);

        val = mmio_read_32(0x03020000); // signal level
        val |= (1 << 26); // set level to high
        mmio_write_32(0x03020000, val);

        // wifi sdio pinmux
        mmio_write_32(0x030010D0, 0x0); // D3
        mmio_write_32(0x030010D4, 0x0); // D2
        mmio_write_32(0x030010D8, 0x0); // D1
        mmio_write_32(0x030010DC, 0x0); // D0
        mmio_write_32(0x030010E0, 0x0); // CMD
        mmio_write_32(0x030010E4, 0x0); // CLK

        // LED 
        //mmio_write_32(0x03001038, 0x3); // SD0_PWR_EN/XGPIOA_14
        PINMUX_CONFIG(SD0_PWR_EN, XGPIOA_14);

        // lcd reset
        mmio_write_32(0x030010A4, 0x0); // PWRGPIO 0 GPIO_MODE

        // lcd backlight
        //mmio_write_32(0x030010EC, 0x0); // GPIOB 0 PWM0_BUCK
        mmio_write_32(0x030010EC, 0x3); // GPIOB 0 GPIO_MODE
        val = mmio_read_32(0x03021004); // GPIOB DIR
        val |= (1 << 0); // output
        mmio_write_32(0x03021004, val);
        val = mmio_read_32(0x03021000); // signal level
        val |= (1 << 0); // set level to high
        mmio_write_32(0x03021000, val);

	// bitbang i2c
        mmio_write_32(0x0300103C, 0x03); // GPIOA 15 GPIO_MODE
	mmio_write_32(0x03001058, 0x03); // GPIOA 27 GPIO_MODE

	// bitbang spi
	mmio_write_32(0x03001060, 0x03); // GPIOA 24 GPIO_MODE
	mmio_write_32(0x0300105C, 0x03); // GPIOA 23 GPIO_MODE
	mmio_write_32(0x03001054, 0x03); // GPIOA 25 GPIO_MODE
	mmio_write_32(0x03001050, 0x03); // GPIOA 22 GPIO_MODE

#endif
        // wait hardware bootup
        suck_loop(100);
        return 0;
}
