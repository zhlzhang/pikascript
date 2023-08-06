#include "_mqtt__MQTT.h"
#include "PikaObj.h"
#include "PikaStdData_List.h"
#include "TinyObj.h"
#include "mqttclient.h"

#if !PIKASCRIPT_VERSION_REQUIRE_MINIMUN(1, 12, 0)
#error "This library requires PikaScript version 1.12.0 or higher"
#endif

PikaEventListener* g_mqtt_event_listener = NULL;

void Subscribe_Handler(void* client, message_data_t* msg);

const uint32_t MQTT_RECONNECTION_EVENT_ID = 0xFFAA0088;

void _mqtt__MQTT___init__(PikaObj* self,
                          char* ip,
                          int port,
                          char* clinetID,
                          char* username,
                          char* password,
                          char* version,
                          char* ca,
                          int keepalive) {
    obj_setInt(self, "_connected", 0);
    mqtt_client_t* _client = mqtt_lease();
    _client->user_data = self;
    // obj_setPtr(self, "_client", _client);
    /* port to str, and cache to object */
    char port_str[10] = {0};
    int tmp = 0;

    if (strlen(ip) > 0) {
        obj_setStr(self, "host_str", ip);
        mqtt_set_host(_client, obj_getStr(self, "host_str"));
    } else {
        __platform_printf("mqtt_init input ip none\r\n");
    }

    memset(port_str, 0, sizeof(port_str));
    __platform_sprintf(port_str, "%d", port);
    obj_setStr(self, "port", port_str);
    mqtt_set_port(_client, obj_getStr(self, "port"));

    if (strlen(clinetID) > 0) {
        obj_setStr(self, "id_str", clinetID);
        mqtt_set_client_id(_client, obj_getStr(self, "id_str"));
    } else {
        __platform_printf("mqtt_init input clinetID none\r\n");
    }

    if (strlen(username) > 0) {
        obj_setStr(self, "username_str", username);
        mqtt_set_user_name(_client, obj_getStr(self, "username_str"));
    } else {
        __platform_printf("mqtt_init input username none\r\n");
    }

    if (strlen(password) > 0) {
        obj_setStr(self, "password_str", password);
        mqtt_set_password(_client, obj_getStr(self, "password_str"));
    } else {
        __platform_printf("mqtt_init input password none\r\n");
    }

    tmp = atoi(version);
    if (tmp > 0) {
        mqtt_set_version(_client, tmp);
    } else {
        __platform_printf("mqtt_init input version none\r\n");
    }

    if (strlen(ca) > 0) {
        obj_setStr(self, "ca_str", ca);
        mqtt_set_ca(_client, obj_getStr(self, "ca_str"));
    } else {
        // __platform_printf("mqtt_init input ca none\r\n");
    }

    if (keepalive > 0) {
        mqtt_set_keep_alive_interval(_client, keepalive);
    } else {
        __platform_printf("mqtt_init input keepalive none\r\n");
    }

    mqtt_set_clean_session(_client, 1);

    obj_setPtr(self, "_client", _client);
    // __platform_printf("Mqtt_Lib buildtime:%s-%s\r\n", __DATE__, __TIME__);
}

void _mqtt__MQTT___del__(PikaObj* self) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");
    if (NULL == _client) {
        return;
    }
    /* disconnect autoly if not disconnected */
    int _connected = obj_getInt(self, "_connected");
    if (_connected) {
        _mqtt__MQTT_disconnect(self);
    }
    // MQTT_LOG_E("%s:%d %s() >_<", __FILE__, __LINE__, __FUNCTION__);
    mqtt_release_free(_client);
}

int _mqtt__MQTT_connect(PikaObj* self) {
    int ret;
    obj_setInt(self, "_connected", 1);
    mqtt_client_t* _client = obj_getPtr(self, "_client");

    ret = mqtt_connect(_client);
    if (ret != 0)
        __platform_printf("mqtt connect ERROR! :%d\r\n", ret);

    // if (ret == 0)
    //     __platform_printf("mqtt connect OK\r\n");
    return ret;
}

int _mqtt__MQTT_disconnect(PikaObj* self) {
    int ret;
    obj_setInt(self, "_connected", 0);
    mqtt_client_t* _client = obj_getPtr(self, "_client");

    ret = mqtt_disconnect(_client);
    if (ret != 0)
        __platform_printf("mqtt disconnect ERROR! :%d\r\n", ret);

    // if (ret == 0)
    //     __platform_printf("mqtt disconnect OK\r\n");
    return ret;
}

PikaObj* _mqtt__MQTT_listSubscribeTopic(PikaObj* self) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");
    // int i = 0;
    mqtt_list_t *curr, *next;
    message_handlers_t* msg_handler;
    PikaObj* list = NULL;

    if (NULL == _client) {
        return NULL;
    }

    if (mqtt_list_is_empty(&_client->mqtt_msg_handler_list)) {
        MQTT_LOG_I("%s:%d %s()... there are no subscribed topics...", __FILE__,
                   __LINE__, __FUNCTION__);
        return NULL;
    }

    list = newNormalObj(New_PikaStdData_List);
    PikaStdData_List___init__(list);

    LIST_FOR_EACH_SAFE(curr, next, &_client->mqtt_msg_handler_list) {
        msg_handler = LIST_ENTRY(curr, message_handlers_t, list);
        /* determine whether a node already exists by mqtt topic, but wildcards
         * are not supported */
        if (NULL != msg_handler->topic_filter) {
            MQTT_LOG_I("%s:%d %s()...[%d] subscribe topic: %s", __FILE__,
                       __LINE__, __FUNCTION__, ++i, msg_handler->topic_filter);
            // __platform_printf("[%d]subscribe topic: %s\n",++i,
            // msg_handler->topic_filter);
            Arg* str_arg1 = arg_newStr((char*)msg_handler->topic_filter);
            PikaStdData_List_append(list, str_arg1);
            arg_deinit(str_arg1);
        }
    }
    return list;
}

int _mqtt__MQTT_publish(PikaObj* self, char* topic, char* payload, int qos) {
    int ret;
    mqtt_message_t msg;

    mqtt_client_t* _client = obj_getPtr(self, "_client");
    memset(&msg, 0, sizeof(msg));

    if ((qos < 0) || (qos > 2)) {
        __platform_printf("input qos error\r\n");
        return -1;
    }
    if (strlen(topic) <= 0) {
        __platform_printf("input topic error\r\n");
        return -2;
    }

    if (strlen(payload) <= 0) {
        __platform_printf("input payload error\r\n");
        return -3;
    }

    msg.payload = (void*)payload;
    msg.qos = qos;
    __platform_printf("msg.qos:%d\r\n", msg.qos);
    ret = mqtt_publish(_client, topic, &msg);
    if (ret == 0) {
        // __platform_printf("MQTT_publish OK\r\n");
    } else
        __platform_printf("MQTT_publish ERROR\r\n");
    return ret;
}

int _mqtt__MQTT_setCa(PikaObj* self, char* ca) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");

    if (ca == NULL) {
        __platform_printf("input ca error\r\n");
        return -1;
    }
    if (strlen(ca) <= 0) {
        __platform_printf("input ca data error\r\n");
        return -2;
    }
    //__platform_printf("ca_str:%s\r\n",ca);
    obj_setStr(self, "ca_str", ca);
    mqtt_set_ca(_client, obj_getStr(self, "ca_str"));

    // __platform_printf("MQTT_setCa len:%d\r\n", strlen(ca));
    return 0;
}

int _mqtt__MQTT_setClientID(PikaObj* self, char* id) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");

    if (id == NULL) {
        __platform_printf("input id error\r\n");
        return -1;
    }
    if (strlen(id) <= 0) {
        __platform_printf("input id data error\r\n");
        return -2;
    }

    obj_setStr(self, "id_str", id);
    mqtt_set_client_id(_client, obj_getStr(self, "id_str"));

    // __platform_printf("MQTT_setClientID :%s\r\n", id);
    return 0;
}

int _mqtt__MQTT_setHost(PikaObj* self, char* host_url) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");

    if (host_url == NULL) {
        __platform_printf("input host_url error\r\n");
        return -1;
    }
    if (strlen(host_url) <= 0) {
        __platform_printf("input host_url data error\r\n");
        return -2;
    }

    obj_setStr(self, "host_str", host_url);
    mqtt_set_host(_client, obj_getStr(self, "host_str"));
    // __platform_printf("MQTT_setHost :%s\r\n", host_url);

    return 0;
}

int _mqtt__MQTT_setKeepAlive(PikaObj* self, int time) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");
    int tmp;

    // tmp = atoi(time);
    tmp = time;
    if (tmp > 0) {
        mqtt_set_keep_alive_interval(_client, tmp);
    } else {
        __platform_printf("input keepalive data error \r\n");
        return -2;
    }

    // __platform_printf("MQTT_setKeepAlive :%d\r\n", tmp);
    return 0;
}

int _mqtt__MQTT_setPassword(PikaObj* self, char* passwd) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");

    if (passwd == NULL) {
        __platform_printf("input passwd error\r\n");
        return -1;
    }
    if (strlen(passwd) <= 0) {
        __platform_printf("input passwd data error\r\n");
        return -2;
    }

    obj_setStr(self, "password_str", passwd);
    mqtt_set_password(_client, obj_getStr(self, "password_str"));

    // __platform_printf("MQTT_setPassword :%s\r\n", passwd);
    return 0;
}

int _mqtt__MQTT_setPort(PikaObj* self, int port) {
    char port_str[10] = {0};
    mqtt_client_t* _client = obj_getPtr(self, "_client");

    if (port <= 0) {
        __platform_printf("input port error\r\n");
        return -1;
    }

    __platform_sprintf(port_str, "%d", port);
    obj_setStr(self, "port", port_str);

    mqtt_set_port(_client, obj_getStr(self, "port"));
    // __platform_printf("MQTT_setPort :%s\r\n", port_str);

    return 0;
}

int _mqtt__MQTT_setUsername(PikaObj* self, char* name) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");

    if (name == NULL) {
        __platform_printf("input name error\r\n");
        return -1;
    }
    if (strlen(name) <= 0) {
        __platform_printf("input name data error\r\n");
        return -2;
    }

    obj_setStr(self, "username_str", name);
    mqtt_set_user_name(_client, obj_getStr(self, "username_str"));

    // __platform_printf("MQTT_setUsername :%s\r\n", name);
    return 0;
}

int _mqtt__MQTT_setVersion(PikaObj* self, char* version) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");
    // int tmp;

    if (version == NULL) {
        __platform_printf("input version str error\n");
        return -1;
    }
    if ((strcmp(version, "3.1") == 0) || (strcmp(version, "3.1.1") == 0)) {
        if (strcmp(version, "3.1.1") == 0)
            mqtt_set_version(_client, 4);
        else
            mqtt_set_version(_client, 3);
    } else {
        __platform_printf("input version data error\n");
        return -2;
    }

    // __platform_printf("MQTT_setVersion :%d\r\n", tmp);
    return 0;
}

int _mqtt__MQTT_setWill(PikaObj* self,
                        char* topic,
                        char* payload,
                        int qos,
                        int retain) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");
    int ret;
    char topic_str[MQTT_TOPIC_LEN_MAX];

    // __platform_printf("\r\n");
    if (topic == NULL) {
        __platform_printf("input topic error\r\n");
        return -1;
    }

    if (strlen(topic) <= 0) {
        __platform_printf("input topic error\r\n");
        return -1;
    }

    if ((qos < 0) || (qos > 2)) {
        __platform_printf("input qos error\r\n");
        return -1;
    }

    if (payload == NULL) {
        __platform_printf("input payload error\r\n");
        return -1;
    }

    if (strlen(payload) <= 0) {
        __platform_printf("input payload error\r\n");
        return -1;
    }

    memset(topic_str, 0, sizeof(topic_str));
    sprintf(topic_str, "%s", topic);
    obj_setStr(self, topic_str, topic);
    obj_setStr(self, "Will_payload", payload);

    // __platform_printf("obj_getStr(self, topic_str) :%s\r\n", obj_getStr(self,
    // topic_str));
    // __platform_printf("iqos :%d\r\n", qos);
    // __platform_printf("retain :%d\r\n", retain);
    // __platform_printf("obj_getStr(self, \"Will_payload\") :%s\r\n",
    // obj_getStr(self, "Will_payload"));

    ret = mqtt_set_will_options(_client, obj_getStr(self, topic_str), qos,
                                (uint8_t)retain,
                                obj_getStr(self, "Will_payload"));

    if (ret == 0) {
        // __platform_printf("MQTT_setWill OK\r\n", topic);
    } else
        __platform_printf("MQTT_setWill ERROR\r\n");

    return 0;
}

int _mqtt__MQTT_subscribe(PikaObj* self, char* topic, Arg* cb, int qos) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");
    int ret;
    char topic_str[MQTT_TOPIC_LEN_MAX + 24];

    // __platform_printf("topic_str:%s \r\n",topic_str);
    if (topic == NULL) {
        __platform_printf("input topic error\r\n");
        return -1;
    }

    if ((strlen(topic) > MQTT_TOPIC_LEN_MAX) || (strlen(topic) <= 0)) {
        __platform_printf("input topic data error strlen(topic):%d\r\n",
                          strlen(topic));
        return -2;
    }

    if ((qos < 0) || (qos > 2)) {
        __platform_printf("input qos error\r\n");
        return -3;
    }

    memset(topic_str, 0, sizeof(topic_str));
    sprintf(topic_str, "%s", topic);
    obj_setStr(self, topic_str, topic);

    ret = mqtt_subscribe(_client, obj_getStr(self, topic_str), qos,
                         Subscribe_Handler);
    if (ret == 0) {
        // __platform_printf("MQTT_subscribe Topic :%s Qos:%d OK\r\n",
        // topic,qos);
        if (cb != NULL) {
            char hash_str[32] = {0};
            memset(hash_str, 0, sizeof(hash_str));
            sprintf(hash_str, "C%d", hash_time33(topic_str));
            obj_newDirectObj(self, hash_str, New_TinyObj);
            PikaObj* eventHandler = obj_getPtr(self, hash_str);
            obj_setArg(eventHandler, "eventCallBack", cb);
            /* init event_listener for the first time */
            if (NULL == g_mqtt_event_listener) {
                pika_eventListener_init(&g_mqtt_event_listener);
            }
            uint32_t eventId = hash_time33(topic_str);
            // __platform_printf("hash_time33(topic_str):%d
            // \r\n",hash_time33(topic_str));
            pika_eventListener_registEvent(g_mqtt_event_listener, eventId,
                                           eventHandler);
        }

    } else
        __platform_printf("MQTT_subscribe Topic ERROR\r\n");

    return ret;
}

int _mqtt__MQTT_unsubscribe(PikaObj* self, char* topic) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");
    int ret;

    if (strlen(topic) <= 0) {
        __platform_printf("input topic error\r\n");
        return -1;
    }

    ret = mqtt_unsubscribe(_client, topic);
    if (ret == 0) {
        // __platform_printf("MQTT_unsubscribe :%s OK\r\n", topic);
    } else
        __platform_printf("MQTT_unsubscribe :%s ERROR\r\n", topic);

    return 0;
}

void Subscribe_Handler(void* client, message_data_t* msg) {
    char topic_str[MQTT_TOPIC_LEN_MAX + 24];

    memset(topic_str, 0, sizeof(topic_str));
    if (strlen(msg->topic_name) <= MQTT_TOPIC_LEN_MAX)
        sprintf(topic_str, "%s", msg->topic_name);
    else {
        __platform_printf("Subscribe Topic recv data topic length ERROR\r\n");
        return;
    }

    Arg* evt_obj_arg = arg_newDirectObj(New_TinyObj);
    PikaObj* evt_obj = arg_getPtr(evt_obj_arg);
    obj_setStr(evt_obj, "topic", (char*)msg->topic_name);
    obj_setStr(evt_obj, "msg", (char*)msg->message->payload);
    obj_setInt(evt_obj, "qos", msg->message->qos);

    pika_eventListener_send(g_mqtt_event_listener, hash_time33(msg->topic_name),
                            evt_obj_arg);

    // MQTT_LOG_I("\n>>>------------------");
    // MQTT_LOG_I("Topic:%s \nlen:%d,message: %s", msg->topic_name,
    //            (int)msg->message->payloadlen, (char*)msg->message->payload);
    // MQTT_LOG_I("------------------<<<");
}

void _mqtt__MQTT__fakeMsg(PikaObj* self, char* topic, int qos, char* msg) {
    message_data_t msg_data;
    mqtt_message_t mqtt_msg;
    mqtt_msg.payload = msg;
    mqtt_msg.payloadlen = strlen(msg);
    mqtt_msg.qos = qos;
    mqtt_msg.retained = 0;
    msg_data.message = &mqtt_msg;
    strcpy(msg_data.topic_name, topic);
    Subscribe_Handler(NULL, &msg_data);
}

void _mqtt___del__(PikaObj* self) {
    if (NULL != g_mqtt_event_listener) {
        pika_eventListener_deinit(&g_mqtt_event_listener);
    }
}

void Reconnect_Handler(void* client, void* reconnect_date) {
    // PikaObj* self = ((mqtt_client_t*)client)->user_data;
    // __platform_printf("Reconnect_Handler\r\n");

    if (((mqtt_client_t*)client)->mqtt_client_state != CLIENT_STATE_CONNECTED) {
        pika_eventListener_sendSignal(g_mqtt_event_listener,
                                      MQTT_RECONNECTION_EVENT_ID, 1);
    }
}

int _mqtt__MQTT_setDisconnectHandler(PikaObj* self, Arg* cb) {
    mqtt_client_t* _client = obj_getPtr(self, "_client");

    // __platform_printf("_mqtt__MQTT_setDisconnectHandler\r\n");

    mqtt_set_reconnect_handler(_client, Reconnect_Handler);

    // char hash_str[32] = {0};
    // memset(hash_str,0,sizeof(hash_str));
    // sprintf(hash_str,"C%d",hash_time33(topic_str));
    // obj_newDirectObj(self,hash_str,New_TinyObj);
    // PikaObj* eventHandler = obj_getPtr(self,hash_str);
    // obj_setArg(eventHandler, "eventCallBack", cb);

    obj_setArg(self, "eventCallBack", cb);
    /* init event_listener for the first time */
    if (NULL == g_mqtt_event_listener) {
        pika_eventListener_init(&g_mqtt_event_listener);
    }
    // uint32_t eventId = hash_time33(topic_str);
    // __platform_printf("hash_time33(topic_str):%d
    // \r\n",hash_time33(topic_str));
    pika_eventListener_registEvent(g_mqtt_event_listener,
                                   MQTT_RECONNECTION_EVENT_ID, self);

    return 0;
}
