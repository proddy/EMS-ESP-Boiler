/*
 * EMS-ESP - https://github.com/proddy/EMS-ESP
 * Copyright 2019  Paul Derbyshire
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EMSESP_SYSTEM_H_
#define EMSESP_SYSTEM_H_

#include <Arduino.h>
#include <ArduinoJson.h>

#include "helpers.h"
#include "settings.h"
#include "console.h"
#include "mqtt.h"
#include "telegram.h"

#if defined(ESP8266)
#include "uart/emsuart_esp8266.h"
#include <RTCVars.h>
#elif defined(ESP32)
#include "uart/emsuart_esp32.h"
#elif defined(EMSESP_STANDALONE)
#include <emsuart_standalone.h>
#endif

#ifndef EMSESP_STANDALONE
#include <uuid/syslog.h>
#endif

#include <uuid/log.h>

using uuid::console::Shell;

namespace emsesp {

class System {
  public:
    static uint8_t free_mem();

    void start();
    void loop();

    static bool safe_mode();
    static void save_safe_mode(const bool safe_mode);
    static void safe_mode(const bool safe_mode);

    static void restart(bool safe_mode);
    static void restart() {
        restart(false); // default, don't boot into safe mode
    }

    static void show_mem(const char * text);

    static void console_commands(Shell & shell, unsigned int context);

  private:
    static uuid::log::Logger logger_;

#ifndef EMSESP_STANDALONE
    static uuid::syslog::SyslogService syslog_;
#endif

    static constexpr uint32_t SYSTEM_CHECK_FREQUENCY = 10000; // check every 10 seconds
    static constexpr uint32_t LED_WARNING_BLINK      = 1000;  // pulse to show no connection, 1 sec
    static constexpr uint32_t LED_WARNING_BLINK_FAST = 100;   // flash quickly for boot up sequence or safe-mode

// internal LED
#if defined(ESP8266)
    static constexpr uint8_t LED_GPIO = 2;
    static constexpr uint8_t LED_ON   = LOW;
#elif defined(ESP32)
    static constexpr uint8_t LED_GPIO = 5;   // 5 on Lolin D32, 2 on Wemos D1-32 mini. Use 0 for off.
    static constexpr uint8_t LED_ON   = LOW; // LOW on Lolin D32, HIGH on Wemos D1-32 mini
#else
    static constexpr uint8_t LED_GPIO = 0;
    static constexpr uint8_t LED_ON   = 0;
#endif

    void led_monitor();
    void set_led_speed(uint32_t speed);
    void mqtt_commands(const char * message);
    void config_syslog();

    static void show_system(uuid::console::Shell & shell);

    void     system_check();
    bool     system_healthy_  = false;
    uint32_t led_flash_speed_ = LED_WARNING_BLINK_FAST; // default boot flashes quickly

    static bool     safe_mode_;
    static uint32_t heap_start_;
    static int      reset_counter_;

    static EMSuart emsuart_;

#if defined(ESP8266)
    static RTCVars state_;
#endif
};

} // namespace emsesp

#endif