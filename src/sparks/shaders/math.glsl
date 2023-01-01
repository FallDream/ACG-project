#ifndef MATH_H_
#define MATH_H_

float safe_sqrt(float x) {
  return sqrt(max(x, 0.f));
}

float safe_rsqrt(float x) {
  if (x < 1e-10) {
    return 0.f;
  } else {
    return sqrt(1.0 / x);
  }
}

float sqr(float x) {
  return x * x;
}

float rcp(float x) {
  if (abs(x) < 1e-10) {
    return 0.f;
  } else {
    return 1.0 / x;
  }
}

float sign_no_zero(float x) {
  if (x < 0.) {
    return -1.f;
  } else {
    return 1.f;
  }
}

// https://graphics.pixar.com/library/OrthonormalB/paper.pdf
void local_coordinate(in vec3 n, out vec3 a, out vec3 b) {
  float sign = sign_no_zero(n.z);
  float n1   = -1.0 / (sign + n.z),
        n2   = n.x * n.y * n1;
  a = vec3(1.f + sign * n.x * n.x * n1, sign * n2, -sign * n.x);
  b = vec3(n2, sign + n.y * n.y * n1, -n.y);
}

void sincos_phi(in vec3 v, out float sin_phi, out float cos_phi) {
  // sin_theta is the projected length on disk
  float sin_theta_2 = v.x * v.x + v.y * v.y;
  if (sin_theta_2 < 1e-9) {
    sin_phi = 1.f;
    cos_phi = 0.f;
  } else {
    float inv_sin_theta = safe_rsqrt(sin_theta_2);
    sin_phi = v.x * inv_sin_theta;
    cos_phi = v.y * inv_sin_theta;
  }
}

#endif