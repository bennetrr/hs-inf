#ifndef LIGHTING_H
#define LIGHTING_H
#include <cgclib/math/Vec3.h>

/**
 * @brief Computes diffuse lighting using Lambert's cosine law.
 *
 * The intensity is proportional to the cosine of the angle between the surface normal and the light direction.
 *
 * @param normal Surface normal vector.
 * @param lightDirection Direction vector from surface to light source.
 * @param color Base color of the surface.
 * @return Vec3 Resulting diffuse-lit color.
 */
Vec3 DiffuseLighting(Vec3 normal, Vec3 lightDirection, Vec3 color);

/**
 * @brief Computes specular lighting using the Blinn-Phong reflection model.
 *
 * Calculates the intensity based on the angle between the surface normal and the halfway vector between light and view
 * directions.
 *
 * @param normal Surface normal vector.
 * @param lightDirection Direction vector from surface to light source.
 * @param viewDirection Direction vector from surface to viewer.
 * @param color Specular color of the surface.
 * @param shinyness Shininess exponent controlling highlight sharpness.
 * @return Vec3 Resulting specular-lit color.
 */
Vec3 BlinnLighting(Vec3 normal, Vec3 lightDirection, Vec3 viewDirection, Vec3 color, float shinyness);

/**
 * @brief Computes specular lighting using the Phong reflection model.
 *
 * @param normal Surface normal vector.
 * @param lightDirection Direction vector from surface to light source.
 * @param viewDirection Direction vector from surface to viewer.
 * @param color Specular color of the surface.
 * @param shinyness Shininess exponent controlling highlight sharpness.
 * @return Vec3 Resulting specular-lit color.
 */
Vec3 PhongLighting(Vec3 normal, Vec3 lightDirection, Vec3 viewDirection, Vec3 color, float shinyness);


#endif
