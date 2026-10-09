---
# Build Command
# pandoc --pdf-engine xelatex -s GouraudShading.md --template ../../eisvogel.latex -o GouraudShading.pdf --listings
listings: true
listings-disable-line-numbers: false
numbersections: true
title: 'Praktikum: Gouraud-Shading'
titlepage: true
author: [Prof. Dr.-Ing. Quirin Meyer]
date: '2026-01-12'
keywords: [CG1 Praktikum, Gouraud, Shading]
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

**Ziel:** Ein 3D-Mesh soll mit Gouraud-Shading gerendert werden. Dabei wird die Beleuchtung pro Vertex berechnet und die resultierenden Farben über
das Dreieck interpoliert.

# Beleuchtungsmethoden

Die Funktionen `DiffuseLighting` und `BlinnLighting` wurden bereits in **Praktikum A07** implementiert. Stellen Sie sicher, dass alle Tests in
`T17TestLighting` erfolgreich durchlaufen.

**Dateien:** `cgclib/math/Lighting.h`, `cgclib/src/math/Lighting.c`

# `Render3DMeshGouraud` implementieren

Implementieren Sie die Funktion **`Render3DMeshGouraud`** in `A08GouraudShading/Render3DMeshGouraudShading.h`.

**Vorgehen:** Iterieren Sie über alle Dreiecke des Meshes und führen Sie für jedes Dreieck folgende Schritte durch:

1. Lesen Sie die drei Vertex-Indizes aus `mesh.indices`.
2. Lesen Sie die drei Positionen aus `mesh.positions` im Objekt-Space.
3. Lesen Sie die drei Normalen aus `mesh.normals` im Objekt-Space.
4. Transformieren Sie die Normalen mit `Mat3xVec3` in den View-Space.
5. Transformieren Sie die Positionen mit `Mat4xVec3Affine` in den View-Space.
6. Berechnen Sie für jeden Vertex den Richtungsvektor zur Kamera (`viewPosition`).
7. Berechnen Sie für jeden Vertex die diffuse Beleuchtungsfarbe mit `DiffuseLighting`.
8. Berechnen Sie für jeden Vertex die spekulare Beleuchtungsfarbe mit `BlinnLighting`.
9. Addieren Sie diffuse und spekulare Farbe pro Vertex.
10. Transformieren Sie die View-Space-Positionen (v0, v1, v2 aus Schritt 5) mit `Mat4xVec3` in den Clip-Space.
11. Führen Sie die perspektivische Division mit `Homogenize` durch (Clip-Space nach NDC).
12. Berechnen Sie die Fixed-Point-Fensterkoordinaten aus den NDC-Koordinaten.
13. Rasterisieren Sie das Dreieck mit `DrawTriangleZBufferGouraud`.

**Datei:** `A08GouraudShading/Render3DMeshGouraudShading.h`

**Ziel:** Wenn Sie `A08GouraudShading` ausführen, soll eine beleuchtete Kugel mit weichen Farbübergängen sichtbar sein.
