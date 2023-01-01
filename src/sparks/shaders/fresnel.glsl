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




#endif 