---
# Build Command
# pandoc --pdf-engine xelatex -s PhongShading.md --template ../../eisvogel.latex -o PhongShading.pdf --listings
listings: true
listings-disable-line-numbers: false
numbersections: true
title: 'Praktikum: Phong-Shading'
titlepage: true
author: [Prof. Dr.-Ing. Quirin Meyer]
date: '2026-01-19'
keywords: [CG1 Praktikum, Phong, Shading]
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

**Ziel:** Ein 3D-Mesh soll mit Phong-Shading gerendert werden. Im Gegensatz zu Gouraud-Shading wird die Beleuchtung nicht pro Vertex, sondern **pro
Pixel** berechnet. Dazu werden Normalen und Positionen über das Dreieck interpoliert und die Beleuchtungsberechnung im Fragment-Shader durchgeführt.

# `Render3DMeshPhong` implementieren

Implementieren Sie die Funktion **`Render3DMeshPhong`** in `A09PhongShading/Render3DMeshPhongShading.h`.

Nutzen Sie `Render3DMeshGouraud` aus `A08GouraudShading/Render3DMeshGouraudShading.h` als Vorlage.

**Unterschied zu Gouraud-Shading:** Anstatt die Beleuchtung pro Vertex zu berechnen und die Farben zu interpolieren, werden die **Normalen** und
**View-Space-Positionen** pro Vertex an `DrawTriangleZBufferBlinnPhong` übergeben. Die Beleuchtungsberechnung erfolgt dann pro Pixel innerhalb der
Rasterisierungsfunktion.

**Vorgehen:**

1. Lesen Sie die drei Vertex-Indizes, Positionen und Normalen aus dem Mesh.
2. Transformieren Sie die Positionen mit `Mat4xVec3` in den Clip-Space und anschließend mit `Homogenize` in NDC.
3. Berechnen Sie die Fixed-Point-Fensterkoordinaten.
4. Transformieren Sie die Positionen mit `Mat4xVec3Affine` in den View-Space (`v0`, `v1`, `v2`).
5. Transformieren Sie die Normalen mit `Mat3xVec3` in den View-Space (`n0`, `n1`, `n2`).
6. Rufen Sie `DrawTriangleZBufferBlinnPhong` mit den View-Space-Positionen und -Normalen auf.

**Datei:** `A09PhongShading/Render3DMeshPhongShading.h`

**Ziel:** Wenn Sie `A09PhongShading` ausführen, soll eine beleuchtete Kugel mit schärferen Glanzlichtern als beim Gouraud-Shading sichtbar sein.
