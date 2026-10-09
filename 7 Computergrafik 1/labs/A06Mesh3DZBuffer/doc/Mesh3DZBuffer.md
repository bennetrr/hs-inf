---
# Build Command
# pandoc --pdf-engine xelatex -s Mesh2D.md --template ../../eisvogel.latex -o Mesh2D.pdf --listings
listings: true
listings-disable-line-numbers: false
numbersections: true
title: 'Praktikum: Mesh 3D mit Z-Buffer zeichnen'
titlepage: true
author: [Prof. Dr.-Ing. Quirin Meyer]
date: '2025-12-05'
keywords: [CG1 Praktikum, Dreiecke, Rasterung]
papersize: A4
fontfamily: roboto
mainfont: 'Roboto-Regular'
lang: 'de'
header-left: "\\theauthor"
header-center: ' '
header-right: 'Computer Grafik 1'
footer-left: 'Hochschule Coburg'
footer-center: "\\thepage"
footer-right: 'FEIF'
...

**Ziel:** Ein Mesh soll so gerendert werden, dass für jeden Pixel stets das vorderste Fragment des Modells dargestellt wird. Dazu wird ein Z‑Buffer
eingesetzt

# `DrawTriangleZBufferFlat` implementieren

Implementiere die Methode **`DrawTriangleZBufferFlat`** in `Triangle.c`.

**Vorgehen:**

1. Berechnen Sie für jeden Pixel den z‑Wert baryzentrisch aus `z0`, `z1`, `z2`.
2. Vergleichen Sie diesen Wert mit dem aktuellen Eintrag im **Z‑Buffer** (`p.zBuffer`).
3. Falls der neue z‑Wert kleiner ist (Pixel liegt näher zur Kamera):
   - Setzen Sie den Pixel.
   - Aktualisieren Sie den Z‑Buffer mit dem neuen z‑Wert.

**Datei:** `cgclib/src/raster/Triangle.c`

# Z-Buffer löschen

- Vor jedem Renderdurchlauf muss der Z‑Buffer zurückgesetzt werden.
- Verwenden Sie dazu die Methode **`ClearZBuffer`**.
- Rufen Sie diese Methode in **`RenderScene`** auf.

**Datei:** `A06Mesh3DZBuffer/Render3DMeshZBuffer.h`

# `Render3DMeshFlatZBuffer` implementieren

- Implementieren Sie **`Render3DMeshFlatZBuffer`** in `Render3DMeshZBuffer.h`.
- Nutzen Sie `Render3DMeshFlatNoZBuffer` als Vorlage.
- Gehen Sie für jedes Dreieck wie folgt vor:
  1. Transformieren Sie die Positionen vom Model- in den View-Space (`modelTransform`).
  2. Transformieren Sie die View-Space-Punkte in den Clip-Space (`projectionTransform`).
  3. Projizieren Sie in NDC mittels `Homogenize`.
  4. Transformieren Sie in Window-Koordinaten (`windowTransform`).
  5. Ersetzen Sie den Aufruf von `DrawTriangleFlat` durch **`DrawTriangleZBufferFlat`** und übergeben Sie die NDC‑z‑Werte.
- Implementieren Sie in `RenderScene` die Berechnung von `projectionTransform` und `windowTransform`.

**Dateien:** `A04Mesh3DNoZBuffer/Render3DMeshNoZBuffer.h`, `A06Mesh3DZBuffer/Render3DMeshZBuffer.h`
