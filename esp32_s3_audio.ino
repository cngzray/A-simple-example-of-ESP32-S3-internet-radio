
#include <Arduino.h>
#include <WiFi.h>
#include <Audio.h>
#include <WebServer.h>

// Digital I/O used
#define I2S_DOUT      6
#define I2S_BCLK      5
#define I2S_LRC       4

String ssid =     "xxxx";
String password = "xxxxx";

// ====== 电台列表 ======
struct Aud {
  String AudioUrl;
  String AudioName;
};

struct Aud AudioList[] = {
 // { "https://live.ximalaya.com/radio-first-page-app/live/93/64.m3u8", "请选择频道" },
//{ "https://live.ximalaya.com/radio-first-page-app/live/93/64.m3u8", "北京交通广播" },
//{ "https://live.ximalaya.com/radio-first-page-app/live/94/64.m3u8", "北京文艺广播" },
{"http://live.ximalaya.com/radio-first-page-app/live/74/64.m3u8", "广东音乐之声"},
{"http://live.ximalaya.com/radio-first-page-app/live/252/64.m3u8", "广东珠江经济电台"},
{"http://live.ximalaya.com/radio-first-page-app/live/247/64.m3u8", "广东城市之声"},
{"http://live.ximalaya.com/radio-first-page-app/live/248/64.m3u8", "广东交通之声"},
{"http://live.ximalaya.com/radio-first-page-app/live/249/64.m3u8", "广东南方生活广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/245/64.m3u8", "广东新闻广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/255/64.m3u8", "广东广播电视台珠江之声"},
{"http://live.ximalaya.com/radio-first-page-app/live/967/64.m3u8", "广东广播电视台文体广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/2896/64.m3u8", "股市广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/256/64.m3u8", "广州新闻资讯广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/258/64.m3u8", "广州交通广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/259/64.m3u8", "广州MYFM 88.0"},
{"http://live.ximalaya.com/radio-first-page-app/live/257/64.m3u8", "广州金曲音乐广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/2564/64.m3u8", "增城电台FM89.0"},
{"http://live.ximalaya.com/radio-first-page-app/live/2635/64.m3u8", "从化电台流溪河之声"},
{"http://live.ximalaya.com/radio-first-page-app/live/264/64.m3u8", "深圳交通频率"},
{"http://live.ximalaya.com/radio-first-page-app/live/2912/64.m3u8", "深圳电台湾区之声1043"},
{"http://live.ximalaya.com/radio-first-page-app/live/263/64.m3u8", "深圳飞扬971"},
{"http://live.ximalaya.com/radio-first-page-app/live/265/64.m3u8", "深圳生活广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/262/64.m3u8", "深圳先锋898"},
{"http://live.ximalaya.com/radio-first-page-app/live/2740/64.m3u8", "FM92.8斗门电台"},
{"http://live.ximalaya.com/radio-first-page-app/live/1216/64.m3u8", "台山人民广播电台"},
{"http://live.ximalaya.com/radio-first-page-app/live/1191/64.m3u8", "中山电台快乐888"},
{"http://live.ximalaya.com/radio-first-page-app/live/2870/64.m3u8", "高要综合广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/283/64.m3u8", "FM91.6 阳江综合广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/1220/64.m3u8", "中山电台新锐967"},
{"http://live.ximalaya.com/radio-first-page-app/live/1198/64.m3u8", "清远综合广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/2916/64.m3u8", "新会人民广播电台"},
{"http://live.ximalaya.com/radio-first-page-app/live/2885/64.m3u8", "开平电台"},
{"http://live.ximalaya.com/radio-first-page-app/live/2892/64.m3u8", "肇庆综合广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/2893/64.m3u8", "肇庆旅游之声"},
{"http://live.ximalaya.com/radio-first-page-app/live/966/64.m3u8", "怀集音乐之声"},
{"http://live.ximalaya.com/radio-first-page-app/live/1205/64.m3u8", "怀集音乐之声第二台"},
{"http://live.ximalaya.com/radio-first-page-app/live/2603/64.m3u8", "广宁综合广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/2888/64.m3u8", "梅州电台交通广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/2845/64.m3u8", "惠州音乐广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/2915/64.m3u8", "潮州电台交通音乐广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/2742/64.m3u8", "佛冈电台"},
{"http://live.ximalaya.com/radio-first-page-app/live/1809/64.m3u8", "客都之声 FM1039"},
{"http://live.ximalaya.com/radio-first-page-app/live/2919/64.m3u8", "兴宁市融媒体中心综合广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/2846/64.m3u8", "惠州综合广播"},
{"http://live.ximalaya.com/radio-first-page-app/live/2848/64.m3u8", "博罗电台"},
{"http://live.ximalaya.com/radio-first-page-app/live/2754/64.m3u8", "FM93.5茂名交通广播"}
};

Audio audio;

void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}

WebServer server(80);

// 生成网页内容的独立函数
String generateHtmlContent() {
  String html = "";
  html += "<!DOCTYPE HTML>\r\n";
  html += "<html>\r\n";
  html += "<head>\r\n";
  html += "<meta charset='UTF-8'>\r\n";
  html += "<title>播放器</title>\r\n";
  html += "<style>\r\n";
  html += "body { font-family: Arial, sans-serif; max-width: 400px; margin: 50px auto; padding: 20px; }\r\n";
  html += ".container { text-align: center; }\r\n";
  html += "input, select { padding: 10px; font-size: 16px; }\r\n";
  html += "button { padding: 10px 20px; font-size: 16px; background-color: #4CAF50; color: white; border: none; cursor: pointer; }\r\n";
  html += "button:hover { background-color: #45a049; }\r\n";
  html += ".status { margin-top: 15px; padding: 10px; background-color: #f0f0f0; border-radius: 5px; }\r\n";
  html += ".success { background-color: #d4edda; color: #155724; }\r\n";
  html += ".error { background-color: #f8d7da; color: #721c24; }\r\n";
  html += "</style>\r\n";
  html += "</head>\r\n";
  html += "<body>\r\n";
  html += "<div class='container'>\r\n";
  html += "<h2>电台选择</h2>\r\n";
  html += "<label for='radio'>选择电台:</label><br>\r\n";
  html += "<select id='radio' name='radio'>\r\n";
  
  // 动态生成下拉菜单选项
  int numRadios = sizeof(AudioList) / sizeof(AudioList[0]);
  for (int i = 0; i < numRadios; i++) {
    html += "<option value='" + String(i) + "'>" + AudioList[i].AudioName + "</option>\r\n";
  }
  
  html += "</select>\r\n";
  html += "<br><br>\r\n";
  html += "<h2>自定义音频URL</h2>\r\n";
  html += "<label for='customUrl'>音频URL:</label><br>\r\n";
  html += "<input type='text' id='customUrl' name='customUrl' placeholder='请输入音频URL' style='width: 100%; box-sizing: border-box;'><br><br>\r\n";
  html += "<button id='playUrlBtn'>播放URL</button>\r\n";
  html += "<br><br>\r\n";
  html += "<h2>音量设置</h2>\r\n";
  html += "<label for='volume'>音量: <span id='volumeValue'>15</span></label><br>\r\n";
  html += "<input type='range' id='volume' name='volume' value='15' min='0' max='21' style='width: 100%;'>\r\n";
  html += "<div id='status' class='status'></div>\r\n";
  html += "</div>\r\n";
  html += "<script>\r\n";
  html += "function showStatus(msg, type) {\r\n";
  html += "  var status = document.getElementById('status');\r\n";
  html += "  status.textContent = msg;\r\n";
  html += "  status.className = 'status ' + type;\r\n";
  html += "  setTimeout(function() { status.className = 'status'; }, 3000);\r\n";
  html += "};\r\n";
  html += "document.getElementById('radio').addEventListener('change', function() {\r\n";
  html += "  var xhr = new XMLHttpRequest();\r\n";
  html += "  xhr.open('POST', '/setRadio', true);\r\n";
  html += "  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\r\n";
  html += "  xhr.onreadystatechange = function() {\r\n";
  html += "    if (xhr.readyState == 4 && xhr.status == 200) {\r\n";
  html += "      var response = JSON.parse(xhr.responseText);\r\n";
  html += "      showStatus(response.message, response.success ? 'success' : 'error');\r\n";
  html += "    }\r\n";
  html += "  };\r\n";
  html += "  xhr.send('radio=' + this.value);\r\n";
  html += "});\r\n";
  html += "var volumeSlider = document.getElementById('volume');\r\n";
  html += "var volumeValue = document.getElementById('volumeValue');\r\n";
  html += "volumeSlider.addEventListener('input', function() {\r\n";
  html += "  volumeValue.textContent = this.value;\r\n";
  html += "});\r\n";
  html += "volumeSlider.addEventListener('mouseup', function() {\r\n";
  html += "  var volume = this.value;\r\n";
  html += "  var xhr = new XMLHttpRequest();\r\n";
  html += "  xhr.open('POST', '/setVolume', true);\r\n";
  html += "  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\r\n";
  html += "  xhr.onreadystatechange = function() {\r\n";
  html += "    if (xhr.readyState == 4 && xhr.status == 200) {\r\n";
  html += "      var response = JSON.parse(xhr.responseText);\r\n";
  html += "      showStatus(response.message, response.success ? 'success' : 'error');\r\n";
  html += "    }\r\n";
  html += "  };\r\n";
  html += "  xhr.send('volume=' + volume);\r\n";
  html += "});\r\n";
  html += "document.getElementById('playUrlBtn').addEventListener('click', function() {\r\n";
  html += "  var url = document.getElementById('customUrl').value.trim();\r\n";
  html += "  if (!url) {\r\n";
  html += "    showStatus('请输入音频URL', 'error');\r\n";
  html += "    return;\r\n";
  html += "  }\r\n";
  html += "  var xhr = new XMLHttpRequest();\r\n";
  html += "  xhr.open('POST', '/playUrl', true);\r\n";
  html += "  xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');\r\n";
  html += "  xhr.onreadystatechange = function() {\r\n";
  html += "    if (xhr.readyState == 4 && xhr.status == 200) {\r\n";
  html += "      var response = JSON.parse(xhr.responseText);\r\n";
  html += "      showStatus(response.message, response.success ? 'success' : 'error');\r\n";
  html += "    }\r\n";
  html += "  };\r\n";
  html += "  xhr.send('url=' + encodeURIComponent(url));\r\n";
  html += "});\r\n";
  html += "</script>\r\n";
  html += "</body>\r\n";
  html += "</html>\r\n";
  return html;
}


void handleSetVolume() {
  if (server.hasArg("volume")) {
    int volume = server.arg("volume").toInt();
    audio.setVolume(volume);
    Serial.printf("Volume set to: %d\n", volume);
    server.send(200, "application/json", "{\"success\":true,\"message\":\"音量已设置为: " + String(volume) + "\"}");
  } else {
    server.send(400, "application/json", "{\"success\":false,\"message\":\"缺少音量参数\"}");
  }
}

void handleSetRadio() {
  if (server.hasArg("radio")) {
    int radioIndex = server.arg("radio").toInt();
    int numRadios = sizeof(AudioList) / sizeof(AudioList[0]);
    
    if (radioIndex >= 0 && radioIndex < numRadios) {
      // 停止当前播放
      audio.stopSong();
      delay(100);
      
      // 连接到新的电台
      String url = AudioList[radioIndex].AudioUrl;
      String name = AudioList[radioIndex].AudioName;
      
      bool success = audio.connecttohost(url.c_str());
      
      if (success) {
        Serial.printf("Connected to: %s - %s\n", name.c_str(), url.c_str());
        server.send(200, "application/json", "{\"success\":true,\"message\":\"已切换到: " + name + "\"}");
      } else {
        Serial.printf("Failed to connect to: %s\n", url.c_str());
        server.send(500, "application/json", "{\"success\":false,\"message\":\"连接失败: " + name + "\"}");
      }
    } else {
      server.send(400, "application/json", "{\"success\":false,\"message\":\"无效的电台索引\"}");
    }
  } else {
    server.send(400, "application/json", "{\"success\":false,\"message\":\"缺少电台参数\"}");
  }
}

void handlePlayUrl() {
  if (server.hasArg("url")) {
    String url = server.arg("url");
    
    if (url.length() > 0) {
      // 停止当前播放
      audio.stopSong();
      delay(100);
      
      bool success = audio.connecttohost(url.c_str());
      
      if (success) {
        Serial.printf("Playing custom URL: %s\n", url.c_str());
        server.send(200, "application/json", "{\"success\":true,\"message\":\"正在播放自定义URL\"}");
      } else {
        Serial.printf("Failed to play URL: %s\n", url.c_str());
        server.send(500, "application/json", "{\"success\":false,\"message\":\"播放失败，请检查URL是否有效\"}");
      }
    } else {
      server.send(400, "application/json", "{\"success\":false,\"message\":\"URL不能为空\"}");
    }
  } else {
    server.send(400, "application/json", "{\"success\":false,\"message\":\"缺少URL参数\"}");
  }
}

void handleRoot() {
  server.send(200, "text/html", generateHtmlContent());
}

void handleNotFound() {
  server.send(404, "text/plain", "Not Found");
}


void setup() {

    Serial.begin(115200);
    
    // Connect to WiFi with timeout
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid.c_str(), password.c_str());
    
    int wifiTimeout = 20; // 20 seconds timeout
    while (WiFi.status() != WL_CONNECTED && wifiTimeout > 0) {
        delay(1000);
        Serial.print(".");
        wifiTimeout--;
    }
    
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("\nWiFi connection failed!");
        while (1) delay(1000); // Halt
    }
    
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  // Start web server
  server.on("/", handleRoot);
  server.on("/setVolume", handleSetVolume);
  server.on("/setRadio", handleSetRadio);
  server.on("/playUrl", handlePlayUrl);
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("Web server started");    
    
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(15); // default 0...21
    
    audio.stopSong();
    delay(100);

    Serial.println("Connecting to audio stream...");
    // Try a different stream URL if the original fails
    bool success = audio.connecttohost("https://live.ximalaya.com/radio-first-page-app/live/93/64.m3u8");
      if (success) {
    Serial.println("connecttohost: 成功启动");
  } else {
    Serial.println("connecttohost: 失败，请检查网络、URL 格式或内存");
  }
}

void loop(){
    audio.loop();
    server.handleClient();
    vTaskDelay(1);
}
