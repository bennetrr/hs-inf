---
# Build Command
# pandoc --pdf-engine xelatex -s Mesh2D.md --template ../../eisvogel.latex -o Mesh2D.pdf --listings
listings: true
listings-disable-line-numbers: false
numbersections: true
title: 'Praktikum: Mesh 3D Optimierung'
titlepage: true
author: [Prof. Dr.-Ing. Quirin Meyer]
date: '2025-12-05'
keywords: [CG1 Praktikum, Optimierung]
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

**Ziel:** Die Phong-Shading-Implementierung aus `A09PhongShading` soll durch frühzeitiges Aussortieren von Dreiecken und Nutzung einer vorberechneten
Bounding Box beschleunigt werden. Als Testmesh dient der Stanford Bunny (`Bunny2k.smm`) mit 2000 Dreiecken. Notieren Sie nach jedem Schritt die neue
Bildberechnungszeit in ms, die auf der Konsole ausgegeben wird.

# Culling-Funktionen implementieren

Implementieren Sie die Funktionen **`IsBackFace`** und **`IsBoundingBoxAPixel`** in `cgclib/raster/TriangleCull.h`. Die Kommentare im Code beschreiben
das erwartete Verhalten.

**Datei:** `cgclib/raster/TriangleCull.h`

**Ziel:** Alle Tests in `T21TriangleCull` sollen erfolgreich durchlaufen.

# `Render3DMeshPhong` optimiert implementieren

Implementieren Sie die Funktion **`Render3DMeshPhong`** in `A10PhongOptimized/Render3DMeshOptimized.h`.

Nutzen Sie `Render3DMeshPhong` aus `A09PhongShading/Render3DMeshPhongShading.h` als Vorlage und erweitern Sie diese um folgende Optimierungsschritte,
**bevor** das Dreieck rasterisiert wird:

# Degenerierte Dreiecke aussortieren

Rufen Sie **`IsDegenerate`** auf. Überspringen Sie das Dreieck mit `continue`, falls es degeneriert ist.

# Rückseiten aussortieren (Backface Culling)

Rufen Sie **`IsBackFace`** auf. Überspringen Sie das Dreieck mit `continue`, falls es eine Rückseite ist.

Überlegen Sie, warum Sie nun `IsDegenerate` eigentlich weglassen könnten!

# Bounding Box berechnen und prüfen

1. Berechnen Sie die Bounding Box mit **`ComputeClippedBoundBox`**.
2. Überspringen Sie das Dreieck mit `continue`, falls `IsBoundingBoxZero` zutrifft (Dreieck liegt vollständig außerhalb des Bildschirms).

# Einzelpixel-Optimierung

Falls `IsBoundingBoxAPixel` zutrifft (Dreieck deckt genau einen Pixel ab):

- Prüfen Sie den Z-Buffer direkt, ohne die Rasterisierungsfunktion aufzurufen.
- Schreiben Sie bei bestandenem Z-Test Farbe und Z-Wert direkt in den Buffer.

# Rasterisierung mit vorberechneter Bounding Box

Rufen Sie **`DrawTriangleZBufferBlinnPhongOptimized`** mit der vorberechneten Bounding Box auf (anstatt `DrawTriangleZBufferBlinnPhong`).

**Datei:** `A10PhongOptimized/Render3DMeshOptimized.h`

# Multiplikationen durch Additionen ersetzen

Ersetzen Sie möglichst viele Multiplikationen durch Additionen (z.B. `EvalLineEquation`, Berechnung von `beta` und `gamma` und `z`)

**Ziel:** Wenn Sie `A10PhongOptimized` ausführen, soll der Stanford Bunny mit Phong-Shading flüssig animiert dargestellt werden - deutlich schneller
als die nicht-optimierte Version aus `A09PhongShading`.
