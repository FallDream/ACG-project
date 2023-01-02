#ifndef FRESNEL_H_
#define FRESNEL_H_

float fresnel_conductor(float cos_theta_i, vec2 eta_c) {
  float cos_theta_i_2 = cos_theta_i * cos_theta_i;
  float sin_theta_i_2 = 1.f - cos_theta_i_2;
  float sin_theta_i_4 = sin_theta_i_2 * sin_theta_i_2;

  // real and imaginary part
  float eta_r = eta_c.x, eta_i = eta_c.y;

  float temp_1 = eta_r * eta_r - eta_i * eta_i - sin_theta_i_2;
  float a_2_pb_2 = safe_sqrt(temp_1 * temp_1 + 4.f * eta_i * eta_i * eta_r * eta_r);
  float a = safe_sqrt(.5f * (a_2_pb_2 + temp_1));

  float term_1 = a_2_pb_2 + cos_theta_i_2;
  float term_2 = 2.f * cos_theta_i * a;

  float r_s = (term_1 - term_2) / (term_1 + term_2);

  float term_3 = a_2_pb_2 * cos_theta_i_2 + sin_theta_i_4;
  float term_4 = term_2 * sin_theta_i_2;

  float r_p = r_s * (term_3 - term_4) / (term_3 + term_4);

  return 0.5f * (r_s + r_p);
}

float fresnel(in float cos_theta_i, in float eta, out float cos_theta_t, 
              out float eta_it, out float eta_ti) {
  bool outside_mask = cos_theta_i >= 0.f;

  float rcp_eta = rcp(eta);
  if (outside_mask) {
    eta_it = eta;
    eta_ti = rcp_eta;
  } else {
    eta_it = rcp_eta;
    eta_ti = eta;
  }

  /* Using Snell's law, calculate the squared sine of the
      angle between the surface normal and the transmitted ray */
  float cos_theta_t_sqr =
      -(-cos_theta_i * cos_theta_i + 1.f) * eta_ti * eta_ti + 1.f;

  /* Find the absolute cosines of the incident/transmitted rays */
  float cos_theta_i_abs = abs(cos_theta_i);
  float cos_theta_t_abs = safe_sqrt(cos_theta_t_sqr);

  bool index_matched = (eta == 1.f);
  bool special_case  = index_matched || (cos_theta_i_abs == 0.f);

  float r_sc = 1.0f;
  if (index_matched) {
    r_sc = 0.0f;
  }

  /* Amplitudes of reflected waves */
  float a_s = (-eta_it * cos_theta_t_abs + cos_theta_i_abs) /
               (eta_it * cos_theta_t_abs + cos_theta_i_abs);

  float a_p = (-eta_it * cos_theta_i_abs + cos_theta_t_abs) /
              (eta_it * cos_theta_i_abs + cos_theta_t_abs);

  float r = 0.5f * (sqr(a_s) + sqr(a_p));

  if (special_case) {
    r = r_sc;
  }

  /* Adjust the sign of the transmitted direction */
  cos_theta_t = cos_theta_t_abs * sign(-cos_theta_i);

  return r;
}


#endif 