#ifndef _PHEV_H_
#define _PHEV_H_

#include <stdint.h>
#include <stdbool.h>
#include "msg_core.h"

#define KO_WF_CONNECT_INFO_GS_SP 1
#define KO_WF_REG_DISP_SP 16
#define KO_WF_INIT_RQ_SP 21
#define KO_WF_VIN_INFO_EVR 21
#define KO_WF_REGISTRATION_EVR 42
#define KO_WF_START_AA_EVR 170
#define KO_WF_ECU_VERSION2_EVR 192
#define KO_WF_REMOTE_SECURTY_PRSNT_INFO 3
#define KO_WF_DATE_INFO_SYNC_SP 5
#define KO_WF_MANUAL_AC_ON_RQ_SP 4
#define KO_WF_DATE_INFO_SYNC_SP 5
#define KO_WF_H_LAMP_CONT_SP 10
#define KO_WF_P_LAMP_CONT_SP 11
#define KO_WF_BATT_LEVEL_INFO_REP_EVR 29

typedef struct phevCtx_t phevCtx_t;
typedef struct phev_pipe_ctx_t phev_pipe_ctx_t;
typedef struct phevPipeEvent_t phevPipeEvent_t;
typedef void (*phevCallBack_t)(phevCtx_t * ctx, void *);
typedef struct phevCallBackCtx_t {
    phevCallBack_t callback;
    phevCtx_t * ctx;
} phevCallBackCtx_t;
typedef enum {
    PHEV_CONNECTED,
    PHEV_REGISTER_UPDATE,
    PHEV_DISCONNECTED,
    PHEV_REGISTERED,
    PHEV_REGISTRATION_COMPLETE,
    PHEV_VIN,
    PHEV_START,
    PHEV_ECU_VERSION,
    PHEV__MAX_REGISTRATIONS,
} phevEventTypes_t;

typedef struct phevEvent_t {
    phevEventTypes_t type;
    uint8_t reg;
    uint8_t * data;
    size_t length;
    phevCtx_t * ctx;
} phevEvent_t;

typedef int (* phevEventHandler_t)(phevEvent_t *);

typedef struct phevSettings_t {
    char * host;
    uint16_t port;
    bool registerDevice;
    uint8_t * mac;
    phevEventHandler_t handler;
    void * ctx;
    messagingClient_t * in;
    messagingClient_t * out;
} phevSettings_t;

phevCtx_t * phev_init(phevSettings_t settings);
void phev_start(phevCtx_t * ctx);
phevCtx_t * phev_registerDevice(phevSettings_t settings);
void phev_updateRegister(uint8_t reg, uint8_t * data, size_t length);
void phev_exit(phevCtx_t * ctx);
void phev_headLights(phevCtx_t * ctx, bool on, phevCallBack_t callback);
void phev_airCon(phevCtx_t * ctx, bool on, phevCallBack_t callback);
bool phev_running(phevCtx_t * ctx);
int phev_batteryLevel(phevCtx_t * ctx);
#endif