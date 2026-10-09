---
# Build Command
# pandoc --pdf-engine xelatex -s Mesh2D.md --template ../../eisvogel.latex -o Mesh2D.pdf --listings
listings: true
listings-disable-line-numbers: false
numbersections: true
title: 'Praktikum: Mesh 3D mit Flat Shading zeichnen'
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

**Ziel:** Ein Mesh soll so gerendert werden, dass jedes Dreieck mit diffuser Beleuchtungsfarbe dargestellt wird.

# Beleuchtungsmethoden implementieren

Implementieren Sie die Funktionen zur Berechnung von diffuser und spekularer Beleuchtung entsprechend ihrer Kommentare. Nutzen Sie die beigelegten
Tests um Ihre Implementierung zu testen. Sie benötigen in dieser Aufgabe nur die diffuse Beleuchtungsberechnung.

**Dateien:** `cgclib/math/Lighting.h`, `cgclib/math/Lighting.c`

# `Render3DMeshFlatShading` implementieren

- Implementieren Sie **`Render3DMeshFlatShading`** in `Render3DMeshFlatShading.h`.
- Nutzen Sie `Render3DMeshFlatZBuffer` als Vorlage und erweitern Sie die Funktion, in dem Sie für jedes Dreieck aus der Normalen und der Lichtrichtung
  `lightDirection` eine diffuse Beleuchtungsfarbe bestimmen.
- Rufen Sie `DrawTriangleZBufferFlat` mit dieser Farbe auf.

**Dateien:** `A06Mesh3DZBuffer/Render3DMeshZBuffer.h`, `A07FlatShading/Render3DMeshFlatShading.h`
