# InsetFace Landing Page

A Vite + React + Tailwind landing page for the InsetFace Metasequoia 4 plugin.

## Local development

```bash
npm install
npm run dev
```

## Production build

```bash
npm run build
```

The generated static site will be in `dist/`.

## Cloudflare Pages settings

- Framework preset: `Vite`
- Build command: `npm run build`
- Build output directory: `dist`
- Node.js version: 18+ or 20+

## Replace placeholders

In `src/App.tsx`:

```ts
const DEMO_VIDEO_URL = "";
const BLOG_URL = "https://xiangao0904.github.io/blog/insetface-algorithm";
```

Set `DEMO_VIDEO_URL` to your `.mp4` or `.webm` demo URL when ready.
