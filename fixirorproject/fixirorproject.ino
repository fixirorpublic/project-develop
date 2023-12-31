#include <ESP8266HTTPClient.h>
#include <WiFiManager.h>

//siapkan variabel untuk sensor api
const int flame = D1;
const int buzz = D2;

//siapkan variabel menampung url
String url;
//siapkan variabel untuk wifi client
WiFiClient client;

void setup() {
  
  pinMode(flame, INPUT);
  pinMode(buzz, OUTPUT);
  WiFi.mode(WIFI_STA);  // explicitly set mode, esp defaults to STA+AP
  // it is a good practice to make sure your code sets wifi mode how you want it.

  // put your setup code here, to run once:
  Serial.begin(115200);

  //WiFiManager, Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wm;

  // reset settings - wipe stored credentials for testing
  // these are stored by the esp library
  wm.resetSettings();

  // Automatically connect using saved credentials,
  // if connection fails, it starts an access point with the specified name ( "AutoConnectAP"),
  // if empty will auto generate SSID, if password is blank it will be anonymous AP (wm.autoConnect())
  // then goes into a blocking loop awaiting configuration and will return success result

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("FIXIROR IOT", "password");  // password protected ap

  if (!res) {
    Serial.println("Failed to connect");
    // ESP.restart();
  } else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
  }
}

void loop() {
  int api = digitalRead(flame);
  if (api == 0) {
    digitalWrite(buzz, HIGH);
    kirim_wa("Pesan Otomatis Perangkat Fixiror Flame Sensor\n\nBahaya!!! telah ditemukan titik api kebakaran. \nSilahkan evakuasi keluarga dan barang didalam rumah anda");
  } else {
    digitalWrite(buzz, LOW);
  }
  delay(3000);
}

void kirim_wa(String pesan) {
  url = "http://localhost:3000/api?nohp=081229563543&pesan="+ urlencode(pesan) +"&token=KNSDKSNDFDKPnpnpnmpljnaslckn";
  //kirim pesan
  postData();
}

void postData() {
  //siapkan untuk menampung pesan terkirim atau tidak ke whatsapp
  int httpCode;
  //siapkan variabel untuk protokol http yang akan terkoneksi ke server callme
  HTTPClient http;
  //eksekusi link url
  http.begin(client, url);
  httpCode = http.POST(url);
  //uji nilai variabel httpCode
  if (httpCode == 200) {
    Serial.println("Notifikasi berhasil terkirim");
  } else {
    Serial.println("Notifikasi tidak terkirim");
  }
  http.end();
}

String urlencode(String str) {
  String encodedString = "";
  char c;
  char code0, code1, code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    // jika ada spasi diantara pesan yang akan dikirim, maka ganti dengan karakter +

    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += '0';
      encodedString += '1';
    }
    yield();
  }
  Serial.println(encodedString);
  return encodedString;
}