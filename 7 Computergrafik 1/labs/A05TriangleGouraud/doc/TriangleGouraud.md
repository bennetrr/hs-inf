---
# Build Command
# pandoc --pdf-engine xelatex -s Mesh2D.md --template ../../eisvogel.latex -o Mesh2D.pdf --listings
listings: true
listings-disable-line-numbers: false
numbersections: true
title: 'Praktikum: Baryzentrische Interpolation (Gouraud Shading)'
titlepage: true
author: [Prof. Dr.-Ing. Quirin Meyer]
date: '2025-11-25'
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

# Baryzentrische Interpolation

Ein Dreieck mit den Ecken $\vec{a},\vec{b},\vec{c}$ hat die _Scaled Signed-Distance Functions_ $l_{*}\left( \vec{x} \right)$

$$l_{\vec{a}\vec{b}}\left( \vec{x} \right) = {\vec{n}}_{\vec{a}\vec{b}}^{\top}\vec{x} - d_{\vec{a}\vec{b}\ },\ \ {\vec{n}}_{\vec{a}\vec{b}} = \mathrm{cross1}\left( \vec{b} - \vec{a} \right),\ \ d_{\vec{a}\vec{b}} = {\vec{n}}_{\vec{a}\vec{b}}^{\top}\vec{a},$$

$$l_{\vec{b}\vec{c}}\left( \vec{x} \right) = {\vec{n}}_{\vec{b}\vec{c}}^{\top}\vec{x} - d_{\vec{b}\vec{c}\ },\ \ {\vec{n}}_{\vec{b}\vec{c}} = \mathrm{cross1}\left( \vec{c} - \vec{b} \right),\ \ d_{\vec{b}\vec{c}} = {\vec{n}}_{\vec{b}\vec{c}}^{\top}\vec{b},$$

$$l_{\vec{c}\vec{a}}\left( \vec{x} \right) = {\vec{n}}_{\vec{c}\vec{a}}^{\top}\vec{x} - d_{\vec{c}\vec{a}\ },\ \ {\vec{n}}_{\vec{c}\vec{a}} = \mathrm{cross1}\left( \vec{a} - \vec{c} \right),\ \ d_{\vec{c}\vec{a}} = {\vec{n}}_{\vec{c}\vec{a}}^{\top}\vec{c}.$$

Der Punkt $\vec{x}$ besitzt folgende baryzentrischen Koordinaten:

$$\alpha = \frac{l_{\vec{b}\vec{c}}\left( \vec{x} \right)}{l_{\vec{b}\vec{c}}\left( \vec{a} \right)},\ \ \beta = \frac{l_{\vec{c}\vec{a}}\left( \vec{x} \right)}{l_{\vec{c}\vec{a}}\left( \vec{b} \right)},\ \ \gamma = \frac{l_{\vec{a}\vec{b}}\left( \vec{x} \right)}{l_{\vec{a}\vec{b}}\left( \vec{c} \right)}.$$

Nutzen Sie Ihre Funktion `DrawTriangleFlat` als Grundlage und erweitern Sie diese zur Funktion `DrawTriangleGouraud` so, dass in jedem Punkt die
baryzentrischen Koordinaten berechnet werden und die Farben entsprechend interpoliert werden.

# Beweis

Beweisen Sie die Formeln für $\alpha,\beta,\gamma$ aus Aufgabe 2.

Hinweis: $\gamma = \frac{\text{area}\left( \vec{a},\vec{b},\vec{x} \right)}{\text{area}\left( \vec{a},\vec{b},\vec{c} \right)},$
$\text{area}\left( \vec{a},\vec{b},\vec{c} \right) = \frac{1}{2}g \cdot h$.
