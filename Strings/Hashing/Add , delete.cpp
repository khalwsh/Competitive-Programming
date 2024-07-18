ll removeAt(ll code, int idx, int val) {
  return (code - (val * fast_power(BASE, idx , mod)) % mod + mod) % mod;
}

ll addAt(ll code, int idx, int val) {
  return (code + (val * fast_power(BASE, idx , mod)) % mod) % mod;
}

ll shiftLeft(ll code) {
  return (code * BASE) % mod;
}

ll shiftRight(ll code) {
  return (code * BASE_INV) % mod;
}