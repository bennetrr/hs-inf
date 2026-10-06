---
# Build Command
# pandoc --pdf-engine xelatex -s CG1P03.md --template ../../eisvogel.latex -o CG1P03.pdf --listings
listings: true
listings-disable-line-numbers: false
numbersections: true
title: "Praktikum: Dreiecksrasterung"
titlepage: true
author: [Prof. Dr.-Ing. Quirin Meyer]
date: "2025-10-09"
keywords: [CG1 Praktikum, Dreiecke, Rasterung]
papersize: A4
fontfamily: roboto
mainfont: "Roboto-Regular"
lang: "de"
header-left: "\\theauthor"
header-center: " "
header-right: "Computer Grafik 1"
footer-left: "Hochschule Coburg"
footer-center: "\\thepage"
footer-right: "FEIF"
...

# Fixed Point
Implementieren Sie die Funktionen in dem Header `FixedPoint.h` gemäß ihrer Kommentare.
Stellen Sie sicher, dass alle Tests in `T03FixedPoint` erfolgreich verlaufen!

# Implizite Linien Gleichungen 
Implementieren Sie die Funktionen in dem Header `LineEquation.h` gemäß ihrer Kommentare.
Stellen Sie sicher, dass alle Tests in `T04LineEquation` erfolgreich verlaufen!

# Degenerierte Dreiecke
Bei degenerierten Dreiecken kann es zu Division-durch-Null Fehlern kommen. Um dies zu verhindern, muss man degenerierte Dreiecke erkennen und aussortieren.
Implementieren Sie dazu die Funktion ```IsDegenerate``` im Header `TriangleCull.h` gemäß ihrer Kommentaranmerkungen.  
Stellen Sie sicher, dass alle Tests in `T05DegenerateTriangle` erfolgreich durchlaufen.

# Clipped Bounding Box
Implementieren Sie die Funktion `ComputeClippedBoundBox` im Header `TriangleCull.h` gemäß ihrer Kommentaranmerkungen. Stellen Sie sicher, dass alle Tests im Modul `T06BoundingBox` erfolgreich durchlaufen.

Eine *Bounding Box* ist das kleinste achsenparallele Rechteck, das eine gegebene Menge von Punkten vollständig umschließt.  
Zusätzlich muss sichergestellt werden, dass die Bounding Box das Bildschirmrechteck nicht verlässt.  
Dazu sind die Koordinaten wie folgt zu beschneiden:
- Werte für `x0` und `y0` dürfen nicht kleiner als `0` sein.
- Werte für `x1` und `y1` dürfen nicht größer als `w - 1` bzw. `h - 1` sein.

# Dreiecke Zeichnen
Nutzen Sie nun die Funktion aus den obigen Aufgaben um ein Dreieck zu zeichnen.
Implementieren Sie dazu die Funktion `DrawTriangleFlat` in `Triangle.h`.
Beachten Sie die Kommentaranmerkungen im `Triangle.h`.
Tests und Referenzbilder sind in `T07FlatTriangle`.




