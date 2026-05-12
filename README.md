# InsetFace

这是从官方 Metasequoia SDK 工程中拆出来的独立插件仓库，只保留 `InsetFace` 插件本身，以及它当前编译实际需要的 SDK 基础文件。

## 目录结构

- `plugin/`：你的插件源码、资源文件
- `vendor/mqsdk/`：从官方 SDK 提取的最小依赖子集
- `InsetFace.sln` / `InsetFace.vcxproj`：独立的 Visual Studio 工程

## 当前整理原则

- 不再保留其他官方示例插件目录
- 不提交 `.vs`、`.user`、`build/`、`x64/`、`Debug/`、`Release/` 等本地或编译产物
- 插件资源不再依赖外部示例目录

## 构建

使用 Visual Studio 2022 打开 `InsetFace.sln`，选择 `x64` + `Debug` 或 `Release` 构建即可。

## 初始化 Git

```powershell
cd D:\myfiles\coding\cpp\mqsdk485\mqsdk\InsetFaceRepo
git init
git add .
git commit -m "Initial standalone InsetFace plugin"
```

## 关于官方 SDK 文件

`vendor/mqsdk/` 中的文件来自官方 Metasequoia SDK。公开发布前，建议你再确认一下官方 SDK 的再分发许可和署名要求。
