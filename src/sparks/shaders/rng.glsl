// float next_random_number(inout uint random_seed) {
//   random_seed ^= (random_seed << 13);
//   random_seed ^= (random_seed >> 17);
//   random_seed ^= (random_seed << 5);
//   return (random_seed & 65535) / 65536.f;
// }

// vec2 next_random_number_square(inout uint random_seed) {
//   float r1 = next_random_number(random_seed);
//   float r2 = next_random_number(random_seed);
//   return vec2(r1, r2);
// }