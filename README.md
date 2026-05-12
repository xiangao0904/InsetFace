# InsetFace

`InsetFace` 是一个面向 Metasequoia 4 的独立插件，提供交互式面内插功能，并附带一个可视化安装器。


## 功能概览

- 支持 `Region` 和 `Individual` 两种 inset 模式
- 支持 `Thickness` 和 `Depth` 两个主要几何参数
- 支持 `Offset Even`（均等偏移）开关
- 支持中文、日文、英文三种界面文本
- 提供独立 Windows 安装器
- 支持预览、拖拽调节、应用、取消和撤销

## 仓库结构

- `plugin/`
  插件本体源码、资源和多语言文件
- `installer/`
  Windows 安装器源码和资源
- `vendor/mqsdk/`
  从官方 SDK 提取出的最小依赖
- `InsetFace.sln`
  Visual Studio 解决方案
- `InsetFace.vcxproj`
  插件工程
- `InsetFaceInstaller.vcxproj`
  安装器工程

## 构建环境

- Visual Studio 2022
- 平台：`x64`
- Windows SDK：与当前 VS 安装匹配的版本

## 构建方法

在 Visual Studio 中打开 `InsetFace.sln` 选择 `x64` 和 `Debug` 或 `Release` 后直接构建。

默认主要产物：

- 插件：`build/x64/<Config>/InsetFace.dll`
- 语言资源：`build/x64/<Config>/InsetFace.resource.xml`
- 安装器：`build/x64/<Config>/InsetFaceInstaller.exe`

## 安装方式

推荐方式是直接运行安装器：

- [InsetFaceInstaller.exe](D:\myfiles\coding\cpp\mqsdk485\mqsdk\InsetFaceRepo\build\x64\Release\InsetFaceInstaller.exe)

安装器会负责：

- 复制 `InsetFace.dll`
- 部署 `InsetFace.resource.xml`
- 部署白/黑主题图标
- 修改 Metasequoia 布局文件
- 写入安装 manifest，供修复和卸载使用

如果你只是调试插件本体，也可以手动把以下文件复制到 Metasequoia 插件目录：

- `InsetFace.dll`
- `InsetFace.resource.xml`
- `cmd_insetface.svg` 白色版
- `cmd_insetface.svg` 黑色版

## 使用说明

1. 在 Metasequoia 中启动 `InsetFace`
2. 选择一个或多个面
3. 选择模式：
   `Region`：把连通面片作为一个整体处理
   `Individual`：每个面单独 inset
4. 调整参数：
   `Thickness`：控制内插厚度
   `Depth`：控制法线方向上的抬升或压入
   `Offset Even`：开启后优先按真实边距解释厚度
5. 预览结果
6. 点击 `Apply` 提交，或点击 `Cancel` 取消

也支持直接在视图中拖拽，快速调整 `Thickness`。

## 多语言

插件文本由 `InsetFace.resource.xml` 提供，当前支持：

- Japanese
- English
- Chinese

语言选择会读取 Metasequoia 当前语言设置


