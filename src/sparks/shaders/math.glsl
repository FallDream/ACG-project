float safe_sqrt(float x) {
  return sqrt(max(x, 0.f));
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