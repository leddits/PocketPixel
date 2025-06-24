void firebaseSetup()
{
  Serial.println("start firebase setting");
  Firebase.printf("Firebase Client v%s\n", "1.3.10");

  ssl_client1.setClient(&basic_client1);
  ssl_client2.setClient(&basic_client2);
  ssl_client3.setClient(&basic_client3);
  ssl_client4.setClient(&basic_client4);

  ssl_client1.setInsecure();
  ssl_client2.setInsecure();
  ssl_client3.setInsecure();
  ssl_client4.setInsecure();

  ssl_client1.setBufferSizes(2048, 1024);
  ssl_client2.setBufferSizes(2048, 1024);
  ssl_client3.setBufferSizes(2048, 1024);

  // In case using ESP8266 without PSRAM and you want to reduce the memory usage,
  // you can use WiFiClientSecure instead of ESP_SSLClient with minimum receive and transmit buffer size setting as following.
  // ssl_client1.setBufferSizes(1024, 512);
  // ssl_client2.setBufferSizes(1024, 512);
  // ssl_client3.setBufferSizes(1024, 512);
  // Note that, because the receive buffer size was set to minimum safe value, 1024, the large server response may not be able to handle.
  // The WiFiClientSecure uses 1k less memory than ESP_SSLClient.

  ssl_client1.setDebugLevel(1);
  ssl_client2.setDebugLevel(1);
  ssl_client3.setDebugLevel(1);

  // In ESP32, when using WiFiClient with ESP_SSLClient, the WiFiClient was unable to detect
  // the server disconnection in case server session timed out and the TCP session was kept alive for reusage.
  // The TCP session timeout in seconds (>= 60 seconds) can be set via `ESP_SSLClient::setSessionTimeout`.
  ssl_client1.setSessionTimeout(150);
  ssl_client1.setSessionTimeout(150);
  ssl_client3.setSessionTimeout(150);
  ssl_client4.setSessionTimeout(10000);

  Serial.println("Initializing app...");
  initializeApp(aClient3, app, getAuth(user_auth), asyncCB, "authTask");
  app.getApp<RealtimeDatabase>(database);
  app.getApp<Storage>(storage);
  database.url(FIREBASE_URL);
  database.setSSEFilters("get,put,patch,keep-alive,cancel,auth_revoked");

  database.get(aClient1, "/Controller/" + macID + "/tagColor", asyncCB, true /* SSE mode (HTTP Streaming) */, "streamTagColorTask"); // 스트리밍시.. set 이후에는 느려짐
  // database.get(aClient2, "/Controller/" + macID + "/tagStatus", asyncCB, true /* SSE mode (HTTP Streaming) */, "streamTagStatusTask"); // 스트리밍시.. set 이후에는 느려짐
}

void getExternalIP()
{
  String str = "";
  WiFiClient client;
  if (!client.connect("api64.ipify.org", 80)) // Change address below when error is happen
  // if (!client.connect("ipv4.seeip.org/jsonip/", 80))
  {
    Serial.println("Failed to connect with 'api64.ipify.org' !");
  }
  else
  {
    int timeout = millis() + 5000;
    client.print("GET /?format=json HTTP/1.1\r\nHost: api64.ipify.org\r\n\r\n"); // Change address below when error is happen
    // client.print("GET /?format=json HTTP/1.1\r\nHost: ipv4.seeip.org/jsonip/\r\n\r\n");
    while (client.available() == 0)
    {
      if (timeout - millis() < 0)
      {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }

    char pubIp[17], pubIp_s, pubIp_e;
    int size;
    while ((size = client.available()) > 7)
    {
      uint8_t *msg = (uint8_t *)malloc(size);
      size = client.read(msg, size);
      Serial.write(msg, size);
      int i = 0;
      while (i < size)
      {
        if (msg[i] == '{')
        {
          int currChIp = i + 7, j = 0;
          pubIp_s = (char)msg[currChIp];
          while (msg[currChIp] != '}')
          {
            pubIp_e = (char)msg[currChIp - 1];
            pubIp[j] = (char)msg[currChIp];
            currChIp++;
            j++;
          }
          pubIp[j - 1] = '\0';

          std::string pubIpStr(pubIp);
          Serial.println(pubIpStr.c_str());
          physicalIP = pubIpStr.c_str();

          // Firebase.RTDB.setString(&firebaseData, "/Controller/" + macID + "/PhysicalIP", pubIp);
          break;
        }
        i++;
      }
      free(msg);
    }
  }
  Serial.println(macID);
  Serial.println(WiFi.localIP().toString());
}

void restart()
{
  Serial.println("Update firmware completed.");
  Serial.println();
#if defined(OTA_STORAGE)
  Serial.println("Applying update...");
  OTA_STORAGE.apply();
#elif defined(ESP32) || defined(ESP8266)
  Serial.println("Restarting...\n\n");
  ESP.restart();
#elif defined(ARDUINO_RASPBERRY_PI_PICO_W)
  Serial.println("Restarting...\n\n");
  rp2040.restart();
#endif
}

void asyncCB(AsyncResult &aResult)
{
  // WARNING!
  // Do not put your codes inside the callback and printResult.

  printResult(aResult);
}

void printResult(AsyncResult &aResult)
{
  if (aResult.isEvent())
  {
    Firebase.printf("Event task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.appEvent().message().c_str(), aResult.appEvent().code());
  }

  if (aResult.isDebug())
  {
    Firebase.printf("Debug task: %s, msg: %s\n", aResult.uid().c_str(), aResult.debug().c_str());
  }

  if (aResult.isError())
  {
    Firebase.printf("Error task: %s, msg: %s, code: %d\n", aResult.uid().c_str(), aResult.error().message().c_str(), aResult.error().code());
  }

  if (aResult.available())
  {
    RealtimeDatabaseResult &RTDB = aResult.to<RealtimeDatabaseResult>();
    if (RTDB.isStream())
    {
      Serial.println();
      Serial.println("----------------------------");
      Firebase.printf("task: %s\n", aResult.uid().c_str());
      Firebase.printf("event: %s\n", RTDB.event().c_str());
      Firebase.printf("path: %s\n", RTDB.dataPath().c_str());
      Firebase.printf("data: %s\n", RTDB.to<const char *>());
      Firebase.printf("type: %d\n", RTDB.type());

      // if (RTDB.to<String>() != "null")
      // {
      //   if (aResult.uid() == "streamTagTypeTask")
      //     tagType = RTDB.to<int>();
      //   else if (aResult.uid() == "streamTagStatusTask")
      //     tagStatus = RTDB.to<int>();
      //   else if (aResult.uid() == "streamTagColorTask")
      //     tagColor = RTDB.to<int>();
      // }

      // The stream event from RealtimeDatabaseResult can be converted to the values as following.
      // bool v1 = RTDB.to<bool>();
      // int v2 = RTDB.to<int>();
      // float v3 = RTDB.to<float>();
      // double v4 = RTDB.to<double>();
      // String v5 = RTDB.to<String>();
    }
    else
    {
      Serial.println();
      Serial.println("----------------------------");
      Firebase.printf("task: %s, payload: %s\n", aResult.uid().c_str(), aResult.c_str());
      Serial.println(aResult.uid().c_str());
      Serial.println(aResult.c_str());
      if (strcmp(aResult.uid().c_str(), "getFirmwareVersionTask") == 0)
      {
        Serial.println("latest version:" + String(aResult.c_str()));

        if (atof(aResult.c_str()) > version)
        {
          Serial.println("New version available");
          Serial.println("Updating your firmware (OTA)... ");
          storage.ota(aClient4, FirebaseStorage::Parent(STORAGE_BUCKET_ID, "firmware.bin"), asyncCB, "otaTask");
        }
      }
    }
    Firebase.printf("Free Heap: %d\n", ESP.getFreeHeap());
  }
  if (aResult.downloadProgress())
  {
    Firebase.printf("Download task: %s, downloaded %d%s (%d of %d)\n", aResult.uid().c_str(), aResult.downloadInfo().progress, "%", aResult.downloadInfo().downloaded, aResult.downloadInfo().total);
    if (aResult.downloadInfo().total == aResult.downloadInfo().downloaded)
    {
      Firebase.printf("Download task: %s, completed!\n", aResult.uid().c_str());
      if (aResult.isOTA())
        restart();
    }
  }

  if (aResult.uploadProgress())
  {
    Firebase.printf("Upload task: %s, uploaded %d%s (%d of %d)\n", aResult.uid().c_str(), aResult.uploadInfo().progress, "%", aResult.uploadInfo().uploaded, aResult.uploadInfo().total);
    if (aResult.uploadInfo().total == aResult.uploadInfo().uploaded)
    {
      Firebase.printf("Upload task: %s, completed!\n", aResult.uid().c_str());
      Serial.print("Download URL: ");
      Serial.println(aResult.uploadInfo().downloadUrl);
    }
  }
}

void printError(int code, const String &msg)
{
  Firebase.printf("Error, msg: %s, code: %d\n", msg.c_str(), code);
}

void wifiSetup()
{
  wifiManager.autoConnect(ssid_ap, password_ap); // wifi connect
  // waiting wifi connect
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
}
