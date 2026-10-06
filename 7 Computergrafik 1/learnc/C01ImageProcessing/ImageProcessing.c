#define _USE_MATH_DEFINES
#include <cgclib/sys/CGWindow.h>
#include <math.h>
#include <stdlib.h>

static int32_t RandomPoints(PixelBuffer p)
{
  for (int32_t y = 0; y < p.height; y++)

  {
    for (int32_t x = 0; x < p.width; x++)
    {
      int32_t ofs   = y * p.width + x;
      uint8_t r     = rand();
      uint8_t g     = rand();
      uint8_t b     = rand();
      p.pixels[ofs] = Color(r, g, b);
    }
  }
  return 1;
}

static int32_t GradientX(PixelBuffer p)
{
  for (int32_t y = 0; y < p.height; y++)

  {
    for (int32_t x = 0; x < p.width; x++)
    {
      float   xf    = (float)(x) / (float)(p.width);
      int32_t ofs   = y * p.width + x;
      uint8_t r     = (uint8_t)(xf * 255.0f + 0.5f);
      uint8_t g     = 0;
      uint8_t b     = 0;
      p.pixels[ofs] = Color(r, g, b);
    }
  }
  return 1;
}

static int32_t GradientXY(PixelBuffer p)
{
  for (int32_t y = 0; y < p.height; y++)

  {
    for (int32_t x = 0; x < p.width; x++)
    {
      float   xf    = (float)(x) / (float)(p.width);
      float   yf    = (float)(y) / (float)(p.height);
      int32_t ofs   = y * p.width + x;
      uint8_t r     = (uint8_t)(xf * 255.0f + 0.5f);
      uint8_t g     = (uint8_t)(yf * 255.0f + 0.5f);
      uint8_t b     = 0;
      p.pixels[ofs] = Color(r, g, b);
    }
  }
  return 1;
}

static int32_t Circle(PixelBuffer p)
{
  for (int32_t y = 0; y < p.height; y++)

  {
    for (int32_t x = 0; x < p.width; x++)
    {
      float cx = (cosf(0.001f * p.time));
      ;
      float cy = (sinf(0.001f * p.time));
      ;

      float   xf  = -1.0f + 2.0f * (float)(x) / (float)(p.width) - cx;
      float   yf  = -1.0f + 2.0f * (float)(y) / (float)(p.height) - cy;
      int32_t ofs = y * p.width + x;
      float   h   = xf * xf + yf * yf - fabsf(sinf(0.0001f * p.time));
      if (h >= 0)
      {
        p.pixels[ofs] = Color((uint32_t)(h * 255.0f), 0, 0);
      }
      else
      {
        p.pixels[ofs] = Color(0, (uint32_t)(-h * 255.0f), 0);
      }
    }
  }
  return 1;
}

static int32_t RotoZoom(PixelBuffer p)
{
  int32_t ofs    = 0;
  float   t      = 0.001f * p.time;
  float   cx     = sinf(1.0f * t);
  float   cy     = cosf(1.0f * t);
  float   aspect = (float)p.height / p.width;
    for (int32_t y = 0; y < p.height; y++)

  {
      float yf = (-1.0f + 2.0f * (float)(y) / (float)(p.height)) * aspect;
  for (int32_t x = 0; x < p.width; x++)
    {
    float xf = -1.0f + 2.0f * (float)(x) / (float)(p.width);

      float xt = cosf(t) * (xf + cx) - sinf(t) * (yf + cy);
      float yt = sinf(t) * (xf + cx) + cosf(t) * (yf + cy);

      xt *= 1.1f + sinf(0.5f * t);
      yt *= 1.1f + sinf(0.5f * t);

      float u = (xt + 1.0f) * 0.5f;
      float v = (yt + 1.0f) * 0.5f;

      uint8_t tu = (int)(u * 255 + 0.5f);
      uint8_t tv = (int)(v * 255 + 0.5f);
      uint8_t c  = tu ^ tv;

      p.pixels[y*p.width+x] = Color(c, c, c);
    }
  }
  return 1;
}

/*
#define timeScale          time * 1.0
#define fireMovement       vec2(-0.01, -0.5)
#define distortionMovement vec2(-0.01, -0.3)
#define normalStrength     40.0
#define distortionStrength 0.1
vec2 hash(vec2 p)
{
  p = vec2(dot(p, vec2(127.1, 311.7)), dot(p, vec2(269.5, 183.3)));

  return -1.0 + 2.0 * fract(sin(p) * 43758.5453123);
}
float noise(in vec2 p)
{
  const float K1 = 0.366025404; // (sqrt(3)-1)/2;
  const float K2 = 0.211324865; // (3-sqrt(3))/6;

  vec2 i = floor(p + (p.x + p.y) * K1);

  vec2 a = p - i + (i.x + i.y) * K2;
  vec2 o = step(a.yx, a.xy);
  vec2 b = a - o + K2;
  vec2 c = a - 1.0 + 2.0 * K2;

  vec3 h = MAX(0.5 - vec3(dot(a, a), dot(b, b), dot(c, c)), 0.0);

  vec3 n = h * h * h * h * vec3(dot(a, hash(i + 0.0)), dot(b, hash(i + o)), dot(c, hash(i + 1.0)));

  return dot(n, vec3(70.0));
}
float fbm(in vec2 p)
{
  float f = 0.0;
  mat2  m = mat2(1.6, 1.2, -1.2, 1.6);
  f       = 0.5000 * noise(p);
  p       = m * p;
  f += 0.2500 * noise(p);
  p = m * p;
  f += 0.1250 * noise(p);
  p = m * p;
  f += 0.0625 * noise(p);
  p = m * p;
  f = 0.5 + 0.5 * f;
  return f;
}
vec3 bumpMap(vec2 uv)
{
  vec2  s  = 1. / resolution.xy;
  float p  = fbm(uv);
  float h1 = fbm(uv + s * vec2(1., 0));
  float v1 = fbm(uv + s * vec2(0, 1.));

  vec2 xy = (p - vec2(h1, v1)) * normalStrength;
  return vec3(xy + .5, 1.);
}
void main()
{
  vec2 uv           = gl_FragCoord.xy / resolution.xy;
  vec3 normal       = bumpMap(uv * vec2(1.0, 0.3) + distortionMovement * timeScale);
  vec2 displacement = clamp((normal.xy - .5) * distortionStrength, -1., 1.);
  uv += displacement;

  vec2  uvT = (uv * vec2(1.0, 0.5)) + fireMovement * timeScale;
  float n   = pow(fbm(8.0 * uvT), 1.0);

  float gradient   = pow(1.0 - uv.y, 2.0) * 5.;
  float finalNoise = n * gradient;

  vec3 color = finalNoise * vec3(2. * n, 2. * n * n * n, n * n * n * n);
  // gl_FragColor = vec4(color, 1.0);
  gl_FragColor = vec4(vec3(finalNoise), 1.);
}

static int32_t Fire(PixelBuffer p)
{
  int32_t ofs = 0;
  for (int32_t y = 0; y < p.height; y++)

  {
    for (int32_t x = 0; x < p.height; x++)
    {

      float u = (float)(x) / (float)(p.width);
      float v = (float)(y) / (float)(p.width);


      vec3 normal       = bumpMap(uv * vec2(1.0, 0.3) + distortionMovement * timeScale);
      vec2           displacement = clamp((normal.xy - .5) * distortionStrength, -1., 1.);
      float displacementx     = clamp(normalx - 0.5f) * distortionStrength;
      float          displacementx = (normalx - 0.5f) * distortionStrength;
      u += displacementx;
      u += displacementy;

      float uvTx = u + fireMovement * timeScale;
      float uvTy = 0.5f * v + fireMovement * timeScale;
      float n   = powf(fbm(8.0 * uvTx, 8.0 * uvTy), 1.0);

      float gradient   = powf(1.0f - v, 2.0f) * 5.0f;
      float finalNoise = n * gradient;
      uint8_t r = (uint8_t)(2.0f * n);
      uint8_t g = (uint8_t)(2.0f * n * n * n);
      uint8_t b = (uint8_t)(n * n * n * n);
      p.pixels[ofs++] = Color(r, g, b);
    }
    */
int main()
{
  CGWindow            cgwindow = {0};
  RenderSceneCallback renderSceneCallback;
  renderSceneCallback =
      // RandomPoints;
      // GradientX;
      // GradientXY;
      // Circle;
      RotoZoom;
  CreateCGWindow(&cgwindow, 2048, 1024, "ImageProcessing", renderSceneCallback);
  RunCGWindow(&cgwindow);
  DestroyCGWindow(&cgwindow);
  return 0;
}
