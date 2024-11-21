#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
//#include <Adafruit_SSD1306.h>
//#define OLED_RESET -1
//Adafruit_SSD1306 display(OLED_RESET);

int menu_point[2] = {0, 0};

// Menu data
String tools[] = {"Tools", "Attacks", "Settings"};
String attacks[] = {"Wifi Repeater", "Web Server"};
String settings[] = {"Deauther", "Evil Twin", "Handshake Attack"};

String* menu_Items[] = {tools, attacks, settings};

// Primary pin initialize
primary_pin(){
  // Set up buttons
  pinMode(btn_right, INPUT);
  pinMode(btn_left, INPUT);
  pinMode(btn_up, INPUT);
  pinMode(btn_down, INPUT);
  pinMode(btn_ok, INPUT);
  pinMode(btn_back, INPUT);
  }

//Webpage data
const String a_header_top = "<!DOCTYPE html><head></head><body style=\"text-align: center; margin: 0; padding: 0; background-color: #a3aabe;\"><div style=\"background-color: #000000; color: white; padding: 10px;\"><h1 style=\"margin: 0;\">";

const String b_header_bottom = "</h1></div>";

const String c_button_top = "<div style=\"padding: 20px;\"><button style=\"width: 450px; padding: 10px; margin: 10px; background-color:lightgreen; border: none; border-radius: 10px; font-size: 25px;\" onclick=\"alert('Tools Selected!')\"><b>";

const String d_button_bottom = "</button></div>";

const String e_footer_bottom = "<div style=\"background-color: #343a40; color: white; padding: 5px; font-size: 14px;\">&copy; 2024 : All Coppywrrite Recived  The Devopler.</div></body></html>"

void handle_web() {
  String html_code = a_header_top;
  if(menu_point[0]==0){
    html_code += "Main Menu";
  }
  else {
    html_code += menu_Items[0][menu_point[0]];// i was here
  }
  server.send(200, "text/html", html_code);
}

void displayMenu() {
  display.clearDisplay();
  
  if (currentMenu == 0) {
    display.setCursor(0,0);
    display.print(menuItems[0]);
    display.setCursor(0, 10);
    display.print(menuItems[1]);
  }
  else if (currentMenu == 1) {
    display.setCursor(0,0);
    display.print(toolsMenu[0]);
    display.setCursor(0, 10);
    display.print(toolsMenu[1]);
    display.setCursor(0, 20);
    display.print(toolsMenu[2]);
  }
  
  display.display();
}

void navigateUp() {
  if (selectedItem > 0) selectedItem--;
}

void navigateDown() {
  if (selectedItem < (sizeof(menuItems) / sizeof(menuItems[0])) - 1) selectedItem++;
}

void selectItem() {
  if (currentMenu == 0 && selectedItem == 0) {
    currentMenu = 1;
    selectedItem = 0;
  } else if (currentMenu == 0 && selectedItem == 1) {
    // Handle Attacks menu selection
  }
}

void goBack() {
  if (currentMenu == 1) {
    currentMenu = 0;
  }
}

ESP8266WebServer server(80);

// I/0 pin for buttons
//const int btn_right = 12;
//const int btn_left = 13;
//const int btn_up = 14;
//const int btn_down = 4;
//const int btn_ok = 5;
//const int btn_back = 0;


void setup() {
  Serial.begin(115200);

  //primary_pin();
  
  // OLED setup
  // if (!display.begin(SSD1306_I2C_ADDRESS, OLED_RESET)) {
  //  Serial.println(F("SSD1306 allocation failed"));
  //  for (;;);
  // }
  // display.display();
  // delay(2000);
  // display.clearDisplay();

  // Set up Wi-Fi Access Point
  WiFi.softAP("Janobi Khatun", "W.j.56564545");
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Set up web server
  server.on("/", HTTP_GET, handleRoot);
  server.on("/tools", HTTP_GET, handleTools);
  server.on("/attacks", HTTP_GET, handleAttacks);
  server.begin();
}

void loop() {
  server.handleClient();

  // Handle OLED button navigation
  if (digitalRead(buttonUp) == HIGH) {
    navigateUp();
  }
  if (digitalRead(buttonDown) == HIGH) {
    navigateDown();
  }
  if (digitalRead(buttonOk) == HIGH) {
    selectItem();
  }
  if (digitalRead(buttonBack) == HIGH) {
    goBack();
  }

  displayMenu();
}
