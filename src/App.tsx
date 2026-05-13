import React, { useMemo, useState } from "react";
import { motion } from "framer-motion";
import { Button } from "@/components/ui/button";
import { Card, CardContent } from "@/components/ui/card";

const REPO_URL = "https://github.com/xiangao0904/InsetFace";
const INSTALLER_URL =
  "https://github.com/xiangao0904/InsetFace/releases/download/v1.0.0/InsetFaceInstaller.exe";
const DEMO_VIDEO_URL = "/demo.mp4";
const BLOG_URL = "https://blog.huliawsl.top/posts/insetface";

const LOCALES = ["en", "zh", "ja"] as const;
type Locale = (typeof LOCALES)[number];

type IconName =
  | "download"
  | "github"
  | "layers"
  | "sliders"
  | "cursor"
  | "languages"
  | "package"
  | "shield"
  | "sparkles"
  | "box"
  | "arrowRight"
  | "check"
  | "play"
  | "book";

type IconProps = { name: IconName; className?: string };

type Copy = {
  navFeatures: string;
  navInstall: string;
  navVideo: string;
  navBlog: string;
  badge: string;
  title: string;
  subtitle: string;
  download: string;
  source: string;
  modes: string;
  languages: string;
  installer: string;
  featuresLabel: string;
  featuresTitle: string;
  featuresSubtitle: string;
  featureRegionTitle: string;
  featureRegionText: string;
  featureControlTitle: string;
  featureControlText: string;
  featureOffsetTitle: string;
  featureOffsetText: string;
  demoLabel: string;
  demoTitle: string;
  demoText: string;
  demoPlaceholder: string;
  demoHint: string;
  workflowLabel: string;
  workflowTitle: string;
  viewportTitle: string;
  viewportText: string;
  safetyTitle: string;
  safetyText: string;
  siteLangTitle: string;
  siteLangText: string;
  installTitle: string;
  installText: string;
  step1: string;
  step2: string;
  step3: string;
  step4: string;
  step5: string;
  ctaTitle: string;
  ctaText: string;
  ctaButton: string;
  footerLang: string;
  dragLabel: string;
  apply: string;
  livePreview: string;
  blogLabel: string;
  blogTitle: string;
  blogText: string;
  blogCardTitle: string;
  blogCardText: string;
  blogButton: string;
};

function BrandMark({ className = "h-6 w-6" }: { className?: string }) {
  return (
    <svg
      viewBox="0 0 512 512"
      className={className}
      aria-hidden="true"
      fill="none"
    >
      <rect
        x="80"
        y="80"
        width="352"
        height="352"
        fill="#E6E6E6"
        stroke="#0f172a"
        strokeWidth="24"
        strokeLinejoin="round"
      />
      <rect
        x="151"
        y="151"
        width="211"
        height="211"
        fill="#FD9EA2"
        stroke="#0f172a"
        strokeWidth="24"
        strokeLinejoin="round"
      />
      <path
        d="M96 96L151 151"
        stroke="#0f172a"
        strokeWidth="24"
        strokeLinecap="round"
      />
      <path
        d="M96 416L151 361"
        stroke="#0f172a"
        strokeWidth="24"
        strokeLinecap="round"
      />
      <path
        d="M416 96L361 151"
        stroke="#0f172a"
        strokeWidth="24"
        strokeLinecap="round"
      />
      <path
        d="M416 416L361 361"
        stroke="#0f172a"
        strokeWidth="24"
        strokeLinecap="round"
      />
      <circle cx="80" cy="80" r="25" fill="#E6E6E6" stroke="#0f172a" strokeWidth="20" />
      <circle cx="80" cy="432" r="25" fill="#E6E6E6" stroke="#0f172a" strokeWidth="20" />
      <circle cx="432" cy="80" r="25" fill="#E6E6E6" stroke="#0f172a" strokeWidth="20" />
      <circle cx="432" cy="432" r="25" fill="#E6E6E6" stroke="#0f172a" strokeWidth="20" />
      <circle cx="151" cy="151" r="25" fill="#FD9EA2" stroke="#0f172a" strokeWidth="20" />
      <circle cx="151" cy="362" r="25" fill="#FD9EA2" stroke="#0f172a" strokeWidth="20" />
      <circle cx="362" cy="151" r="25" fill="#FD9EA2" stroke="#0f172a" strokeWidth="20" />
      <circle cx="362" cy="362" r="25" fill="#FD9EA2" stroke="#0f172a" strokeWidth="20" />
    </svg>
  );
}

function Icon({ name, className = "h-5 w-5" }: IconProps) {
  if (name === "github") {
    return (
      <svg
        viewBox="0 0 24 24"
        className={className}
        aria-hidden="true"
        fill="currentColor"
      >
        <path d="M12 .5C5.73.5.75 5.6.75 12.02c0 5.1 3.29 9.43 7.86 10.96.58.11.79-.25.79-.57v-2.02c-3.2.71-3.87-1.42-3.87-1.42-.52-1.36-1.28-1.72-1.28-1.72-1.05-.74.08-.73.08-.73 1.16.08 1.77 1.22 1.77 1.22 1.03 1.8 2.71 1.28 3.37.98.1-.76.4-1.28.73-1.58-2.55-.3-5.23-1.31-5.23-5.82 0-1.29.45-2.34 1.19-3.16-.12-.3-.52-1.5.11-3.12 0 0 .97-.32 3.18 1.21a10.7 10.7 0 0 1 5.8 0c2.2-1.53 3.17-1.21 3.17-1.21.63 1.62.23 2.82.11 3.12.74.82 1.19 1.87 1.19 3.16 0 4.52-2.69 5.52-5.25 5.81.42.37.78 1.1.78 2.22v3.29c0 .32.21.69.8.57a11.52 11.52 0 0 0 7.85-10.95C23.25 5.6 18.27.5 12 .5Z" />
      </svg>
    );
  }
  const common = {
    fill: "none",
    stroke: "currentColor",
    strokeWidth: 2,
    strokeLinecap: "round" as const,
    strokeLinejoin: "round" as const,
  };
  const paths: Record<IconName, React.ReactNode> = {
    download: (
      <>
        <path d="M12 3v12" />
        <path d="m7 10 5 5 5-5" />
        <path d="M5 21h14" />
      </>
    ),
    github: null,
    layers: (
      <>
        <path d="m12 3 9 5-9 5-9-5 9-5Z" />
        <path d="m3 12 9 5 9-5" />
        <path d="m3 16 9 5 9-5" />
      </>
    ),
    sliders: (
      <>
        <path d="M4 6h10" />
        <path d="M18 6h2" />
        <circle cx="16" cy="6" r="2" />
        <path d="M4 12h2" />
        <path d="M10 12h10" />
        <circle cx="8" cy="12" r="2" />
        <path d="M4 18h8" />
        <path d="M16 18h4" />
        <circle cx="14" cy="18" r="2" />
      </>
    ),
    cursor: (
      <>
        <path d="M4 3 18 14l-6 1.2L9.3 21 4 3Z" />
        <path d="m13 15 5 5" />
      </>
    ),
    languages: (
      <>
        <path d="m5 8 6 6" />
        <path d="m4 14 6-6 2-3" />
        <path d="M2 5h12" />
        <path d="M7 2h1" />
        <path d="m22 22-5-10-5 10" />
        <path d="M14 18h6" />
      </>
    ),
    package: (
      <>
        <path d="m3 7 9 5 9-5" />
        <path d="M12 22V12" />
        <path d="M21 7v10l-9 5-9-5V7l9-5 9 5Z" />
        <path d="m9 12 2 2 4-4" />
      </>
    ),
    shield: (
      <>
        <path d="M12 22s8-4 8-10V5l-8-3-8 3v7c0 6 8 10 8 10Z" />
        <path d="m9 12 2 2 4-5" />
      </>
    ),
    sparkles: (
      <>
        <path d="M12 3 14 9l6 2-6 2-2 6-2-6-6-2 6-2 2-6Z" />
        <path d="M19 3v4" />
        <path d="M21 5h-4" />
        <path d="M5 17v4" />
        <path d="M7 19H3" />
      </>
    ),
    box: (
      <>
        <path d="m21 8-9-5-9 5 9 5 9-5Z" />
        <path d="M3 8v8l9 5 9-5V8" />
        <path d="M12 13v8" />
      </>
    ),
    arrowRight: (
      <>
        <path d="M5 12h14" />
        <path d="m12 5 7 7-7 7" />
      </>
    ),
    check: (
      <>
        <circle cx="12" cy="12" r="10" />
        <path d="m9 12 2 2 4-4" />
      </>
    ),
    play: <path d="M5 3v18l16-9L5 3Z" />,
    book: (
      <>
        <path d="M4 19.5A2.5 2.5 0 0 1 6.5 17H20" />
        <path d="M4 4.5A2.5 2.5 0 0 1 6.5 2H20v20H6.5A2.5 2.5 0 0 1 4 19.5v-15Z" />
        <path d="M8 7h8" />
        <path d="M8 11h6" />
      </>
    ),
  };
  return (
    <svg
      viewBox="0 0 24 24"
      className={className}
      aria-hidden="true"
      {...common}
    >
      {paths[name]}
    </svg>
  );
}

const copy: Record<Locale, Copy> = {
  zh: {
    navFeatures: "Features",
    navInstall: "Installation",
    navVideo: "Demo",
    navBlog: "Blog",
    badge: "Interactive inset face plugin for Metasequoia 4",
    title: "Metasequoia 4 的交互式内插面插件",
    subtitle:
      "InsetFace 让面内插变成可视化、可拖拽、可预览的建模动作。支持整体区域内插、独立面内插、厚度/深度控制和等距偏移，适合硬表面、低模与细节结构建模。",
    download: "下载安装程序",
    source: "查看 GitHub 源码",
    modes: "Inset Modes",
    languages: "Languages",
    installer: "Installer",
    featuresLabel: "Core Features",
    featuresTitle: "把常用内插操作压缩成一次流畅交互",
    featuresSubtitle:
      "面向实际建模流程设计：少点菜单、少手工修边，多实时反馈。",
    featureRegionTitle: "Region vs Individual",
    featureRegionText:
      "按区域整体生成内插面，或让每个面独立内插。多面建模时不用反复切换工具。",
    featureControlTitle: "Thickness / Depth 精确控制",
    featureControlText:
      "厚度控制边距，深度控制沿法线方向的凸起或凹陷；既能数值输入，也能在视口交互拖拽。",
    featureOffsetTitle: "Offset Even 等距偏移",
    featureOffsetText:
      "针对不规则多边形优化边距观感，减少窄角、斜边导致的视觉不均匀。",
    demoLabel: "Demo Video",
    demoTitle: "实际演示视频",
    demoText:
      "观看 InsetFace 的实际操作流程：拖拽 Thickness、切换 Region / Individual，并应用 Offset Even。",
    demoPlaceholder: "Demo video placeholder",
    demoHint:
      "将 DEMO_VIDEO_URL 替换为你的 .mp4 / .webm 地址即可自动显示视频。",
    workflowLabel: "Why it feels fast",
    workflowTitle: "实时预览，拖拽即建模",
    viewportTitle: "Viewport Drag",
    viewportText: "直接在视口拖动快速调整 Thickness。",
    safetyTitle: "Apply / Cancel / Undo",
    safetyText: "结果可预览，提交和撤销边界清晰。",
    siteLangTitle: "Multilingual Site",
    siteLangText: "站点和插件说明支持中文、English、日本語切换。",
    installTitle: "一键安装，无需手动拖拽 DLL",
    installText:
      "推荐使用 Windows 可视化安装程序。它会自动部署插件 DLL、资源文件、明暗主题图标，并写入布局集成信息；后续修复或卸载也更可靠。",
    step1: "下载 Windows 可视化安装程序 InsetFaceInstaller.exe。",
    step2:
      "运行安装程序，自动复制 DLL、资源文件与图标，并集成到 Metasequoia 4 布局。",
    step3: "打开 Metasequoia 4，在工具面板启动 InsetFace。",
    step4:
      "选择面，切换 Region / Individual，调整 Thickness、Depth 和 Offset Even。",
    step5: "实时预览结果；满意后点击 Apply，不满意则 Cancel。",
    ctaTitle: "准备把 InsetFace 加到你的建模工具箱？",
    ctaText:
      "下载 Windows 安装程序，在 Metasequoia 4 中获得交互式内插面工作流。",
    ctaButton: "立即下载",
    footerLang: "站点与插件支持中文、English、日本語。",
    dragLabel: "Drag to adjust",
    apply: "Apply Inset",
    livePreview: "Live Preview",
    blogLabel: "Technical Blog",
    blogTitle: "算法解析文章",
    blogText:
      "这篇博客详细介绍 InsetFace 的内插面算法、Offset Even 的几何处理、交互式预览的数据流，以及插件实现细节。",
    blogCardTitle: "InsetFace Algorithm Notes",
    blogCardText:
      "详细记录了 Inset Face 插件的算法工程化方案实现。",
    blogButton: "阅读文章",
  },
  en: {
    navFeatures: "Features",
    navInstall: "Installation",
    navVideo: "Demo",
    navBlog: "Blog",
    badge: "Interactive inset face plugin for Metasequoia 4",
    title: "Interactive Inset Face Plugin for Metasequoia 4",
    subtitle:
      "InsetFace turns inset modeling into a visual, draggable, preview-first workflow. It supports region inset, individual face inset, thickness/depth controls, and even offset for clean hard-surface modeling.",
    download: "Download Installer",
    source: "View GitHub Source",
    modes: "Inset Modes",
    languages: "Languages",
    installer: "Installer",
    featuresLabel: "Core Features",
    featuresTitle:
      "Compress common inset operations into one fluid interaction",
    featuresSubtitle:
      "Designed for real modeling workflows: fewer menus, less manual cleanup, more immediate feedback.",
    featureRegionTitle: "Region vs Individual",
    featureRegionText:
      "Inset connected regions as a whole, or inset each selected face independently without switching tools repeatedly.",
    featureControlTitle: "Precise Thickness / Depth Control",
    featureControlText:
      "Control margin with Thickness and normal-direction extrusion with Depth, using numeric input or direct viewport dragging.",
    featureOffsetTitle: "Offset Even",
    featureOffsetText:
      "Improves visual margin consistency on irregular polygons and reduces uneven results around narrow angles and skewed edges.",
    demoLabel: "Demo Video",
    demoTitle: "Real demo video",
    demoText:
      "Watch the real InsetFace workflow: drag Thickness, switch Region / Individual, and apply Offset Even.",
    demoPlaceholder: "Demo video placeholder",
    demoHint:
      "Replace DEMO_VIDEO_URL with your .mp4 / .webm URL to display the real video automatically.",
    workflowLabel: "Why it feels fast",
    workflowTitle: "Live preview, drag-driven modeling",
    viewportTitle: "Viewport Drag",
    viewportText: "Adjust Thickness directly in the viewport by dragging.",
    safetyTitle: "Apply / Cancel / Undo",
    safetyText:
      "Preview first, then apply or cancel with a clear editing boundary.",
    siteLangTitle: "Multilingual Site",
    siteLangText:
      "The site and plugin description can switch between Chinese, English, and Japanese.",
    installTitle: "One-click installation. No manual DLL dragging.",
    installText:
      "Use the Windows visual installer. It deploys the plugin DLL, resources, light/dark icons, and layout integration automatically, making updates and uninstalling more reliable.",
    step1: "Download the Windows visual installer: InsetFaceInstaller.exe.",
    step2:
      "Run the installer to copy the DLL, resources, icons, and Metasequoia 4 layout integration files automatically.",
    step3: "Open Metasequoia 4 and launch InsetFace from the tool panel.",
    step4:
      "Select faces, switch Region / Individual, then adjust Thickness, Depth, and Offset Even.",
    step5:
      "Preview the result live; click Apply when satisfied or Cancel to discard it.",
    ctaTitle: "Ready to add InsetFace to your modeling toolkit?",
    ctaText:
      "Download the Windows installer and get an interactive inset face workflow in Metasequoia 4.",
    ctaButton: "Download Now",
    footerLang: "Site and plugin support Chinese, English, and Japanese.",
    dragLabel: "Drag to adjust",
    apply: "Apply Inset",
    livePreview: "Live Preview",
    blogLabel: "Technical Blog",
    blogTitle: "Reserved section for algorithm analysis",
    blogText:
      "Use this area to link to your personal blog later, covering the inset algorithm, Offset Even geometry handling, live-preview data flow, and plugin implementation details.",
    blogCardTitle: "InsetFace Algorithm Notes",
    blogCardText:
      "Planned article: selected-face topology, boundary offsetting, depth projection, and Metasequoia 4 plugin integration.",
    blogButton: "Blog Link Placeholder",
  },
  ja: {
    navFeatures: "Features",
    navInstall: "Installation",
    navVideo: "Demo",
    navBlog: "Blog",
    badge: "Metasequoia 4 向けインタラクティブ面差し込みプラグイン",
    title: "Metasequoia 4 のインタラクティブ面差し込みプラグイン",
    subtitle:
      "InsetFace は、面の差し込み操作を視覚的でドラッグ可能なプレビュー中心のワークフローにします。Region、Individual、Thickness / Depth、Offset Even に対応しています。",
    download: "インストーラーをダウンロード",
    source: "GitHub ソースを見る",
    modes: "Inset Modes",
    languages: "Languages",
    installer: "Installer",
    featuresLabel: "Core Features",
    featuresTitle: "よく使う差し込み操作を一つの滑らかな操作へ",
    featuresSubtitle:
      "実際のモデリング作業向けに設計。メニュー操作を減らし、手作業の修正を抑え、すばやく確認できます。",
    featureRegionTitle: "Region vs Individual",
    featureRegionText:
      "接続された領域をまとめて差し込むか、選択面をそれぞれ独立して差し込むかを選べます。",
    featureControlTitle: "Thickness / Depth の精密制御",
    featureControlText:
      "Thickness で余白、Depth で法線方向の押し出しを制御。数値入力とビューポート上のドラッグに対応します。",
    featureOffsetTitle: "Offset Even",
    featureOffsetText:
      "不規則な多角形での見た目の余白を整え、狭い角や斜めの辺による不均一さを軽減します。",
    demoLabel: "Demo Video",
    demoTitle: "実際のデモ動画",
    demoText:
      "InsetFace の実際の操作フロー：Thickness のドラッグ、Region / Individual の切替、Offset Even の適用を確認できます。",
    demoPlaceholder: "Demo video placeholder",
    demoHint:
      "DEMO_VIDEO_URL を .mp4 / .webm の URL に置き換えると、動画が自動表示されます。",
    workflowLabel: "Why it feels fast",
    workflowTitle: "ライブプレビュー、ドラッグ中心のモデリング",
    viewportTitle: "Viewport Drag",
    viewportText: "ビューポート上で直接ドラッグして Thickness を調整できます。",
    safetyTitle: "Apply / Cancel / Undo",
    safetyText: "結果をプレビューしてから Apply または Cancel できます。",
    siteLangTitle: "Multilingual Site",
    siteLangText:
      "サイトとプラグイン説明は中文、English、日本語で切り替えられます。",
    installTitle: "ワンクリックインストール。DLL の手動配置は不要。",
    installText:
      "Windows 用のビジュアルインストーラーを推奨します。DLL、リソース、明暗テーマ用アイコン、レイアウト統合を自動で配置します。",
    step1:
      "Windows 用ビジュアルインストーラー InsetFaceInstaller.exe をダウンロードします。",
    step2:
      "インストーラーを実行し、DLL、リソース、アイコン、Metasequoia 4 への統合ファイルを自動配置します。",
    step3: "Metasequoia 4 を開き、ツールパネルから InsetFace を起動します。",
    step4:
      "面を選択し、Region / Individual を切り替え、Thickness、Depth、Offset Even を調整します。",
    step5:
      "結果をリアルタイムで確認し、問題なければ Apply、破棄する場合は Cancel を押します。",
    ctaTitle: "InsetFace をモデリング環境に追加しますか？",
    ctaText:
      "Windows インストーラーをダウンロードして、Metasequoia 4 でインタラクティブな面差し込みワークフローを使えます。",
    ctaButton: "今すぐダウンロード",
    footerLang: "サイトとプラグインは中文、English、日本語に対応しています。",
    dragLabel: "Drag to adjust",
    apply: "Apply Inset",
    livePreview: "Live Preview",
    blogLabel: "Technical Blog",
    blogTitle: "アルゴリズム解説記事用の予約エリア",
    blogText:
      "後で個人ブログへのリンクを配置し、面差し込みアルゴリズム、Offset Even の幾何処理、ライブプレビューのデータフロー、プラグイン実装の詳細を紹介できます。",
    blogCardTitle: "InsetFace Algorithm Notes",
    blogCardText:
      "予定記事：選択面トポロジー、境界オフセット、深度投影、Metasequoia 4 プラグイン統合。",
    blogButton: "Blog リンク予約",
  },
};

const fadeUp = { hidden: { opacity: 0, y: 20 }, visible: { opacity: 1, y: 0 } };
type Feature = {
  icon: IconName;
  title: string;
  text: string;
  diagram: "region" | "individual" | "offset";
};
type FastPoint = { icon: IconName; title: string; text: string };

function MeshPreview({ t }: { t: Copy }) {
  return (
    <div className="relative overflow-hidden rounded-lg border border-blue-100 bg-white p-3 shadow-xl shadow-blue-100/70">
      <div className="rounded-md border border-slate-200 bg-slate-50 p-4">
        <div className="mb-4 flex items-center justify-between">
          <div className="flex gap-2" aria-hidden="true">
            <span className="h-3 w-3 bg-slate-300" />
            <span className="h-3 w-3 bg-slate-300" />
            <span className="h-3 w-3 bg-blue-500" />
          </div>
          <span className="border border-blue-200 bg-blue-50 px-3 py-1 text-xs font-medium text-blue-700">
            {t.livePreview}
          </span>
        </div>
        <div className="grid gap-4 md:grid-cols-[1.1fr_.9fr]">
          <div className="relative aspect-[4/3] overflow-hidden rounded-md border border-slate-200 bg-white">
            <div className="absolute inset-0 bg-[linear-gradient(rgba(148,163,184,.14)_1px,transparent_1px),linear-gradient(90deg,rgba(148,163,184,.14)_1px,transparent_1px)] bg-[size:28px_28px]" />
            <svg
              viewBox="0 0 420 320"
              className="absolute inset-0 h-full w-full"
              role="img"
              aria-label="Animated inset face preview"
            >
              <defs>
                <linearGradient id="face" x1="0" x2="1" y1="0" y2="1">
                  <stop offset="0%" stopColor="#bfdbfe" stopOpacity="0.9" />
                  <stop offset="100%" stopColor="#dbeafe" stopOpacity="0.9" />
                </linearGradient>
              </defs>
              <polygon
                points="80,82 338,62 360,235 118,270"
                fill="url(#face)"
                stroke="#60a5fa"
                strokeWidth="2"
              />
              <polygon
                points="128,116 305,102 318,210 150,236"
                fill="#ffffff"
                stroke="#2563eb"
                strokeWidth="3"
              />
              <polygon
                points="166,142 274,132 281,190 180,205"
                fill="#eff6ff"
                stroke="#60a5fa"
                strokeWidth="2"
              />
              <line
                x1="80"
                y1="82"
                x2="128"
                y2="116"
                stroke="#94a3b8"
                strokeWidth="1.2"
                opacity="0.65"
              />
              <line
                x1="338"
                y1="62"
                x2="305"
                y2="102"
                stroke="#94a3b8"
                strokeWidth="1.2"
                opacity="0.65"
              />
              <line
                x1="360"
                y1="235"
                x2="318"
                y2="210"
                stroke="#94a3b8"
                strokeWidth="1.2"
                opacity="0.65"
              />
              <line
                x1="118"
                y1="270"
                x2="150"
                y2="236"
                stroke="#94a3b8"
                strokeWidth="1.2"
                opacity="0.65"
              />
              <motion.g
                initial={{ x: -6, y: -4 }}
                animate={{ x: 16, y: 10 }}
                transition={{
                  repeat: Infinity,
                  repeatType: "reverse",
                  duration: 1.7,
                  ease: "easeInOut",
                }}
              >
                <path
                  d="M292 214 L317 270 L297 264 L284 293 L270 287 L283 258 L264 253 Z"
                  fill="#ffffff"
                  stroke="#1e293b"
                  strokeWidth="2"
                />
                <circle cx="293" cy="214" r="9" fill="#3b82f6" opacity="0.25" />
              </motion.g>
            </svg>
            <div className="absolute bottom-4 left-4 rounded-md border border-slate-200 bg-white/90 px-4 py-3 shadow-sm backdrop-blur">
              <p className="text-xs uppercase tracking-[0.22em] text-slate-500">
                {t.dragLabel}
              </p>
              <p className="mt-1 text-sm font-medium text-slate-900">
                Thickness 12.4 / Depth -3.0
              </p>
            </div>
          </div>
          <div className="space-y-3 rounded-md border border-slate-200 bg-white p-4">
            <div>
              <div className="mb-2 flex items-center justify-between text-sm text-slate-600">
                <span>Thickness</span>
                <span>12.4</span>
              </div>
              <div className="h-2 overflow-hidden bg-slate-100">
                <motion.div
                  className="h-full bg-blue-600"
                  initial={{ width: "35%" }}
                  animate={{ width: ["35%", "72%", "52%"] }}
                  transition={{ repeat: Infinity, duration: 3 }}
                />
              </div>
            </div>
            <div>
              <div className="mb-2 flex items-center justify-between text-sm text-slate-600">
                <span>Depth</span>
                <span>-3.0</span>
              </div>
              <div className="h-2 overflow-hidden bg-slate-100">
                <motion.div
                  className="h-full bg-sky-400"
                  initial={{ width: "42%" }}
                  animate={{ width: ["42%", "28%", "64%"] }}
                  transition={{ repeat: Infinity, duration: 3.4 }}
                />
              </div>
            </div>
            <div className="grid grid-cols-2 gap-3 pt-2">
              <div className="rounded-md border border-slate-200 bg-slate-50 p-3">
                <p className="text-xs text-slate-500">Mode</p>
                <p className="mt-1 font-semibold text-slate-900">Region</p>
              </div>
              <div className="rounded-md border border-blue-100 bg-blue-50 p-3">
                <p className="text-xs text-slate-500">Offset Even</p>
                <p className="mt-1 font-semibold text-blue-700">Enabled</p>
              </div>
            </div>
            <Button className="mt-2 w-full rounded-md bg-blue-600 text-white hover:bg-blue-700">
              {t.apply}
            </Button>
          </div>
        </div>
      </div>
    </div>
  );
}

function DemoVideoSlot({ t }: { t: Copy }) {
  return (
    <section id="demo" className="scroll-mt-24 mx-auto max-w-6xl px-4 py-20">
      <div className="mb-10 max-w-3xl">
        <p className="text-sm font-semibold uppercase tracking-[0.3em] text-blue-600">
          {t.demoLabel}
        </p>
        <h2 className="mt-4 text-4xl font-bold tracking-tight text-slate-950 md:text-5xl">
          {t.demoTitle}
        </h2>
        <p className="mt-5 text-lg leading-8 text-slate-600">{t.demoText}</p>
      </div>

      <div className="rounded-lg border border-slate-200 bg-white p-3 shadow-sm">
        <video
          className="aspect-[2558/1378] w-full rounded-md bg-slate-100 object-cover"
          src={DEMO_VIDEO_URL}
          controls
          playsInline
          autoPlay
          muted
          loop
          preload="auto"
        />
      </div>
    </section>
  );
}

function BlogSlot({ t }: { t: Copy }) {
  const button = (
    <Button
      variant="outline"
      className="mt-6 rounded-md border-slate-200 bg-white text-slate-700 hover:bg-blue-50 hover:text-blue-700"
    >
      {t.blogButton}
      <Icon name="arrowRight" className="ml-2 h-4 w-4" />
    </Button>
  );
  return (
    <section
      id="blog"
      className="scroll-mt-24 border-y border-slate-200 bg-white"
    >
      <div className="mx-auto grid max-w-6xl gap-10 px-4 py-20 lg:grid-cols-[0.9fr_1.1fr]">
        <div>
          <p className="text-sm font-semibold uppercase tracking-[0.3em] text-blue-600">
            {t.blogLabel}
          </p>
          <h2 className="mt-4 text-4xl font-bold tracking-tight text-slate-950 md:text-5xl">
            {t.blogTitle}
          </h2>
          <p className="mt-5 text-lg leading-8 text-slate-600">{t.blogText}</p>
        </div>
        <div className="rounded-lg border border-blue-100 bg-blue-50 p-6 shadow-sm">
          <div className="rounded-md border border-slate-200 bg-white p-6">
            <div className="mb-5 flex h-12 w-12 items-center justify-center rounded-md border border-blue-100 bg-blue-50 text-blue-600">
              <Icon name="book" className="h-6 w-6" />
            </div>
            <h3 className="text-2xl font-semibold tracking-tight text-slate-950">
              {t.blogCardTitle}
            </h3>
            <p className="mt-4 leading-7 text-slate-600">{t.blogCardText}</p>
            {BLOG_URL ? (
              <a href={BLOG_URL} target="_blank" rel="noreferrer">
                {button}
              </a>
            ) : (
              button
            )}
          </div>
        </div>
      </div>
    </section>
  );
}

function MiniDiagram({ type }: { type: "region" | "individual" | "offset" }) {
  if (type === "region")
    return (
      <svg
        viewBox="0 0 220 120"
        className="h-28 w-full"
        role="img"
        aria-label="Region inset diagram"
      >
        <rect
          x="20"
          y="25"
          width="80"
          height="70"
          rx="2"
          fill="#f8fafc"
          stroke="#3b82f6"
        />
        <rect
          x="120"
          y="25"
          width="80"
          height="70"
          rx="2"
          fill="#f8fafc"
          stroke="#3b82f6"
        />
        <path
          d="M36 42H184V78H36Z"
          fill="#dbeafe"
          stroke="#60a5fa"
          strokeWidth="2"
        />
        <path
          d="M56 53H164V69H56Z"
          fill="none"
          stroke="#1d4ed8"
          strokeWidth="2"
          strokeDasharray="4 4"
        />
      </svg>
    );
  if (type === "individual")
    return (
      <svg
        viewBox="0 0 220 120"
        className="h-28 w-full"
        role="img"
        aria-label="Individual inset diagram"
      >
        <rect
          x="20"
          y="25"
          width="80"
          height="70"
          rx="2"
          fill="#f8fafc"
          stroke="#3b82f6"
        />
        <rect
          x="120"
          y="25"
          width="80"
          height="70"
          rx="2"
          fill="#f8fafc"
          stroke="#3b82f6"
        />
        <rect
          x="38"
          y="43"
          width="44"
          height="34"
          rx="1"
          fill="#dbeafe"
          stroke="#2563eb"
          strokeWidth="2"
        />
        <rect
          x="138"
          y="43"
          width="44"
          height="34"
          rx="1"
          fill="#dbeafe"
          stroke="#2563eb"
          strokeWidth="2"
        />
      </svg>
    );
  return (
    <svg
      viewBox="0 0 220 120"
      className="h-28 w-full"
      role="img"
      aria-label="Offset even diagram"
    >
      <g fill="none" strokeLinecap="round" strokeLinejoin="round">
        <polygon
          points="38,26 188,38 166,92 58,84"
          fill="#f8fafc"
          stroke="#3b82f6"
          strokeWidth="2"
        />
        <polygon
          points="68,45 152,52 142,74 78,69"
          fill="#dbeafe"
          stroke="#2563eb"
          strokeWidth="2"
        />
        <path d="M38 26 L68 45" stroke="#60a5fa" strokeWidth="2" />
        <path d="M188 38 L152 52" stroke="#60a5fa" strokeWidth="2" />
        <path d="M166 92 L142 74" stroke="#60a5fa" strokeWidth="2" />
        <path d="M58 84 L78 69" stroke="#60a5fa" strokeWidth="2" />
      </g>
      <text x="66" y="112" fill="#64748b" fontSize="11">
        uniform visual margin
      </text>
    </svg>
  );
}

function makeFeatures(t: Copy): Feature[] {
  return [
    {
      icon: "layers",
      title: t.featureRegionTitle,
      text: t.featureRegionText,
      diagram: "region",
    },
    {
      icon: "sliders",
      title: t.featureControlTitle,
      text: t.featureControlText,
      diagram: "individual",
    },
    {
      icon: "sparkles",
      title: t.featureOffsetTitle,
      text: t.featureOffsetText,
      diagram: "offset",
    },
  ];
}
function makeFastPoints(t: Copy): FastPoint[] {
  return [
    { icon: "cursor", title: t.viewportTitle, text: t.viewportText },
    { icon: "shield", title: t.safetyTitle, text: t.safetyText },
    { icon: "languages", title: t.siteLangTitle, text: t.siteLangText },
  ];
}
function makeSteps(t: Copy) {
  return [t.step1, t.step2, t.step3, t.step4, t.step5];
}
function scrollToSection(id: string) {
  const target = document.getElementById(id);
  if (!target) return;
  const navOffset = 80;
  const top = target.getBoundingClientRect().top + window.scrollY - navOffset;
  window.scrollTo({ top, behavior: "smooth" });
}

function runSmokeTests() {
  const failures: string[] = [];
  const blogFields: Array<keyof Copy> = [
    "blogLabel",
    "blogTitle",
    "blogText",
    "blogCardTitle",
    "blogCardText",
    "blogButton",
  ];
  if (!REPO_URL.includes("github.com/xiangao0904/InsetFace"))
    failures.push("REPO_URL should point to the InsetFace repository.");
  if (!INSTALLER_URL.endsWith("InsetFaceInstaller.exe"))
    failures.push(
      "INSTALLER_URL should point to the Windows installer executable.",
    );
  if (typeof DEMO_VIDEO_URL !== "string")
    failures.push(
      "DEMO_VIDEO_URL should be a string pointing to the real demo video.",
    );
  if (typeof BLOG_URL !== "string" || !BLOG_URL.startsWith("https://"))
    failures.push(
      "BLOG_URL should be a valid https link for the technical blog.",
    );
  for (const locale of LOCALES)
    for (const field of blogFields)
      if (!copy[locale][field] || copy[locale][field].trim().length === 0)
        failures.push(
          `The technical blog placeholder field ${String(field)} should be localized in ${locale}.`,
        );
  const features = makeFeatures(copy.zh);
  const fastPoints = makeFastPoints(copy.zh);
  const steps = makeSteps(copy.zh);
  if (features.length !== 3)
    failures.push(
      "The landing page should render exactly three feature cards.",
    );
  if (!features.some((feature) => feature.title.includes("Region")))
    failures.push("Features should include Region vs Individual.");
  if (!features.some((feature) => feature.title.includes("Thickness")))
    failures.push("Features should include Thickness / Depth control.");
  if (!features.some((feature) => feature.title.includes("Offset Even")))
    failures.push("Features should include Offset Even.");
  if (fastPoints.length !== 3)
    failures.push(
      "The fast workflow section should render three supporting points.",
    );
  if (steps.length < 5)
    failures.push(
      "Installation instructions should include at least five concrete steps.",
    );
  if (failures.length > 0)
    throw new Error(
      `InsetFace landing page smoke tests failed:\n${failures.join("\n")}`,
    );
}
if (import.meta.env.DEV) runSmokeTests();

export default function InsetFaceLandingPage() {
  const [locale, setLocale] = useState<Locale>("en");
  const t = copy[locale];
  const features = useMemo(() => makeFeatures(t), [t]);
  const fastPoints = useMemo(() => makeFastPoints(t), [t]);
  const steps = useMemo(() => makeSteps(t), [t]);
  return (
    <main className="min-h-screen bg-white text-slate-900">
      <nav className="fixed top-0 z-10 w-full border-b border-slate-200 bg-white/85 backdrop-blur">
        <div className="mx-auto flex max-w-6xl items-center justify-between px-4 py-4">
          <a
            href="#"
            className="flex items-center gap-2 text-xl font-bold tracking-wider text-slate-950"
            aria-label="InsetFace home"
          >
            <BrandMark className="h-7 w-7 shrink-0" />
            InsetFace
          </a>
          <div className="hidden items-center gap-6 text-sm font-medium text-slate-700 md:flex">
            <button
              type="button"
              onClick={() => scrollToSection("features")}
              className="transition hover:text-blue-600"
            >
              {t.navFeatures}
            </button>
            <button
              type="button"
              onClick={() => scrollToSection("demo")}
              className="transition hover:text-blue-600"
            >
              {t.navVideo}
            </button>
            {locale === "zh" ? (
              <button
                type="button"
                onClick={() => scrollToSection("blog")}
                className="transition hover:text-blue-600"
              >
                {t.navBlog}
              </button>
            ) : null}
            <button
              type="button"
              onClick={() => scrollToSection("install")}
              className="transition hover:text-blue-600"
            >
              {t.navInstall}
            </button>
            <a
              href={REPO_URL}
              target="_blank"
              rel="noreferrer"
              className="inline-flex items-center gap-1.5 transition hover:text-blue-600"
            >
              <Icon name="github" className="h-4 w-4" />
              GitHub
            </a>
            <div className="flex overflow-hidden rounded-md border border-slate-200 bg-white">
              {LOCALES.map((item) => (
                <button
                  key={item}
                  type="button"
                  onClick={() => setLocale(item)}
                  className={`px-2.5 py-1 text-xs font-semibold transition ${locale === item ? "bg-blue-600 text-white" : "text-slate-600 hover:bg-blue-50 hover:text-blue-700"}`}
                  aria-pressed={locale === item}
                >
                  {item.toUpperCase()}
                </button>
              ))}
            </div>
          </div>
        </div>
      </nav>
      <section className="relative overflow-hidden bg-gradient-to-b from-blue-50 via-white to-white pt-20">
        <div className="absolute inset-x-0 top-0 h-px bg-gradient-to-r from-transparent via-blue-300 to-transparent" />
        <div className="relative mx-auto max-w-6xl px-4 py-20 lg:py-28">
          <div className="grid items-center gap-12 lg:grid-cols-[.95fr_1.05fr]">
            <motion.div
              initial="hidden"
              animate="visible"
              variants={fadeUp}
              transition={{ duration: 0.55 }}
            >
              <div className="mb-6 inline-flex items-center gap-2 rounded-md border border-blue-200 bg-white px-4 py-2 text-sm font-medium text-blue-700 shadow-sm">
                <Icon name="cursor" className="h-4 w-4" />
                {t.badge}
              </div>
              <h1 className="text-5xl font-bold tracking-tight text-slate-950 md:text-6xl lg:text-7xl">
                {t.title}
              </h1>
              <p className="mt-6 max-w-2xl text-lg leading-8 text-slate-600">
                {t.subtitle}
              </p>
              <div className="mt-9 flex flex-col gap-3 sm:flex-row">
                <Button
                  asChild
                  size="lg"
                  className="rounded-md bg-blue-600 px-7 text-base font-semibold text-white shadow-lg shadow-blue-200 hover:bg-blue-700"
                >
                  <a href={INSTALLER_URL}>
                    <Icon name="download" className="mr-2 h-5 w-5" />
                    {t.download}
                  </a>
                </Button>
                <Button
                  asChild
                  size="lg"
                  variant="outline"
                  className="rounded-md border-slate-200 bg-white px-7 text-base text-slate-800 shadow-sm hover:bg-blue-50 hover:text-blue-700"
                >
                  <a href={REPO_URL}>
                    <Icon name="github" className="mr-2 h-5 w-5" />
                    {t.source}
                  </a>
                </Button>
              </div>
              <div className="mt-8 grid max-w-xl grid-cols-3 gap-3 text-sm text-slate-600">
                <div className="rounded-md border border-slate-200 bg-white p-4 shadow-sm">
                  <p className="text-2xl font-bold text-slate-950">2</p>
                  <p>{t.modes}</p>
                </div>
                <div className="rounded-md border border-slate-200 bg-white p-4 shadow-sm">
                  <p className="text-2xl font-bold text-slate-950">3</p>
                  <p>{t.languages}</p>
                </div>
                <div className="rounded-md border border-slate-200 bg-white p-4 shadow-sm">
                  <p className="text-2xl font-bold text-slate-950">1-click</p>
                  <p>{t.installer}</p>
                </div>
              </div>
            </motion.div>
            <motion.div
              initial={{ opacity: 0, scale: 0.98 }}
              animate={{ opacity: 1, scale: 1 }}
              transition={{ duration: 0.65, delay: 0.1 }}
            >
              <MeshPreview t={t} />
            </motion.div>
          </div>
        </div>
      </section>
      <section
        id="features"
        className="scroll-mt-24 mx-auto max-w-6xl px-4 py-20"
      >
        <div className="mx-auto max-w-3xl text-center">
          <p className="text-sm font-semibold uppercase tracking-[0.3em] text-blue-600">
            {t.featuresLabel}
          </p>
          <h2 className="mt-4 text-4xl font-bold tracking-tight text-slate-950 md:text-5xl">
            {t.featuresTitle}
          </h2>
          <p className="mt-5 text-lg leading-8 text-slate-600">
            {t.featuresSubtitle}
          </p>
        </div>
        <div className="mt-14 grid gap-5 md:grid-cols-3">
          {features.map((feature) => (
            <Card
              key={feature.title}
              className="overflow-hidden rounded-md border-slate-200 bg-white text-slate-900 shadow-sm transition hover:-translate-y-1 hover:shadow-xl hover:shadow-blue-100/70"
            >
              <CardContent className="p-6">
                <div className="mb-5 flex h-12 w-12 items-center justify-center rounded-md border border-blue-100 bg-blue-50 text-blue-600">
                  <Icon name={feature.icon} className="h-6 w-6" />
                </div>
                <MiniDiagram type={feature.diagram} />
                <h3 className="mt-5 text-xl font-semibold text-slate-950">
                  {feature.title}
                </h3>
                <p className="mt-3 leading-7 text-slate-600">{feature.text}</p>
              </CardContent>
            </Card>
          ))}
        </div>
      </section>
      <DemoVideoSlot t={t} />
      {locale === "zh" ? <BlogSlot t={t} /> : null}
      <section className="border-y border-slate-200 bg-slate-50">
        <div className="mx-auto grid max-w-6xl gap-10 px-4 py-20 lg:grid-cols-3">
          <div className="lg:col-span-1">
            <p className="text-sm font-semibold uppercase tracking-[0.3em] text-blue-600">
              {t.workflowLabel}
            </p>
            <h2 className="mt-4 text-4xl font-bold tracking-tight text-slate-950">
              {t.workflowTitle}
            </h2>
          </div>
          <div className="grid gap-4 md:grid-cols-3 lg:col-span-2">
            {fastPoints.map((point) => (
              <div
                key={point.title}
                className="rounded-md border border-slate-200 bg-white p-5 shadow-sm"
              >
                <Icon name={point.icon} className="h-6 w-6 text-blue-600" />
                <h3 className="mt-4 font-semibold text-slate-950">
                  {point.title}
                </h3>
                <p className="mt-2 text-sm leading-6 text-slate-600">
                  {point.text}
                </p>
              </div>
            ))}
          </div>
        </div>
      </section>
      <section
        id="install"
        className="scroll-mt-24 mx-auto max-w-6xl px-4 py-20"
      >
        <div className="grid gap-10 lg:grid-cols-[.9fr_1.1fr]">
          <div>
            <div className="mb-5 inline-flex h-14 w-14 items-center justify-center rounded-md bg-blue-600 text-white shadow-lg shadow-blue-200">
              <Icon name="package" className="h-7 w-7" />
            </div>
            <h2 className="text-4xl font-bold tracking-tight text-slate-950 md:text-5xl">
              {t.installTitle}
            </h2>
            <p className="mt-5 text-lg leading-8 text-slate-600">
              {t.installText}
            </p>
            <div className="mt-8 flex flex-col gap-3 sm:flex-row">
              <Button
                asChild
                size="lg"
                className="rounded-md bg-blue-600 text-white shadow-lg shadow-blue-200 hover:bg-blue-700"
              >
                <a href={INSTALLER_URL}>
                  <Icon name="download" className="mr-2 h-5 w-5" />
                  {t.download}
                </a>
              </Button>
              <Button
                asChild
                size="lg"
                variant="outline"
                className="rounded-md border-slate-200 bg-white text-slate-800 shadow-sm hover:bg-blue-50 hover:text-blue-700"
              >
                <a href={REPO_URL}>
                  README <Icon name="arrowRight" className="ml-2 h-5 w-5" />
                </a>
              </Button>
            </div>
          </div>
          <div className="rounded-lg border border-slate-200 bg-white p-6 shadow-sm">
            <ol className="space-y-4">
              {steps.map((step, index) => (
                <li
                  key={step}
                  className="flex gap-4 rounded-md border border-slate-200 bg-slate-50 p-4"
                >
                  <span className="flex h-9 w-9 shrink-0 items-center justify-center rounded-md bg-blue-600 font-bold text-white">
                    {index + 1}
                  </span>
                  <p className="pt-1 leading-7 text-slate-700">{step}</p>
                </li>
              ))}
            </ol>
          </div>
        </div>
      </section>
      <section className="mx-auto max-w-6xl px-4 pb-20">
        <div className="rounded-lg border border-blue-100 bg-blue-50 p-8 md:p-12">
          <div className="grid items-center gap-8 md:grid-cols-[1fr_auto]">
            <div>
              <h2 className="text-3xl font-bold text-slate-950 md:text-4xl">
                {t.ctaTitle}
              </h2>
              <p className="mt-4 max-w-2xl text-slate-600">{t.ctaText}</p>
            </div>
            <Button
              asChild
              size="lg"
              className="rounded-md bg-blue-600 text-white shadow-lg shadow-blue-200 hover:bg-blue-700"
            >
              <a href={INSTALLER_URL}>
                {t.ctaButton} <Icon name="download" className="ml-2 h-5 w-5" />
              </a>
            </Button>
          </div>
        </div>
      </section>
      <footer className="border-t border-slate-200 bg-white px-4 py-10">
        <div className="mx-auto flex max-w-6xl flex-col gap-6 text-sm text-slate-500 md:flex-row md:items-center md:justify-between">
          <div>
            <div className="flex items-center gap-2 font-semibold text-slate-950">
              <BrandMark className="h-6 w-6 shrink-0" />
              InsetFace for Metasequoia 4
            </div>
            <p className="mt-2">{t.footerLang}</p>
          </div>
          <div className="flex flex-wrap gap-4">
            <a href={REPO_URL} className="hover:text-blue-700">
              GitHub Source
            </a>
            <a href={INSTALLER_URL} className="hover:text-blue-700">
              Download Installer
            </a>
          </div>
        </div>
      </footer>
    </main>
  );
}
