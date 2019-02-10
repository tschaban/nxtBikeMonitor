#include "AFE-Sites-Generator.h"

AFESitesGenerator::AFESitesGenerator() {}

const String AFESitesGenerator::generateHeader(uint8_t redirect) {

  String page = "<!doctype html>"
                "<html lang=\"en\">"
                "<head>"
                "<meta charset=\"utf-8\">";

  if (redirect > 0) {
    page += "<meta http-equiv=\"refresh\" content=\"";
    page += String(redirect);
    page += "; url=/\">";
  }

  page += "<title>NxtBike Monitor ";
  page +=
      "]</title>"
      "<style>#l,#r{padding:20px}.ltag,.ltit,body{margin:0}.b,.itm "
      "a,a{text-decoration:none}body{background:#ddd;padding:15px}#c{display:"
      "table;width:100%}#l,#r{display:table-cell}#l{width:300px;background:#"
      "282828;color:#eee}#r{background:#eee}a,button,h1,h3,h4,input,label,li,p,"
      "span{font-family:sans-serif}.ltag{font-weight:300;color:#b0cadb;margin-"
      "bottom:20px}.lst{list-style:none;margin:0;padding:0}.itm "
      "a{display:block;white-space:nowrap;padding:.2em "
      "1em;color:#777;font-size:95%}.cf "
      "label,.hint,input,select{display:inline-block;vertical-align:middle}."
      "itm a:focus,.itm "
      "a:hover{background-color:#eee;text-decoration:none;padding:.2em "
      "1.5em;color:#000}.ci{margin-bottom:2em}.ci "
      "h1{color:#aaa;border-bottom:1px solid "
      "#ddd;font-size:110%;font-weight:500;letter-spacing:.1em}.ci "
      ".cd{color:#444;line-height:1.8em;font-size:80%;font-style:italic}.cm{"
      "color:#999;font-size:90%;margin:0 0 20px}.la{margin:0 .1em;padding:.3em "
      "1em;color:#fff;background:#999;font-size:80%}.cc label,.cf "
      "label{font-size:.875em}.lr{background:#ca3c3c}.bs,.lg{background:#"
      "2fb548}fieldset{margin:0;padding:.35em 0 "
      ".75em;border:0}.cf{margin-bottom:.5em}.cc{margin:1em 0 .5em 9.4em}.cf "
      "label{text-align:right;width:10em;margin:0 1em 0 "
      "0}input,select{padding:.5em .6em;border:1px solid "
      "#ccc;box-sizing:border-box}.hint{padding-left:.3em;color:#aaa;font-size:"
      "80%}.b{font-size:100%;padding:.5em 1em;border:1px solid "
      "#999;border:transparent;color:#fff}.be{background:#ca3c3c}.bw{"
      "background:#df7514}.bc{background:#42b8dd}.b:focus,.b:hover{filter:"
      "alpha(opacity=90);background-image:-webkit-linear-gradient(transparent,"
      "rgba(0,0,0,.05) "
      "40%,rgba(0,0,0,.1));background-image:linear-gradient(transparent,rgba(0,"
      "0,0,.05) 40%,rgba(0,0,0,.1))}</style>"
      "</head>"
      "<body>"
      "<div id=\"c\">"
      "<div id=\"l\">"
      "<h3 class=\"ltit\">AFE FIRMWARE</h3>"
      "<h4 class=\"ltag\">";

  page += "Monitor";

  page += "</h4><h4>MENU</h4>"
          "<ul class=\"lst\">";

  uint8_t deviceMode = Data.getDeviceMode();

  if (deviceMode != MODE_NORMAL) {

    DEVICE Device = Data.getDeviceConfiguration();

    page += "<li class=\"itm\"><a href=\"\\?option=device\">";
    page += "Urządzenie";
    page += "</a></li> "
            "<li class=\"itm\"><a href=\"\\?option=network\">";
    page += "Sieć WiFi";
    page += "</a></li>";

    uint8_t itemPresent = 0;

    for (uint8_t i = 0; i < sizeof(Device.isLED); i++) {
      if (Device.isLED[i]) {
        itemPresent++;
      } else {
        break;
      }
    }

    if (itemPresent > 0) {
      page += "<li class=\"itm\"><a href=\"\\?option=led\">LEDy";
      page += "</a></li>";
    }

    /* Relay */
    itemPresent = 0;
    for (uint8_t i = 0; i < sizeof(Device.isRelay); i++) {
      if (Device.isRelay[i]) {
        itemPresent++;
      } else {
        break;
      }
    }

    if (itemPresent > 0) {
      page += "<li  class=\"itm\"><a><i>";
      page += "Konfiguracja przekaźników";
      page += "</i></a></li>";

      for (uint8_t i = 0; i < itemPresent; i++) {
        page += "<li class=\"itm\"><a href=\"\\?option=relay";
        page += i;
        page += "\">&#8227; ";
        page += "Przekaźnik";
        page += ": ";
        page += i + 1;
        page += "</a></li>";
      }
    }

    /* Switch */
    itemPresent = 0;
    for (uint8_t i = 0; i < sizeof(Device.isSwitch); i++) {
      if (Device.isSwitch[i]) {
        itemPresent++;
      } else {
        break;
      }
    }

    if (itemPresent > 0) {
      page += "<li  class=\"itm\"><a><i>";
      page += "Przyciski / wyłączniki";
      page += "</i></a></li>";

      for (uint8_t i = 0; i < itemPresent; i++) {
        page += "<li class=\"itm\"><a href=\"\\?option=switch";
        page += i;
        page += "\">&#8227; ";
        page += "Przycisk: ";
        page += i + 1;
        page += "</a></li>";
      }
    }

    /* Sensor DS18B20 */

    if (Device.isDS18B20) {
      page += "<li class=\"itm\"><a href=\"\\?option=ds18b20\">";
      page += "Czujnik temperatury";
      page += "</a></li>";
    }

    /* Language, Upgrade, Exit */
    page += "<br><br><li class=\"itm\"><a "
            "href=\"\\?option=language\">[PL] Język / "
            "[EN] Language</a></li><br><br><li class=\"itm\"><a "
            "href=\"\\update\">";
    page += "Aktulizacja firmware";
    page += "</a></li><li class=\"itm\"><a href=\"\\?option=reset\">";
    page += "Przywracanie ustawień początkowych";
    page += "</a></li><br><br><li class=\"itm\"><a href=\"\\?option=exit\">";
    page += "Zakończ konfigurację";
  } else {
    /* Settings, Access Point */
    page += "<li class=\"itm\"><a href=\"\\?option=help&cmd=1\">";
    page += "Ustawienia";
    page += "</a></li><li class=\"itm\"><a href=\"\\?option=help&cmd=2\">";
    page += "Ustawienia (tryb: Access Point)";
  }
  /* Information section */
  page += "</a></li></ul><br><br><h4>INFORMACJE";
  page += "</h4><ul class=\"lst\"><li class=\"itm\"><a "
          "href=\"https://www.smartnydom.pl/afe-firmware-";
  page += "pl";
  page += "/\" target=\"_blank\">Dokumentacja";
  page += "</a></li></ul></div><div id=\"r\">";

  return page;
}

String AFESitesGenerator::addDeviceConfiguration() {
  DEVICE configuration = Data.getDeviceConfiguration();
  uint8_t itemsNumber = 0;

  String body = "<fieldset>";

  /* LED */
  for (uint8_t i = 0; i < sizeof(configuration.isLED); i++) {
    if (configuration.isLED[i]) {
      itemsNumber++;
    } else {
      break;
    }
  }

  body += generateHardwareItemsList(sizeof(configuration.isLED), itemsNumber,
                                    "hl", "Ilość Led'ów");

  itemsNumber = 0;
  for (uint8_t i = 0; i < sizeof(configuration.isSwitch); i++) {
    if (configuration.isSwitch[i]) {
      itemsNumber++;
    } else {
      break;
    }
  }

  /* Relay */
  itemsNumber = 0;
  for (uint8_t i = 0; i < sizeof(configuration.isRelay); i++) {
    if (configuration.isRelay[i]) {
      itemsNumber++;
    } else {
      break;
    }
  }

  body += generateHardwareItemsList(sizeof(configuration.isRelay), itemsNumber,
                                    "hr", "Ilość przekaźników");

  /* Switch */
  itemsNumber = 0;
  for (uint8_t i = 0; i < sizeof(configuration.isSwitch); i++) {
    if (configuration.isSwitch[i]) {
      itemsNumber++;
    } else {
      break;
    }
  }

  body += generateHardwareItemsList(sizeof(configuration.isSwitch), itemsNumber,
                                    "hs", "Ilość przycisków");

  body += "<div class=\"cc\"><label><input name =\"ds\" type=\"checkbox\" "
          "value=\"1\"";
  body += configuration.isDS18B20 ? " checked=\"checked\">" : ">";
  body += " DS18B20";
  body += "</label></div>";

  body += "</fieldset>";

  return addConfigurationBlock("Konfiguracja urządzenia",
                               "Wybierz podłączone elementy do urządzenia",
                               body);
}

String AFESitesGenerator::addNetworkConfiguration() {

  NETWORK configuration;
  configuration = Data.getNetworkConfiguration();

  String body = "<fieldset>";
  body += "<div class=\"cf\"><label>";
  body += "Nazwa sieci WiFi";
  body += "</label><input name=\"s\" type=\"text\" maxlength=\"32\" value=\"";
  body += configuration.ssid;
  body += "\"><span class=\"hint\">Max 32 ";
  body += "znaków";
  body += "</span></div><div class=\"cf\"><label>";
  body += "Hasło";
  body += "</label><input type=\"password\" name=\"p\" maxlength=\"32\" "
          "value=\"";
  body += configuration.password;
  body += "\"><span class=\"hint\">Max 32 ";
  body += "znaków";
  body += "</span></div><div class=\"cf\"><label>MAC</label><input "
          "type=\"text\" readonly=\"readonly\" value=\"";
  body += WiFi.macAddress();
  body += "\"></div></fieldset>";

  String page =
      addConfigurationBlock("WiFi",
                            "Urządzenie bez dostępu do sieci będzie "
                            "działać tylko w trybie sterowania ręcznego",
                            body);

  body = "<fieldset><div class=\"cf\"><label>";
  body += "Ilość prób łączenia się";
  body += "</label><input name=\"na\" type=\"number\" min=\"1\" max=\"255\" "
          "step=\"1\" "
          "value=\"";
  body += configuration.noConnectionAttempts;
  body += "\"><span class=\"hint\">1-255</span></div><div class=\"cf\"><label>";
  body += "Czas między próbami łączenia się";
  body += "</label><input type=\"number\" name=\"wc\" "
          "min=\"1\" max=\"255\" step=\"1\" value=\"";
  body += configuration.waitTimeConnections;
  body += "\"><span class=\"hint\">1-255 (";
  body += "sekundy";
  body += ")</span></div><div class=\"cf\"><label>";
  body += "Czas po jakim powtórzyć próby łączenia się";
  body += "</label><input type=\"number\" name=\"ws\" min=\"1\" max=\"255\" "
          "step=\"1\" "
          "value=\"";
  body += configuration.waitTimeSeries;
  body += "\"><span class=\"hint\">1-255 (";
  body += "sekundy";
  body += ")</span></div></fieldset>";

  page += addConfigurationBlock("Zaawansowane", "", body);

  return page;
}

String AFESitesGenerator::addLEDConfiguration(uint8_t id) {
  LED configuration;
  configuration = Data.getLEDConfiguration(id);

  String body = "<fieldset>";
  char filed[13];
  sprintf(filed, "g%d", id);
  body += "<div class=\"cf\">";
  body += generateConfigParameter_GPIO(filed, configuration.gpio);
  body += "<label style=\"width: 300px;\"><input name=\"o";
  body += id;
  body += "\" type=\"checkbox\" value=\"1\"";
  body += configuration.changeToOppositeValue ? " checked=\"checked\"" : "";
  body += ">";
  body += "Zmień świecenie diody LED na odwrotne";
  body += "</label></div></fieldset>";

  return addConfigurationBlock("LED #" + String(id + 1), "", body);
}

String AFESitesGenerator::addSystemLEDConfiguration() {
  uint8_t configuration = Data.getSystemLedID();
  DEVICE Device = Data.getDeviceConfiguration();

  String body =
      "<fieldset><div class=\"cf\"><label>LED</label><select name=\"i\">";

  body += "<option value=\"0\"";
  body += configuration == 0 ? " selected=\"selected\"" : "";
  body += ">Brak";
  body += "</option>";

  for (uint8_t i = 1; i <= sizeof(Device.isLED); i++) {
    if (Device.isLED[i - 1]) {
      body += "<option value=\"";
      body += i;
      body += "\"";
      body += configuration == i ? " selected=\"selected\"" : "";
      body += ">";
      body += i;
      body += "</option>";
    } else {
      break;
    }
  }

  body += "</select></div></fieldset>";

  return addConfigurationBlock(
      "LED systemowy",
      "Wybierz diodę LED, która będzie sygnalizowała stan "
      "urządzenia oraz występujące zdarzenia",
      body);
}

String AFESitesGenerator::addRelayConfiguration(uint8_t id) {
  RELAY configuration = Data.getRelayConfiguration(id);
  DEVICE Device = Data.getDeviceConfiguration();
  String body = "<fieldset>";
  char filed[13];
  sprintf(filed, "g%d", id);

  body += generateConfigParameter_GPIO(filed, configuration.gpio);

  body += "<br><p class=\"cm\">";
  body += "Wybierz LED sygnalizujący stan przekaźnika";
  body += "</p>";

  body += "<div class=\"cf\">";
  body += "<label>LED</label>";
  body += "<select  name=\"l" + String(id) + "\">";
  body += "<option value=\"0\"";
  body += configuration.ledID == 0 ? " selected=\"selected\"" : "";
  body += ">Brak";
  body += "</option>";

  for (uint8_t i = 1; i <= sizeof(Device.isLED); i++) {
    if (Device.isLED[i - 1]) {
      body += "<option value=\"";
      body += i;
      body += "\"";
      body += configuration.ledID == i ? " selected=\"selected\"" : "";
      body += ">";
      body += i;
      body += "</option>";
    } else {
      break;
    }
  }

  body += "</select>";
  body += "</div>";

  body += "</fieldset>";

  char title[23];
  sprintf(title, "Przekaźnik #%d", id + 1);

  String page = addConfigurationBlock(title, "", body);

  return page;
}

String AFESitesGenerator::addSwitchConfiguration(uint8_t id) {

  SWITCH configuration;
  configuration = Data.getSwitchConfiguration(id);

  String body = "<fieldset>";
  char filed[13];
  sprintf(filed, "g%d", id);
  body += "<div class=\"cf\">";
  body += generateConfigParameter_GPIO(filed, configuration.gpio);
  body += "</div>";
  body += "<div class=\"cf\">";
  body += "<label>";
  body += "Funkcja";
  body += "</label>";
  body += "<select name=\"f" + String(id) + "\">";
  body += "<option value=\"0\"";
  body += (configuration.functionality == 0 ? " selected=\"selected\"" : "");
  body += ">";
  body += "Przycisk systemowy";
  body += "</option>";
  body += "<option value=\"1\"";
  body += (configuration.functionality == 1 ? " selected=\"selected\"" : "");
  body += ">";

  body += "</option>";

  body += "</select>";
  body += "</div>";

  body += "<br><p class=\"cm\">";
  body += "Czułość należy ustawić metodą prób, aż uzyska się "
          "pożądane działanie przycisku podczas jego wciskania";

  body += "</p><div class=\"cf\">";
  body += "<label>";
  body += "Czułość";
  body += "</label>";
  body += "<input name=\"s" + String(id) +
          "\" type=\"number\" max=\"999\" min=\"0\" step=\"1\" "
          "value=\"";
  body += configuration.sensitiveness;
  body += "\">";
  body += "<span class=\"hint\">0 - 999 (milise";
  body += "kund";
  body += ")</span>";
  body += "</div>";
  body += "</fieldset>";

  char title[23];
  sprintf(title, "Przycisk / Włącznik #%d", id + 1);

  return addConfigurationBlock(title, "", body);
}

String AFESitesGenerator::addDS18B20Configuration() {

  DS18B20 configuration = Data.getSensorConfiguration();
  String body = "<fieldset>";
  body += generateConfigParameter_GPIO("g", configuration.gpio);

  body += "<div class=\"cf\">";
  body += "<label>";
  body += "Odczyty co";
  body += "</label>";
  body +=
      "<input name=\"i\" min=\"5\" max=\"86400\" step=\"1\" type=\"number\" "
      "value=\"";
  body += configuration.interval;
  body += "\">";
  body += "<span class=\"hint\">";
  body += "sekund. Zakres: 5 do 86400sek";
  body += " (24h)</span>";
  body += "</div>";

  body += "</fieldset>";

  String page = addConfigurationBlock("Czujnik temperatury DS18B20", "", body);

  return page;
}

String AFESitesGenerator::addDeviceI2CAddressSelection(uint8_t address) {
  AFEI2CScanner I2CScanner;
  String body = "<div class=\"cf\"><label>I2C Ad";
  body += "res";
  body += ": </label><select name=\"a\">";
  body += "<option value=\"0\"";
  body += address == 0 ? " selected=\"selected\"" : "";
  body += ">";
  body += "Brak";
  body += "</option>";

  for (byte addressToScan = 1; addressToScan < 127; addressToScan++) {
    if (I2CScanner.scan(addressToScan)) {
      body += "<option value=\"";
      body += addressToScan;
      body += "\"";
      body += addressToScan == address ? " selected=\"selected\"" : "";
      body += ">[0x";
      body += String(addressToScan, HEX);
      body += "] : ";
      body += I2CScanner.getName(addressToScan);
      body += "</option>";
    }
  }
  body += "</select></div>";
  return body;
}

String AFESitesGenerator::addUpgradeSection() {
  String body = "<fieldset><div class=\"cf\"><label>";
  body += "Wybierz";
  body += " firmware</label><input class=\"bs\" name=\"update\" type=\"file\" "
          "accept=\".bin\"></div><p class=\"cm\">";
  body += "Po zakończeniu aktualizacji urządzenie zostanie "
          "automatycznie zresetowane<br><br><strong>Uwaga:</strong> po "
          "aktualizacji nie odłączaj urządzenia przez conajmniej 1min.<br>"
          "Urządzenie formatuje pamięć i wgrywa domyślne ustawienia. "
          "<br><strong>Ten proces nie może zostać przerwany</strong>.";
  body += "</p><button type=\"submit\" class=\"b be\">";
  body += "Aktualizuj";
  body += "</button></fieldset>";
  return addConfigurationBlock(
      "Aktualizacja firmware",
      "<strong>UWAGA</strong>: nie odłączaj "
      "urządzenia od źródła zasilania podczas aktualizacji",
      body);
}

String AFESitesGenerator::addPostUpgradeSection(boolean status) {

  String body = "<fieldset><ul>";
  if (status) {
    body += "<li style=\"color:red\">";
    body += "Aktualizacja nie powiodła się";
  } else {
    body += "<li class=\"cm\">";
    body += "Aktualizacja zakończona pomyślnie";
  }
  body += "</li><li class=\"cm\">";
  body += "Po 15 "
          "sekundach przełącznik zostanie przeładowany. Proszę czekać";
  body += "....</li>";
  body += "</fieldset>";
  return addConfigurationBlock("Aktualizacja firmware", "", body);
}

String AFESitesGenerator::addResetSection(uint8_t command) {
  String body = "<fieldset>";
  String subtitle;
  if (command == 0) {
    body += "<a href=\"\\?option=reset&cmd=1\" class=\"b be\">";
    body += "Przywróć ustawienia początkowe";
    body += "</a><strong>";
    subtitle += "Uwaga";
    subtitle += "</strong>: ";
    subtitle += "przywrócenie ustawień "
                "początkowych usuwa wszystkie ustawienia "
                "urządzenia, włącznie z konfiguracją sieci WiFi";
  } else {
    subtitle += "";
    body += "<p class=\"cm\">";
    body += "Trwa przywracanie ustawień początkowych";
    body += "</p><p class=\"cm\">";

    body += "Po 20 sekundach połącz się z siecią WiFi o "
            "nazwie: <strong>AFE-Device</strong>, a następnie "
            "połącz się z "
            "panelem konfiguracyjnym pod adresem";
    body += ": </p><a href=\"http://192.168.5.1\">http://192.168.5.1</a>";
  }
  body += "</fieldset>";
  return addConfigurationBlock("Przywracanie ustawień początkowych", subtitle,
                               body);
}

String AFESitesGenerator::addExitSection() {
  String body = "<fieldset><div class=\"cf\"><ul><li class=\"cm\">";
  body += "Trwa restart urządzenia";
  body += ".....</li><li class=\"cm\">";
  body += "Strona zostanie przeładowana automatycznie... czekaj";
  body += "</li></ul></div></fieldset>";
  return addConfigurationBlock("Restart urządzenia", "", body);
}

String AFESitesGenerator::addHelpSection() {
  DEVICE configuration;
  configuration = Data.getDeviceConfiguration();

  uint8_t deviceMode = Data.getDeviceMode();

  String page = "<fieldset><div class=\"cf\"><label>";
  page += "Stan: uruchomione ";
  page += "</label><span></div></fieldset>";

  if (deviceMode != MODE_ACCESS_POINT) {

    String body = "<a "
                  "href=\"https://www.smartnydom.pl/afe-firmware-";
    body += "pl";
    body += "/log\" target=\"_blank\"><img "
            "src=\"https://img.shields.io/badge/"
            "version%20-%20";
    body += FIRMWARE_VERSION;
    body += "%20-blue.svg\" /></a> ";

    body += "<a href=\"https://github.com/tschaban/AFE-Firmware/"
            "issues?q=is:issue+is:open+label:Defect\" target=\"_blank\"><img "
            "src=\"https://img.shields.io/github/issues/tschaban/AFE-Firmware/"
            "Defect.svg\" /></a> ";

    body += "<a href=\"https://www.smartnydom.pl/forum/afe-firmware/\" "
            "target=\"_blank\"><img "
            "src=\"https://img.shields.io/badge/help-forum-red.svg\" /></a> ";

    body += "<a "
            "href=\"https://github.com/tschaban/AFE-Firmware/blob/master/"
            "LICENSE\" target=\"_blank\"><img "
            "src=\"https://img.shields.io/github/license/tschaban/"
            "AFE-Firmware.svg\" /></a>";

    page += addConfigurationBlock("Firmware", "", body);

    body = "<p class=\"cm\">";
    body += "Oprogramowanie dostępne jest za darmo";
    body += ". Jeśli spełnia Twoje oczekiwania to postaw ";
    body += " <a href=\"https://www.smartnydom.pl/o-stronie/\" "
            "target=\"_blank\" style=\"color:#00e\">aut";
    body += "orowi";
    body += "</a> ";
    body += "browarka";
    body += " ;)</p>";

    body += "</fieldset><br>";

    page += addConfigurationBlock("Wsparcie", "", body);
  }

  return page;
}

const char *AFESitesGenerator::generateFooter() {
  return "<hr style=\"border:0;border-top:1px solid "
         "#eee;\"/></div></div></body></html>";
}

String AFESitesGenerator::addConfigurationBlock(const String title,
                                                const String description,
                                                const String body) {
  String page = "<div class=\"ci\">";
  page += "<h1>" + title + "</h1>";
  page += "<p class=\"cd\">" + description + "</p>";
  page += body;
  page += "</div>";

  return page;
}

const String AFESitesGenerator::generateConfigParameter_GPIO(
    const char *field, uint8_t selected, const String title) {
  String page = "<div class=\"cf\"><label>";
  page += title;
  page += "</label><select name=\"";
  page += field;
  page += "\">";
  for (uint8_t i = 0; i <= 16; i++) {
    page += "<option value=\"" + String(i) + "\"" +
            (selected == i ? "selected=\"selected\"" : "") + ">" + String(i) +
            "</option>";
  }
  page += "</select></div>";
  return page;
}

const String AFESitesGenerator::generateHardwareItemsList(
    uint8_t noOfItems, uint8_t noOffConnected, const char *field,
    const char *label) {

  String body = "<div class=\"cf\"><label>";
  body += label;
  body += "</label>";
  body += "<select name=\"";
  body += field;
  body += "\">";
  body += "<option value=\"0\"";
  body += (noOffConnected == 0 ? " selected=\"selected\"" : "");
  body += ">";
  body += "Brak";
  body += "</option>";

  for (uint8_t i = 1; i <= noOfItems; i++) {
    body += "<option value=\"";
    body += i;
    body += "\"";
    body += noOffConnected == i ? " selected=\"selected\"" : "";
    body += ">";
    body += i;
    body += "</option>";
  }

  body += "</select>";
  body += "</div>";

  return body;
}
