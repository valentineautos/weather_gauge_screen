#include <Arduino.h>
#include <string>
#include <ESP_Panel_Library.h>
#include <lvgl.h>
#include "lvgl_port_v8.h"
#include "fonts/roboto_regular_24.h"
#include "fonts/roboto_semibold_28.h"
#include "fonts/roboto_semibold_64.h"
#include "fonts/roboto_semibold_40.h"
#include "fonts/roboto_semibold_80.h"
#include "fonts/weather_font_48.h"
#include "fonts/weather_font_120.h"
#include <WiFi.h>
#include <esp_now.h>
  
// ESPNow structures
typedef struct struct_location {
  int8_t flag;
  int8_t time_hour;
  int8_t time_minute;
  int8_t date_day;
  int8_t date_month;
  uint16_t date_year;
  int8_t satellites;
  int temperature_now;
  int8_t weather_code_now;
  float wind_now;
  float rain_now;
  char location_name[30];
}struct_location;

struct_location locationData;

// Global components
lv_obj_t *loading_scr;
lv_obj_t *home_scr;
lv_obj_t *weather_scr;
lv_obj_t *loading_label;
lv_obj_t *time_label;
lv_obj_t *date_label;
lv_obj_t *location_label;
lv_obj_t *temperature_label;
lv_obj_t *temperature_unit_label;
lv_obj_t *rainfall_label;
lv_obj_t *windspeed_label;
lv_obj_t *weather_icon;


// Global styles
static lv_style_t style_text_small;
static lv_style_t style_text_medium;
static lv_style_t style_text_large;
static lv_style_t style_text_larger;
static lv_style_t style_text_unit;
static lv_style_t icon_style;
static lv_style_t weather_icon_style_small;
static lv_style_t weather_icon_style_large;

// Color palette
lv_color_t palette_amber = LV_COLOR_MAKE(250, 140, 0);
lv_color_t palette_black = LV_COLOR_MAKE(0, 0, 0);
lv_color_t palette_red = LV_COLOR_MAKE(255, 0, 0);
lv_color_t palette_white = LV_COLOR_MAKE(255, 255, 255);
lv_color_t palette_grey = LV_COLOR_MAKE(45, 45, 45);

// Attributes
bool first_load =           false;
volatile bool data_ready =  false;
hw_timer_t* timer =         nullptr;

uint32_t last_update_time = 0;
const uint32_t timeout_ms = 120000; // how long until considered timed out

const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
                        "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

// Screen dimensions
const int diameter =        480;
const int radius =          diameter / 2;
const int line_width =      4;


void IRAM_ATTR onTimer() {
    lv_tick_inc(1); // Increment LVGL's tick by 1ms
}

void tick_init(void) {
  const uint32_t lv_tick_frequency = 1000; // 1 kHz = 1ms period

  timer = timerBegin(lv_tick_frequency); // Configure the timer with 1kHz frequency
  if (!timer) {
      Serial.println("Failed to configure timer!");
      while (1); // Halt execution on failure
  }

  timerAttachInterrupt(timer, &onTimer); // Attach the ISR to the timer
  Serial.println("Timer initialized for LVGL tick!");

  last_update_time = lv_tick_get();
}

// ESPNow received - minimal code here
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&locationData, incomingData, sizeof(locationData));

  last_update_time = lv_tick_get();
  data_ready = true;
}

void esp_now_timeout() {
  uint32_t current_time = lv_tick_get();
  if (current_time - last_update_time > timeout_ms) {
      Serial.print("GPS Offline (Timeout)");

      last_update_time = current_time;
  }
}

// Styles
void make_styles(void) {
  lv_style_init(&style_text_small);
  lv_style_set_text_font(&style_text_small, &roboto_regular_24);
  lv_style_set_text_color(&style_text_small, palette_white);

  lv_style_init(&style_text_medium);
  lv_style_set_text_font(&style_text_medium, &roboto_semibold_40);
  lv_style_set_text_color(&style_text_medium, palette_white);

  lv_style_init(&style_text_large);
  lv_style_set_text_font(&style_text_large, &roboto_semibold_64);
  lv_style_set_text_color(&style_text_large, palette_white);

  lv_style_init(&style_text_larger);
  lv_style_set_text_font(&style_text_larger, &roboto_semibold_80);
  lv_style_set_text_color(&style_text_larger, palette_white);

  lv_style_init(&style_text_unit);
  lv_style_set_text_font(&style_text_unit, &roboto_semibold_28);
  lv_style_set_text_color(&style_text_unit, palette_amber);

  lv_style_init(&icon_style);
  lv_style_set_text_font(&icon_style, &lv_font_montserrat_40);

  lv_style_init(&weather_icon_style_small);
  lv_style_set_text_font(&weather_icon_style_small, &weather_font_48);
  lv_style_set_text_color(&weather_icon_style_small, palette_white);

  lv_style_init(&weather_icon_style_large);
  lv_style_set_text_font(&weather_icon_style_large, &weather_font_120);
  lv_style_set_text_color(&weather_icon_style_large, palette_white);
}


// Utility functions
void set_weather_icon(int weather_code, int left_offset) {
  char icon_code[2];
  int top_offset = 0;

  if (weather_code == 0) {
   strcpy(icon_code, "1");
    top_offset = 20;
  }
  if (weather_code == 1) {
    strcpy(icon_code, "2");
    top_offset = 24;
  }
  if (weather_code == 2) {
    strcpy(icon_code, "A");
    top_offset = 20;
  }
  if (weather_code == 3) {
    strcpy(icon_code, "3");
    top_offset = 13;
  }
  if ((weather_code == 45) ||
      (weather_code == 48)) {
    strcpy(icon_code, "Z");
    top_offset = -6;
  }
  if ((weather_code == 51) ||
      (weather_code == 56)) {
    strcpy(icon_code, "M");
    top_offset = -1;
  }
  if ((weather_code == 53) ||
      (weather_code == 61) ||
      (weather_code == 66) ||
      (weather_code == 80)) {
    strcpy(icon_code, "W");
    top_offset = -6;
  }
  if ((weather_code == 65) ||
      (weather_code == 67) ||
      (weather_code == 82)) {
    strcpy(icon_code, "O");
    top_offset = -6;
  }
  if ((weather_code == 55) ||
      (weather_code == 57) ||
      (weather_code == 63) ||
      (weather_code == 81)) {
    strcpy(icon_code, "U");
    top_offset = -2;
  }
  if ((weather_code == 71) ||
      (weather_code == 73) ||
      (weather_code == 75) ||
      (weather_code == 77) ||
      (weather_code == 85) ||
      (weather_code == 86)) {
   strcpy(icon_code, "I");
    top_offset = 0;
  }
  if (weather_code == 95) {
    strcpy(icon_code, "Y");
    top_offset = -1;
  }
   if ((weather_code == 96) ||
       (weather_code == 99)) {
    strcpy(icon_code, "Q");
    top_offset = -6;
  }

  lv_label_set_text(weather_icon, icon_code);
  lv_obj_align(weather_icon, LV_ALIGN_RIGHT_MID, left_offset, -150 + top_offset);
}

String get_date_suffix(int day) {
  if (day < 1 || day > 31) {
    return "";
  }

  if (day >= 11 && day <= 13) {
    return "th";
  }

  switch (day % 10) {
    case 1:
      return "st";
    case 2:
      return "nd";
    case 3:
      return "rd";
    default:
      return "th";
  }
}

void update_location(void) {
    char new_temp[4];
    sprintf(new_temp, "%d", locationData.temperature_now);
    lv_label_set_text(temperature_label, new_temp);
    
    char new_windspeed[10];
    sprintf(new_windspeed, "%.1fmph", locationData.wind_now);
    lv_label_set_text(windspeed_label, new_windspeed);

    char new_rain[10];
    sprintf(new_rain, "%.1fmm", locationData.rain_now);
    lv_label_set_text(rainfall_label, new_rain);
  
    int icon_left_offset = -240;

    lv_label_set_text(location_label, locationData.location_name);

    if ((locationData.temperature_now > 9) || (locationData.temperature_now < -9)) {
      icon_left_offset = -250;
      lv_obj_align(temperature_label, LV_ALIGN_LEFT_MID, 240, -144);
      lv_obj_align(temperature_unit_label, LV_ALIGN_LEFT_MID, 330, -158);
    } else {
      lv_obj_align(temperature_label, LV_ALIGN_LEFT_MID, 270, -144);
      lv_obj_align(temperature_unit_label, LV_ALIGN_LEFT_MID, 310, -158);
    }

    set_weather_icon(locationData.weather_code_now, icon_left_offset);
}

void update_load_message(char *new_message) {
  lv_label_set_text(loading_label, new_message);
}

// Update UI elements
void update_time(void) {
  
  // format - 18:22
  char new_time[6];
  snprintf(new_time, sizeof(new_time), "%02d:%02d", locationData.time_hour, locationData.time_minute);
  lv_label_set_text(time_label, new_time);

  // format - 15th Dec, 2024
  char new_date[32];
  snprintf(new_date, sizeof(new_date), "%d%s %s, %02d", locationData.date_day, get_date_suffix(locationData.date_day), months[locationData.date_month -1], locationData.date_year);
  lv_label_set_text(date_label, new_date);
}

// Label Generator
void make_label(lv_obj_t **label, lv_obj_t **scr, const char* text, lv_style_t* style, lv_align_t align, int x_offset, int y_offset) {  
    *label = lv_label_create(*scr);
    lv_label_set_text(*label, text);
    lv_obj_add_style(*label, style, 0);
    lv_obj_align(*label, align, x_offset, y_offset);
}

// Home Page UI Elements
void make_time_date(void) {
    lv_obj_t *time_date_bg = lv_obj_create(home_scr);
    lv_obj_set_size(time_date_bg, 480, 180);
    lv_obj_set_style_bg_color(time_date_bg, palette_grey, 0);
    lv_obj_set_style_border_width(time_date_bg, 0, 0);
    lv_obj_align(time_date_bg, LV_ALIGN_BOTTOM_MID, 0, 0);

    make_label(&time_label, &home_scr, "19:22", &style_text_large, LV_ALIGN_CENTER, 0, 115);
    make_label(&date_label, &home_scr, "Dec 14th, 2024", &style_text_small, LV_ALIGN_CENTER, 0, 165);
}

void make_temperature(void) {
    make_label(&weather_icon, &home_scr, "A", &weather_icon_style_large, LV_ALIGN_RIGHT_MID, NULL, NULL);
    make_label(&temperature_label, &home_scr, "8", &style_text_larger, LV_ALIGN_LEFT_MID, NULL, NULL);
    make_label(&temperature_unit_label, &home_scr, "°C", &style_text_unit, LV_ALIGN_LEFT_MID, NULL, NULL);

    lv_obj_t *temp_line = lv_obj_create(home_scr);
    lv_obj_set_size(temp_line, 300, 4);
    lv_obj_set_style_bg_color(temp_line, palette_white, 0);
    lv_obj_set_style_border_width(temp_line, 0, 0);
    lv_obj_align(temp_line, LV_ALIGN_CENTER, 0, -40);
}

void make_location(void) {
    make_label(&location_label, &home_scr, "BRISTOL", &style_text_medium, LV_ALIGN_CENTER, 0, 12);
}


void make_weather_details(void) {
    lv_obj_t *windspeed_icon;
    lv_obj_t *rainfall_icon; 

    make_label(&windspeed_icon, &home_scr, "E", &weather_icon_style_small, LV_ALIGN_LEFT_MID, 100, -78);
    make_label(&windspeed_label, &home_scr, "3.2mph", &style_text_small, LV_ALIGN_LEFT_MID, 148, -77);
    
    make_label(&rainfall_icon, &home_scr, "M", &weather_icon_style_small, LV_ALIGN_LEFT_MID, 270, -80);
    make_label(&rainfall_label, &home_scr, "0.0mm", &style_text_small, LV_ALIGN_LEFT_MID, 309, -77);
}

// Loading Page UI Elements
void make_loader_screen(void) {
  make_label(&loading_label, &loading_scr, "loading", &style_text_unit, LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_text_color(loading_label, palette_white, LV_PART_MAIN);
}

void make_home_screen(void) {
  make_time_date();
  make_temperature();
  make_location();
  make_weather_details();
}

void scr_init() {
    ESP_Panel *panel = new ESP_Panel();
    panel->init();

    #if LVGL_PORT_AVOID_TEAR
        // When avoid tearing function is enabled, configure the RGB bus according to the LVGL configuration
        ESP_PanelBus_RGB *rgb_bus = static_cast<ESP_PanelBus_RGB *>(panel->getLcd()->getBus());
        rgb_bus->configRgbFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
        rgb_bus->configRgbBounceBufferSize(LVGL_PORT_RGB_BOUNCE_BUFFER_SIZE);
    #endif
    panel->begin();

    lvgl_port_init(panel->getLcd(), panel->getTouch());
}

void wifi_init() {
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    update_load_message("espnow failed");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(esp_now_recv_cb_t(OnDataRecv));
}

void setup() {
  Serial.begin(115200);

  scr_init();
  tick_init();
  wifi_init();

  home_scr = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(home_scr, palette_black, 0);

  loading_scr = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(loading_scr, palette_black, 0);

  // Start screen
  lv_scr_load(loading_scr);

  // Common styles
  make_styles();

  // Loader Page UI
  make_loader_screen();

  // Home Page UI
  make_home_screen();

  // Weather Page UI
}

void loop(){
    lv_timer_handler();
    esp_now_timeout();

    if (data_ready) {
      update_time();
      update_location();
      // do stuff here when ESPNow recieves updates
      data_ready = false;
       if (first_load == false) {
        Serial.print("first data received");
        lv_scr_load_anim(home_scr, LV_SCR_LOAD_ANIM_OUT_TOP, 500, 1000, true); // anim out and delete
        first_load = true;
      }
    }
}