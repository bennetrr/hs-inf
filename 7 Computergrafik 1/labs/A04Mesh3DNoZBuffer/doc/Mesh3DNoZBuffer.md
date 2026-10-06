---
# Build Command
# pandoc --pdf-engine xelatex -s Mesh2D.md --template ../../eisvogel.latex -o Mesh2D.pdf --listings
listings: true
listings-disable-line-numbers: false
numbersections: true
title: "Praktikum: Mesh 3D ohne Tiefen-Test zeichnen"
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

In dieser Aufgabe erstellen und animieren wir ein 3D-Mesh des Stanford Bunnys. 
Die Darstellung ist noch inkorrekt, weil wir keinen Tiefen-Test durchführen.

# Homogene Koordinaten

Implementieren Sie die Funktion gemäß den Kommentaren in `cgclib/math/Vec4.h`.

**Datei:** `cgclib/math/Vec4.h`

**Ziel:** Alle Tests in `T12TestVec4` sollen erfolgreich durchlaufen.

# Projektive Transformationen

Implementieren Sie die Funktion `Projection3D` aus dem Header `cgclib/math/Transforms.h`:

**Hinweis:** Die Kommentare im Code geben Ihnen genaue Hinweise zur Umsetzung.

**Datei:** `cgclib/math/Transforms.h`

**Ziel:** Alle Tests in `T13TestProj3D` sollen erfolgreich durchlaufen.

# 3D-Mesh rendern

Vervollständigen Sie die Funktion `Render3DMeshFlatNoZBuffer` aus dem Header `Render3DMeshNoZBuffer.h`, um das `SimpleMesh mesh` mit `DrawTriangleFlat` zu zeichnen.

Gehen Sie dazu für jedes Dreieck wie folgt vor:
1. Bestimmen Sie die drei Vertex-Indizes des Dreiecks.
1. Nutzen Sie die Vertex-Indizes um  drei 3D Positionen jedes Dreiecks zu extrahieren.
1. Transformieren Sie diese vom Model- in den View-Space mittels der `modelTransform`.
1. Berechnen Sie für jedes Dreieck aus dessen Ecken die normalisierte Normale $\vec{n}$ mit dem 3D-Kreuzprodukt.
1. Transformieren Sie die View-Space-Punkte in Clip-Space-Punkte (mittels der `projectionTransform`).
1. Projizieren Sie die Clip-Space-Punkte in NDC mittels `Homogenize`.
1. Transformieren Sie die NDC Punkte in Window Koordinaten mittels der `windowTransform`.
1. Konvertieren Sie alle nötigen `float` in `fixed_t`.
1. Zeichnen Sie das Dreieck `DrawTriangleFlat`. Setzen Sie die Farbe des Dreiecks auf $\frac{1}{2}\cdot\left(\vec{n} + \left[1, 1, 1\right]^\top\right)$.


**Datei:** `Render3DMeshNoZBuffer.h`

**Ziel:** Wenn Sie `A04Mesh3DNoZBuffer` ausführen, soll ein kleiner Hase sichtbar sein.

# Animationen 
Der Hase soll sich drehen und gleichzeitig verschoben werden. 
Vervollständigen Sie dazu `cgclib/src/math/Mesh3DTransforms.c`.

**Schritt 1: Objekt in den View-Space transformieren**

Implementieren Sie `ModelTransform`. Diese soll eine Matrix zurückgeben, welche

1. um den Winkel, der in der Variablen `alpha` hinterlegt ist, 
  zunächst um die X-, dann um die Y- und schließlich um die Z-Achse, rotiert. 
1. Anschließend sollen Vektoren um  
  $$
  \vec{t} = \begin{bmatrix} 0 \\ 0 \\ -3.7 \end{bmatrix}$$ 
  verschoben werden.

**Wichtig:** Achten Sie auf die korrekte Reihenfolge der Matrix-Multiplikationen!

**Schritt 2: Objekt in Clip Space Transformieren** 

Implementieren Sie in `ProjectionTransform` durch einen passenden  Aufruf!
Verwenden Sie als Kameraöffnungswinkel 45 Grad, als Near-Plane Abstand 0.01, und als Far-Plane Abstand 16.5.

Achtung: Denken Sie an das Vorzeichen von Near- und Far-Plane!

**Schritt 3: Objekt in Window Koordinaten transformieren**  

Implementieren Sie in `WindowTransform` einen passenden  Aufruf!

**Datei:** `Mesh3DTransforms.c`

1. Wenn alles korrekt ist, zeigt die Anwendung `A04Mesh3DNoZBuffer` eine schöne, flüssige Animation des Hasen.
1. Die Tests in `T14Render3DMeshNoZBuffer` erzeugen Vergleichsbilder und prüfen diese gegen die Referenz.

