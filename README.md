## Fun stuff:
- USB descriptor will always fail on CM4, as that core does not have access to the memory area containing the device ID. Mitigated with fixed ID.
- UART4 is connected in reverse to STDC14 debug connector (whoopsie)
- 
