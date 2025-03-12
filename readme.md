# 酒店管理系统

## 项目简介

酒店管理系统是一个基于MFC框架的Windows应用程序，用于管理酒店的日常运营，包括客房预订、客户管理、房间展示等功能。

## 项目结构

```
酒店管理系统/
├── 测试.cpp
├── 酒店管理系统.cpp
├── 酒店管理系统.h
├── 酒店管理系统.vcxproj
├── 酒店管理系统.vcxproj.filters
├── 酒店管理系统Doc.cpp
├── 酒店管理系统Doc.h
├── 酒店管理系统View.cpp
├── 酒店管理系统View.h
├── CDisplayView.cpp
├── CDisplayView.h
├── CGuest.cpp
├── CGuest.h
├── CLoginDlg.cpp
├── CLoginDlg.h
├── ConnectDB.cpp
├── ConnectDB.h
├── COrderRoom.cpp
├── COrderRoom.h
├── CSelectView.cpp
├── CSelectView.h
├── CShowRoom.cpp
├── CShowRoom.h
├── CUserDlg.cpp
├── CUserDlg.h
├── framework.h
├── libmysql.dll
├── MainFrm.cpp
├── MainFrm.h
├── My.rc
├── pch.cpp
├── pch.h
├── res/
│   └── ...
├── 酒店管理系统.sln
└── libmysql.dll
```

## 主要功能

- **客户管理**：管理客户信息，包括新增、修改和删除客户。
- **房间预订**：提供房间预订功能，支持查看房间状态和预订记录。
- **房间展示**：展示酒店房间信息，包括房间类型、价格和状态等。
- **登录系统**：提供用户登录功能，确保系统安全。

## 环境配置

1. 安装 [Visual Studio](https://visualstudio.microsoft.com/)。
2. 安装 MySQL 数据库，并配置相关环境变量。
3. 将 `libmysql.dll` 复制到项目根目录。

## 编译与运行

1. 打开 `酒店管理系统.sln` 解决方案文件。
2. 选择 `Debug` 或 `Release` 模式。
3. 点击“生成”菜单，选择“生成解决方案”。
4. 生成成功后，点击“调试”菜单，选择“开始调试”或“开始执行（不调试）”。

## 贡献

欢迎提交问题（Issues）和合并请求（Pull Requests）来改进本项目。

## 许可证

本项目采用 MIT 许可证，详情请参阅 [LICENSE](LICENSE) 文件。