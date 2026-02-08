# Feishu (Lark) Setup Guide | 飞书配置指南

**[English](#english) | [中文](#中文)**

---

## English

MimiClaw supports [Feishu (Lark)](https://www.feishu.cn/) as a messaging channel. It uses **WebSocket long connection** — no public IP or webhook server required. Just configure your Feishu app credentials and MimiClaw connects directly to Feishu's event gateway.

### 1. Create a Feishu App

1. Go to [Feishu Open Platform](https://open.feishu.cn/app) and create a new app
2. In **Credentials & Basic Info**, copy the **App ID** and **App Secret**

### 2. Enable Bot Capability

1. Go to **Add Capabilities** → enable **Bot**
2. Give your bot a name and avatar

### 3. Add Permissions

Go to **Permissions & Scopes** and add:

| Permission | Description |
|-----------|-------------|
| `im:message` | Send messages |
| `im:message.receive_v1` | Receive messages |

### 4. Enable Events (Long Connection)

1. Go to **Event Subscriptions**
2. Set subscription mode to **Long Connection** (WebSocket)
3. Add event: `im.message.receive_v1` (Receive messages)

> **Important:** You must select **Long Connection** mode, not HTTP callback. This allows MimiClaw to receive events without a public IP.

### 5. Publish the App

1. Go to **App Release** → **Create Version**
2. Fill in version info and submit for review
3. For self-built apps in your own organization, approval is usually instant

### 6. Configure MimiClaw

**Option A: Build-time** — Edit `main/mimi_secrets.h`:

```c
#define MIMI_SECRET_FEISHU_APP_ID     "cli_xxxxxxxxxxxxxxxx"
#define MIMI_SECRET_FEISHU_APP_SECRET "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
```

Then rebuild: `idf.py fullclean && idf.py build`

**Option B: Runtime** — Via serial CLI (no recompile needed):

```
mimi> set_feishu_id cli_xxxxxxxxxxxxxxxx
mimi> set_feishu_secret xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
mimi> restart
```

### 7. Verify

After restart, you should see in the serial monitor:

```
I (xxxx) feishu: Feishu credentials loaded (app_id=cli_xxxx...)
I (xxxx) feishu: Connecting to Feishu WebSocket...
I (xxxx) feishu: WebSocket connected to Feishu
```

Send a message to your bot in Feishu — MimiClaw will reply!

### Chat ID Format

| Format | Type | Example |
|--------|------|---------|
| `ou_*` | User (1-on-1 chat) | `ou_abc123def456` |
| `oc_*` | Group chat | `oc_xyz789ghi012` |

### Troubleshooting

- **"No Feishu credentials"** — Set App ID and App Secret via CLI or mimi_secrets.h
- **WebSocket won't connect** — Check that event subscription mode is "Long Connection", not "HTTP callback"
- **Bot doesn't respond in group** — Make sure the bot is added to the group and has `im:message` permission
- **"Token API error"** — Verify App ID and App Secret are correct; check that the app is published

---

## 中文

MimiClaw 支持[飞书](https://www.feishu.cn/)作为消息通道。使用 **WebSocket 长连接** — 不需要公网 IP 或 webhook 服务器。只需配置飞书应用凭证，MimiClaw 就会直接连接飞书的事件网关。

### 1. 创建飞书应用

1. 前往[飞书开放平台](https://open.feishu.cn/app)，创建一个新应用
2. 在**凭证与基础信息**中，复制 **App ID** 和 **App Secret**

### 2. 启用机器人能力

1. 进入**添加应用能力** → 启用**机器人**
2. 设置机器人名称和头像

### 3. 添加权限

进入**权限管理**，添加以下权限：

| 权限 | 说明 |
|-----|------|
| `im:message` | 发送消息 |
| `im:message.receive_v1` | 接收消息 |

### 4. 启用事件订阅（长连接）

1. 进入**事件订阅**
2. 订阅方式选择**长连接**（WebSocket）
3. 添加事件：`im.message.receive_v1`（接收消息）

> **重要：** 必须选择**长连接**模式，不是 HTTP 回调。这样 MimiClaw 不需要公网 IP 就能接收事件。

### 5. 发布应用

1. 进入**版本管理与发布** → **创建版本**
2. 填写版本信息并提交审核
3. 自建应用在自己组织内通常会即时通过

### 6. 配置 MimiClaw

**方式 A：编译时** — 编辑 `main/mimi_secrets.h`：

```c
#define MIMI_SECRET_FEISHU_APP_ID     "cli_xxxxxxxxxxxxxxxx"
#define MIMI_SECRET_FEISHU_APP_SECRET "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
```

然后重新编译：`idf.py fullclean && idf.py build`

**方式 B：运行时** — 通过串口 CLI（无需重新编译）：

```
mimi> set_feishu_id cli_xxxxxxxxxxxxxxxx
mimi> set_feishu_secret xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
mimi> restart
```

### 7. 验证

重启后，串口监控应显示：

```
I (xxxx) feishu: Feishu credentials loaded (app_id=cli_xxxx...)
I (xxxx) feishu: Connecting to Feishu WebSocket...
I (xxxx) feishu: WebSocket connected to Feishu
```

在飞书给你的机器人发一条消息 — MimiClaw 会回复！

### Chat ID 格式

| 格式 | 类型 | 示例 |
|------|------|------|
| `ou_*` | 用户（单聊） | `ou_abc123def456` |
| `oc_*` | 群聊 | `oc_xyz789ghi012` |

### 常见问题

- **"No Feishu credentials"** — 通过 CLI 或 mimi_secrets.h 设置 App ID 和 App Secret
- **WebSocket 连接不上** — 检查事件订阅方式是否为「长连接」，而不是「HTTP 回调」
- **群里机器人不回复** — 确保机器人已加入群组，并且有 `im:message` 权限
- **"Token API error"** — 检查 App ID 和 App Secret 是否正确，应用是否已发布
