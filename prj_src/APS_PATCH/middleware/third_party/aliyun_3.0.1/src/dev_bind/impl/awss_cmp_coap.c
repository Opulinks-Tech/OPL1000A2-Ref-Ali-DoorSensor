/*
 * Copyright (C) 2015-2018 Alibaba Group Holding Limited
 */
#include "dev_bind_internal.h"
#ifdef WIFI_PROVISION_ENABLED
#if defined(AWSS_SUPPORT_ADHA) || defined(AWSS_SUPPORT_AHA)
#include "awss_wifimgr.h"
#endif
#endif
#include "os.h"

#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

static void *g_coap_ctx = NULL;

int awss_release_coap_ctx(void *session)
{
#if 0    
    struct coap_session_ctx_t *ctx = (struct coap_session_ctx_t *)session;
    if (ctx == NULL) {
        return 0;
    }

    if (ctx->request) {
        void *payload = ((struct CoAPMessage *)ctx->request)->payload;
        if (payload) {
            HAL_Free(payload);
        }
        HAL_Free(ctx->request);
    }
    if (ctx->remote) {
        HAL_Free(ctx->remote);
    }
    HAL_Free(ctx);
#endif    
    return 0;
}

void *awss_cpy_coap_ctx(void *request, void *remote, char mcast)
{
#if 0    
    struct coap_session_ctx_t *ctx = os_zalloc_(sizeof(struct coap_session_ctx_t));
    if (ctx == NULL) {
        goto CPY_CTX_FAIL;
    }

    ctx->request = os_zalloc_(sizeof(struct CoAPMessage));
    if (ctx->request == NULL) {
        goto CPY_CTX_FAIL;
    }

    memcpy(ctx->request, request, sizeof(struct CoAPMessage));
    do {
        char *payload = NULL;
        int len = 0;
        struct CoAPMessage *req = (struct CoAPMessage *)ctx->request;

        payload = awss_cmp_get_coap_payload(request, &len);
        req->payloadlen = len;
        if (payload == NULL) {
            break;
        }

        req->payload = os_zalloc_(len + 1);
        if (req->payload == NULL) {
            goto CPY_CTX_FAIL;
        }

        memcpy(req->payload, payload, len);
    } while (0);

    ctx->remote = os_zalloc_(sizeof(platform_netaddr_t));
    if (ctx->remote == NULL) {
        goto CPY_CTX_FAIL;
    }

    memcpy(ctx->remote, remote, sizeof(platform_netaddr_t));
    ctx->is_mcast = mcast;

    return ctx;

CPY_CTX_FAIL:
    awss_release_coap_ctx(ctx);
    return NULL;
#endif
    return 0;
}

uint8_t awss_cmp_get_coap_code(void *request)
{
#if 0     
    struct CoAPMessage *msg = NULL;
    if (request == NULL) {
        return 0x60;
    }
    msg = (struct CoAPMessage *)request;
    return msg->header.code;
#endif
    return 0;    
}

char *awss_cmp_get_coap_payload(void *request, int *payload_len)
{
#if 0     
    struct CoAPMessage *msg = (struct CoAPMessage *)request;
    if (request == NULL) {
        return NULL;
    }

    msg = (struct CoAPMessage *)request;
    if (payload_len) {
        *payload_len = msg->payloadlen;
    }
    return (char *)msg->payload;
#endif
    return 0;    
}

int awss_cmp_coap_register_cb(char *topic, void *cb)
{
#if 0    
    if (g_coap_ctx == NULL) {
        g_coap_ctx = (void *)CoAPServer_init();
    }

    if (g_coap_ctx == NULL) {
        return -1;
    }
    if (topic == NULL) {
        return -1;
    }

    CoAPServer_register(g_coap_ctx, (const char *)topic, (CoAPRecvMsgHandler)cb);
#endif    
    return 0;
}

int awss_cmp_coap_cancel_packet(uint16_t msgid)
{
#if 0
    if (g_coap_ctx == NULL) {
        return -1;
    }
    return CoAPMessageId_cancel(g_coap_ctx, msgid);
#endif
    return 0;     
}

int awss_cmp_coap_send(void *buf, uint32_t len, void *sa, const char *uri, void *cb, uint16_t *msgid)
{
#if 0    
    if (g_coap_ctx == NULL) {
        g_coap_ctx = (void *)CoAPServer_init();
    } else {
        CoAPMessageId_cancel(g_coap_ctx, *msgid);
    }
    return CoAPServerMultiCast_send(g_coap_ctx, (NetworkAddr *)sa, uri, (uint8_t *)buf,
                                    (uint16_t)len, (CoAPSendMsgHandler)cb, msgid);
#endif
    return 0;    
}

int awss_cmp_coap_send_resp(void *buf, uint32_t len, void *sa, const char *uri, void *req, void *cb, uint16_t *msgid, char qos)
{
#if 0     
    if (g_coap_ctx == NULL) {
        g_coap_ctx = (void *)CoAPServer_init();
    }

    return CoAPServerResp_send(g_coap_ctx, (NetworkAddr *)sa, (uint8_t *)buf, (uint16_t)len, req, uri, (CoAPSendMsgHandler)cb, msgid, qos);
#endif
    return 0;     
    
}

int awss_cmp_coap_ob_send(void *buf, uint32_t len, void *sa, const char *uri, void *cb)
{
#if 0    
    if (g_coap_ctx == NULL) {
        g_coap_ctx = (void *)CoAPServer_init();
    }

    return CoAPObsServer_notify(g_coap_ctx, uri, (uint8_t *)buf, (uint16_t)len, (CoAPDataEncrypt)cb);
#endif
    return 0;    
}

int awss_cmp_coap_deinit()
{
#if 0    
    void *coap_ctx = g_coap_ctx;
    g_coap_ctx = NULL;

    if (coap_ctx) {
        CoAPServer_deinit(coap_ctx);
    }
#endif
    return 0;
}

const struct awss_cmp_couple awss_local_couple[] = {
#ifdef WIFI_PROVISION_ENABLED
#if defined(AWSS_SUPPORT_ADHA) || defined(AWSS_SUPPORT_AHA)
    {AWSS_LC_INIT_PAP,                       TOPIC_AWSS_SWITCHAP,                 wifimgr_process_switch_ap_request},
    {AWSS_LC_INIT_PAP,                       TOPIC_AWSS_WIFILIST,                 wifimgr_process_get_wifilist_request},
    {AWSS_LC_INIT_ROUTER | AWSS_LC_INIT_PAP, TOPIC_AWSS_GETDEVICEINFO_MCAST,      wifimgr_process_mcast_get_device_info},
    {AWSS_LC_INIT_ROUTER | AWSS_LC_INIT_PAP, TOPIC_AWSS_GETDEVICEINFO_UCAST,      wifimgr_process_ucast_get_device_info},
#endif
#ifdef AWSS_SUPPORT_DEV_AP
    {AWSS_LC_INIT_DEV_AP,                    TOPIC_AWSS_DEV_AP_SWITCHAP,          wifimgr_process_dev_ap_switchap_request},
#endif
    {AWSS_LC_INIT_SUC,                       TOPIC_AWSS_GET_CONNECTAP_INFO_MCAST, awss_process_mcast_get_connectap_info},
    {AWSS_LC_INIT_SUC,                       TOPIC_AWSS_GET_CONNECTAP_INFO_UCAST, awss_process_ucast_get_connectap_info},
#ifndef AWSS_DISABLE_REGISTRAR
    {AWSS_LC_INIT_BIND,                      TOPIC_NOTIFY,                        online_dev_bind_monitor},
    {AWSS_LC_INIT_BIND,                      TOPIC_AWSS_CONNECTAP_NOTIFY,         online_dev_bind_monitor},
#endif
#endif
    {AWSS_LC_INIT_BIND,                      TOPIC_GETDEVICEINFO_MCAST,           online_mcast_get_device_info},
    {AWSS_LC_INIT_BIND,                      TOPIC_GETDEVICEINFO_UCAST,           online_ucast_get_device_info}
};

int awss_cmp_local_init(int init_stage)
{
    char topic[TOPIC_LEN_MAX] = {0};
    int i;

    for (i = 0; i < sizeof(awss_local_couple) / sizeof(awss_local_couple[0]); i ++) {
        if ((awss_local_couple[i].init_stage & init_stage) == 0) {
            continue;
        }
        memset(topic, 0, sizeof(topic));
        awss_build_topic(awss_local_couple[i].topic, topic, TOPIC_LEN_MAX);        
        awss_cmp_coap_register_cb(topic, awss_local_couple[i].cb);        
    }

    return 0;
}

int awss_cmp_local_deinit(int force)
{
    if (g_coap_ctx == NULL) {
        return 0;
    }
#ifdef WIFI_PROVISION_ENABLED
#if defined(AWSS_SUPPORT_ADHA) || defined(AWSS_SUPPORT_AHA)
    awss_devinfo_notify_stop();
#endif
    awss_suc_notify_stop();
#endif
    if (force) {        
        awss_cmp_coap_deinit();        
    }

    return 0;
}
#if defined(__cplusplus)  /* If this is a C++ compiler, use C linkage */
}
#endif
