# Flashing instructions

```bash
openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c
"program build/pico_rover.elf verify reset exit"
```