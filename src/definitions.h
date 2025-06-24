// version
float version = 0.;

// wifi setting
String macID = WiFi.macAddress();
String ssid_ap_str = "POCKETPIXEL-" + macID;
const char *ssid_ap = ssid_ap_str.c_str();
const char *password_ap = "";
WiFiManager wifiManager;
String physicalIP;
String localIp = WiFi.localIP().toString();

// firebase setting
unsigned long timeout = 0;
unsigned long timeout2 = 0;
unsigned long timeout3 = 0;
int taskComplete = 1;
int tagTaskComplete = 1;


int tag = 0;
int tagStatus = 0;
int tagType = 0;
int tagColor = 0;
String tagID = "";
String latestVersion = "";

void asyncCB(AsyncResult &aResult);
void printResult(AsyncResult &aResult);
DefaultNetwork network; // initilize with boolean parameter to enable/disable network reconnection
UserAuth user_auth(FIREBASE_API_KEY, FIREBASE_USER_EMAIL, FIREBASE_USER_PW);
FirebaseApp app;
// WiFiClientSecure ssl_client; // 조금 더 느림
WiFiClient basic_client1, basic_client2, basic_client3, basic_client4;
// WiFiClient basic_client;
ESP_SSLClient ssl_client1, ssl_client2, ssl_client3, ssl_client4;
// ESP_SSLClient ssl_client;
using AsyncClient = AsyncClientClass;
AsyncClient
    aClient1(ssl_client1, getNetwork(network)),
    aClient2(ssl_client2, getNetwork(network)),
    aClient3(ssl_client3, getNetwork(network)),
    aClient4(ssl_client4, getNetwork(network));
// AsyncClient aClient(ssl_client, getNetwork(network));
RealtimeDatabase database;
// AsyncResult aResult_no_callback;
Storage storage;
