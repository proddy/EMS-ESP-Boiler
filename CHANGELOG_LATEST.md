# Changelog

### Added
- function keys in editor: cursor, del, home, end. F1=help, F2=show, and other shortcuts
- SM100 pump working time and energy units
- heating curve parameters and commands for RC300
- `wwonetime` for RC300 thermostat
- expose test framework via api (#611)
- SysLog has enable/disable flag in WebUI
- Add solar configuration telegrams (#616) [thanks @hpanther]
- `log trace` shows decoded or optional raw telegrams, `watch unknown` for only unknown telegrams
- WM10 switch telegrams
- boiler information (#633), pumpmod min/max commands
- maintenance message and command
- thermostat program, reducemode, controlmode
- optional delayed start for sending tx-telegrams to prevent conflicts with KM200
- RC35 holiday setting with `+` for 'at home'

### Fixed
- mixer IPM pumpstatus
- mixer devices in HA were incorrectly named
- Prevent HA MQTT config messages for thermostat that has no 'currtemp' (#582)
- serviceCodeNumber, 3-char serviceCode, exhausttemp and heating_active for newer ems+ boilers
- prevent MQTT publish messages from sending twice
- repeated output on read commands
- heating_active for ems+
- fix telegrams matched to masterthermostat 0x18

### Changed
- optimized MQTT for HA to reduce heap fragmentation issues
- change syslog settings without reboot
- HA-config split in smaller blocks
- commands `fetch` and `publish [ha]` as call
- mqtt json package sizes
- renamed the command system info (which showed settings) to `settings`
- renamed the command system report (Which dumped debug info) to `info`
- Changing settings via web restarts only selected services
- renamed pio targets (esp8266-ci and esp32-ci for GitHub CI)
- telnet default settings `log info`, timeout 60 min
- `log debug` not showing telegram names, use `log trace` or `watch on` to show the telegrams
- optimized how console and web display device data (#632)

### Removed
- old shell and python build scripts
