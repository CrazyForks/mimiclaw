#pragma once

#include "esp_err.h"

/**
 * Initialize Feishu bot (load credentials from NVS/secrets).
 */
esp_err_t feishu_bot_init(void);

/**
 * Start Feishu bot (create WebSocket long connection task on Core 0).
 */
esp_err_t feishu_bot_start(void);

/**
 * Send a text message to a Feishu user or group.
 * @param chat_id  Feishu open_id (ou_*) or chat_id (oc_*)
 * @param text     Message content
 */
esp_err_t feishu_send_message(const char *chat_id, const char *text);

/**
 * Save Feishu App ID to NVS.
 */
esp_err_t feishu_set_app_id(const char *app_id);

/**
 * Save Feishu App Secret to NVS.
 */
esp_err_t feishu_set_app_secret(const char *app_secret);
